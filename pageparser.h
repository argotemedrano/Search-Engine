#ifndef ELEM_PARSER_H
#define ELEM_PARSER_H

#include <string>
#include "webpage.h"

/**
 * Base class for parsers (for some specific
 *  format such as MD or HTML)
 */

class PageParser {
public:
    virtual ~PageParser() { }

    /**
     * Parses a file and returns all unique words according
     *  to some parser rules and all outgoing page links based
     *  on the format the parser is designed to implement
     *
     * @param[in] filename
     *   The file to be parsed
     * @param[out] allSearchableTerms
     *   Set to be filled with all searchable terms
     * @param[out] allOutGoingLinks
     *   Set to be filled with all outgoing links/page names
     *
     * @throws std::invalid_argument if the filename doesn't exist
     */
    virtual void parse(std::string filename,
                       std::set<std::string>& allSearchableTerms,
                       std::set<std::string>& allOutgoingLinks) = 0;

    /**
     * Parses a file and returns a string containing a display version
     *  of the file contents (keeping appropriate anchor text but
     *  with links removed)
     *
     * @param[in] filename
     *   The file to be displayed
     * @returns the string representing the display version of the page
     *
     * @throws std::invalid_argument if the filename doesn't exist
     */
    virtual std::string display_text(std::string filename) = 0;
};

#endif
