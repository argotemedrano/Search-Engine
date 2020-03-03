#ifndef HANDLER_H
#define HANDLER_H
#include <string>
#include <istream>
#include "searcheng.h"

/**
 * Implements a chain-of-responsibility design pattern which
 * essentially is a linked list of polymorphic objects each
 * handling a different command.
 */
class Handler
{
public:
    /**
     * Return status options from handle() and process()
     * 	 HANDLER_OK    = successful and processing should continue
     *   HANDLER_QUIT  = successful and processing should stop / program should quit
     *   HANDLER_ERROR = an error occurred but processing can continue
     *   HANDLER_KILL  = an error occurred and the program should halt immediately
     */
    enum HANDLER_STATUS_T {HANDLER_OK = 0, HANDLER_QUIT, HANDLER_ERROR, HANDLER_KILL};

    /**
     *  Default constructor
     */
    Handler();

    /**
     * Initializing constructor
     * @param [in] next
     *    Pointer to next constructor
     */
    Handler(Handler* next);

    /**
     * Destructor
     */
    virtual ~Handler();

    /**
     * Handle a command (processing any options in the input stream)
     *
     * @param [in] eng
     *   Pointer to the search engine
     * @param [in] cmd
     *   Command name attempting to be handled
     * @param [inout] instr
     *   Input stream to read additional command arguments, if needed
     * @param [inout] ostr
     *   Output stream to output results of the command, if needed
     * @return
    *   Appropriate HANLDER_STATUS_T value
     */
    HANDLER_STATUS_T handle(SearchEng* eng, const std::string& cmd, std::istream& instr, std::ostream& ostr);

    /**
     * Sets the next handler field
     *
     * @param[in] next
     */
    void set_next(Handler* next);

protected:

    /**
     * Determines if this handler can handle the command given by cmd
     *
     * @param[in] cmd
     *   Command name attempting to be handled
     * @return
     *   true, if this Handler can process cmd
     *   false, otherwise
     */

    virtual bool canHandle(const std::string& cmd) const = 0;

    /**
     * Processes the command
     *
     * @param [in] eng
     *   Pointer to the search engine object
     * @param [inout] instr
     *   Input stream to read additional command arguments, if needed
     * @param [inout] ostr
     *   Output stream to output results of the command, if needed
     */
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr)  = 0;

private:
    Handler* next_;
};

#endif
