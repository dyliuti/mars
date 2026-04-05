#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace mars_boost {
void throw_exception(std::exception const& e) {
    throw e;
}
}
