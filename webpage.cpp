#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "webpage.h"
#include "util.h"

using namespace std;

WebPage::WebPage() : filename_("uninit")
{

}

WebPage::WebPage(std::string filename) : filename_(filename)
{

}

WebPage::~WebPage()
{

}


std::string WebPage::filename() const
{
    return filename_;
}

void WebPage::filename(std::string fname)
{
    filename_ = fname;
}

void WebPage::all_terms(const StringSet& terms)
{
    terms_ = terms;
}

StringSet WebPage::all_terms() const
{
#ifdef DEBUG
    for(set<string>::iterator wit = terms_.begin(); wit != terms_.end(); ++wit) {
        cout << "all_words contains: " << *wit << endl;
    }
#endif
    return terms_;
}

void WebPage::add_incoming_link(WebPage* wp)
{
    this->in_links_.insert(wp);
}

WebPageSet WebPage::incoming_links() const
{
    return in_links_;
}
void WebPage::add_outgoing_link(WebPage* wp)
{
    out_links_.insert(wp);
}
WebPageSet WebPage::outgoing_links() const
{
    return out_links_;
}


