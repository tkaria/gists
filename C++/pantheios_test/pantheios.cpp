#include "pantheios/pantheios.hpp" //primary header file, always be included
#include "pantheios/frontends/stock.h"
#include "pantheios/inserters/args.hpp"
#include "pantheios/backends/bec.file.h"
#include "pantheios/inserters/integer.hpp"

// Headers for implicit linking
#include <pantheios/implicit_link/core.h>
#include <pantheios/implicit_link/fe.simple.h>
#include <pantheios/implicit_link/be.file.h>
#include <pantheios/implicit_link/bec.file.h>
#include <pantheios/implicit_link/be.fprintf.h>
#include <pantheios/implicit_link/bec.fprintf.h>

#include <time.h>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

//Specify process identity
const PAN_CHAR_T PANTHEIOS_FE_PROCESS_IDENTITY[] = "p";

int main(int argc, char** argv){

//Use pantheios::log_xxx() or pantheios::log(xxx, ) with xxx is severity level

try
{
pantheios_be_file_setFilePath("log.local");
pantheios::log(pantheios::debug, "Entering main(", pantheios::args(argc, argv, pantheios::args::arg0FileOnly), ")");
pantheios::log_DEBUG("debug");
pantheios::log_INFORMATIONAL("informational");
pantheios::log_NOTICE("notice");
pantheios::log_WARNING("warning");
pantheios::log_ERROR("error");
pantheios::log_CRITICAL("critical");
pantheios::log_ALERT("alert");
pantheios::log_EMERGENCY("emergency");


    ptime time_start(microsec_clock::local_time());

    pantheios::log_DEBUG("01234567890123456789012345678901234567890123456789012345678901234567890123456789");
    timespec ts;
/*
    for (int i = 0; i< 1000000; i++) {
        clock_gettime(CLOCK_MONOTONIC, &ts);
        pantheios::log_DEBUG("This is a test and a timestamp", pantheios::integer(ts.tv_sec), pantheios::integer(ts.tv_nsec));
    }
*/

    ptime time_end(microsec_clock::local_time());
    time_duration duration(time_end - time_start);
    std::cout << duration << '\n';

return 1;
}
catch(std::bad_alloc&){
	pantheios::log_ALERT("out of memory");
}
catch(std::exception& x){
	pantheios::log_CRITICAL("Exception: ", x);
}
catch(...){
	pantheios::puts(pantheios::emergency, "Unknown error");
}

return 2;
}
