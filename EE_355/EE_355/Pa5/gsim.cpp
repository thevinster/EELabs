#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "vlg_parser.h"
#ifdef AUTOPARSE
#include "vlg_parser_auto.h"
#else
#include "vlg_parser_man.h"
#endif

#include "design.h"
#include "gates.h"
#include "net.h"
#include "LogicSim.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*if(argc < 3){
      cerr << "Usage ./gsim infile.v outfile.v" << endl;
      return 1;
    }*/
#ifdef AUTOPARSE
    VlgParser *parser = new VlgParserAuto();
#else
    VlgParser *parser = new VlgParserMan();
#endif
    //Design *d = parser->parse(argv[1]);
	Design* d = parser->parse("C:\\Users\\Vincent\\Documents\\GitHub\\EELabs\\EE_355\\x64\\Debug\\adder4.v");
	vector<string> pis = d->getPI();
	LogicSim lSim(pis, d);
	lSim.parse("C:\\Users\\Vincent\\Documents\\GitHub\\EELabs\\EE_355\\x64\\Debug\\adder4.sim",
		"C:\\Users\\Vincent\\Documents\\GitHub\\EELabs\\EE_355\\x64\\Debug\\adder4.out");
    // Add more of your code here to simply dump the design back
    // out to a file named output.v
	/*ofstream out("C:\\Users\\Vincent\\Documents\\GitHub\\EELabs\\EE_355\\x64\\Debug\\output.v");
	if (out.fail()) {
		cerr << "Failed to open the file" << endl;
		return 1;
	}
	d->dump(out);
	out.close();*/
	getchar();
    delete parser;
	delete d;
    return 0;
}

