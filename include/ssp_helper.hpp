/*
 * ssp_helper.hpp
 *
 */

#ifndef SSP_HELPER_HPP_
#define SSP_HELPER_HPP_

#include <stdexcept>
#include <sstream>

namespace ssp {

    //SIMPLE SERIALIZATION PROTOCOL
    //
    const char SSP_TYPE_OBJECT     = 0; // objectType    intType COUNT (stringType FIELD_NAME valueType FIELD_VALUE)*
    const char SSP_TYPE_ARRAY      = 1; // arrayType     intType COUNT (                      valueType FIELD_VALUE)*
    const char SSP_TYPE_STRING     = 2; // stringType    intType COUNT (                                 BYTE_VALUE)*
    const char SSP_TYPE_DECIMAL    = 4; // decimalType   intType COUNT (                                 BYTE_VALUE)*
    const char SSP_TYPE_INT_8      =10; // int8Type      BYTE_VALUE
    const char SSP_TYPE_INT_16     =11; // int16Type     BYTE_VALUE0 BYTE_VALUE1
    const char SSP_TYPE_INT_32     =12; // int32Type     BYTE_VALUE0 BYTE_VALUE1 BYTE_VALUE2 BYTE_VALUE3
    const char SSP_TYPE_INT_64     =13; // int64Type     BYTE_VALUE0 BYTE_VALUE1 BYTE_VALUE2 BYTE_VALUE3 BYTE_VALUE4 BYTE_VALUE5 BYTE_VALUE6 BYTE_VALUE7
    const char SSP_TYPE_FLOAT_32   =15; // float32Type   BYTE_VALUE0 BYTE_VALUE1 BYTE_VALUE2 BYTE_VALUE3
    const char SSP_TYPE_FLOAT_64   =16; // float64Type   BYTE_VALUE0 BYTE_VALUE1 BYTE_VALUE2 BYTE_VALUE3 BYTE_VALUE4 BYTE_VALUE5 BYTE_VALUE6 BYTE_VALUE7
    const char SSP_TYPE_BYTE_ARRAY =20; // byteArrayType intType COUNT (                                 BYTE_VALUE)*


    char getTypeOf         (const long long value);
    char getTypeOf         (const double    value);

    void writeType         (std::basic_ostream<char> &dest, const char         value);

    void writeByteArray    (std::basic_ostream<char> &dest, const int offset, const int size, char const * const buffer);

    void writeObject       (std::basic_ostream<char> &dest, const int          fieldCount);

    void writeField        (std::basic_ostream<char> &dest, const std::string &fieldName);

    void writeArray        (std::basic_ostream<char> &dest, const int itemCount);

    void writeUTF8String   (std::basic_ostream<char> &dest, const int size, char const * const value);
    void writeString       (std::basic_ostream<char> &dest, const std::string &value);
    void writeInt          (std::basic_ostream<char> &dest, const long long    value);

    void writeInt8         (std::basic_ostream<char> &dest, const char         value);
    void writeInt16        (std::basic_ostream<char> &dest, const short        value);
    void writeInt32        (std::basic_ostream<char> &dest, const int          value);
    void writeInt64        (std::basic_ostream<char> &dest, const long long    value);

    void writeInt32Data    (std::basic_ostream<char> &dest, const int          value);
    void writeInt64Data    (std::basic_ostream<char> &dest, const long long    value);

    void writeFloat        (std::basic_ostream<char> &dest, const double       value);

    void writeFloat32      (std::basic_ostream<char> &dest, const float        value);
    void writeFloat64      (std::basic_ostream<char> &dest, const double       value);

    void writeDecimalString(std::basic_ostream<char> &dest, const std::string &value);


    char        checkType(char actual, char required);

    char        readType            (std::basic_istream<char> &src);

    int         readByteArrayDataTo  (std::basic_istream<char> &src, char type, std::basic_ostream<char> &dest);
    std::string readByteArrayData    (std::basic_istream<char> &src, char type);

    int         readUTF8StringDataTo (std::basic_istream<char> &src, char type, std::basic_ostream<char> &dest);
    std::string readUTF8StringData   (std::basic_istream<char> &src, char type);
    std::string readStringData       (std::basic_istream<char> &src, char type);

    long long   readIntData          (std::basic_istream<char> &src, char type);
    char        readInt8Data         (std::basic_istream<char> &src, char type);
    short       readInt16Data        (std::basic_istream<char> &src, char type);
    int         readInt32Data        (std::basic_istream<char> &src, char type);
    long long   readInt64Data        (std::basic_istream<char> &src, char type);

    double      readFloatData        (std::basic_istream<char> &src, char type);
    float       readFloat32Data      (std::basic_istream<char> &src, char type);
    double      readFloat64Data      (std::basic_istream<char> &src, char type);

    std::string readDecimalStringData(std::basic_istream<char> &src, char type);

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
    std::string readByteArray    (std::basic_istream<char> &src);
    std::string readUTF8String   (std::basic_istream<char> &src);

    std::string readString       (std::basic_istream<char> &src);
    long long   readInt          (std::basic_istream<char> &src);
    char        readInt8         (std::basic_istream<char> &src);
    short       readInt16        (std::basic_istream<char> &src);
    int         readInt32        (std::basic_istream<char> &src);
    long long   readInt64        (std::basic_istream<char> &src);
    double      readFloat        (std::basic_istream<char> &src);
    float       readSingle       (std::basic_istream<char> &src);
    double      readDouble       (std::basic_istream<char> &src);
    std::string readDecimalString(std::basic_istream<char> &src);

    /*
    SSPAny readAny          (InputStream src) throws EOFException { return readAnyData          (src, readType(src)); }
    SSPAny readObject       (InputStream src) throws EOFException { return readObjectData       (src, readType(src)); }
    SSPAny readArray        (InputStream src) throws EOFException { return readArrayData        (src, readType(src)); }
    */

    class SSPInvalidDataException : public std::runtime_error {
    public:
        SSPInvalidDataException(const std::string& msg): std::runtime_error(msg) {};
    };

	namespace xml {

		using namespace std;

		const string XML_TAG_STRING   = "string"   ;
		const string XML_TAG_DECIMAL  = "decimal"  ;
		const string XML_TAG_INTEGER  = "int"      ;
		const string XML_TAG_FLOAT    = "float"    ;
		const string XML_TAG_OBJECT   = "object"   ;
		const string XML_TAG_ARRAY    = "array"    ;
		const string XML_TAG_BYTEARRAY= "bytearray";

		const string XML_ATTR_NAME    = "name"     ;
	}


}




#endif /* SSP_HELPER_HPP_ */
