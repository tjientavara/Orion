
namespace Orion {
namespace Rigel {

/** Rigel Serial Object Notation.
 * This namespace includes functions for encoding and decoding C++ objects
 * into RSON binary format.
 *
 * Documentation for RSON binary format can be found here: [RSON.md](RSON.md).
 */
namespace RSON {

const char MARK_CODE = 0x00;
const char NONE_CODE = 0x10;
const char TRUE_CODE = 0x11;
const char FALSE_CODE = 0x12;
const char LIST_CODE = 0x13;
const char DICTIONARY_CODE = 0x14;
const char DECIMAL_FLOAT_CODE = 0x15;
const char BINARY_FLOAT_CODE = 0x16;
const char BYTE_ARRAY_CODE = 0x17;
const char UTF8_STRING_CODE = 0x18;
const char RESERVED1_CODE = 0x19;
const char RESERVED2_CODE = 0x1a;

};};};