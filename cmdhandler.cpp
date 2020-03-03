#include "cmdhandler.h"
#include "util.h"

using namespace std;

// COMPLETE
QuitHandler::QuitHandler() { }

QuitHandler::QuitHandler(Handler* next)
    : Handler(next) { }

bool QuitHandler::canHandle(const std::string& cmd) const {
    return cmd == "QUIT";
}

Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    return HANDLER_QUIT;
}

PrintHandler::PrintHandler() { }

PrintHandler::PrintHandler(Handler* next)
    : Handler(next) { }

bool PrintHandler::canHandle(const std::string& cmd) const {
    return cmd == "PRINT";
}

Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

// INCOMING HANDLER
IncomingHandler::IncomingHandler() { }

IncomingHandler::IncomingHandler(Handler* next) : Handler(next) { }

bool IncomingHandler::canHandle(const std::string& cmd) const {
    return cmd == "INCOMING";
}

Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    std::string page_name;
    instr >> page_name;

    // Unable to extract page name: Page does not exist
    if (instr.fail()) {
        return HANDLER_ERROR;
    }

    const WebPage* page = eng->retrieve_page(page_name);

    // Page doesn't exist
    if (page == NULL) {
        return HANDLER_ERROR;
    }

    const WebPageSet& incoming_links_set = page->incoming_links();
    
    // Display Incoming Links
    display_hits(incoming_links_set, ostr);

    return HANDLER_OK;
}

// OUTGOING HANDLER
OutgoingHandler::OutgoingHandler() { }

OutgoingHandler::OutgoingHandler(Handler* next) : Handler(next) { }

bool OutgoingHandler::canHandle(const std::string& cmd) const {
    return cmd == "OUTGOING";
}

Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    std::string page_name;
    instr >> page_name;

    // Unable to extract page name: Page does not exist
    if (instr.fail()) {
        return HANDLER_ERROR;
    }

    const WebPage* page = eng->retrieve_page(page_name);

    // Page doesn't exist
    if (page == NULL) {
        return HANDLER_ERROR;
    }

    const WebPageSet& outgoing_links_set = page->outgoing_links();

    // Display outgoing links
    display_hits(outgoing_links_set, ostr);
    
    return HANDLER_OK;
}

// AND HANDLER
AndHandler::AndHandler() { }

AndHandler::AndHandler(Handler* next) : Handler(next) { }

bool AndHandler::canHandle(const std::string& cmd) const {
    return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    std::vector<std::string> terms = std::vector<std::string>();

    // Get all terms
    std::string new_term = std::string();
    while (instr >> new_term) {
        terms.emplace_back(conv_to_lower(new_term));
    }

    // Get results
    AndCombiner* and_combiner = new AndCombiner;
    WebPageSet results = eng->search(terms, and_combiner);
    delete and_combiner;

    // Display number of results and results
    display_hits(results, ostr);

    return HANDLER_OK;
}

// OR HANDLER
OrHandler::OrHandler() { }

OrHandler::OrHandler(Handler* next) : Handler(next) { }

bool OrHandler::canHandle(const std::string& cmd) const {
    return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    std::vector<std::string> terms = std::vector<std::string>();

    // Get all terms
    std::string new_term = std::string();
    while (instr >> new_term) {
        terms.emplace_back(conv_to_lower(new_term));
    }

    // Get results
    OrCombiner* or_combiner = new OrCombiner();
    WebPageSet results = eng->search(terms, or_combiner);
    delete or_combiner;

    // Display number of results and results
    display_hits(results, ostr);

    return HANDLER_OK;
}

// DIFF HANDLER
DiffHandler::DiffHandler() { }

DiffHandler::DiffHandler(Handler* next) : Handler(next) { }

bool DiffHandler::canHandle(const std::string& cmd) const {
    return cmd == "DIFF";
}

Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr) {
    std::vector<std::string> terms = std::vector<std::string>();

    // Get all terms
    std::string new_term = std::string();
    while (instr >> new_term) {
        terms.emplace_back(conv_to_lower(new_term));
    }

    // Get results
    DiffCombiner* diff = new DiffCombiner();
    WebPageSet results = eng->search(terms, diff);
    delete diff;

    // Display number of results and results
    display_hits(results, ostr);
    return HANDLER_OK;  
}