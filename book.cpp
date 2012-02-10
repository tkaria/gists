
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
		std::cerr << "input file supplied" << std::endl;
	}

	std::string symbol("EUR/USD");
	capitalk::PriceDepthOrderBook b(symbol, 10);
	if (argc > 1) {
		std::string f(argv[1]);
		in.open(f.c_str());
		if (!in.is_open()) return 1;
	}
	typedef boost::tokenizer< boost::escaped_list_separator<char> > Tokenizer;
	std::vector<std::string> vec;
	std::string line;
	std::string k;

	std::vector<std::string>::iterator it ;

	capitalk::PriceDepthOrderBook*  pBook = &b;
	std::string logFileName("OUT.txt");
	std::ostream* pLog = new std::ofstream(logFileName, std::ios::out | std::ios::app);
	std::map<std::string, std::ostream*>  bookToLog;
	bookToLog[symbol] = pLog;
	//std::ostream* pLog = new std::ostream(&logFile);
		
	pLog = NULL;
	while(getline(in, line)) {
		Tokenizer tok(line);
		vec.assign(tok.begin(), tok.end());

		std::cerr << "Processing raw line(" << line << ")" << std::endl;

		const char* action = vec[1].c_str();
		const char* type = vec[2].c_str();
		const char* price = vec[4].c_str();
		const char* size = vec[5].c_str();	
/*
		std::cerr << "TIME: " << vec[0] << "\n"; 
		std::cerr << "ACTION: "  << action << "\n";
		std::cerr << "TYPE: " << type << "\n";
		std::cerr << "ID: " << vec[3] << "\n";
		std::cerr << "PRICE: "  << price << "\n";
		std::cerr << "SIZE: " << std::fixed << size << "\n";
*/
		std::cerr << "ENTRY ID: " << vec[3] << "\n";
		FIX::UtcTimeStamp ts = FIX::UtcTimeStamp(FIX::UtcTimeStampConvertor::convert(vec[0]));
		FIX::MDUpdateAction ua = FIX::MDUpdateAction(action[0]);	
		FIX::MDEntryType ty = FIX::MDEntryType(type[0]); 
		FIX::MDEntryID id =  FIX::MDEntryID(vec[3]);
		FIX::MDEntryPx px =	FIX::MDEntryPx(atof(price));
		FIX::MDEntrySize sz = FIX::MDEntrySize(atof(size));
			
		capitalk::PriceDepthOrderBookEntry obe = capitalk::PriceDepthOrderBookEntry(ts, ua, ty, id, px, sz);
		//std::cerr << obe << std::endl;
		b.enter(obe);
		//b.enter(PriceDepthOrderBookEntry(ts, ua, ty, id, px, sz));
		try {
			//pLog = bookToLog[symbol];
			//(*pLog) << (*pBook);
			//std::cerr << "operator<<(POINTER)" << std::endl;
			//std::cout << pBook;
			//pBook->print(*pLog);
		}
		catch (FIX::IncorrectDataFormat& idf) {
			std::cerr << idf.field << std::endl;	
		}
		
		std::getline(std::cin, k);
		if (k == "q") {
			exit(0);
		}
		if (k.empty()) {
			continue;
		}
		//for (it = vec.begin(); it != vec.end(); it++) {
			//std::cout << *it << std::endl;
			
		//}	
		// parsed data is now in vec
		//if (vec.size() < 
		//	

	}
/*
	b.enter(capitalk::PriceDepthOrderBookEntry(FIX::UtcTimeStamp(2011),
												FIX::MDUpdateAction('0'), 
												FIX::MDEntryType('1'), 
												FIX::MDEntryID("newoffer"), 
												FIX::MDEntryPx(1.30),
												FIX::MDEntrySize(300)));
	
	b.enter(capitalk::PriceDepthOrderBookEntry(FIX::UtcTimeStamp(2011),
												FIX::MDUpdateAction('0'), 
												FIX::MDEntryType('0'), 
												FIX::MDEntryID("newbid"), 
												FIX::MDEntryPx(1.29),
												FIX::MDEntrySize(2292)));

	b.enter(capitalk::PriceDepthOrderBookEntry(FIX::UtcTimeStamp(2011),
												FIX::MDUpdateAction('1'), 
												FIX::MDEntryType('1'), 
												FIX::MDEntryID("modifyoffer"), 
												FIX::MDEntryPx(1.31),
												FIX::MDEntrySize(333)));
	
	b.enter(capitalk::PriceDepthOrderBookEntry(FIX::UtcTimeStamp(2011),
												FIX::MDUpdateAction('1'), 
												FIX::MDEntryType('0'), 
												FIX::MDEntryID("modifybid"), 
												FIX::MDEntryPx(1.2995),
												FIX::MDEntrySize(232323)));

	b.enter(capitalk::PriceDepthOrderBookEntry(FIX::UtcTimeStamp(2011),
												FIX::MDUpdateAction('0'), 
												FIX::MDEntryType('0'), 
												FIX::MDEntryID("addbid"), 
												FIX::MDEntryPx(1.29),
												FIX::MDEntrySize(2)));

*/
}
