
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//#include "../src/dataCollector.baxter/KPriceDepthOrderBook.h"
//#include "../src/dataCollector.baxter/KOrderBook.h"
#include "KPriceDepthOrderBook.h"
#include "KOrderBook.h"


#include "quickfix/Values.h"
#include "quickfix/FieldConvertors.h"
#include "quickfix/FieldMap.h"
#include "quickfix/Parser.h"
#include "quickfix/Message.h"

#include <boost/tokenizer.hpp>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char* argv[])
{
/*
	PriceDepthOrderBook testbook("FOO", 3);
	std::cerr << "operator<<(REFERENCE)" << std::endl;
	std::cout << testbook;
	
	en testobj(99, "123");
	std::cerr << "operator<<(REFERENCE)" << std::endl;
	std::cout << testobj;


	return 0;
*/
	std::ifstream in;
	if (argc < 2) {
		std::cerr << "argv[0] [inputfile]" << std::endl;
	
	}
	if (argv[1]) {
		std::cerr << "Reading from: " << argv[1] << std::endl;
	}

	if (argc > 1) {
		std::string f(argv[1]);
		in.open(f.c_str());
		if (!in.is_open()) return 1;
	}
	typedef boost::tokenizer< boost::escaped_list_separator<char> > Tokenizer;
	std::vector<std::string> vec;
	std::string line;
	std::string strMsg;
	std::string k;

	std::vector<std::string>::iterator it ;

    FIX::Parser parser;
	while(getline(in, line)) {
        parser.addToStream(line);
        if (parser.readFixMessage(strMsg))
            std::cout << "readFixMessage returned TRUE" << std::endl;
        else 
            std::cout << "readFixMessage returned FALSE" << std::endl;
        FIX::Message m(strMsg);
        if (m.isEmpty()) { 
            std::cout << "message is empty!" << std::endl;
        }
        std::string s;
        m.toString(s);
        std::cout << s << std::endl;
        if (m.getHeader().isSetField(FIX::FIELD::MsgType)) {
            FIX::MsgType msgType;
            m.getHeader().getField(msgType);
            std::cout << "msgType: " << msgType  << std::endl;
        }

        for (FIX::Message::iterator it = m.begin(); it != m.end(); it++) {
            std::cout <<  it->first << ":" << it->second.getString() << std::endl;
        }
            
        boost::escaped_list_separator<char> sep('\\', ';', '\"');
        Tokenizer tok(line, sep);
//`		Tokenizer tok(line);
		vec.assign(tok.begin(), tok.end());

		std::cerr << "Processing raw line(" << line << ")" << std::endl;

		const char* action = vec[1].c_str();
		const char* type = vec[2].c_str();
		const char* price = vec[4].c_str();
		const char* size = vec[5].c_str();	
		std::getline(std::cin, k);
		if (k == "q") {
			exit(0);
		}
		if (k.empty()) {
			continue;
		}

	}
}
