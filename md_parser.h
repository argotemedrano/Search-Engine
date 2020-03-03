#ifndef MD_PARSER_H
#define MD_PARSER_H

#include <string>
#include <set>

#include "pageparser.h"

class MDParser : public PageParser {
public:
    /**
     * See documentation in PageParser class
     * [TO BE COMPLETED]
     */
    void parse(std::string filename,
               std::set<std::string>& allSearchableTerms,
               std::set<std::string>& allOutgoingLinks);

    /**
     * See documentation in PageParser class
     * [COMPLETED]
     */
    std::string display_text(std::string filename);

private:
    // You may add additional private helpers or data members below

};

#endif
