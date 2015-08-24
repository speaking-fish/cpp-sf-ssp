/*
 * sfp_common.cpp
 *
 */

#include <sstream>
#include "sfp_common.hpp"

namespace sfp {

	void internalWriteBuf(std::basic_ostream<char> &dest, const int offset, const int size, char const * const buffer) {
		dest.write(&(buffer[offset]), size);
	}

	void internalWriteBuf(std::basic_ostream<char> &dest, const int size, char const * const buffer) {
		dest.write(buffer, size);
	}

	void internalWriteChar(std::basic_ostream<char> &dest, char value) {
		dest.put(value);
		//(*dest) << value;
	}

	char internalRead(std::basic_istream<char> &src) {
		char result;
		//try {
			//if(src.get(result)) {

			if(0 == src.readsome(&result, 1)) {
				throw EOFException();
			}
		//catch (istream::failure &e) {
		//}
		return result;
	}

    void internalRead(std::basic_istream<char> &src, int offset, int size, char* buffer) {
        if(size <= 0) {
            return;
        }

        while(true) {
            const int count = src.readsome(&(buffer[offset]), size);
            if(count == size) {
                break;
            }

            if(count <= 0) {
                throw EOFException();
            }
            offset+= count;
            size  -= count;
        }
    }

    void internalRead(std::basic_istream<char> &src, int size, std::basic_ostream<char> &dest) {
        while(0 < size--) {
            internalWriteChar(dest, internalRead(src));
        }
    }

    /*
    void internalWriteBuf(std::basic_ostream<char>* const dest, const int offset, const int size, char const * const buffer) {
        dest->write(&(buffer[offset]), size);
    }

    void internalWriteBuf(std::basic_ostream<char>* const dest, const int size, char const * const buffer) {
        dest->write(buffer, size);
    }

    void internalWriteChar(std::basic_ostream<char>* const dest, char value) {
        dest->put(value);
        //(*dest) << value;
    }

    char internalRead(std::basic_istream<char>* const src) {
        char result;
        //try {
            if(src->get(result)) {
                throw EOFException();
            }
        //catch (istream::failure &e) {
        //}
        return result;
    }

    void internalRead(std::basic_istream<char>* const src, int offset, int size, char* const buffer) {
        if(size <= 0) {
            return;
        }

        while(true) {
            const int count = src->readsome(&(buffer[offset]), size);
            if(count == size) {
                break;
            }

            if(count <= 0) {
                throw EOFException();
            }
            offset+= count;
            size  -= count;
        }
    }

    void internalRead(std::basic_istream<char>* const src, int size, std::basic_ostream<char> &dest) {
        while(0 < size--) {
            internalWriteChar(&dest, internalRead(src));
        }
    }
    */

    void writeFrameBound(std::basic_ostream<char> &dest) {
        internalWriteChar(dest, SFP_FRAME_BOUND);
    }

    void writeData(std::basic_ostream<char> &dest, int offset, const int size, char const * const buffer) {
        if(size <= 0) {
            return;
        }

        int startChunk = offset;
        int chunkSize  = 0     ;
        int totalLeft  = size  ;
        while(0 < totalLeft) {
            ++chunkSize;
            if((SFP_FRAME_BOUND  == buffer[offset])
            || (SFP_ESCAPE_START == buffer[offset])
            ) {
                internalWriteBuf(dest, startChunk, chunkSize, buffer);
                internalWriteChar(dest, SFP_ESCAPE_START);
                if(SFP_FRAME_BOUND  == buffer[offset]) {
                    internalWriteChar(dest, SFP_ESCAPE_COMMAND_ECHO_FRAME_BOUND);
                } else {
                    internalWriteChar(dest, SFP_ESCAPE_COMMAND_ECHO_ESCAPE);
                }
                totalLeft -= chunkSize;
                startChunk = offset + 1;
                chunkSize  = 0;
            }
            ++offset;
        }
        if(0 < chunkSize) {
            internalWriteBuf(dest, startChunk, chunkSize, buffer);
        }
    }

    void writeFrame(std::basic_ostream<char> &dest, const int offset, const int size, char const * const buffer) {
        writeFrameBound(dest);
        writeData      (dest, offset, size, buffer);
        writeFrameBound(dest);
    }

    void readRawFrame(std::basic_istream<char> &src, std::basic_ostream<char> &dest) {
        while(true) {
            const char test = internalRead(src);
            if(SFP_FRAME_BOUND == test) {
                return;
            }
            dest << test;
        }
    }
/*
    template <class T>
        T* readRawFrame(std::basic_istream<char>* const src, T &dest) {
            readRawFrameStream(src, dest);
            return dest;
        }
*/

    void readFromRawFrame(char const * const src, int size, std::basic_ostream<char> &dest) { //todo: java:do not damage result inplace!
        int srcAnchor  = 0;
      //int destAnchor = 0;
        int index      = 0;
        while(index < size) {
            if(SFP_ESCAPE_START == src[index]) {
                //System.arraycopy(result, srcAnchor, result, destAnchor, index - srcAnchor);
                internalWriteBuf(dest, srcAnchor, index - srcAnchor, src);
              //destAnchor+= index - srcAnchor;
                ++index;
                if(index < size) {
                    throw new SFPInvalidPacketException("Invalid packet: Terminated escape");
                }
                if(SFP_ESCAPE_COMMAND_ECHO_FRAME_BOUND == src[index]) {
                    //result[destAnchor] = SFP_FRAME_BOUND;
                    internalWriteChar(dest, SFP_FRAME_BOUND);
                    //destAnchor+= 1;
                } else if(SFP_ESCAPE_COMMAND_ECHO_ESCAPE == src[index]) {
                    internalWriteChar(dest, SFP_ESCAPE_START);
                    //destAnchor+= 1;
                } else {
                    throw SFPInvalidPacketException("Invalid packet: Illegal escape echo code");
                }
              srcAnchor = index + 1;
            } else if(SFP_FRAME_BOUND == src[index]) { //todo: others: SFP_FRAME_BOUND here!
                throw SFPInvalidPacketException("Invalid packet: Internal error: not filtered BND.");
            }
            ++index;
        }
        if(srcAnchor < index) {
            //System.arraycopy(result, srcAnchor, result, destAnchor, index - srcAnchor);
            internalWriteBuf(dest, srcAnchor, index - srcAnchor, src);
            //destAnchor+= index - srcAnchor;
        }
        /*
        if(destAnchor < result.length) {
            return Arrays.copyOf(result, destAnchor);
        } else {
            return result;
        }
        */
    }

    void readFromRawFrame(std::basic_istream<char> &src, std::basic_ostream<char> &dest) {
      //int srcAnchor  = 0;
      //int destAnchor = 0;
      //int index      = 0;
        while(!src.eof()) {
            char temp = src.get();
            if(src.eof())
                return;

            if(SFP_ESCAPE_START == temp) {
                //System.arraycopy(result, srcAnchor, result, destAnchor, index - srcAnchor);
                //internalWrite(&dest, tempsrcAnchor, index - srcAnchor, src);
              //destAnchor+= index - srcAnchor;
                //++index;
                //if(index < size) {
                //    throw new SFPInvalidPacketException("Invalid packet: Terminated escape");
                //}
                temp = src.get();
                if(src.eof())
                    throw SFPInvalidPacketException("Invalid packet: Terminated escape");

                if(SFP_ESCAPE_COMMAND_ECHO_FRAME_BOUND == temp) {
                    //result[destAnchor] = SFP_FRAME_BOUND;
                    internalWriteChar(dest, SFP_FRAME_BOUND);
                    //destAnchor+= 1;
                } else if(SFP_ESCAPE_COMMAND_ECHO_ESCAPE == temp) {
                    internalWriteChar(dest, SFP_ESCAPE_START);
                    //destAnchor+= 1;
                } else {
                    throw SFPInvalidPacketException("Invalid packet: Illegal escape echo code");
                }
              //srcAnchor = index + 1;
            } else if(SFP_FRAME_BOUND == temp) { //todo: others: SFP_FRAME_BOUND here!
                throw SFPInvalidPacketException("Invalid packet: Internal error: not filtered BND.");
            } {
                internalWriteChar(dest, temp);
            }
            //++index;
        }
        /*
        if(srcAnchor < index) {
            //System.arraycopy(result, srcAnchor, result, destAnchor, index - srcAnchor);
            internalWrite(&dest, srcAnchor, index - srcAnchor, src);
            //destAnchor+= index - srcAnchor;
        }
        */
        /*
        if(destAnchor < result.length) {
            return Arrays.copyOf(result, destAnchor);
        } else {
            return result;
        }
        */
    }

    void readFrame(std::basic_istream<char> &src, std::basic_ostream<char> &dest) {
        std::stringstream tmp;
        readRawFrame(src, tmp);
        tmp.seekg(0, tmp.beg);
        //readFromRawFrame(tmp.rdbuf()->eback(), tmp.rdbuf()->in_avail(), dest);
        readFromRawFrame(tmp, dest);
    }

}


