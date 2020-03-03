#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>
#include "webpage.h"

/**
 * Returns an all lower-case version of the input string
 * [COMPLETED]
 *
 * @param[in] src
 *   String to convert
 * @return Lower-case version of src
 */
std::string conv_to_lower(std::string src);

/**
 * Returns an all upper-case version of the input string
 * [COMPLETED]
 *
 * @param[in] src
 *   String to convert
 * @return Upper-case version of src
 */
std::string conv_to_upper(std::string src);

/**
 * Prints results of a WebPageSet
 * [COMPLETED]
 *
 * @param[in] hits
 *   Set of WebPage pointers whose filenames should be displayed
 * @param[inout] ostr
 *   Stream to output results
 */
void display_hits(const WebPageSet& hits, std::ostream& ostr);



#endif
