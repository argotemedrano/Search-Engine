#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "searchui.h"
#include "md_parser.h"
#include "txt_parser.h"
#include "cmdhandler.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Must provide an index file" << endl;
        return 1;
    }

    SearchEng seng(new TXTParser);
    seng.register_parser("md", new MDParser);
    seng.register_parser("txt", new TXTParser);

    SearchUI ui(&seng);

    // Available Commands
    ui.add_handler(new QuitHandler());
    ui.add_handler(new PrintHandler());
    ui.add_handler(new AndHandler());
    ui.add_handler(new OrHandler());
    ui.add_handler(new DiffHandler());
    ui.add_handler(new IncomingHandler());
    ui.add_handler(new OutgoingHandler());

    // ------------------------------------------------------------------------

    try {
        seng.read_pages_from_index(argv[1]);
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
        return 1;
    }

    bool result;
    if (argc == 2)
    {
        result = ui.run(cin, cout);

    }
    else if (argc == 3) {
        ifstream in_file(argv[2]);
        result = ui.run(in_file, cout);
    }
    else  {
        ifstream in_file(argv[2]);
        ofstream out_file(argv[3]);
        result = ui.run(in_file, out_file);
    }
    return result;
}
