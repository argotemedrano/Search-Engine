#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

// EXTRA
#include <utility>

using namespace std;

std::string extract_extension(const std::string& filename);


SearchEng::SearchEng(PageParser* noExtensionParser) {
    if (NULL == noExtensionParser)
    {
        throw std::invalid_argument("default parser cannot be NULL");
    }
    this->noExtensionParser_ = noExtensionParser;

    // Add additional code if necessary

    // Empty extension parsers
    this->extensionParsers_ = std::map<std::string, PageParser*>();

    // Empty search terms
    this->search_terms_ = std::map<std::string, WebPageSet>();

    // Empty Webpages map
    this->webPages_ = std::map<std::string, WebPage*>();

    // Empty Webpage Parse Tracker
    this->page_parsed_ = std::map<std::string, bool>();

}

SearchEng::~SearchEng() {
    // Delete extensionParsers (if dynamically allocated)
    delete noExtensionParser_;

    // Deallocate extension parsers
    std::map<std::string, PageParser*>::iterator extPar_itr = extensionParsers_.begin();
    for (; extPar_itr != extensionParsers_.end(); ++extPar_itr) {
        delete extPar_itr->second;
    }

    // Deallocate webpages
    std::map<std::string, WebPage*>::iterator web_pages_itr = webPages_.begin();
    for (; web_pages_itr != webPages_.end(); ++web_pages_itr) {
        delete web_pages_itr->second;
    }
}

void SearchEng::read_pages_from_index(const std::string& index_file) {
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

std::string extract_extension(const std::string& filename) {
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}

// Registering Parser
void SearchEng::register_parser(const std::string& extension, PageParser* parser) {
    // Make sure parser with corresponding extension isn't already owned
    std::map<std::string, PageParser*>::iterator parser_itr = extensionParsers_.find(extension);
    
    // Add if not owned already
    if (parser_itr == extensionParsers_.end()) {
        extensionParsers_.insert(std::pair<std::string, PageParser*>(extension, parser));
    } 
    // No need to add parser, deallocate memory
    else {
        delete parser;
    }
}

void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const {
    std::map<std::string, WebPage*>::const_iterator page_itr = webPages_.find(page_name);
    std::string display_contents = std::string();

    // Exists
    // Q: Guaranteed to be parsed?
    if (page_itr != webPages_.end()) {
        // Parse based on extension
        std::string file_extension = extract_extension(page_name);
        
        // No extension: default no extension parser
        if (file_extension.size() == 0) {
            display_contents = noExtensionParser_->display_text(page_name);
        }
        // Parse based on extension
        else {
            // Find extension
            std::map<std::string, PageParser*>::const_iterator parser_itr = extensionParsers_.find(file_extension);

            // Parser for extension doesn't exist: Throw exception
            if (parser_itr == extensionParsers_.end()) {
                throw std::logic_error("No parser registered with extension type.");
            }
            // Extension exists
            else {
                display_contents = parser_itr->second->display_text(page_name);
            }
        }
    }
    // Page DOES NOT exist
    else {
        throw std::invalid_argument("Page doesn't exist");
    }

    // Output contents
    ostr << display_contents;
}


WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const {
    // No terms: return empty set
    if (terms.size() == 0) {
        return WebPageSet();
    }
    // Only one terms: return one set containing that word
    else if (terms.size() == 1) {
        std::map<std::string, WebPageSet>::const_iterator find_itr = search_terms_.find(terms[0]);
        if (find_itr != search_terms_.end()) {
            return find_itr->second;
        }
        else {
            return WebPageSet();
        }
    }

    WebPageSet combined = WebPageSet();
    WebPageSet setB = WebPageSet();

    // Is it gauranteed that THIS IS FOUND?? WHAT HAPPENS IF IT ISN'T? WHAT EXPECTED BEHAVIOR? UNEXPECTED BEHAVIOR?
    std::map<std::string, WebPageSet>::const_iterator term_itr = search_terms_.find(terms[0]);
    if (term_itr != search_terms_.end()) {
        combined = term_itr->second;
    }

    for (unsigned int i = 1; i < terms.size(); ++i) {
        // Find for second term
        term_itr = search_terms_.find(terms[i]);

        // Keyword found: Extract set of web pages
        if (term_itr != search_terms_.end()) {
            setB = term_itr->second;
        } 
        // Keyword NOT found: Empty set
        else {
            setB = WebPageSet();
        }

        // Combine
        combined = combiner->combine(combined, setB);
    }

    return combined;
}

// Reads a page
void SearchEng::read_page(const std::string& filename) {
    std::map<std::string, bool>::iterator pages_itr = page_parsed_.find(filename);

    // Make sure file has not been parsed before
    if (pages_itr == page_parsed_.end() || !pages_itr->second) {
        WebPage* newPage = nullptr;

        // Find WebPage object
        std::map<std::string, WebPage*>::iterator web_page_itr = webPages_.find(filename);

        // Allocate new web page if it has not been allocated before
        if (web_page_itr == webPages_.end()) {
            newPage = new WebPage(filename);

            // Add web page to map
            webPages_.insert(std::pair<std::string, WebPage*>(filename, newPage));
        }
        // Web page has already been allocated
        else {
            newPage = web_page_itr->second;
        }

        // Insert to parser tracker if not inserted before
        if (pages_itr == page_parsed_.end()) {
            page_parsed_.insert(std::pair<std::string, bool>(filename, false));
        }

        // Parse based on extension
        std::string file_extension = extract_extension(filename);
        std::set<std::string> searchableTerms = std::set<std::string>();
        std::set<std::string> outgoingLinks = std::set<std::string>();

        // No extension
        if (file_extension.size() == 0) {
            try {
                noExtensionParser_->parse(filename, searchableTerms, outgoingLinks);
            } catch (std::exception& e) { }
        }
        // Parse with particular file extension
        else {
             std::map<std::string, PageParser*>::iterator parser_itr = extensionParsers_.find(file_extension);

            // Parser doesn't exist: Throw exception?
            if (parser_itr == extensionParsers_.end()) {
                throw std::logic_error("No parser for file with specified extension");
            }
            else {
                try {
                    parser_itr->second->parse(filename, searchableTerms, outgoingLinks);
                } catch (std::exception& e) { }
            }
        }

        // Add searchable terms
        newPage->all_terms(searchableTerms);

        // Add outgoing and incoming links
        std::set<std::string>::iterator outgoingLink_itr = outgoingLinks.begin();
        for (; outgoingLink_itr != outgoingLinks.end(); ++outgoingLink_itr) {
            std::map<std::string, WebPage*>::iterator find_page = webPages_.find(*outgoingLink_itr);

            // Add Outgoing Link to current WebPage being parsed
            // Add current WebPage as incoming link for all outgoing web pages
            if (find_page == webPages_.end()) {
                WebPage* page = new WebPage(*outgoingLink_itr);

                // Add to webpages
                webPages_.insert(std::pair<std::string, WebPage*>(*outgoingLink_itr, page));

                // Add to parser tracker
                page_parsed_.insert(std::pair<std::string, bool>(*outgoingLink_itr, false));

                // Add new page to outgoing link
                newPage->add_outgoing_link(page);

                // Add incoming link to this outgoinglink page
                page->add_incoming_link(newPage);
            }
            else {
                find_page->second->add_incoming_link(newPage);
                newPage->add_outgoing_link(find_page->second);
            }
            
        }       

        // Change parser tracker to true
        pages_itr = page_parsed_.find(filename);

        // Make sure it is found (for safety)
        pages_itr->second = true;

        /* DONE PARSING */

        /* ADD TO SEARCH TERMS MAP */
        // Add all searchable terms set
        std::set<std::string>::iterator parsed_terms_itr = searchableTerms.begin();
        std::map<std::string, WebPageSet>::iterator search_terms_itr;

        for (; parsed_terms_itr != searchableTerms.end(); ++parsed_terms_itr) {
            search_terms_itr = search_terms_.find(*parsed_terms_itr);

            if (search_terms_itr == search_terms_.end()) {
                WebPageSet newSet = WebPageSet();
                newSet.insert(newPage);
                search_terms_.insert(std::pair<std::string, WebPageSet>(*parsed_terms_itr, newSet));
            }
            else {
                (search_terms_itr->second).insert(newPage); // Is a reference returned when doing insert?
            }
        }
    }
}

WebPage* SearchEng::retrieve_page(const std::string& page_name) const {
    std::map<std::string, WebPage*>::const_iterator find_page_itr = webPages_.find(page_name);
   
   // Page Exists
    if (find_page_itr != webPages_.end()) {
        return find_page_itr->second;
    }
    else { // Page does not exist
        return NULL;
    }
} 
