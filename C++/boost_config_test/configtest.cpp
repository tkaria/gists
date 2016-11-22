
#include <boost/config.hpp>
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/parsers.hpp>

#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

namespace pod = boost::program_options::detail;

int main() {
  std::ifstream cfg("configtest.ini");

  if (!cfg) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  std::set<std::string> options;
  std::map<std::string, std::string> params;

  options.insert("*");

  try {
    for (pod::config_file_iterator i(cfg, options), e; i != e; ++i) {
      params[i->string_key] = i->value[0];
    }
    std::cerr << params["testing.a"] << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
