/*
 * sfp_common.hpp
 *
 *  Created on: 14 авг. 2014 г.
 *      Author: borka
 */

#ifndef SFP_COMMON_HPP_
#define SFP_COMMON_HPP_

#include <sstream>
#include <stdexcept>

namespace sfp {

	class EOFException : public std::runtime_error {
	public:
		EOFException(): std::runtime_error("SFP:EOF exception") {};
	};

	void internalWriteBuf(std::basic_ostream<char> &dest, const int offset, const int size, char const * const buffer);

	void internalWriteBuf(std::basic_ostream<char> &dest, const int size, char const * const buffer);

	void internalWriteChar(std::basic_ostream<char> &dest, char value);

	char internalRead(std::basic_istream<char> &src);

    void internalRead(std::basic_istream<char> &src, int offset, int size, char* const buffer);

    void internalRead(std::basic_istream<char> &src, int size, std::basic_ostream<char> &dest);


    const char SFP_FRAME_BOUND                    = (char) 0xF0; // bnd
    const char SFP_ESCAPE_START                   = (char) 0xF1; // esc
    const char SFP_ESCAPE_COMMAND_MIN             =           0; // esc 00
    const char SFP_ESCAPE_COMMAND_ECHO_FRAME_BOUND=        0x00; // esc 00
    const char SFP_ESCAPE_COMMAND_ECHO_ESCAPE     =        0x01; // esc 01
    const char SFP_ESCAPE_COMMAND_MAX             =        0x0F; // esc 0F

    class SFPInvalidPacketException : public std::runtime_error {
    public:
        SFPInvalidPacketException(const std::string& msg): std::runtime_error(msg) {};
    };

/*
    void internalWriteBuf (std::basic_ostream<char>* const dest, const int offset, const int size, char const * const buffer);

    void internalWriteBuf (std::basic_ostream<char>* const dest,                   const int size, char const * const buffer);

    void internalWriteChar(std::basic_ostream<char>* const dest, const char value);

    char internalRead(std::basic_istream<char>* const src);

    void internalRead(std::basic_istream<char>* const src, int offset, int size, char* const buffer);

    void internalRead(std::basic_istream<char>* const src, const int size, std::basic_ostream<char> &dest);
*/
    void writeFrameBound(std::basic_ostream<char> &dest);

    void writeData(std::basic_ostream<char> &dest, int offset, const int size, char const * const buffer);

    void writeFrame(std::basic_ostream<char> &dest, const int offset, const int size, char const * const buffer);

    void readRawFrame(std::basic_istream<char> &src, std::basic_ostream<char> &dest);

/*
    template <class T>
        T* readRawFrame(std::basic_istream<char>* const src, T &dest) {
            readRawFrameStream(src, dest);
            return dest;
        }
*/

    void readFromRawFrame(char const * const src, int size, std::basic_ostream<char> &dest); //todo: java:do not damage result inplace!

    void readFromRawFrame(std::basic_istream<char> &src, std::basic_ostream<char> &dest);

    void readFrame(std::basic_istream<char> &src, std::basic_ostream<char> &dest);

}

#endif /* SFP_COMMON_HPP_ */
