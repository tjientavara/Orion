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
#pragma once

#include "int_utils.hpp"

#include <cstdint>
#include <utility>
#include <string>
#include <algorithm>
#include <boost/exception/all.hpp>
#include <string.h>
#include <emmintrin.h>
#include <nmmintrin.h>
#include <smmintrin.h>
#include <wmmintrin.h>
#include <xmmintrin.h>

namespace Orion {
namespace Rigel {

struct aes128_crc_location_error: virtual boost::exception, virtual std::exception {};

/** Implementation of the CTR-mode of the AES-128 encryption algorithm.
 * This implemenation is designed to run on Intel Broadwell or later CPUs.
 *
 * It will run 8 blocks of 128-bits in parallel, to fill the CPU pipeline.
 */
class AES128 {
    __uint128_t key;
    __uint128_t keyRounds[11];

    template<int BLOCK_NR>
    static __m128i Round0(__m128i &counter, __m128i key, size_t nrBlocks)
    {
        __m128i cypher;

        if (BLOCK_NR < nrBlocks) {
            cypher = _mm_xor_si128(counter, key);
            counter = mm_inc_si128(counter);
        }
        return cypher;
    }

    template<bool ENCRYPT, int BLOCK_NR>
    static inline uint32_t XorFullBlock(uint32_t CRC, size_t nrBlocks, __uint128_t *dst, const __uint128_t *src, __m128i cypher)
    {
        if (BLOCK_NR < nrBlocks) {
            auto block = _mm_load_si128(reinterpret_cast<const __m128i *>(src));

            if (ENCRYPT) {
                auto blockLo = _mm_cvtsi128_si64(block);
                auto blockHi = _mm_extract_epi64(block, 1);
                CRC = _mm_crc32_u64(CRC, blockLo);
                CRC = _mm_crc32_u64(CRC, blockHi);

                block = _mm_xor_si128(block, cypher);
            } else {
                block = _mm_xor_si128(block, cypher);

                auto blockLo = _mm_cvtsi128_si64(block);
                auto blockHi = _mm_extract_epi64(block, 1);

                CRC = _mm_crc32_u64(CRC, blockLo);
                CRC = _mm_crc32_u64(CRC, blockHi);
            }

            _mm_store_si128(reinterpret_cast<__m128i *>(dst), block);
        }
        return CRC;
    }

    template<int RCON>
    static inline __m128i KeyExpansion(__m128i prev_key)
    {
        // aeskeyassist xmm2 = xmm1, RCON
        auto tmp1 = _mm_aeskeygenassist_si128(prev_key, RCON);

        // pshufd xmm2 = xmm2, 0xff
        auto tmp2 = _mm_shuffle_epi32(tmp1, 0xff);

        // vpslldq xmm3 = xmm1, 0x4
        auto tmp3 = _mm_slli_si128(prev_key, 4);

        // pxor xmm1 = xmm1, xmm3
        auto tmp4 = _mm_xor_si128(prev_key, tmp3);

        // vpslldq xmm3 = xmm1, 0x4
        auto tmp5 = _mm_slli_si128(tmp4, 4);

        // pxor xmm1 = xmm1, xmm3
        auto tmp6 = _mm_xor_si128(tmp4, tmp5);

        // vpslldq xmm3 = xmm1, 0x4
        auto tmp7 = _mm_slli_si128(tmp6, 4);

        // pxor xmm1 = xmm1, xmm3
        auto tmp8 = _mm_xor_si128(tmp6, tmp7);

        // pxor xmm1 = xmm1, xmm2 
        auto key = _mm_xor_si128(tmp8, tmp2);
        return key;
    }

    /** Process a buffer of up to a full block.
     * This function executed XOR and CRC calculation byte-by-byte.
     * Therefor it can ignore the CRC in the encrypted data, or end
     * early without readingt src or modifying dst beyond their size.
     *
     * @param ENCRYPT true to encrypt, false to decrypt.
     * @param CRC32_LOCATION location of the CRC-32C to ignore during decrypting.
     * @param CRC The CRC calculated from a previous call.
     * @param counter Counter value incremented by 1.
     * @param dst Destination buffer. dst and src may alias.
     * @param src Source buffer. dst and src may alias.
     * @param size Number of bytes to process. size must be between 1 and 16 (inclusive).
     * @return CRC-32C Result of the plain-text data.
     */
    template<bool ENCRYPT, ssize_t CRC32_LOCATION=-1>
    uint32_t CTRProcessPartialBlock(uint32_t CRC, __m128i &counter, __uint128_t *dst, const __uint128_t *src, size_t size) const
    {
        auto mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[0]));
        auto cypher = AES128::Round0<0>(counter, mm_key, 1);

        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[1]));
        cypher = _mm_aesenc_si128(cypher, mm_key);
        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[2]));
        cypher = _mm_aesenc_si128(cypher, mm_key);
        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[3]));
        cypher = _mm_aesenc_si128(cypher, mm_key);
        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[4]));
        cypher = _mm_aesenc_si128(cypher, mm_key);
        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[5]));
        cypher = _mm_aesenc_si128(cypher, mm_key);
        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[6]));
        cypher = _mm_aesenc_si128(cypher, mm_key);
        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[7]));
        cypher = _mm_aesenc_si128(cypher, mm_key);
        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[8]));
        cypher = _mm_aesenc_si128(cypher, mm_key);
        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[9]));
        cypher = _mm_aesenc_si128(cypher, mm_key);
        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[10]));
        cypher = _mm_aesenclast_si128(cypher, mm_key);

        __uint128_t cypher128;
        auto cypher8 = reinterpret_cast<const uint8_t *>(&cypher128);
        auto src8 = reinterpret_cast<const uint8_t *>(src);
        auto dst8 = reinterpret_cast<uint8_t *>(dst);

        _mm_store_si128(reinterpret_cast<__m128i *>(&cypher128), cypher);
        for (size_t i = 0; i < size; i++) {
            auto byte = src8[i];

            if (ENCRYPT) {
                CRC = _mm_crc32_u8(CRC, byte);
                byte ^= cypher8[i];

            } else {
                byte ^= cypher8[i];
                if (
                    (CRC32_LOCATION >= 0) &&
                    (i >= static_cast<size_t>(CRC32_LOCATION)) &&
                    (i < static_cast<size_t>(CRC32_LOCATION) * sizeof (uint32_t))
                ) {
                    // Ignore the CRC that was encrypted.
                    CRC = _mm_crc32_u8(CRC, 0);
                } else {
                    CRC = _mm_crc32_u8(CRC, byte);
                }
            }

            dst8[i] = byte;
        }

        return CRC;
    }

    /** Process a buffer of up to 8 128-bit blocks in parralel.
     *
     * @param ENCRYPT true if encrypting, false if decrypting.
     * @param SCRUB_CRC Don't take the CRC in the encrypted message into account
     *        when calculating the CRC. The CRC in the encrypted message is located
     *        in the last 32-bit word of the first 128-bit block.
     * @param CRC The CRC calculated from a previous call.
     * @param counter Counter value incremented by the number of blocks processed.
     * @param dst Destination buffer. dst and src may alias.
     * @param src Source buffer. dst and src may alias.
     * @param nrBlocks Number of 128-bit blocks to process. nrBlocks must be between 1 and 8 (inclusive).
     * @return CRC-32C Result of the plain-text data.
     */
    template<bool ENCRYPT>
    uint32_t CTRProcess8FullBlocks(uint32_t CRC, __m128i &counter, __uint128_t *dst, const __uint128_t *src, size_t nrBlocks) const
    {
        auto mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[0]));\
        auto cypher0 = AES128::Round0<0>(counter, mm_key, nrBlocks);
        auto cypher1 = AES128::Round0<1>(counter, mm_key, nrBlocks);
        auto cypher2 = AES128::Round0<2>(counter, mm_key, nrBlocks);
        auto cypher3 = AES128::Round0<3>(counter, mm_key, nrBlocks);
        auto cypher4 = AES128::Round0<4>(counter, mm_key, nrBlocks);
        auto cypher5 = AES128::Round0<5>(counter, mm_key, nrBlocks);
        auto cypher6 = AES128::Round0<6>(counter, mm_key, nrBlocks);
        auto cypher7 = AES128::Round0<7>(counter, mm_key, nrBlocks);

#define AES128_ROUND(instruction, ROUND)\
        mm_key = _mm_load_si128(reinterpret_cast<const __m128i *>(&keyRounds[ROUND]));\
        switch (nrBlocks) {\
        case 8: cypher7 = instruction(cypher7, mm_key);\
        case 7: cypher6 = instruction(cypher6, mm_key);\
        case 6: cypher5 = instruction(cypher5, mm_key);\
        case 5: cypher4 = instruction(cypher4, mm_key);\
        case 4: cypher3 = instruction(cypher3, mm_key);\
        case 3: cypher2 = instruction(cypher2, mm_key);\
        case 2: cypher1 = instruction(cypher1, mm_key);\
        case 1: cypher0 = instruction(cypher0, mm_key);\
        }

        AES128_ROUND(_mm_aesenc_si128,     1);
        AES128_ROUND(_mm_aesenc_si128,     2);
        AES128_ROUND(_mm_aesenc_si128,     3);
        AES128_ROUND(_mm_aesenc_si128,     4);
        AES128_ROUND(_mm_aesenc_si128,     5);
        AES128_ROUND(_mm_aesenc_si128,     6);
        AES128_ROUND(_mm_aesenc_si128,     7);
        AES128_ROUND(_mm_aesenc_si128,     8);
        AES128_ROUND(_mm_aesenc_si128,     9);
        AES128_ROUND(_mm_aesenclast_si128, 10);
#undef AES128_ROUND

        CRC = AES128::XorFullBlock<ENCRYPT, 0>(CRC, nrBlocks, &dst[0], &src[0], cypher0);
        CRC = AES128::XorFullBlock<ENCRYPT, 1>(CRC, nrBlocks, &dst[1], &src[1], cypher1);
        CRC = AES128::XorFullBlock<ENCRYPT, 2>(CRC, nrBlocks, &dst[2], &src[2], cypher2);
        CRC = AES128::XorFullBlock<ENCRYPT, 3>(CRC, nrBlocks, &dst[3], &src[3], cypher3);
        CRC = AES128::XorFullBlock<ENCRYPT, 4>(CRC, nrBlocks, &dst[4], &src[4], cypher4);
        CRC = AES128::XorFullBlock<ENCRYPT, 5>(CRC, nrBlocks, &dst[5], &src[5], cypher5);
        CRC = AES128::XorFullBlock<ENCRYPT, 6>(CRC, nrBlocks, &dst[6], &src[6], cypher6);
        CRC = AES128::XorFullBlock<ENCRYPT, 7>(CRC, nrBlocks, &dst[7], &src[7], cypher7);
        return CRC;
    }

public:
    /** Constructor
     * @param key 128-bit AES-key.
     */
    AES128(__uint128_t key) :
        key(key)
    {
        auto mm_key = _mm_load_si128(reinterpret_cast<__m128i *>(&key));

        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[0]), mm_key);
        mm_key = AES128::KeyExpansion<0x01>(mm_key);
        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[1]), mm_key);
        mm_key = AES128::KeyExpansion<0x02>(mm_key);
        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[2]), mm_key);
        mm_key = AES128::KeyExpansion<0x04>(mm_key);
        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[3]), mm_key);
        mm_key = AES128::KeyExpansion<0x08>(mm_key);
        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[4]), mm_key);
        mm_key = AES128::KeyExpansion<0x10>(mm_key);
        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[5]), mm_key);
        mm_key = AES128::KeyExpansion<0x20>(mm_key);
        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[6]), mm_key);
        mm_key = AES128::KeyExpansion<0x40>(mm_key);
        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[7]), mm_key);
        mm_key = AES128::KeyExpansion<0x80>(mm_key);
        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[8]), mm_key);
        mm_key = AES128::KeyExpansion<0x1b>(mm_key);
        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[9]), mm_key);
        mm_key = AES128::KeyExpansion<0x36>(mm_key);
        _mm_store_si128(reinterpret_cast<__m128i *>(&keyRounds[10]), mm_key);
    }

    /** Process (encrypt/decrypt) buffer.
     *
     * @param ENCRYPT true to encrypt, false to decrypt.
     * @param CRC32_LOCATION Location of the CRC-32C value in the encrypted data, to ignore.
     * @param counter CTR counter+nonce value at start of buffer.
     * @param dst Destination buffer. Dst and src may alias.
     * @param src Source buffer. Dst and src may alias.
     * @param size Size of the src and dst buffers in bytes.
     * @return CRC-32C value of the plain-text data.
     */
    template<bool ENCRYPT, ssize_t CRC32_LOCATION=-1>
    uint32_t CTRProcess(__uint128_t _counter, __uint128_t *dst, const __uint128_t *src, size_t size) const
    {
        uint32_t CRC = 0xffffffff;
        auto counter = _mm_load_si128(reinterpret_cast<__m128i *>(&_counter));

        size_t todoBytes = size;
        size_t todoBlocks = size / sizeof (__uint128_t);
        size_t doneBlocks = 0;

        if (CRC32_LOCATION >= 0) {
            if (size < (CRC32_LOCATION + sizeof (uint32_t))) {
                BOOST_THROW_EXCEPTION(aes128_crc_location_error());
            }

            // Process all the full blocks, up to 8, before the block with the CRC inside it.
            const size_t CRC32_BLOCK_LOCATION = CRC32_LOCATION / sizeof (__uint128_t);
            while (doneBlocks < CRC32_BLOCK_LOCATION) {
                auto nrBlocks = std::min(todoBlocks, static_cast<size_t>(8));

                CRC = CTRProcess8FullBlocks<ENCRYPT>(CRC, counter, &dst[doneBlocks], &src[doneBlocks], nrBlocks);

                todoBytes -= nrBlocks * sizeof (__uint128_t);
                todoBlocks -= nrBlocks;
                doneBlocks += nrBlocks;
            }

            // The CRC is located inside this block. Most often this is a full block, but we use this function
            // to mask the CRC during decryption.
            auto nrBytes = std::min(todoBytes, sizeof (__uint128_t));
            CRC = CTRProcessPartialBlock<ENCRYPT,CRC32_LOCATION % sizeof (__uint128_t)>(CRC, counter, &dst[doneBlocks], &src[doneBlocks], nrBytes);

            todoBytes -= nrBytes;
            if (nrBytes == sizeof (__uint128_t)) {
                todoBlocks -= 1;
            }
        }

        // Process all the full blocks, up to 8, until the end of the data.
        while (todoBlocks > 0) {
            auto nrBlocks = std::min(todoBlocks, static_cast<size_t>(8));

            CRC = CTRProcess8FullBlocks<ENCRYPT>(CRC, counter, &dst[doneBlocks], &src[doneBlocks], nrBlocks);

            todoBytes -= nrBlocks * sizeof (__uint128_t);
            todoBlocks -= nrBlocks;
            doneBlocks += nrBlocks;
        }

        // Process the last few bytes in the last block.
        if (todoBytes) {
            CRC = AES128::CTRProcessPartialBlock<ENCRYPT>(CRC, counter, &dst[doneBlocks], &src[doneBlocks], todoBytes);
        }

        return CRC ^ 0xffffffff;
    }

    /** Process (encrypt/decrypt) buffer.
     * This function allows dst or src to be unaligned.
     * It may need to copy dst or src internally to align.
     *
     * @param ENCRYPT true to encrypt, false to decrypt.
     * @param CRC32_LOCATION Location of the CRC-32C value in the encrypted data, to ignore.
     * @param counter CTR counter+nonce value at start of buffer.
     * @param dst Destination buffer. Dst and src may alias.
     * @param src Source buffer. Dst and src may alias.
     * @param size Size of the src and dst buffers in bytes.
     * @return CRC-32C value of the plain-text data.
     */
    template<bool ENCRYPT, ssize_t CRC32_LOCATION=-1>
    uint32_t CTRProcess(__uint128_t counter, void *dst, const void *src, size_t size) const
    {
        const __uint128_t *src128;
        __uint128_t *dst128;

        if (isAligned<__uint128_t>(src)) {
            src128 = reinterpret_cast<const __uint128_t *>(src);
        } else {
            auto tmp = new __uint128_t[nrItems<__uint128_t>(size)];
            memcpy(tmp, src, size);
            src128 = reinterpret_cast<const __uint128_t *>(tmp);
        }

        if (isAligned<__uint128_t>(dst)) {
            dst128 = reinterpret_cast<__uint128_t *>(dst);
        } else {
            dst128 = new __uint128_t[nrItems<__uint128_t>(size)];
        }

        auto CRC = CTRProcess<ENCRYPT, CRC32_LOCATION>(counter, dst128, src128, size);

        if (!isAligned<__uint128_t>(src)) {
            delete[] src128;
        }

        if (!isAligned<__uint128_t>(dst)) {
            memcpy(dst, dst128, size);
            delete[] dst128;
        }

        return CRC;
    }

    /** Process (encrypt/decrypt) buffer.
     *
     * @param ENCRYPT true to encrypt, false to decrypt.
     * @param CRC32_LOCATION Location of the CRC-32C value in the encrypted data, to ignore.
     * @param counter CTR counter+nonce value at start of buffer.
     * @param src A string to process.
     * @return CRC-32C value of the plain-text data and the processed string.
     */
    template<bool ENCRYPT, ssize_t CRC32_LOCATION=-1>
    std::pair<uint32_t, std::string> CTRProcess(__uint128_t counter, const std::string &src) const
    {
        auto dst = new __uint128_t[nrItems<__uint128_t>(src.size())];

        uint32_t CRC = CTRProcess<ENCRYPT, CRC32_LOCATION>(counter, dst, src.data(), src.size());

        auto dstString = std::string(reinterpret_cast<const char *>(dst), src.size());
        delete[] dst;

        return std::pair<uint32_t, std::string>(CRC, dstString);
    }
};

};};
