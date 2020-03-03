#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "searchui.h"
#include "util.h"

using namespace std;

SearchUI::SearchUI(SearchEng* eng)
{
    this->eng_ = eng;
    this->handlers_ = NULL;
}

/**
 * Destructor
 */
SearchUI::~SearchUI() {
    delete handlers_;
}

/**
 *  Add a command handler
 *
 *  @param[in] handler
 *     Pointer to the handler for a particular command.
 */
void SearchUI::add_handler(Handler* handler)
{
    handler->set_next(handlers_);
    handlers_ = handler;
}


bool SearchUI::run(std::istream& istr, std::ostream& ostr)
{
    ostr << "=====================================" << endl;
    ostr << "Menu: " << endl;
    ostr << "  AND term term ...                  " << endl;
    ostr << "  OR term term ...                   " << endl;
    ostr << "  DIFF term not-present-term not-present-term ... " << endl;
    ostr << "  PRINT page                         " << endl;
    ostr << "  INCOMING page                      " << endl;
    ostr << "  OUTGOING page                      " << endl;
    ostr << "  QUIT                               " << endl;
    ostr << "=====================================" << endl;

    Handler::HANDLER_STATUS_T status = Handler::HANDLER_OK;
    while (status != Handler::HANDLER_QUIT && status != Handler::HANDLER_KILL)
    {
        ostr << "\n$: ";
        string line;
        if(getline(istr, line))
        {
            ostr << endl;
            stringstream ss(line);
            string cmd;
            if ((ss >> cmd)) {
                // convert to upper case
                cmd = conv_to_upper(cmd);
                // Invoke the chain of responsibility
                status = handlers_->handle(eng_, cmd, ss, ostr);
                if (status == Handler::HANDLER_ERROR)
                {
                    ostr << "Error" << endl;
                }
            }
        }
        else {
            status = Handler::HANDLER_KILL;
        }
    }
    return status != Handler::HANDLER_QUIT;
}
