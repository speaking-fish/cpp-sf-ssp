/*
 * ssp_types.cpp
 *
 */

#include "ssp_types.hpp"
#include "ssp_helper.hpp"
#include "ssp_any.hpp"
#include <limits.h>
#include <math.h>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <vector>
//#include <strstream>
#include <ios>

namespace ssp {

    /*
    public static abstract class SSPAnyAbstractImpl implements SSPAny {

        @Override public abstract short  type           ();
        @Override public abstract int    size           ();
      //@Override public abstract String toString       ();
        @Override public abstract byte[] asUTF8String   ();
        @Override public abstract String asString       ();
        @Override public abstract long   asInt          ();
        @Override public abstract byte   asInt8         ();
        @Override public abstract short  asInt16        ();
        @Override public abstract int    asInt32        ();
        @Override public abstract long   asInt64        ();
        @Override public abstract double asFloat        ();
        @Override public abstract float  asFloat32      ();
        @Override public abstract double asFloat64      ();
        @Override public abstract double asDecimal      ();
        @Override public abstract String asDecimalString();
        @Override public abstract byte[] asByteArray    ();

        @Override public abstract int    insert (int    index, SSPAny value);
        @Override public abstract int    add    (              SSPAny value);
        @Override public abstract int    add    (String  name, SSPAny value);
        @Override public abstract SSPAny update (int    index, SSPAny value);
        @Override public abstract SSPAny update (String  name, SSPAny value);
        @Override public abstract SSPAny remove (int    index              );
        @Override public abstract SSPAny remove (String  name              );
        @Override public abstract int    indexOf(String  name              );
        @Override public abstract String nameOf (int    index              );
        @Override public abstract SSPAny item   (int    index              );
        @Override public abstract SSPAny item   (String  name              );
        / *
        @Override public abstract void writeExternal(ObjectOutput out) throws IOException;
        @Override public abstract void readExternal(ObjectInput in) throws IOException, ClassNotFoundException;
        * /
        @Override public abstract void writeTo(OutputStream dest);
    }

    public static abstract class SSPAnyDefaultImpl extends SSPAnyAbstractImpl {

      //@Override public short  type           () { throw new UnsupportedOperationException(); };
        @Override public int    size           () { throw new UnsupportedOperationException(); };
      //@Override public String toString       () { throw new UnsupportedOperationException(); };
        @Override public byte[] asUTF8String   () { throw new UnsupportedOperationException(); };
        @Override public String asString       () { throw new UnsupportedOperationException(); };
        @Override public long   asInt          () { throw new UnsupportedOperationException(); };
        @Override public byte   asInt8         () { throw new UnsupportedOperationException(); };
        @Override public short  asInt16        () { throw new UnsupportedOperationException(); };
        @Override public int    asInt32        () { throw new UnsupportedOperationException(); };
        @Override public long   asInt64        () { throw new UnsupportedOperationException(); };
        @Override public double asFloat        () { throw new UnsupportedOperationException(); };
        @Override public float  asFloat32      () { throw new UnsupportedOperationException(); };
        @Override public double asFloat64      () { throw new UnsupportedOperationException(); };
        @Override public double asDecimal      () { throw new UnsupportedOperationException(); };
        @Override public String asDecimalString() { throw new UnsupportedOperationException(); };
        @Override public byte[] asByteArray    () { throw new UnsupportedOperationException(); };

        @Override public int    insert (int    index, SSPAny value) { throw new UnsupportedOperationException(); };
        @Override public int    add    (              SSPAny value) { throw new UnsupportedOperationException(); };
        @Override public int    add    (String  name, SSPAny value) { throw new UnsupportedOperationException(); };
        @Override public SSPAny update (int    index, SSPAny value) { throw new UnsupportedOperationException(); };
        @Override public SSPAny update (String  name, SSPAny value) { throw new UnsupportedOperationException(); };
        @Override public SSPAny remove (int    index              ) { throw new UnsupportedOperationException(); };
        @Override public SSPAny remove (String  name              ) { throw new UnsupportedOperationException(); };
        @Override public int    indexOf(String  name              ) { throw new UnsupportedOperationException(); };
        @Override public String nameOf (int    index              ) { throw new UnsupportedOperationException(); };
        @Override public SSPAny item   (int    index              ) { throw new UnsupportedOperationException(); };
        @Override public SSPAny item   (String  name              ) { throw new UnsupportedOperationException(); };

    }
    */

    class AnyDefaultImpl : public Any {
    public:
        AnyDefaultImpl() : Any() {};
        virtual ~AnyDefaultImpl() {};
      //virtual char        type           () const = 0;
        virtual int         size           () const { throw UnsupportedOperationException();};
      //virtual std::string toString       () const { throw UnsupportedOperationException();};
        virtual std::string asUTF8String   () const { throw UnsupportedOperationException();};
        virtual std::string asString       () const { throw UnsupportedOperationException();};
        virtual long long   asInt          () const { throw UnsupportedOperationException();};
        virtual char        asInt8         () const { throw UnsupportedOperationException();};
        virtual short       asInt16        () const { throw UnsupportedOperationException();};
        virtual int         asInt32        () const { throw UnsupportedOperationException();};
        virtual long long   asInt64        () const { throw UnsupportedOperationException();};
        virtual double      asFloat        () const { throw UnsupportedOperationException();};
        virtual float       asFloat32      () const { throw UnsupportedOperationException();};
        virtual double      asFloat64      () const { throw UnsupportedOperationException();};
        virtual double      asDecimal      () const { throw UnsupportedOperationException();};
        virtual std::string asDecimalString() const { throw UnsupportedOperationException();};
        virtual std::string asByteArray    () const { throw UnsupportedOperationException();};

        virtual int         insert (const int         index, Any* value)       { throw UnsupportedOperationException();};
        virtual int         add    (                         Any* value)       { throw UnsupportedOperationException();};
        virtual int         add    (const std::string &name, Any* value)       { throw UnsupportedOperationException();};
        virtual Any*        update (const int         index, Any* value)       { throw UnsupportedOperationException();};
        virtual Any*        update (const std::string &name, Any* value)       { throw UnsupportedOperationException();};
        virtual Any*        remove (const int         index            )       { throw UnsupportedOperationException();};
        virtual Any*        remove (const std::string &name            )       { throw UnsupportedOperationException();};
        virtual int         indexOf(const std::string &name            ) const { throw UnsupportedOperationException();};
        virtual std::string nameOf (const int         index            ) const { throw UnsupportedOperationException();};
        virtual Any*        item   (const int         index            ) const { throw UnsupportedOperationException();};
        virtual Any*        item   (const std::string &name            ) const { throw UnsupportedOperationException();};

      //  virtual void writeTo(std::basic_ostream<char>* const dest) const = 0;
      /*
        //virtual friend bool operator==(const SSPAny &self, const SSPAny &dest) const = 0;/ *{
        virtual bool operator==(const SSPAny &dest) const = 0;/ *{
            if(NULL == dest)
                return false;

            if(*self == *dest)
                return true;

            compatibleTypes(self.type(), dest.type());
            return self.dataEquals(dest);
        }* /

        //virtual friend bool operator!=(const SSPAny &self, const SSPAny &dest) const {
        //    return !(self == dest);
        //}
        virtual bool operator!=(const SSPAny &dest) const {
            return !((*this) == dest);
        }

        / *
        template <typename T_OSTREAM>
        T_OSTREAM& operator<<(T_OSTREAM& out, const SSPAny& any) {
            return out << any.toString();
        }
        * /

        //template </ *typename CharT,* / typename Traits>
        //std::basic_ostream</ *CharT,* /char, Traits>& operator<<(
        //std::basic_ostream</ *CharT,* /char, Traits>& out, const SSPAny& any) {
        friend std::basic_ostream<char>& operator<<(
        std::basic_ostream<char>& out, const SSPAny& any) {
            return out << any.toString();
        }
       */
    };

    class StringImpl : public AnyDefaultImpl {
    protected:
        std::string const _value;
    public:
        StringImpl(const std::string value) : AnyDefaultImpl() , _value(value) { }

        virtual Any*        clone          () const { return new StringImpl(_value); };

        virtual char        type           () const { return SSP_TYPE_STRING; };
        virtual int         size           () const { return _value.length(); };
        virtual std::string toString       () const { return std::string() + '"' + _value + '"'; }
        virtual std::string asString       () const { return _value; };
        virtual std::string asUTF8String   () const { return _value; }

        virtual void writeTo(std::basic_ostream<char> &dest) const { writeString(dest, _value); }

        //virtual int hashCode() { return _value.hashCode(); }

        virtual bool operator==(const Any &dest) const {
            if(this == &dest)
                return true;

            if(!&dest)
                return false;

            if(type() != dest.type())
                return false;

            return _value == dest.asString();
        };
    };

    class IntImpl : public AnyDefaultImpl {
    protected:
        const char      _type ;
        const long long _value;
    public:
        IntImpl(const char type, const long long value) : AnyDefaultImpl(), _type(type), _value(value) {}

        IntImpl(const long long value) : AnyDefaultImpl(), _type(getTypeOf(value)), _value(value) {}

        virtual Any*        clone          () const { return new IntImpl(_type, _value); };

        virtual char        type           () const { return _type; };
        virtual std::string toString       () const { return asString(); }
        virtual std::string asString       () const {
            std::ostringstream tmp;
            tmp << _value;
            return tmp.str();
        };
        virtual long long   asInt          () const { return         _value; };
        virtual char        asInt8         () const { return (char ) _value; };
        virtual short       asInt16        () const { return (short) _value; };
        virtual int         asInt32        () const { return (int  ) _value; };
        virtual long long   asInt64        () const { return         _value; };

        virtual void writeTo(std::basic_ostream<char> &dest) const { writeInt(dest, _value); }

        //int hashCode() { return (int) (_value ^ (_value >>> 32)); }

        virtual bool operator==(const Any &dest) const {
            if(this == &dest)
                return true;

            if(!&dest)
                return false;

            switch(dest.type()) {
            case SSP_TYPE_INT_8 : break;
            case SSP_TYPE_INT_16: break;
            case SSP_TYPE_INT_32: break;
            case SSP_TYPE_INT_64: break;
            default: return false;
            }

            return _value == dest.asInt();
        };

    };

    class FloatImpl : public AnyDefaultImpl {
    protected:
        const char   _type ;
        const double _value;
    public:
        FloatImpl(const char type, const double value) : AnyDefaultImpl(), _type(type), _value(value) { }

        FloatImpl(const double value) : AnyDefaultImpl(), _type(getTypeOf(value)), _value(value) {}

        virtual Any*        clone          () const { return new FloatImpl(_type, _value); };

        virtual char        type           () const { return _type; };
        virtual std::string toString       () const { return asString(); }
        virtual std::string asString       () const {
            std::ostringstream tmp;
            tmp << _value;
            return tmp.str();
        };
        virtual double      asFloat        () const { return         _value; };
        virtual float       asFloat32      () const { return (float) _value; };
        virtual double      asFloat64      () const { return         _value; }

        virtual void writeTo(std::basic_ostream<char> &dest) const { writeFloat(dest, _value); }
        /*
        @Override public int hashCode() {
            final long temp = Double.doubleToLongBits(_value);
            return (int) (temp ^ (temp >>> 32));
        }
        */
        virtual bool operator==(const Any &dest) const {
            if(this == &dest)
                return true;

            if(!&dest)
                return false;

            switch(dest.type()) {
            case SSP_TYPE_FLOAT_32: break;
            case SSP_TYPE_FLOAT_64: break;
            default: return false;
            }

            return _value == dest.asFloat();
        };

    };

    class DecimalImpl : public AnyDefaultImpl {
    protected:
        const std::string _value;

    public:
        DecimalImpl(const std::string &value) : AnyDefaultImpl(), _value(value) {}

        virtual Any*        clone          () const { return new DecimalImpl(_value); };

        virtual char        type           () const { return SSP_TYPE_DECIMAL; };
        virtual std::string toString       () const { return asString(); }
        virtual std::string asString       () const { return _value; };
        virtual double      asDecimal      () const {
            double tmp;
            if(!(std::istringstream(_value) >> tmp)) {
                throw SSPInvalidDataException("Error convert " + _value + " to double");
            }
            return tmp;
        }
        virtual std::string asDecimalString() const { return _value; };

        virtual void writeTo(std::basic_ostream<char> &dest) const { writeDecimalString(dest, _value); }

        //int hashCode() { return _value.hashCode(); }

        virtual bool operator==(const Any &dest) const {
            if(this == &dest)
                return true;

            if(!&dest)
                return false;

            if(type() != dest.type())
                return false;

            return _value == dest.asDecimalString();
        };
    };

    class ByteArrayImpl : public AnyDefaultImpl {
    protected:
        const std::string _value;

    public:
        ByteArrayImpl(const std::string &value) : AnyDefaultImpl(), _value(value) {}
        //SSPByteArrayImpl(const int size, const char const * buf) : SSPAny(), _value(buf, size) {}

        //protected static final char[] hexArray = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
        virtual Any*        clone          () const { return new ByteArrayImpl(_value); };

        virtual char        type           () const { return SSP_TYPE_BYTE_ARRAY; };
        virtual int         size           () const { return _value.length(); };
        virtual std::string asByteArray    () const { return _value; };
        virtual std::string toString       () const {
            std::ostringstream tmp;
            tmp << std::setw(2) << std::setfill('0') << std::hex << std::uppercase;
            std::copy(_value.begin(), _value.end(), std::ostream_iterator<unsigned int>(tmp, " "));
            return tmp.str();
            /*
            final char[] result = new char[_value.length * 2];
            for(int i = 0; i < _value.length; ++i) {
                final byte v = _value[i];
                result[i * 2 + 0] = hexArray[v >>> 4];
                result[i * 2 + 1] = hexArray[v & 0x0F];
            }
            return new String(result);
            */
        }

        virtual void writeTo(std::basic_ostream<char> &dest) const { writeByteArray(dest, 0, _value.length(), _value.c_str()); }

        //virtual int hashCode() { return Arrays.hashCode(_value); }

        virtual bool operator==(const Any &dest) const {
            if(this == &dest)
                return true;

            if(!&dest)
                return false;

            if(type() != dest.type())
                return false;

            return _value == dest.asByteArray();
        }

    };

    class ArrayImpl : public AnyDefaultImpl {
    protected:
        std::vector<Any*> _value;

        //protected SSPArrayImpl(List<SSPAny> value) { super(); _value = value; }

    public:
        ArrayImpl() : AnyDefaultImpl(), _value() { }
        ~ArrayImpl() {
            for(int i = 0; i < size(); ++i) {
                delete item(i);
            }
        }

        virtual Any*        clone          () const {
            Any* result = new ArrayImpl();
            for(int i = 0; i < size(); ++i) {
                result->add(item(i)->clone());
            }
            return result;
        };

        virtual char        type           () const { return SSP_TYPE_ARRAY; };
        virtual int         size           () const { return _value.size    (); };
        virtual std::string toString       () const {
            //return _value.toString();
            std::ostringstream tmp;
            tmp << "[";
            std::copy(_value.begin(), _value.end(), std::ostream_iterator<Any*>(tmp, ", "));
            tmp << "]";
            return tmp.str();
        }

        virtual int    add    (              Any* value) {
            _value.push_back(value);
            return _value.size() - 1;
        };

        virtual int    insert (int    index, Any* value) {
            _value.insert(_value.begin() + index, value);
            return index;
        };

        virtual Any*   update (int    index, Any* value) {
            /*
            SSPAny* tmp = _value.at(index);
            _value.at(index) = value;
            */
            std::vector<Any*>::reference ref(_value.at(index));
            Any* old = ref;
            ref = value;
            return old;
        };

        virtual Any*    remove (int    index               ) {
            /*
            SSPAny* old = _value.at(index);
            _value.erase(_value.begin() + index);
            */
            std::vector<Any*>::iterator i(_value.begin() + index);
            Any* old = *i;
            _value.erase(i);
            return old;
        };

        virtual Any*    item   (int    index               ) const { return _value.at    (index); };
        virtual void writeTo(std::basic_ostream<char> &dest) const {
            writeArray(dest, size());
            for(int i = 0; i < size(); ++i) {
                item(i)->writeTo(dest);
            }
        }

        //virtual int hashCode() { return _value.hashCode(); }

        virtual bool operator==(const Any &dest) const {
            if(this == &dest)
                return true;

            if(!&dest)
                return false;

            if(type() != dest.type())
                return false;

            if(size() != dest.size())
                return false;

            for(int i = 0; i < size(); ++i) {
                if(*item(i) != *dest.item(i))
                    return false;
            }
            return true;
        }

    };

    class ObjectImpl : public AnyDefaultImpl {
    protected:
        std::vector<std::string> _names;
        std::vector<Any*> _value;
    public: //todo java: construcor protected -> public
        ObjectImpl() : AnyDefaultImpl(), _names(),_value() {}
        ~ObjectImpl() {
            for(int i = 0; i < size(); ++i) {
                delete item(i);
            }
        }

        virtual Any*        clone          () const {
            Any* result = new ObjectImpl();
            for(int i = 0; i < size(); ++i) {
                result->add(nameOf(i), item(i)->clone());
            }
            return result;
        };

        virtual char        type           () const { return SSP_TYPE_OBJECT; };
        virtual int         size           () const { return _value.size(); };
        virtual std::string toString       () const {
            std::stringstream tmp;
            tmp << "{"; //TODO: add this to java
            if(0 < size()) {
                tmp << "\"" << nameOf(0) << "\": " << *item(0);
                for(int i = 1; i < size(); ++i) {
                    tmp << ", \"" << nameOf(i) << "\": " << *item(i);
                }
            }
            tmp << "}";
            return tmp.str();
        }

        virtual int    add    (const std::string &name, Any* value) {
            int index = indexOf(name);
            if(0 <= index) {
                _value.at(index) = value;
                return index;
            } else {
                _names.push_back(name);
                _value.push_back(value);
                return _value.size();
            }
        };

        virtual Any* update (int         index, Any* value) {
            std::vector<Any*>::reference ref = _value.at(index);
            Any* old = ref;
            ref = value;
            return old;
        };

        virtual Any* update (const std::string &name, Any* value) { return update(indexOf(name), value); };

        virtual Any* remove (int    index              ) {
            /*
            _names.remove(index);
            return _value.remove(index);
            */
            _names.erase(_names.begin() + index);
            const std::vector<Any*>::iterator i(_value.begin() + index);
            Any* old = *i;
            _value.erase(i);
            return old;
        };

        virtual Any*        remove (const std::string &name              ) { return remove(indexOf(name)); };
        virtual int         indexOf(const std::string &name              ) const {
            std::string n(name);
            //return _names.indexOf(name);
            /*
            conversion from '__gnu_cxx::
            __normal_iterator<const std::basic_string<char>*, std::vector<std::basic_string<char> > >
            ' to non-scalar type '
            std::vector<std::basic_string<char> >::iterator {aka __gnu_cxx::
            __normal_iterator<      std::basic_string<char>*, std::vector<std::basic_string<char> > >}' requested
            */
            /*
             * conversion from '__gnu_cxx::
             * __normal_iterator<const std::basic_string<char>*, std::vector<      std::basic_string<char> > >' to non-scalar type '
             * std::vector<const std::basic_string<char> >::iterator {aka __gnu_cxx::
             * __normal_iterator<const std::basic_string<char>*, std::vector<const std::basic_string<char> > >}' requested
             */
            const std::vector<std::string>::const_iterator i = std::find(_names.begin(), _names.end(), name);
            return (i == _names.end())
                ? -1
                : i - _names.begin();
        };

        virtual std::string nameOf (int               index              ) const { return _names.at(index); };
        virtual Any*        item   (int               index              ) const { return _value.at(index); };

        virtual Any*        item   (const std::string &name              ) const {
            const int index = indexOf(name);
            return (index < 0) ? NULL : item(index);
        };

        virtual void writeTo(std::basic_ostream<char> &dest) const {
            writeObject(dest, size());
            for(int i = 0; i < size(); ++i) {
                writeField(dest, nameOf(i));
                item(i)->writeTo(dest);
            }
        }

        //virtual int hashCode() { return _value.hashCode(); }

        virtual bool operator==(const Any &dest) const {
            if(this == &dest)
                return true;

            if(!&dest)
                return false;

            if(type() != dest.type())
                return false;

            if(size() != dest.size())
                return false;

            for(int i = 0; i < size(); ++i) {
                if(*item(i) != *(dest.item(nameOf(i))))
                    return false;
            }
            return true;
        }
    };


    Any* readAnyData(std::basic_istream<char> &src, const char type) {
        switch(type) {
        case SSP_TYPE_OBJECT    : return                       readObjectData       (src, type) ;
        case SSP_TYPE_ARRAY     : return                       readArrayData        (src, type) ;
        case SSP_TYPE_STRING    : return newAnyString   (      readStringData       (src, type));
        case SSP_TYPE_BYTE_ARRAY: return newAnyByteArray(      readByteArrayData    (src, type));
        case SSP_TYPE_DECIMAL   : return newAnyDecimal  (      readDecimalStringData(src, type));
        case SSP_TYPE_INT_8     : return newAnyInt      (type, readInt8Data         (src, type));
        case SSP_TYPE_INT_16    : return newAnyInt      (type, readInt16Data        (src, type));
        case SSP_TYPE_INT_32    : return newAnyInt      (type, readInt32Data        (src, type));
        case SSP_TYPE_INT_64    : return newAnyInt      (type, readInt64Data        (src, type));
        case SSP_TYPE_FLOAT_32  : return newAnyFloat    (type, readFloat32Data      (src, type));
        case SSP_TYPE_FLOAT_64  : return newAnyFloat    (type, readFloat64Data      (src, type));
        default                 : {
            std::ostringstream tmp;
            tmp << "Illegal type: " << type << ".";
            throw SSPInvalidDataException(tmp.str());
        }
        }
    }

    Any* readObjectData(std::basic_istream<char> &src, const char type) {
        checkType(type, SSP_TYPE_OBJECT);
        const int size = (int) readInt(src);
        Any* result = newAnyObject();
        try {
			for(int i = 0; i < size; ++i) {
				const std::string name = readString(src);
				result->add(name, readAny(src));
			}
        } catch(...) {
        	delete result;
        	result = 0;
        	throw;
        }
        return result;
    }

    Any* readArrayData(std::basic_istream<char> &src, const char type) {
        checkType(type, SSP_TYPE_ARRAY);
        const int size = readInt(src);
        /*
        final List<SSPAny> list = new ArrayList<SSPAny>(size);
        for(int i = 0; i < size; ++i) {
            list.add(readAny(src));
        }
        return new SSPArrayImpl(list);
        */
        Any* result = newAnyArray();
        try {
			for(int i = 0; i < size; ++i) {
				result->add(readAny(src));
			}
        } catch(...) {
        	delete result;
        	result = 0;
        	throw;
        }
        return result;
    }

    Any* readAny          (std::basic_istream<char> &src) { return readAnyData          (src, readType(src)); }
    Any* readObject       (std::basic_istream<char> &src) { return readObjectData       (src, readType(src)); }
    Any* readArray        (std::basic_istream<char> &src) { return readArrayData        (src, readType(src)); }

    Any* readAny          (const std::string &src             ) {
    	std::istringstream tmp(src);
    	return readAny(tmp);
    }

    Any* newAnyObject   (                                   ) { return new ObjectImpl   (           ); };
    Any* newAnyArray    (                                   ) { return new ArrayImpl    (           ); };
    Any* newAnyInt      (           const long long    value) { return new IntImpl      (      value); };
    Any* newAnyFloat    (           const double       value) { return new FloatImpl    (      value); };
    Any* newAnyString   (           const std::string &value) { return new StringImpl   (      value); };
    Any* newAnyDecimal  (           const std::string &value) { return new DecimalImpl  (      value); };
    Any* newAnyByteArray(           const std::string &value) { return new ByteArrayImpl(      value); };
    Any* newAnyInt      (char type, const long long    value) { return new IntImpl      (type, value); };
    Any* newAnyFloat    (char type, const double       value) { return new FloatImpl    (type, value); };

    Any* newAny         (           const Any      &value) { return value.clone(); }

    void writeAny(std::basic_ostream<char> &dest, const Any &value) {
        value.writeTo(dest);
    }

}



