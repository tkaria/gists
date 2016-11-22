#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/time_facet.hpp>

int main() {
  boost::posix_time::ptime t(boost::posix_time::second_clock::universal_time());
  std::cout << t << " date:" << boost::gregorian::to_iso_string(t.date())
            << std::endl;

  boost::gregorian::date d(boost::gregorian::day_clock::universal_day());
  std::cout << " date:" << to_iso_string(d) << std::endl;
};
