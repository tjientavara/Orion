/* Copyright 2018 Tjienta Vara
 * This file is part of Orion.
 *
 * Orion is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Orion is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Orion.  If not, see <http://www.gnu.org/licenses/>.
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BigInt
#include <boost/test/unit_test.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include "BigInt.hpp"

using namespace std;
using namespace boost;
using namespace Orion::Rigel;

BOOST_AUTO_TEST_CASE(TestStringInitialization)
{
    BOOST_CHECK_EQUAL(BigInt<2048>("0"), BigInt<2048>("0x0"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1"), BigInt<2048>("0x1"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10"), BigInt<2048>("0xa"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100"), BigInt<2048>("0x64"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000"), BigInt<2048>("0x3e8"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000"), BigInt<2048>("0x2710"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000"), BigInt<2048>("0x186a0"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000"), BigInt<2048>("0xf4240"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000"), BigInt<2048>("0x989680"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000"), BigInt<2048>("0x5f5e100"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000"), BigInt<2048>("0x3b9aca00"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000"), BigInt<2048>("0x2540be400"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000"), BigInt<2048>("0x174876e800"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000"), BigInt<2048>("0xe8d4a51000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000"), BigInt<2048>("0x9184e72a000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000"), BigInt<2048>("0x5af3107a4000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000"), BigInt<2048>("0x38d7ea4c68000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000"), BigInt<2048>("0x2386f26fc10000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000"), BigInt<2048>("0x16345785d8a0000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000"), BigInt<2048>("0xde0b6b3a7640000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000"), BigInt<2048>("0x8ac7230489e80000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000"), BigInt<2048>("0x56bc75e2d63100000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000"), BigInt<2048>("0x3635c9adc5dea00000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000000"), BigInt<2048>("0x21e19e0c9bab2400000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000000"), BigInt<2048>("0x152d02c7e14af6800000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000000"), BigInt<2048>("0xd3c21bcecceda1000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000000000"), BigInt<2048>("0x84595161401484a000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000000000"), BigInt<2048>("0x52b7d2dcc80cd2e4000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000000000"), BigInt<2048>("0x33b2e3c9fd0803ce8000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000000000000"), BigInt<2048>("0x204fce5e3e25026110000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000000000000"), BigInt<2048>("0x1431e0fae6d7217caa0000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000000000000"), BigInt<2048>("0xc9f2c9cd04674edea40000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000000000000000"), BigInt<2048>("0x7e37be2022c0914b2680000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000000000000000"), BigInt<2048>("0x4ee2d6d415b85acef8100000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000000000000000"), BigInt<2048>("0x314dc6448d9338c15b0a00000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000000000000000000"), BigInt<2048>("0x1ed09bead87c0378d8e6400000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000000000000000000"), BigInt<2048>("0x13426172c74d822b878fe800000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000000000000000000"), BigInt<2048>("0xc097ce7bc90715b34b9f1000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000000000000000000000"), BigInt<2048>("0x785ee10d5da46d900f436a000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000000000000000000000"), BigInt<2048>("0x4b3b4ca85a86c47a098a224000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000000000000000000000"), BigInt<2048>("0x2f050fe938943acc45f65568000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000000000000000000000000"), BigInt<2048>("0x1d6329f1c35ca4bfabb9f5610000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000000000000000000000000"), BigInt<2048>("0x125dfa371a19e6f7cb54395ca0000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000000000000000000000000"), BigInt<2048>("0xb7abc627050305adf14a3d9e40000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000000000000000000000000000"), BigInt<2048>("0x72cb5bd86321e38cb6ce6682e80000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000000000000000000000000000"), BigInt<2048>("0x47bf19673df52e37f2410011d100000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000000000000000000000000000"), BigInt<2048>("0x2cd76fe086b93ce2f768a00b22a00000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000000000000000000000000000000"), BigInt<2048>("0x1c06a5ec5433c60ddaa16406f5a400000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000000000000000000000000000000"), BigInt<2048>("0x118427b3b4a05bc8a8a4de845986800000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000000000000000000000000000000"), BigInt<2048>("0xaf298d050e4395d69670b12b7f41000000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("10000000000000000000000000000000000000000000000000"), BigInt<2048>("0x6d79f82328ea3da61e066ebb2f88a000000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("100000000000000000000000000000000000000000000000000"), BigInt<2048>("0x446c3b15f9926687d2c40534fdb564000000000000"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1000000000000000000000000000000000000000000000000000"), BigInt<2048>("0x2ac3a4edbbfb8014e3ba83411e915e8000000000000"));

    BOOST_CHECK_EQUAL(BigInt<2048>("1"), BigInt<2048>("0x1"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12"), BigInt<2048>("0xc"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123"), BigInt<2048>("0x7b"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234"), BigInt<2048>("0x4d2"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345"), BigInt<2048>("0x3039"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456"), BigInt<2048>("0x1e240"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567"), BigInt<2048>("0x12d687"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678"), BigInt<2048>("0xbc614e"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789"), BigInt<2048>("0x75bcd15"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890"), BigInt<2048>("0x499602d2"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901"), BigInt<2048>("0x2dfdc1c35"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012"), BigInt<2048>("0x1cbe991a14"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123"), BigInt<2048>("0x11f71fb04cb"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234"), BigInt<2048>("0xb3a73ce2ff2"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345"), BigInt<2048>("0x7048860ddf79"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456"), BigInt<2048>("0x462d53c8abac0"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567"), BigInt<2048>("0x2bdc545d6b4b87"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678"), BigInt<2048>("0x1b69b4ba630f34e"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789"), BigInt<2048>("0x112210f47de98115"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567890"), BigInt<2048>("0xab54a98ceb1f0ad2"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678901"), BigInt<2048>("0x6b14e9f812f366c35"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789012"), BigInt<2048>("0x42ed123b0bd8203a14"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567890123"), BigInt<2048>("0x29d42b64e76714244cb"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678901234"), BigInt<2048>("0x1a249b1f10a06c96aff2"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789012345"), BigInt<2048>("0x1056e0f36a6443de2df79"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567890123456"), BigInt<2048>("0xa364c98227eaa6adcbac0"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678901234567"), BigInt<2048>("0x661efdf158f2a82c9f4b87"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789012345678"), BigInt<2048>("0x3fd35eb6d797a91be38f34e"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567890123456789"), BigInt<2048>("0x27e41b3246bec9b16e398115"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678901234567890"), BigInt<2048>("0x18ee90ff6c373e0ee4e3f0ad2"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789012345678901"), BigInt<2048>("0xf951a9fa3a286c94f0e766c35"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567890123456789012"), BigInt<2048>("0x9bd30a3c645943dd1690a03a14"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678901234567890123"), BigInt<2048>("0x6163e665beb7ca6a2e1a64244cb"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789012345678901234"), BigInt<2048>("0x3cde6fff9732de825cd07e96aff2"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567890123456789012345"), BigInt<2048>("0x260b05ffbe7fcb117a024f1e2df79"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678901234567890123456"), BigInt<2048>("0x17c6e3bfd70fdeeaec417172dcbac0"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789012345678901234567"), BigInt<2048>("0xedc4e57e669eb52d3a8e6e7c9f4b87"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567890123456789012345678"), BigInt<2048>("0x949b0f6f0023313c4499050de38f34e"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678901234567890123456789"), BigInt<2048>("0x5ce0e9a56015fec5aadfa328ae398115"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789012345678901234567890"), BigInt<2048>("0x3a0c92075c0dbf3b8acbc5f96ce3f0ad2"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567890123456789012345678901"), BigInt<2048>("0x2447db449988978536bf5bbbe40e766c35"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678901234567890123456789012"), BigInt<2048>("0x16ace90adff55eb3423799556e890a03a14"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789012345678901234567890123"), BigInt<2048>("0xe2c11a6cbf95b300962bfd56515a64244cb"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567890123456789012345678901234"), BigInt<2048>("0x8db8b083f7bd8fe05ddb7e55f2d87e96aff2"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678901234567890123456789012345"), BigInt<2048>("0x58936e527ad679ec3aa92ef5b7c74f1e2df79"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789012345678901234567890123456"), BigInt<2048>("0x375c24f38cc60c33a4a9bd5992dc9172dcbac0"));
    BOOST_CHECK_EQUAL(BigInt<2048>("12345678901234567890123456789012345678901234567"), BigInt<2048>("0x2299971837fbc7a046ea1657fbc9dae7c9f4b87"));
    BOOST_CHECK_EQUAL(BigInt<2048>("123456789012345678901234567890123456789012345678"), BigInt<2048>("0x159ffe6f22fd5cc42c524df6fd5e28d0de38f34e"));
    BOOST_CHECK_EQUAL(BigInt<2048>("1234567890123456789012345678901234567890123456789"), BigInt<2048>("0xd83ff0575de59fa9bb370ba5e5ad9828ae398115"));
}

BOOST_AUTO_TEST_CASE(TestCompare)
{
    BOOST_CHECK(!(BigInt<128>("1") >= BigInt<128>("2")));
    BOOST_CHECK(  BigInt<128>("2") >= BigInt<128>("2"));
    BOOST_CHECK(  BigInt<128>("3") >= BigInt<128>("2"));

    BOOST_CHECK(  BigInt<128>("1") <= BigInt<128>("2"));
    BOOST_CHECK(  BigInt<128>("2") <= BigInt<128>("2"));
    BOOST_CHECK(!(BigInt<128>("3") <= BigInt<128>("2")));

    BOOST_CHECK(!(BigInt<128>("1") > BigInt<128>("2")));
    BOOST_CHECK(!(BigInt<128>("2") > BigInt<128>("2")));
    BOOST_CHECK(  BigInt<128>("3") > BigInt<128>("2"));

    BOOST_CHECK(  BigInt<128>("1") < BigInt<128>("2"));
    BOOST_CHECK(!(BigInt<128>("2") < BigInt<128>("2")));
    BOOST_CHECK(!(BigInt<128>("3") < BigInt<128>("2")));

    BOOST_CHECK(!(BigInt<128>("1") == BigInt<128>("2")));
    BOOST_CHECK(  BigInt<128>("2") == BigInt<128>("2"));
    BOOST_CHECK(!(BigInt<128>("3") == BigInt<128>("2")));

    BOOST_CHECK(  BigInt<128>("1") != BigInt<128>("2"));
    BOOST_CHECK(!(BigInt<128>("2") != BigInt<128>("2")));
    BOOST_CHECK(  BigInt<128>("3") != BigInt<128>("2"));
}

BOOST_AUTO_TEST_CASE(TestRandomInitialization)
{
	// This is a non-deterministic random test.
	// We do a lot of tests and see if on average each bit toggles.
	const int NR_BITS = 4096;
	const int NR_TESTS = 1000;

	// Create a set of random numbers.
	vector<BigInt<NR_BITS>>	results;

	for (int i = 0; i < NR_TESTS; i++) {
		auto result = BigIntRandom<NR_BITS>();

        // Check if bits change within in a single result.
        int bitCount = 0;
        for (int bitNr = 0; bitNr < NR_BITS; bitNr++) {
			if (result.getBit(bitNr)) {
				bitCount++;
			}
        }
		BOOST_CHECK(bitCount >= (NR_BITS * 0.3) && bitCount <= (NR_BITS * 0.7));

		results.push_back(result);
	}

    // Check over multiple result that the bits change.
	for (int bitNr = 0; bitNr < NR_BITS; bitNr++) {
		int bitCount = 0;
		for (auto &result: results) {
			if (result.getBit(bitNr)) {
				bitCount++;
			}
		}
		BOOST_CHECK(bitCount >= (NR_TESTS * 0.3) && bitCount <= (NR_TESTS * 0.7));
	}
}

BOOST_AUTO_TEST_CASE(TestMultiplication)
{
    BOOST_CHECK_EQUAL(
        BigInt<256>("1000000000000000000000000000000") * BigInt<256>("1000000000000000000000000000000"),
        BigInt<256>("1000000000000000000000000000000000000000000000000000000000000")
    );

    BOOST_CHECK_EQUAL(
        BigInt<128>("1234567890123456789012345678901") * BigInt<256>("1000000000000000000000000000000"),
        BigInt<256>("1234567890123456789012345678901000000000000000000000000000000")
    );
}

BOOST_AUTO_TEST_CASE(TestAddition)
{
    BOOST_CHECK_EQUAL(
        BigInt<256>("1000000000000000000000000000000") +
        BigInt<256>("1000000000000000000000000000000"),
        BigInt<256>("2000000000000000000000000000000")
    );

    BOOST_CHECK_EQUAL(
        BigInt<128>("1234567890123456789012345678901") +
        BigInt<256>("1000000000000000000000000000000"),
        BigInt<256>("2234567890123456789012345678901")
    );
}

BOOST_AUTO_TEST_CASE(TestSubtract)
{
    BOOST_CHECK_EQUAL(
        BigInt<256>("1000000000000000000000000000000") -
        BigInt<256>("1000000000000000000000000000000"),
        BigInt<256>("0")
    );

    BOOST_CHECK_EQUAL(
        BigInt<128>("1234567890123456789012345678901") -
        BigInt<128>("1000000000000000000000000000000"),
        BigInt<128>( "234567890123456789012345678901")
    );
}

BOOST_AUTO_TEST_CASE(TestDivision)
{
    {
        auto scaledOne = BigIntHighbit<129>();
        auto a = BigInt<64>(10);
        BigInt<128> r;
        r.initDivision(scaledOne, a);

        BOOST_CHECK_EQUAL(
            r,
            BigInt<128>("34028236692093846346337460743176821145")
        );
    }

    BOOST_CHECK_EQUAL(
        BigInt<256>("1234567890123456789012345678901") /
        BigInt<256>("1000000000000000000000000000"),
        BigInt<256>("1234")
    );

    BOOST_CHECK_EQUAL(
        BigInt<256>("1234567890123456789012345678901") %
        BigInt<256>("1000000000000000000000000000"),
        BigInt<256>("567890123456789012345678901")
    );
}

BOOST_AUTO_TEST_CASE(TestBarretReduction)
{
    {
        auto br = BarretReduction<129>(BigInt<128>("36893488147422849766"));
        auto x = BigInt<128>("34894070664390072009");
        BOOST_CHECK_EQUAL(
            br.modulo(x * x),
            BigInt<128>("17757749993113403289")
        );
    }

    {
        auto br = BarretReduction<65>(BigInt<64>("10"));
        BOOST_CHECK_EQUAL(
            br.modulo(BigInt<64>(9)),
            BigInt<64>(9)
        );
    }
}

BOOST_AUTO_TEST_CASE(TestModularPower)
{
    BOOST_CHECK_EQUAL(
        BigInt<64>(3).modularPower(BigInt<64>(2), BigInt<64>(10)),
        BigInt<64>(9)
    );

    BOOST_CHECK_EQUAL(
        BigInt<64>(3).modularPower(BigInt<64>(12345), BigInt<64>(10)),
        BigInt<64>("3")
    );

    BOOST_CHECK_EQUAL(
        BigInt<128>(3).modularPower(BigInt<128>(12345), BigInt<128>("36893488147422849766")),
        BigInt<128>("24918863617337492911")
    );

    BOOST_CHECK_EQUAL(
        BigInt<2048>(2).modularPower(BigInt<2048>("0x1f"), BigInt<2048>(
            "0xFFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DD"
              "EF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED"
              "EE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F"
              "83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA237327FFFFFFFFFFFFFFFF"
        )),
        BigInt<2048>("2147483648")
    );

    BOOST_CHECK_EQUAL(
        BigInt<2048>(2).modularPower(BigInt<2048>("0x20"), BigInt<2048>(
            "0xFFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DD"
              "EF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED"
              "EE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F"
              "83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA237327FFFFFFFFFFFFFFFF"
        )),
        BigInt<2048>("4294967296")
    );

    BOOST_CHECK_EQUAL(
        BigInt<2048>(2).modularPower(BigInt<2048>("0x123456789012345678901234567890"), BigInt<2048>(
            "0xFFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DD"
              "EF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED"
              "EE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F"
              "83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA237327FFFFFFFFFFFFFFFF"
        )),
        BigInt<2048>(
            "23825202221033527095845266879302780519801252119995682766205272453918410022371030866557173776877007"
            "45979171468319836038597443166132103939456403029009374802199945677756130982355791093110688942270938"
            "70583641331550576059235475467510911262612715058758495732325446082628766711467597200266516763855336"
            "26735252247197742426858405885317124895348963675484492866148153425606105392094637696671375693487150"
            "43966309599053088006556616133052662019451592674047544491011840110002437"
        )
    );

    // Regression test 2018-05-30, overflow.
    BOOST_CHECK_EQUAL(
        BigInt<1536>("2").modularPower(
            BigInt<1536>("0xdae8c2d14f1435859a159a79b116da24621e064336d9a042c44f9105cc64a2fb775e470c6611f1c1f56955a9dd117a78d4ef56019748ee38cb04562ab117fdb0b68d768c62cd4f7f80e7a2533a42ca38a94c49fab0045fa212f928cd9d0c739e706d76b3153e4ad5489528db8cde820633ef4f922424aeac833d1ba34273a03bb9113e125f2aaeaea9e41b4f4f77ff6741a80e9f43ba2650022cd818c31c398f3e302acb7dd6da69df5bc41d014876f2c8419fa8f46c0856df8b3543885f47e0"),
            BigInt<1536>("0xffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd129024e088a67cc74020bbea63b139b22514a08798e3404ddef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7edee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3dc2007cb8a163bf0598da48361c55d39a69163fa8fd24cf5f83655d23dca3ad961c62f356208552bb9ed529077096966d670c354e4abc9804f1746c08ca237327ffffffffffffffff")
        ),
        BigInt<1536>("0x327844426003b125842c2218acd7ca033bb3289534a2083050e4b167a79007bdffade0fb2bc29df19cbe6188c5bca8c0984e17e691e875a04269df2050ecce8ab718e1e46a7008031b41da8499c7e7fd8371070d49dd3859a820805df5b147a3629904ef29ff742ad1b07b27e31c6d6d4a924e6eed6d8f342dfe2d511ae3e9f8d9c2e5eac51b1e3da75fb6b9a4212c6edd4bfb5217cbd0a44465e6c758ba380834cd90f2df13c8fc470c007932d104a66f4d797d8ca861e1baf4d77b86d7251c")
    );
}



