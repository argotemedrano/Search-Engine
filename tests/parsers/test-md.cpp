#include <iostream>
#include <fstream>
#include <set>
#include <exception>
#include "../../md_parser.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        throw std::invalid_argument("Not enough command line arguments");
    }
    MDParser md_parser;

    const char* LINKOUT_PATH = argv[3];
    const char* TERMSOUT_PATH = argv[2];
    const std::string INPUT = argv[1];

    std::ofstream link_out(LINKOUT_PATH);
    std::ofstream term_out(TERMSOUT_PATH);

    std::set<std::string> links = std::set<std::string>();
    std::set<std::string> terms = std::set<std::string>();

    md_parser.parse(INPUT, terms, links);

    // Output terms
    std::set<std::string>::iterator term_itr = terms.begin();
    for (; term_itr != terms.end(); ++term_itr) {
        term_out << *term_itr << std::endl;
    }

    // Output links
    std::set<std::string>::iterator links_itr = links.begin();
    for (; links_itr != links.end(); ++links_itr) {
        link_out << *links_itr << std::endl;
    }


    return 0;
}