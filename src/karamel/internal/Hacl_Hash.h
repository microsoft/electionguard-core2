/* MIT License
 *
 * Copyright (c) 2016-2020 INRIA, CMU and Microsoft Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __internal_Hacl_Hash_H
#define __internal_Hacl_Hash_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "../Hacl_Krmllib.h"
#include "../evercrypt_targetconfig.h"
#include "karamel/krml/internal/builtin.h"
#include "karamel/krml/internal/target.h"
#include "karamel/krml/internal/types.h"
#include "karamel/krml/lowstar_endianness.h"

#include <string.h>
void Hacl_Hash_Core_SHA2_init_224(uint32_t *s);

void Hacl_Hash_Core_SHA2_init_256(uint32_t *s);

void Hacl_Hash_Core_SHA2_init_384(uint64_t *s);

void Hacl_Hash_Core_SHA2_init_512(uint64_t *s);

void Hacl_Hash_Core_SHA2_finish_224(uint32_t *s, uint8_t *dst);

void Hacl_Hash_Core_SHA2_finish_256(uint32_t *s, uint8_t *dst);

void Hacl_Hash_Core_SHA2_finish_384(uint64_t *s, uint8_t *dst);

void Hacl_Hash_Core_SHA2_finish_512(uint64_t *s, uint8_t *dst);

void Hacl_Hash_SHA2_update_multi_224(uint32_t *s, uint8_t *blocks, uint32_t n_blocks);

void Hacl_Hash_SHA2_update_multi_256(uint32_t *s, uint8_t *blocks, uint32_t n_blocks);

void Hacl_Hash_SHA2_update_multi_384(uint64_t *s, uint8_t *blocks, uint32_t n_blocks);

void Hacl_Hash_SHA2_update_multi_512(uint64_t *s, uint8_t *blocks, uint32_t n_blocks);

void Hacl_Hash_SHA2_update_last_224(uint32_t *s, uint64_t prev_len, uint8_t *input,
                                    uint32_t input_len);

void Hacl_Hash_SHA2_update_last_256(uint32_t *s, uint64_t prev_len, uint8_t *input,
                                    uint32_t input_len);

void Hacl_Hash_SHA2_update_last_384(uint64_t *s, FStar_UInt128_uint128 prev_len, uint8_t *input,
                                    uint32_t input_len);

void Hacl_Hash_SHA2_update_last_512(uint64_t *s, FStar_UInt128_uint128 prev_len, uint8_t *input,
                                    uint32_t input_len);

void Hacl_Hash_SHA2_hash_256(uint8_t *input, uint32_t input_len, uint8_t *dst);

void Hacl_Hash_SHA2_hash_384(uint8_t *input, uint32_t input_len, uint8_t *dst);

void Hacl_Hash_SHA2_hash_512(uint8_t *input, uint32_t input_len, uint8_t *dst);

void Hacl_Hash_Core_SHA1_legacy_init(uint32_t *s);

void Hacl_Hash_Core_SHA1_legacy_finish(uint32_t *s, uint8_t *dst);

void Hacl_Hash_SHA1_legacy_update_multi(uint32_t *s, uint8_t *blocks, uint32_t n_blocks);

void Hacl_Hash_SHA1_legacy_update_last(uint32_t *s, uint64_t prev_len, uint8_t *input,
                                       uint32_t input_len);

void Hacl_Hash_SHA1_legacy_hash(uint8_t *input, uint32_t input_len, uint8_t *dst);

#if defined(__cplusplus)
}
#endif

#define __internal_Hacl_Hash_H_DEFINED
#endif