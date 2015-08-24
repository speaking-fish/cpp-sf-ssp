/*
 * ssp_helper.cpp
 *
 */

#include <limits.h>
#include <math.h>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include "sfp_common.hpp"
#include "ssp_helper.hpp"

#ifdef _MSC_VER
#define isnan _isnan
#endif

namespace ssp {

    union FloatIntUnion {
      float floatValue;
      int   intValue  ;
    };

    union DoubleLongUnion {
      double    doubleValue;
      long long longValue  ;
    };

    char getTypeOf(const long long value) {
             if(value <    INT_MIN) return SSP_TYPE_INT_64;
        else if(value <   SHRT_MIN) return SSP_TYPE_INT_32;
        else if(value <  SCHAR_MIN) return SSP_TYPE_INT_16;
        else if(value <= SCHAR_MAX) return SSP_TYPE_INT_8 ;
        else if(value <=  SHRT_MAX) return SSP_TYPE_INT_16;
        else if(value <=   INT_MAX) return SSP_TYPE_INT_32;
        else                        return SSP_TYPE_INT_64;
    }

    char getTypeOf(const double value) {
        const float tempSingle = (float) value;
        if(isnan(tempSingle) || (tempSingle == value))
            return SSP_TYPE_FLOAT_32; else
            return SSP_TYPE_FLOAT_64;
    }

    void writeType(std::basic_ostream<char> &dest, const char value) {
        sfp::internalWriteChar(dest, value);
    }

    void writeByteArray(std::basic_ostream<char> &dest, const int offset, const int size, char const * const buffer) {
        writeType(dest, SSP_TYPE_BYTE_ARRAY);
        writeInt(dest, size);
        sfp::internalWriteBuf(dest, offset, size, buffer);
    }

    void writeObject(std::basic_ostream<char> &dest, const int fieldCount) {
        writeType(dest, SSP_TYPE_OBJECT);
        writeInt(dest, fieldCount);
    }

    void writeField(std::basic_ostream<char> &dest, const std::string &fieldName) {
        writeString(dest, fieldName);
    }

    void writeArray(std::basic_ostream<char> &dest, const int itemCount) {
        writeType(dest, SSP_TYPE_ARRAY);
        writeInt(dest, itemCount);
    }

    void writeUTF8String(std::basic_ostream<char> &dest, const int size, char const * const value) {
        writeType(dest, SSP_TYPE_STRING);
        writeInt(dest, size);
        sfp::internalWriteBuf(dest, size, value);
    }

    void writeString(std::basic_ostream<char> &dest, const std::string &value) {
        writeUTF8String(dest, value.length(), value.c_str());
    }

    void writeInt(std::basic_ostream<char> &dest, const long long value) {
        const char type = getTypeOf(value);

        switch(type) {
            case SSP_TYPE_INT_8 : writeInt8 (dest, (char     ) value); break;
            case SSP_TYPE_INT_16: writeInt16(dest, (short    ) value); break;
            case SSP_TYPE_INT_32: writeInt32(dest, (int      ) value); break;
            default             : writeInt64(dest, (long long) value); break;
        }
    }

    void writeInt8         (std::basic_ostream<char> &dest, const char   value) {
        writeType(dest, SSP_TYPE_INT_8 );
        sfp::internalWriteChar(dest, value);
    }

    void writeInt32        (std::basic_ostream<char> &dest, const int    value) {
        writeType(dest, SSP_TYPE_INT_32);
        writeInt32Data(dest, value);
    }

    void writeInt64        (std::basic_ostream<char> &dest, const long long value) {
        writeType(dest, SSP_TYPE_INT_64);
        writeInt64Data(dest, value);
    }

    void writeInt16        (std::basic_ostream<char> &dest, const short  value) {
        writeType(dest, SSP_TYPE_INT_16);
        sfp::internalWriteChar(dest, (char) (value >> (8 * 1)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 0)));
    }

    void writeInt32Data    (std::basic_ostream<char> &dest, const int    value) {
        sfp::internalWriteChar(dest, (char) (value >> (8 * 3)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 2)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 1)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 0)));
    }

    void writeInt64Data    (std::basic_ostream<char> &dest, const long long value) {
        sfp::internalWriteChar(dest, (char) (value >> (8 * 7)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 6)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 5)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 4)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 3)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 2)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 1)));
        sfp::internalWriteChar(dest, (char) (value >> (8 * 0)));
    }

    void writeFloat        (std::basic_ostream<char> &dest, const double value) {
        const char type = getTypeOf(value);
        if(SSP_TYPE_FLOAT_32 == type) {
            writeFloat32(dest, (float) value);
        } else {
            writeFloat64(dest,         value);
        }
    }

    void writeFloat32      (std::basic_ostream<char> &dest, const float  value) {
        writeType(dest, SSP_TYPE_FLOAT_32);
        FloatIntUnion tmp;
        tmp.floatValue = value;
        writeInt32Data(dest, tmp.intValue);
    }

    void writeFloat64      (std::basic_ostream<char> &dest, const double value) {
        writeType(dest, SSP_TYPE_FLOAT_64);
        DoubleLongUnion tmp;
        tmp.doubleValue = value;
        writeInt64Data(dest, tmp.longValue);
    }

    void writeDecimalString(std::basic_ostream<char> &dest, const std::string &value) {
        writeType(dest, SSP_TYPE_DECIMAL);
        writeInt(dest, value.length());
        sfp::internalWriteBuf(dest, value.length(), value.c_str());
    }

    char checkType(char actual, char required) {
        if(actual != required) {
            throw SSPInvalidDataException(std::string() + "Illegal type: " + actual + ". Required type: " + required + ".");
        }
        return actual;
    }

    char readType(std::basic_istream<char> &src) {
        return readInt8Data(src, SSP_TYPE_INT_8);
    }

    int readByteArrayDataTo(std::basic_istream<char> &src, char type, std::basic_ostream<char> &dest) {
        checkType(type, SSP_TYPE_BYTE_ARRAY);
        const int size = readInt(src);
        if(0 < size) {
            sfp::internalRead(src, size, dest);
        }
        return size;
    }

    std::string readByteArrayData(std::basic_istream<char> &src, char type) {
        std::stringstream tmp;
        readByteArrayDataTo(src, type, tmp);
        return tmp.str();
    }

    int readUTF8StringDataTo(std::basic_istream<char> &src, char type, std::basic_ostream<char> &dest) {
        checkType(type, SSP_TYPE_STRING);
        const int size = readInt(src);
        if(0 < size) {
            sfp::internalRead(src, size, dest);
        }
        return size;
    }

    std::string readStringData(std::basic_istream<char> &src, char type) {
        std::stringstream tmp;
        readUTF8StringDataTo(src, type, tmp);
        return tmp.str();
    }

    long long readIntData(std::basic_istream<char> &src, char type) {
        switch(type) {
        case SSP_TYPE_INT_8 : return readInt8Data (src, type);
        case SSP_TYPE_INT_16: return readInt16Data(src, type);
        case SSP_TYPE_INT_32: return readInt32Data(src, type);
        case SSP_TYPE_INT_64: return readInt64Data(src, type);
        default             : throw new SSPInvalidDataException(std::string()
            + "Illegal type: " + type + ". Required types: ("
            + SSP_TYPE_INT_8  + ','
            + SSP_TYPE_INT_16 + ','
            + SSP_TYPE_INT_32 + ','
            + SSP_TYPE_INT_64 + ")."
            );
        }
    }

    char readInt8Data(std::basic_istream<char> &src, char type) {
        checkType(type, SSP_TYPE_INT_8 ); return sfp::internalRead(src);
    }

    short readInt16Data(std::basic_istream<char> &src, char type) {
        checkType(type, SSP_TYPE_INT_16);
        return  (short) ((((0
            | (sfp::internalRead(src) & (short) 0xFF)) << 8)
            | (sfp::internalRead(src) & (short) 0xFF))     )
            ;
    }

    int readInt32Data(std::basic_istream<char> &src, char type) {
        checkType(type, SSP_TYPE_INT_32);
        return  (int) ((((((((0
            | (sfp::internalRead(src) & (int) 0xFF)) << 8)
            | (sfp::internalRead(src) & (int) 0xFF)) << 8)
            | (sfp::internalRead(src) & (int) 0xFF)) << 8)
            | (sfp::internalRead(src) & (int) 0xFF))     )
            ;
    }

    long long readInt64Data(std::basic_istream<char> &src, char type) {
        checkType(type, SSP_TYPE_INT_64);
        return  (long) ((((((((((((((((0
            | (sfp::internalRead(src) & (long long) 0xFFL)) << 8)
            | (sfp::internalRead(src) & (long long) 0xFFL)) << 8)
            | (sfp::internalRead(src) & (long long) 0xFFL)) << 8)
            | (sfp::internalRead(src) & (long long) 0xFFL)) << 8)
            | (sfp::internalRead(src) & (long long) 0xFFL)) << 8)
            | (sfp::internalRead(src) & (long long) 0xFFL)) << 8)
            | (sfp::internalRead(src) & (long long) 0xFFL)) << 8)
            | (sfp::internalRead(src) & (long long) 0xFFL))     )
            ;
    }

    double readFloatData(std::basic_istream<char> &src, char type) {
        switch(type) {
        case SSP_TYPE_FLOAT_32: return readFloat32Data(src, type);
        case SSP_TYPE_FLOAT_64: return readFloat64Data(src, type);
        default               : throw SSPInvalidDataException(std::string()
            + "Illegal type: " + type + ". Required types: ("
            + SSP_TYPE_FLOAT_32 + ','
            + SSP_TYPE_FLOAT_64 + "')."
            );
        }
    }

    float readFloat32Data(std::basic_istream<char> &src, char type) {
        checkType(type, SSP_TYPE_FLOAT_32);
        FloatIntUnion tmp;
        tmp.intValue = readInt32Data(src, SSP_TYPE_INT_32);
        return tmp.floatValue;
    }

    double readFloat64Data(std::basic_istream<char> &src, char type) {
        checkType(type, SSP_TYPE_FLOAT_64);
        DoubleLongUnion tmp;
        tmp.longValue = readInt64Data(src, SSP_TYPE_INT_64);
        return tmp.doubleValue;
    }

    std::string readDecimalStringData(std::basic_istream<char> &src, char type) {
        checkType(type, SSP_TYPE_DECIMAL);
        std::stringstream tmp;
        readUTF8StringDataTo(src, SSP_TYPE_STRING, tmp);
        return tmp.str();
    }


    /*
    public static SSPAny readAnyData(InputStream src, byte type) throws EOFException {
        switch(type) {
        case SSP_TYPE_OBJECT    : return                            readObjectData       (src, type) ;
        case SSP_TYPE_ARRAY     : return                            readArrayData        (src, type) ;
        case SSP_TYPE_STRING    : return new SSPStringImpl   (      readStringData       (src, type));
        case SSP_TYPE_BYTE_ARRAY: return new SSPByteArrayImpl(      readByteArrayData    (src, type));
        case SSP_TYPE_DECIMAL   : return new SSPDecimalImpl  (      readDecimalStringData(src, type));
        case SSP_TYPE_INT_8     : return new SSPIntImpl      (type, readInt8Data         (src, type));
        case SSP_TYPE_INT_16    : return new SSPIntImpl      (type, readInt16Data        (src, type));
        case SSP_TYPE_INT_32    : return new SSPIntImpl      (type, readInt32Data        (src, type));
        case SSP_TYPE_INT_64    : return new SSPIntImpl      (type, readInt64Data        (src, type));
        case SSP_TYPE_FLOAT_32  : return new SSPFloatImpl    (type, readFloat32Data      (src, type));
        case SSP_TYPE_FLOAT_64  : return new SSPFloatImpl    (type, readFloat64Data      (src, type));
        default                 : throw new SSPInvalidDataException("Illegal type: " + type + ".");
        }
    }

    public static SSPAny readObjectData(InputStream src, byte type) throws EOFException {
        checkType(type, SSP_TYPE_OBJECT);
        final int size = (int) readInt(src);
        final SSPAny result = new SSPObjectImpl();
        for(int i = 0; i < size; ++i) {
            final String name = readString(src);
            result.add(name, readAny(src));
        }
        return result;
    }

    public static SSPAny readArrayData(InputStream src, byte type) throws EOFException {
        checkType(type, SSP_TYPE_ARRAY);
        final int size = (int) readInt(src);
        final List<SSPAny> list = new ArrayList<SSPAny>(size);
        for(int i = 0; i < size; ++i) {
            list.add(readAny(src));
        }
        return new SSPArrayImpl(list);
    }
*/
    /*
    byte[] readByteArray    (std::basic_istream<char> &src) { return readByteArrayData    (src, readType(src)); }
    byte[] readUTF8String   (std::basic_istream<char> &src) { return readUTF8StringData   (src, readType(src)); }
    */
    std::string readString       (std::basic_istream<char> &src) { return readStringData       (src, readType(src)); }
    long long   readInt          (std::basic_istream<char> &src) { return readIntData          (src, readType(src)); }
    char        readInt8         (std::basic_istream<char> &src) { return readInt8Data         (src, readType(src)); }
    short       readInt16        (std::basic_istream<char> &src) { return readInt16Data        (src, readType(src)); }
    int         readInt32        (std::basic_istream<char> &src) { return readInt32Data        (src, readType(src)); }
    long long   readInt64        (std::basic_istream<char> &src) { return readInt64Data        (src, readType(src)); }
    double      readFloat        (std::basic_istream<char> &src) { return readFloatData        (src, readType(src)); }
    float       readSingle       (std::basic_istream<char> &src) { return readFloat32Data      (src, readType(src)); }
    double      readDouble       (std::basic_istream<char> &src) { return readFloat64Data      (src, readType(src)); }
    std::string readDecimalString(std::basic_istream<char> &src) { return readDecimalStringData(src, readType(src)); }
    /*
    SSPAny readAny          (InputStream src) throws EOFException { return readAnyData          (src, readType(src)); }
    SSPAny readObject       (InputStream src) throws EOFException { return readObjectData       (src, readType(src)); }
    SSPAny readArray        (InputStream src) throws EOFException { return readArrayData        (src, readType(src)); }
    */

}


