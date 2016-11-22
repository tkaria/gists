#include <string>
#include <iostream>
#include <fstream>

#include "MurmurHash3.h"
#include "JenkinsHash.h"
#include <sys/types.h>
#include <stdio.h>

#include <stdlib.h>

#include <uuid/uuid.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "SuperFastHash.cpp"

#include "spooky.h"

#include "city.h"

using namespace boost::posix_time;

int 
main(int argc, char* argv[])
{
	int x = 12093482;
	uint64_t out;
	uuid_t uuid;

	time_duration unitcheck;
	std::cout << "Min time resolution: " << unitcheck.unit() << std::endl;

	uint32_t hashval;
	ptime b5(microsec_clock::local_time());	
	for (int i = 0; i<1000000; i++) {
		//uint64_t x = rand();
		uuid_generate(uuid);
		SuperFastHash(uuid, 16, 0, &hashval);
	}
	ptime e5(microsec_clock::local_time());	
	time_duration duration5 = e5 - b5;
	std::cout << "Duration 1e6 iters SuperFastHash: " << duration5 << std::endl;   

	ptime b1(microsec_clock::local_time());	
	for (int i = 0; i<1000000; i++) {
		//uint64_t x = rand();
		uuid_generate(uuid);
		hashval = hashlittle(uuid, 16, 0);
	}
	ptime e1(microsec_clock::local_time());	
	time_duration duration1 = e1 - b1;
	std::cout << "Duration 1e6 iters Jenkins: " << duration1 << std::endl;   

	ptime b7(microsec_clock::local_time());	
	for (int i = 0; i<1000000; i++) {
		//uint64_t x = rand();
		uuid_generate(uuid);
		hashval = CityHash64((char*)uuid, 16);
	}
	ptime e7(microsec_clock::local_time());	
	time_duration duration7 = e7 - b7;
	std::cout << "Duration 1e6 iters CityHash64: " << duration7 << std::endl;   












	ptime b2(microsec_clock::local_time());	
	for (int i = 0; i<1000000; i++) {
		int x = rand();
		MurmurHash3_x86_128(&x, sizeof(x), 0, &out);
	}
	ptime e2(microsec_clock::local_time());	
	time_duration duration2 = e2 - b2;
	std::cout << "Duration 1e6 iters MurmurHash3_x86_128: " << duration2 << std::endl;   
    
	ptime b3(microsec_clock::local_time());	
	for (int i = 0; i<1000000; i++) {
		int x = rand();
		MurmurHash3_x86_32(&x, sizeof(x), 0, &out);
	}
	ptime e3(microsec_clock::local_time());	
	time_duration duration3 = e3 - b3;
	std::cout << "Duration 1e6 iters MurmurHash3_x86_32: " << duration3 << std::endl;   

	ptime b4(microsec_clock::local_time());	
	for (int i = 0; i<1000000; i++) {
		int x = rand();
		MurmurHash3_x64_128(&x, sizeof(x), 0, &out);
	}
	ptime e4(microsec_clock::local_time());	
	time_duration duration4 = e4 - b4;
	std::cout << "Duration 1e6 iters MurmurHash3_x64_128: " << duration4 << std::endl;   

	ptime b6(microsec_clock::local_time());	
	for (int i = 0; i<1000000; i++) {
		int x = rand();
		uint32_t shv = SpookyHash::Hash64(&x, sizeof(x), 0);
	}
	ptime e6(microsec_clock::local_time());	
	time_duration duration6 = e6 - b6;
	std::cout << "Duration 1e6 iters SpookyHash::Hash64: " << duration6 << std::endl;   
}

