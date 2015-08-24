/*
 * ssp_any.hpp
 *
 */

#ifndef SSP_ANY_HPP_
#define SSP_ANY_HPP_

#include <sstream>
#include <stdexcept>

namespace ssp {

    class UnsupportedOperationException : public std::runtime_error {
    public:
        //SSPUnsupportedOperationException(const std::string& msg): std::runtime_error(msg) {};
        UnsupportedOperationException(): std::runtime_error("Operation unsupported") {};
    };

    //TODO basic_ostream<char> << this
    //TODO string + this
    //TODO << to binary stream ?
    class Any {
    public:
        Any() {};
        virtual ~Any() {};
        virtual Any*        clone          () const = 0;
        virtual char        type           () const = 0;
        virtual int         size           () const = 0;
        virtual std::string toString       () const = 0;
        virtual std::string asUTF8String   () const = 0;
        virtual std::string asString       () const = 0;
        virtual long long   asInt          () const = 0;
        virtual char        asInt8         () const = 0;
        virtual short       asInt16        () const = 0;
        virtual int         asInt32        () const = 0;
        virtual long long   asInt64        () const = 0;
        virtual double      asFloat        () const = 0;
        virtual float       asFloat32      () const = 0;
        virtual double      asFloat64      () const = 0;
        virtual double      asDecimal      () const = 0;
        virtual std::string asDecimalString() const = 0;
        virtual std::string asByteArray    () const = 0;

        virtual int         insert (const int         index, Any* value)       = 0;
        virtual int         add    (                         Any* value)       = 0;
        virtual int         add    (const std::string &name, Any* value)       = 0;
        virtual Any*        update (const int         index, Any* value)       = 0;
        virtual Any*        update (const std::string &name, Any* value)       = 0;
        virtual Any*        remove (const int         index               )       = 0;
        virtual Any*        remove (const std::string &name               )       = 0;
        virtual int         indexOf(const std::string &name               ) const = 0;
        virtual std::string nameOf (const int         index               ) const = 0;
        virtual Any*        item   (const int         index               ) const = 0;
        virtual Any*        item   (const std::string &name               ) const = 0;

        virtual void writeTo(std::basic_ostream<char> &dest) const = 0;

        //virtual friend bool operator==(const SSPAny &self, const SSPAny &dest) const = 0;/*{
        virtual bool operator==(const Any &dest) const = 0;/*{
            if(NULL == dest)
                return false;

            if(*self == *dest)
                return true;

            compatibleTypes(self.type(), dest.type());
            return self.dataEquals(dest);
        }*/

        //virtual friend bool operator!=(const SSPAny &self, const SSPAny &dest) const {
        //    return !(self == dest);
        //}
        virtual bool operator!=(const Any &dest) const {
            return !((*this) == dest);
        }

        /*
        template <typename T_OSTREAM>
        T_OSTREAM& operator<<(T_OSTREAM& out, const SSPAny& any) {
            return out << any.toString();
        }
        */

        //template </*typename CharT,*/ typename Traits>
        //std::basic_ostream</*CharT,*/char, Traits>& operator<<(
        //std::basic_ostream</*CharT,*/char, Traits>& out, const SSPAny& any) {
        friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& out, const Any& any) {
            return out << any.toString();
        }

    };

}




#endif /* SSP_ANY_HPP_ */
