/*
 * ssp_types.hpp
 *
 */

#ifndef SSP_TYPES_HPP_
#define SSP_TYPES_HPP_

#include <sstream>
#include "ssp_any.hpp"

namespace ssp {

    Any* readAnyData   (std::basic_istream<char> &src, const char type);
    Any* readObjectData(std::basic_istream<char> &src, const char type);
    Any* readArrayData (std::basic_istream<char> &src, const char type);

    Any* readAny       (std::basic_istream<char> &src);
    Any* readObject    (std::basic_istream<char> &src);
    Any* readArray     (std::basic_istream<char> &src);

    Any* readAny        (const std::string &src             );

    Any* newAnyObject   (                                   );
    Any* newAnyArray    (                                   );
    Any* newAnyInt      (           const long long    value);
    Any* newAnyFloat    (           const double       value);
    Any* newAnyString   (           const std::string &value);
    Any* newAnyDecimal  (           const std::string &value);
    Any* newAnyByteArray(           const std::string &value);

    Any* newAnyInt      (char type, const long long    value);
    Any* newAnyFloat    (char type, const double       value);

    Any* newAny         (           const Any         &value);

    void writeAny(std::basic_ostream<char> &dest, const Any &value);
}


#endif /* SSP_TYPES_HPP_ */
