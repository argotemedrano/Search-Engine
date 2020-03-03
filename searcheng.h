#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "pageparser.h"

class WebPageSetCombiner
{
public:
    /**
     * Destructor
     */
    virtual ~WebPageSetCombiner() {}

    /**
     * Combines two sets of webpages into a resulting set based on some strategy
     *
     * @param[in] setA
     *   first set of webpages
     * @param[in] setB
     *   second set of webpages
     * @return set of webpages that results from the combination strategy
     */
    virtual
    WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB) = 0;
};

/*** Define Derived WebPageSetCombiners (for AND, OR, DIFF) classes below ***/
class AndCombiner : public WebPageSetCombiner {
public:
    virtual WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};

class OrCombiner : public WebPageSetCombiner {
public:
    virtual WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};

class DiffCombiner : public WebPageSetCombiner {
public:
    virtual WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);
};

/**
 * Provides parsing and indexing of search terms as well as search operations.
 * Provides webpage display and retrieval.
 */
class SearchEng {
public:
    /**
    * Default constructor
    *
    * @param[in] parser
    *  A parser for files that have no extension.
    *  SearchEng will now be responsible for this parser and its deallocation.
    *
    */
    SearchEng(PageParser* noExtensionParser);

    /**
     * Destructor
     * [COMPLETED]
     */
    ~SearchEng();

    /**
     * Register a parser for a particular file extension
     * [COMPLETED]
     *
     * @param[in] extension
     *   File type/extension that should use this parser
     * @param[in] parser
     *   Pointer to the parser
      *  SearchEng will now be responsible for this parser and its deallocation.
     */
    void register_parser(const std::string& extension, PageParser* parser);

    /**
     * Reads and parses files specified in the given index file
     * [COMPLETED]
     *
     * @param[in] index_file
     *   Name of the index file containing the list of files to read/parse
     *
     * @throw std::logic_error
     *   If the file has an extension but no parser is registered for
     *   that extension
     */

    void read_pages_from_index(const std::string& index_file);

    /**
     * Retrieves the WebPage object for a given page/file
     * [COMPELTED]
     *
     * @param[in] page_name
     *   Name of page/file to retrieve
     *
     * @return Pointer to the corresponding WebPage object.  Should not be used
     *   to alter or deallocate the object.
     *   Return NULL if page_name does not exist.
     */
    WebPage* retrieve_page(const std::string& page_name) const;

    /**
     * Displays the contents of the page/file
     * [COMPLETED]
     *
     * @param[inout] ostr
     *   Output stream to display the contnents
     * @param[in] page_name
     *   Name of page/file to display
     *
     * @throw std::invalid_argument if the page_name does not exist
     * @throw std::logic_error
     *   If the file has an extension but no parser is registered for
     *   that extension
     */
    void display_page(std::ostream& ostr, const std::string& page_name) const;

    /**
     * Uses the given search terms and combiner to find the set of webpages
     *  that match the query
     * [COMPLETED]
     *
     * @param[in] terms
     *   words/terms to search for
     * @param[in] combiner
     *   Combiner object that implements the strategy for combining the
     *   pages that contain each term (i.e. AND, OR, DIFF, etc.)
     *
     * @return Set of webpages matching the query
     */
    WebPageSet search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const;

private:
    // Helper function to read/parse a single page
    void read_page(const std::string& filename);

    // Parsers
    PageParser* noExtensionParser_;
    std::map<std::string, PageParser*> extensionParsers_;

    // Search items linking web pages
    // Function: Associates a search term with web pages
    // Usage: To answer queries
    // key[std::string]: search term
    // value[WebPage*]: WebPages that contain that term
    std::map<std::string, WebPageSet> search_terms_;
    
    // Webpages
    // Contains all webpages
    // key[std::string]: file name
    // value[WebPage*]: WebPage object corresponding to that file
    std::map<std::string, WebPage*> webPages_;
    // Shows if a webpage has been parsed
    // Usage: When parsing
    // key[std::string]: filename
    // value[bool]: If Webpage object created, parsed status
    std::map<std::string, bool> page_parsed_;

};

#endif
