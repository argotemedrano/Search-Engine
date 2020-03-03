#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <string>
#include <iostream>
#include <vector>
#include <set>

class WebPage;

typedef std::set<WebPage*> WebPageSet;
typedef std::set<std::string> StringSet;

/****** THIS CLASS IS COMPLETED AND NEED NOT BE MODIFIED **********/

class WebPage
{
public:
    /**
     * Default constructor
     */
    WebPage();
    /**
     * Initializing constructor
     */
    WebPage(std::string filename);

    /**
     * Destructor
     */
    ~WebPage();

    /**
     * Sets the filename/URL of this webpage
     */
    void filename(std::string fname);

    /**
     * Returns the filename/URL of this webpage
     */
    std::string filename() const;

    /**
     * Updates the set containing all unique words in the text
     */
    void all_terms(const StringSet& words);

    /**
     * Returns all the unique, tokenized words in this webpage
     */
    StringSet all_terms() const;

    /**
     * Adds a webpage that links to this page
     */
    void add_incoming_link(WebPage* wp);

    /**
     * Returns all webpages that link to this page
     */
    WebPageSet incoming_links() const;

    /**
     * Adds a webpage that this page links to
     */
    void add_outgoing_link(WebPage* wp);

    /**
     * Returns all webpages this page links to
     */
    WebPageSet outgoing_links() const;



private:
    std::vector<std::string> strip(std::string word);
    WebPageSet in_links_;
    WebPageSet out_links_;
    StringSet terms_;
    std::string filename_;

};
#endif
