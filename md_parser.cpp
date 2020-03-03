#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;


void MDParser::parse(std::string filename, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if(!wfile) {
        throw invalid_argument("Bad webpage filename in MDParser::parse()");
    }

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    // Initialize the current term and link as empty strings.
    string term = "";
    string link = "";

    // Get the first character from the file.
    char c = wfile.get();

    // Continue reading from the file until input fails.
    while(!wfile.fail())
    {
        // Logic for parsing a normal term.
        if(state == NORMALTEXT)
        {
            // NOT ALPHANUMERIC:
            // Add term to results, clear term to "" 
            // Change state if necessary
            if (!isalnum(c)) {
                // There is some term to add
                if (0 != term.size()) {
                    term = conv_to_lower(term);
                    allSearchableTerms.insert(term);
                    term = "";
                }

                // Change state: LINKTEXT
                if (c == '[') {
                    state = LINKTEXT;
                }
            }
            // ALPHANUMERIC: Append c to term
            else {
                term += c;
            }
        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            // NOT ALPHANUMERIC:
            // Add term to results, clear term to ""
            // Change state if necessary
            if (!isalnum(c)) {
                // There is some term to add
                if (0 != term.size()) {
                    term = conv_to_lower(term);
                    allSearchableTerms.insert(term);
                    term = "";
                }

                // Change state: ISLINK
                if (c == ']') {
                    state = ISLINK;
                }
            } 
            // ALPHANUMERIC: Append c to term
            else {
                term += c;
            }
        }
        else if(state == ISLINK)
        {
            /*// Change state: LINKURL or NORMALTEXT
            if (c == '(') {
                link = "";
                state = LINKURL;
            } else {
                state = NORMALTEXT;
                if (isalnum(c)) {
                    term += c;
                } else {
                    link = "";
                }
            } */

            // NOT ALPHANUMERIC: Clear link
            if (!isalnum(c)) {
                // Clear link
                link = "";

                // Change state: LINKURL
                if (c == '(') {
                    state = LINKURL;
                }
                // Change state: NORMALTEXT
                else {
                    state = NORMALTEXT;
                }
            }
            // ALPHANUMERIC: Append c to term
            // Change state: NORMALTEXT
            else {
                // Append c to term
                term += c;
                state = NORMALTEXT;
            }
        }
        // Else we are in the LINKURL state.
        else
        {
            // Append c to link
            if (c != ')') {
                link += c;
            }
            // Add link to results
            else {
                // There is a link to add
                if (0 != link.size()) {
                    allOutgoingLinks.insert(link);
                    link = "";
                }

                // Change state
                state = NORMALTEXT;
            }
        }
        // Attempt to get another character from the file.
        c = wfile.get();
    }
    // ADD ANY REMAINING CODE HERE




    // Close the file.
    wfile.close();
}

std::string MDParser::display_text(std::string filename)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if (!wfile) {
        throw std::invalid_argument("Bad webpage filename in TXTParser::parse()");
    }
    std::string retval;

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    char c = wfile.get();

    // Continue reading from the file until input fails.
    while (!wfile.fail()) {
        // Logic for parsing a normal term.
        if (state == NORMALTEXT)
        {
            // The moment we hit a bracket, we input our current working term
            // into the allSearchableTerms set, reset the current term, and move into
            // parsing a link.
            if (c == '[')
            {
                state = LINKTEXT;
            }
            retval += c;
        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            // When we hit the closing bracket, then we must be finished getting the link.
            if (c == ']')
            {
                state = ISLINK;
            }
            retval += c;
        }
        else if (state == ISLINK) {
            if (c == '(') {
                state = LINKURL;
            }
            else
            {
                state = NORMALTEXT;
                retval += c;
            }
        }
        // Else we are in the LINKURL state.
        else
        {
            // When we hit a closing parenthese then we are done, and the link can be inserted.
            if (c == ')')
            {
                state = NORMALTEXT;
            }
        }
        c = wfile.get();
    }
    return retval;
}


