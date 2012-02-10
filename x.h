
#include <boost/shared_ptr.hpp>

class C;
typedef boost::shared_ptr<C> pC;
struct Ccomp : public std::binary_function<pC, pC, bool> {

    bool operator() (pC const & a, pC const & b) {
            return *(a.get()) < *(b.get());
    }; 
};

