#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AES128
#include <boost/test/unit_test.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include "AES128.hpp"

using namespace std;
using namespace boost;
using namespace Orion::Rigel;

BOOST_AUTO_TEST_CASE(TestCRC)
{
    {
        auto plainText = std::string(
            "\x00\x00\x00\x00" "\x00\x00\x00\x00"
            "\x00\x00\x00\x00" "\x00\x00\x00\x00"
            "\x00\x00\x00\x00" "\x00\x00\x00\x00"
            "\x00\x00\x00\x00" "\x00\x00\x00\x00",
            32
        );

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0x8a9136aa);
    }

    {
        auto plainText = std::string(
            "\xff\xff\xff\xff" "\xff\xff\xff\xff"
            "\xff\xff\xff\xff" "\xff\xff\xff\xff"
            "\xff\xff\xff\xff" "\xff\xff\xff\xff"
            "\xff\xff\xff\xff" "\xff\xff\xff\xff",
            32
        );

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0x62a8ab43);
    }

    {
        auto plainText = std::string(
            "\x00\x01\x02\x03" "\x04\x05\x06\x07"
            "\x08\x09\x0a\x0b" "\x0c\x0d\x0e\x0f"
            "\x10\x11\x12\x13" "\x14\x15\x16\x17"
            "\x18\x19\x1a\x1b" "\x1c\x1d\x1e\x1f",
            32
        );

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0x46dd794e);
    }

    {
        auto plainText = std::string(
            "\x1f\x1e\x1d\x1c" "\x1b\x1a\x19\x18"
            "\x17\x16\x15\x14" "\x13\x12\x11\x10"
            "\x0f\x0e\x0d\x0c" "\x0b\x0a\x09\x08"
            "\x07\x06\x05\x04" "\x03\x02\x01\x00",
            32
        );

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0x113fdb5c);
    }

    {
        auto plainText = std::string(
            "\x01\xc0\x00\x00" "\x00\x00\x00\x00"
            "\x00\x00\x00\x00" "\x00\x00\x00\x00"
            "\x14\x00\x00\x00" "\x00\x00\x04\x00"
            "\x00\x00\x00\x14" "\x00\x00\x00\x18"
            "\x28\x00\x00\x00" "\x00\x00\x00\x00"
            "\x02\x00\x00\x00" "\x00\x00\x00\x00",
            48
        );

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0xd9963a56);
    }

    {
        auto plainText = std::string("", 0);

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0x00000000);
    }

    {
        auto plainText = std::string("a", 1);

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0xc1d04330);
    }

    {
        auto plainText = std::string("abc", 3);

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0x364b3fb7);
    }

    {
        auto plainText = std::string("message digest", 14);

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0x02bd79d0);
    }

    {
        auto plainText = std::string("abcdefghijklmnopqrstuvwxyz", 26);

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0x9ee6ef25);
    }

    {
        auto plainText = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", 62);

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0xa245d57d);
    }

    {
        auto plainText = std::string("12345678901234567890123456789012345678901234567890123456789012345678901234567890", 80);

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0x477a6781);
    }

    {
        auto plainText = std::string("123456789", 9);

        auto C = AES128(0);
        auto CRC_CypherText = C.CTRProcess<true>(0, plainText);
        auto CRC = CRC_CypherText.first;

        BOOST_CHECK_EQUAL(CRC, 0xe3069283);
    }
}

BOOST_AUTO_TEST_CASE(TestEncrypt)
{
    // Single FullBlock test.
    {
        __uint128_t counter;
        __uint128_t key;

        memcpy(&counter,                "\x00\x00\x00\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01", sizeof (counter));
        memcpy(&key,                    "\xAE\x68\x52\xF8\x12\x10\x67\xCC\x4B\xF7\xA5\x76\x55\x77\xF3\x9E", sizeof (key));

        auto plainText    = std::string("\x53\x69\x6E\x67\x6C\x65\x20\x62\x6C\x6F\x63\x6B\x20\x6D\x73\x67", 16);
        auto expectedText = std::string("\xE4\x09\x5D\x4F\xB7\xA7\xB3\x79\x2D\x61\x75\xA3\x26\x13\x11\xB8", 16);

        auto C = AES128(key);
        auto CRC_CypherText = C.CTRProcess<true>(counter, plainText);
        auto cypherText = CRC_CypherText.second;

        BOOST_CHECK_EQUAL(cypherText, expectedText);
    }

    // PartialBlock test.
    {
        __uint128_t counter;
        __uint128_t key;

        memcpy(&counter,                "\x00\x00\x00\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01", sizeof (counter));
        memcpy(&key,                    "\xAE\x68\x52\xF8\x12\x10\x67\xCC\x4B\xF7\xA5\x76\x55\x77\xF3\x9E", sizeof (key));

        auto plainText    = std::string("\x53\x69\x6E\x67\x6C\x65\x20\x62\x6C\x6F\x63\x6B\x20\x6D", 14);
        auto expectedText = std::string("\xE4\x09\x5D\x4F\xB7\xA7\xB3\x79\x2D\x61\x75\xA3\x26\x13", 14);

        auto C = AES128(key);
        auto CRC_CypherText = C.CTRProcess<true>(counter, plainText);
        auto cypherText = CRC_CypherText.second;

        BOOST_CHECK_EQUAL(cypherText, expectedText);
    }

    // Double FullBlock test.
    {
        __uint128_t counter;
        __uint128_t key;

        memcpy(&counter,                "\x00\x6C\xB6\xDB\xC0\x54\x3B\x59\xDA\x48\xD9\x0B\x00\x00\x00\x01", sizeof (counter));
        memcpy(&key,                    "\x7E\x24\x06\x78\x17\xFA\xE0\xD7\x43\xD6\xCE\x1F\x32\x53\x91\x63", sizeof (key));

        auto plainText    = std::string("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 32);
        auto expectedText = std::string("\x51\x04\xA1\x06\x16\x8A\x72\xD9\x79\x0D\x41\xEE\x8E\xDA\xD3\x88\xEB\x2E\x1E\xFC\x46\xDA\x57\xC8\xFC\xE6\x30\xDF\x91\x41\xBE\x28", 32);

        auto C = AES128(key);
        auto CRC_CypherText = C.CTRProcess<true>(counter, plainText);
        auto cypherText = CRC_CypherText.second;

        BOOST_CHECK_EQUAL(cypherText, expectedText);
    }

}


