#include <iostream>
#include "handler.h"
using namespace std;

Handler::Handler() :
    next_(NULL)
{
}
Handler::Handler(Handler* next) :
    next_(next)
{
}

Handler::~Handler()
{
    if(next_) {
        delete next_;
    }
}

void Handler::set_next(Handler* next)
{
    next_ = next;
}

Handler::HANDLER_STATUS_T Handler::handle(SearchEng* eng, const std::string& cmd, std::istream& instr, std::ostream& ostr)
{
    // check if this handler can process this command
    if(canHandle(cmd)) {
        return process(eng, instr, ostr);
    }
    // otherwise delegate to the next handler or return
    else if(next_ != NULL) {
        return next_->handle(eng, cmd, instr, ostr);
    }
    // This was the last handler, so no one was able to process this command
    else {
        cout << "Unrecognized command" << endl;
        return HANDLER_ERROR; // Error
    }
}

