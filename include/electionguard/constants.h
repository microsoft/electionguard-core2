#ifndef __ELECTIONGUARD_CPP_CONSTANTS_H_INCLUDED__
#define __ELECTIONGUARD_CPP_CONSTANTS_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define HASHED_CIPHERTEXT_BLOCK_LENGTH 32U
#define HASHED_CIPHERTEXT_BLOCK_LENGTH_IN_BITS 256U
#define HASHED_CIPHERTEXT_PAD_INDICATOR_SIZE sizeof(uint16_t)
enum HASHED_CIPHERTEXT_PADDED_DATA_SIZE {
    BYTES_32 = 32 - HASHED_CIPHERTEXT_PAD_INDICATOR_SIZE,
    BYTES_64 = 64 - HASHED_CIPHERTEXT_PAD_INDICATOR_SIZE,
    BYTES_128 = 128 - HASHED_CIPHERTEXT_PAD_INDICATOR_SIZE,
    BYTES_256 = 256 - HASHED_CIPHERTEXT_PAD_INDICATOR_SIZE,
    BYTES_512 = 512 - HASHED_CIPHERTEXT_PAD_INDICATOR_SIZE
};

enum MAX_IDENIFIER_LENGTH { MAX_IDENIFIER_LENGTH = 256 };
enum MAX_P_LEN { MAX_P_LEN = 64, MAX_P_LEN_32 = 128 };
enum MAX_Q_LEN { MAX_Q_LEN = 4, MAX_Q_LEN_32 = 8 };

// values used for fixed-base exponentiation tables
static const uint64_t LUT_WINDOW_SIZE = 8;
static const uint64_t LUT_ORDER_BITS = 256;
static const uint64_t LUT_TABLE_LENGTH = 32;

static const uint8_t MAX_P_LEN_DOUBLE = 128;
static const uint8_t MAX_Q_LEN_DOUBLE = 8;

static const uint32_t DEFAULT_PRECOMPUTE_SIZE = 5000;
static const uint64_t DEFAULT_MAX_BALLOTS = 1000000;

static const uint64_t DLOG_MAX_SIZE = 1000000;

static const uint32_t MAX_P_SIZE = MAX_P_LEN * sizeof(uint64_t);
static const uint32_t MAX_Q_SIZE = MAX_Q_LEN * sizeof(uint64_t);

static const uint64_t MAX_UINT64 = 0xffffffffffffffff;

static const uint64_t MAX_256[MAX_Q_LEN] = {0xffffffffffffffff, 0xffffffffffffffff,
                                            0xffffffffffffffff, 0xffffffffffffffff};

static const uint64_t MAX_4096[MAX_P_LEN] = {
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
};

// HACL expects certain array values to be reversed
// so both the inverted and regular hex arrays are provided

#ifdef USE_STANDARD_PRIMES

// Small Prime Q
// Q = 2^256 - 189
// 115792089237316195423570985008687907853269984665640564039457584007913129639747
static const uint64_t Q_ARRAY[MAX_Q_LEN] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFF43};

// Max Q value in Hacl_Bignum256 format
static const uint64_t Q_ARRAY_REVERSE[MAX_Q_LEN] = {0xFFFFFFFFFFFFFF43, 0xFFFFFFFFFFFFFFFF,
                                                    0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};

// MAX_256 - Q + 1 in Hacl_Bignum256 format
static const uint64_t Q_ARRAY_INVERSE_OFFSET[MAX_Q_LEN] = {0x00000000000000bd, 0x0000000000000000,
                                                           0x0000000000000000, 0x0000000000000000};

// Large Prime P
static const uint64_t P_ARRAY[MAX_P_LEN] = {
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xb17217f7d1cf79ab, 0xc9e3b39803f2f6af, 0x40f343267298b62d, 0x8a0d175b8baafa2b,
  0xe7b876206debac98, 0x559552fb4afa1b10, 0xed2eae35c1382144, 0x27573b291169b825,
  0x3e96ca16224ae8c5, 0x1acbda11317c387e, 0xb9ea9bc3b136603b, 0x256fa0ec7657f74b,
  0x72ce87b19d6548ca, 0xf5dfa6bd38303248, 0x655fa1872f20e3a2, 0xda2d97c50f3fd5c6,
  0x07f4ca11fb5bfb90, 0x610d30f88fe551a2, 0xee569d6dfc1efa15, 0x7d2e23de1400b396,
  0x17460775db8990e5, 0xc943e732b479cd33, 0xcccc4e659393514c, 0x4c1a1e0bd1d6095d,
  0x25669b333564a337, 0x6a9c7f8a5e148e82, 0x074db6015cfe7aa3, 0x0c480a5417350d2c,
  0x955d5179b1e17b9d, 0xae313cdb6c606cb1, 0x078f735d1b2db31b, 0x5f50b5185064c18b,
  0x4d162db3b365853d, 0x7598a1951ae273ee, 0x5570b6c68f969834, 0x96d4e6d330af889b,
  0x44a02554731cdc8e, 0xa17293d1228a4ef9, 0x8d6f5177fbcf0755, 0x268a5c1f9538b982,
  0x61affd446b1ca3cf, 0x5e9222b88c66d3c5, 0x422183edc9942109, 0x0bbb16faf3d949f2,
  0x36e02b20cee886b9, 0x05c128d53d0bd2f9, 0x621363196af50302, 0x0060e49908391a0c,
  0x57339ba2beba7d05, 0x2ac5b61cc4e9207c, 0xef2f0ce2d7373958, 0xd762265890445744,
  0xfb5f2da4b7510058, 0x92d356890defe9ca, 0xd9b9d4b713e06162, 0xa2d8fdd0df2fd608,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
};

// Max P value in Hacl_Bignum4096 format
static const uint64_t P_ARRAY_REVERSE[MAX_P_LEN] = {
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xa2d8fdd0df2fd608, 0xd9b9d4b713e06162, 0x92d356890defe9ca, 0xfb5f2da4b7510058,
  0xd762265890445744, 0xef2f0ce2d7373958, 0x2ac5b61cc4e9207c, 0x57339ba2beba7d05,
  0x0060e49908391a0c, 0x621363196af50302, 0x05c128d53d0bd2f9, 0x36e02b20cee886b9,
  0x0bbb16faf3d949f2, 0x422183edc9942109, 0x5e9222b88c66d3c5, 0x61affd446b1ca3cf,
  0x268a5c1f9538b982, 0x8d6f5177fbcf0755, 0xa17293d1228a4ef9, 0x44a02554731cdc8e,
  0x96d4e6d330af889b, 0x5570b6c68f969834, 0x7598a1951ae273ee, 0x4d162db3b365853d,
  0x5f50b5185064c18b, 0x078f735d1b2db31b, 0xae313cdb6c606cb1, 0x955d5179b1e17b9d,
  0x0c480a5417350d2c, 0x074db6015cfe7aa3, 0x6a9c7f8a5e148e82, 0x25669b333564a337,
  0x4c1a1e0bd1d6095d, 0xcccc4e659393514c, 0xc943e732b479cd33, 0x17460775db8990e5,
  0x7d2e23de1400b396, 0xee569d6dfc1efa15, 0x610d30f88fe551a2, 0x07f4ca11fb5bfb90,
  0xda2d97c50f3fd5c6, 0x655fa1872f20e3a2, 0xf5dfa6bd38303248, 0x72ce87b19d6548ca,
  0x256fa0ec7657f74b, 0xb9ea9bc3b136603b, 0x1acbda11317c387e, 0x3e96ca16224ae8c5,
  0x27573b291169b825, 0xed2eae35c1382144, 0x559552fb4afa1b10, 0xe7b876206debac98,
  0x8a0d175b8baafa2b, 0x40f343267298b62d, 0xc9e3b39803f2f6af, 0xb17217f7d1cf79ab,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
};

// MAX_4096 - P + 1 in Hacl_Bignum256 format
static const uint64_t P_ARRAY_INVERSE_OFFSET[MAX_P_LEN] = {
  0x0000000000000001, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x5d27022f20d029f7, 0x26462b48ec1f9e9d, 0x6d2ca976f2101635, 0x04a0d25b48aeffa7,
  0x289dd9a76fbba8bb, 0x10d0f31d28c8c6a7, 0xd53a49e33b16df83, 0xa8cc645d414582fa,
  0xff9f1b66f7c6e5f3, 0x9dec9ce6950afcfd, 0xfa3ed72ac2f42d06, 0xc91fd4df31177946,
  0xf444e9050c26b60d, 0xbdde7c12366bdef6, 0xa16ddd4773992c3a, 0x9e5002bb94e35c30,
  0xd975a3e06ac7467d, 0x7290ae880430f8aa, 0x5e8d6c2edd75b106, 0xbb5fdaab8ce32371,
  0x692b192ccf507764, 0xaa8f4939706967cb, 0x8a675e6ae51d8c11, 0xb2e9d24c4c9a7ac2,
  0xa0af4ae7af9b3e74, 0xf8708ca2e4d24ce4, 0x51cec324939f934e, 0x6aa2ae864e1e8462,
  0xf3b7f5abe8caf2d3, 0xf8b249fea301855c, 0x95638075a1eb717d, 0xda9964ccca9b5cc8,
  0xb3e5e1f42e29f6a2, 0x3333b19a6c6caeb3, 0x36bc18cd4b8632cc, 0xe8b9f88a24766f1a,
  0x82d1dc21ebff4c69, 0x11a9629203e105ea, 0x9ef2cf07701aae5d, 0xf80b35ee04a4046f,
  0x25d2683af0c02a39, 0x9aa05e78d0df1c5d, 0x0a205942c7cfcdb7, 0x8d31784e629ab735,
  0xda905f1389a808b4, 0x4615643c4ec99fc4, 0xe53425eece83c781, 0xc16935e9ddb5173a,
  0xd8a8c4d6ee9647da, 0x12d151ca3ec7debb, 0xaa6aad04b505e4ef, 0x184789df92145367,
  0x75f2e8a4745505d4, 0xbf0cbcd98d6749d2, 0x361c4c67fc0d0950, 0x4e8de8082e308654,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
};

// Cofactor R
static const uint64_t R_ARRAY[MAX_P_LEN] = {
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0100000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0xbcb17217f7d1cf79,
  0xabc9e3b39803f2f6, 0xaf40f343267298b6, 0x2d8a0d175b8bab85, 0x7ae8f42816541880,
  0x6c62b0ea36355a3a, 0x73e0c741985bf6a0, 0xe3130179bf2f0b43, 0xe33ad862923861b8,
  0xc9f768c416951960, 0x0bad06093f964b27, 0xe02d86831231a916, 0x0de48f4da53d8ab5,
  0xe69e386b694bec1a, 0xe722d47579249d54, 0x24767c5c33b9151e, 0x07c5c11d106ac446,
  0xd330b47db59d352e, 0x47a53157de044619, 0x00f6fe360db897df, 0x5316d87c94ae71da,
  0xd0be84b647c4bcf8, 0x18c23a2d4ebb53c7, 0x02a5c8062d19f5e9, 0xb5033a94f7ff732f,
  0x54129712869d97b8, 0xc96c412921a9d867, 0x9770f499a041c297, 0xcff79d4c9149eb6c,
  0xaf67b9ea3dc563d9, 0x65f3aad1377ff22d, 0xe9c3e62068dd0ed6, 0x151c37b4f74634c2,
  0xbd09da912fd599f4, 0x333a8d2cc005627d, 0xca37bad43e64a396, 0x3119c0bfe34810a2,
  0x1ee7cfc421d53398, 0xcbc7a95b3bf585e5, 0xa04b790e2fe1fe9b, 0xc264fda8109f6454,
  0xa082f5efb2f37ea2, 0x37aa29df320d6ea8, 0x60c41a9054ccd248, 0x76c6253f667bfb01,
  0x39b5531ff3018996, 0x1202fd2b0d55a752, 0x72c7fd73343f7899, 0xbca0b36a4c470a64,
  0xa009244c84e77ceb, 0xc92417d5bb13bf18, 0x167d8033eb6c4dd7, 0x879fd4a7f529fd4a,
  0x7f529fd4a7f529fd, 0x4a7f529fd4a7f529, 0xfd4a7f529fd4a7f5, 0x000000000000002a,
};

// cofactor R in Hacl_Bignum4096 format
static const uint64_t R_ARRAY_REVERSE[MAX_P_LEN] = {
  0x4a7f529fd4a7f52a, 0x7f529fd4a7f529fd, 0x529fd4a7f529fd4a, 0x9fd4a7f529fd4a7f,
  0x7d8033eb6c4dd787, 0x2417d5bb13bf1816, 0x09244c84e77cebc9, 0xa0b36a4c470a64a0,
  0xc7fd73343f7899bc, 0x02fd2b0d55a75272, 0xb5531ff301899612, 0xc6253f667bfb0139,
  0xc41a9054ccd24876, 0xaa29df320d6ea860, 0x82f5efb2f37ea237, 0x64fda8109f6454a0,
  0x4b790e2fe1fe9bc2, 0xc7a95b3bf585e5a0, 0xe7cfc421d53398cb, 0x19c0bfe34810a21e,
  0x37bad43e64a39631, 0x3a8d2cc005627dca, 0x09da912fd599f433, 0x1c37b4f74634c2bd,
  0xc3e62068dd0ed615, 0xf3aad1377ff22de9, 0x67b9ea3dc563d965, 0xf79d4c9149eb6caf,
  0x70f499a041c297cf, 0x6c412921a9d86797, 0x129712869d97b8c9, 0x033a94f7ff732f54,
  0xa5c8062d19f5e9b5, 0xc23a2d4ebb53c702, 0xbe84b647c4bcf818, 0x16d87c94ae71dad0,
  0xf6fe360db897df53, 0xa53157de04461900, 0x30b47db59d352e47, 0xc5c11d106ac446d3,
  0x767c5c33b9151e07, 0x22d47579249d5424, 0x9e386b694bec1ae7, 0xe48f4da53d8ab5e6,
  0x2d86831231a9160d, 0xad06093f964b27e0, 0xf768c4169519600b, 0x3ad862923861b8c9,
  0x130179bf2f0b43e3, 0xe0c741985bf6a0e3, 0x62b0ea36355a3a73, 0xe8f428165418806c,
  0x8a0d175b8bab857a, 0x40f343267298b62d, 0xc9e3b39803f2f6af, 0xb17217f7d1cf79ab,
  0x00000000000000bc, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000001, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
};

// Generator G
static const uint64_t G_ARRAY[MAX_P_LEN] = {
  0x36036fed214f3b50, 0xdc566d3a312fe413, 0x1fee1c2bce6d02ea, 0x39b477ac05f7f885,
  0xf38cfe77a7e45acf, 0x4029114c4d7a9bfe, 0x058bf2f995d2479d, 0x3dda618ffd910d3c,
  0x4236ab2cfdd783a5, 0x016f7465cf59bbf4, 0x5d24a22f130f2d04, 0xfe93b2d58bb9c1d1,
  0xd27fc9a17d2af49a, 0x779f3ffbdca22900, 0xc14202ee6c996160, 0x34be35cbcdd3e7bb,
  0x7996adfe534b63cc, 0xa41e21ff5dc778eb, 0xb1b86c53bfbe9998, 0x7d7aea0756237fb4,
  0x0922139f90a62f2a, 0xa8d9ad34dff799e3, 0x3c857a6468d001ac, 0xf3b681db87dc4242,
  0x755e2ac5a5027db8, 0x1984f033c4d17837, 0x1f273dbb4fcea1e6, 0x28c23e52759bc776,
  0x5728035cea26b44c, 0x49a65666889820a4, 0x5c33dd37ea4a1d00, 0xcb62305cd541be1e,
  0x8a92685a07012b1a, 0x20a746c3591a2db3, 0x815000d2aaccfe43, 0xdc49e828c1ed7387,
  0x466afd8e4bf19355, 0x93b2a442eec271c5, 0x0ad39f733797a1ea, 0x11802a2557916534,
  0x662a6b7e9a9e449a, 0x24c8cff809e79a4d, 0x806eb681119330e6, 0xc57985e39b200b48,
  0x93639fdfdea49f76, 0xad1acd997eba1365, 0x7541e79ec57437e5, 0x04eda9dd01106151,
  0x6c643fb30d6d58af, 0xccd28b73feda29ec, 0x12b01a5eb86399a5, 0x93a9d5f450de39cb,
  0x92962c5ec6925348, 0xdb54d128fd99c14b, 0x457f883ec20112a7, 0x5a6a0581d3d80a3b,
  0x4ef09ec86f9552ff, 0xda1653f133aa2534, 0x983a6f31b0ee4697, 0x935a6b1ea2f75b85,
  0xe7eba151ba486094, 0xd68722b054633fec, 0x51ca3f29b31e77e3, 0x17b178b6b9d8ae0f,
};

// G in Hacl_Bignum4096 format
static const uint64_t G_ARRAY_REVERSE[MAX_P_LEN] = {
  0x17b178b6b9d8ae0f, 0x51ca3f29b31e77e3, 0xd68722b054633fec, 0xe7eba151ba486094,
  0x935a6b1ea2f75b85, 0x983a6f31b0ee4697, 0xda1653f133aa2534, 0x4ef09ec86f9552ff,
  0x5a6a0581d3d80a3b, 0x457f883ec20112a7, 0xdb54d128fd99c14b, 0x92962c5ec6925348,
  0x93a9d5f450de39cb, 0x12b01a5eb86399a5, 0xccd28b73feda29ec, 0x6c643fb30d6d58af,
  0x04eda9dd01106151, 0x7541e79ec57437e5, 0xad1acd997eba1365, 0x93639fdfdea49f76,
  0xc57985e39b200b48, 0x806eb681119330e6, 0x24c8cff809e79a4d, 0x662a6b7e9a9e449a,
  0x11802a2557916534, 0x0ad39f733797a1ea, 0x93b2a442eec271c5, 0x466afd8e4bf19355,
  0xdc49e828c1ed7387, 0x815000d2aaccfe43, 0x20a746c3591a2db3, 0x8a92685a07012b1a,
  0xcb62305cd541be1e, 0x5c33dd37ea4a1d00, 0x49a65666889820a4, 0x5728035cea26b44c,
  0x28c23e52759bc776, 0x1f273dbb4fcea1e6, 0x1984f033c4d17837, 0x755e2ac5a5027db8,
  0xf3b681db87dc4242, 0x3c857a6468d001ac, 0xa8d9ad34dff799e3, 0x0922139f90a62f2a,
  0x7d7aea0756237fb4, 0xb1b86c53bfbe9998, 0xa41e21ff5dc778eb, 0x7996adfe534b63cc,
  0x34be35cbcdd3e7bb, 0xc14202ee6c996160, 0x779f3ffbdca22900, 0xd27fc9a17d2af49a,
  0xfe93b2d58bb9c1d1, 0x5d24a22f130f2d04, 0x016f7465cf59bbf4, 0x4236ab2cfdd783a5,
  0x3dda618ffd910d3c, 0x058bf2f995d2479d, 0x4029114c4d7a9bfe, 0xf38cfe77a7e45acf,
  0x39b477ac05f7f885, 0x1fee1c2bce6d02ea, 0xdc566d3a312fe413, 0x36036fed214f3b50,
};

#endif

#ifdef USE_STANDARD_EG_1_PRIMES

// Small Prime Q
// Q = 2^256 - 189
// 115792089237316195423570985008687907853269984665640564039457584007913129639747
static const uint64_t Q_ARRAY[MAX_Q_LEN] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFF43};

// Max Q value in Hacl_Bignum256 format
static const uint64_t Q_ARRAY_REVERSE[MAX_Q_LEN] = {0xFFFFFFFFFFFFFF43, 0xFFFFFFFFFFFFFFFF,
                                                    0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};

// MAX_256 - Q + 1 in Hacl_Bignum256 format
static const uint64_t Q_ARRAY_INVERSE_OFFSET[MAX_Q_LEN] = {0x00000000000000bd, 0x0000000000000000,
                                                           0x0000000000000000, 0x0000000000000000};

// Large Prime P
// 1044388881413152506691752710716624382579964249047383780384233483283953907971553643537729993126875883902173634017777416360502926082946377942955704498542097614841825246773580689398386320439747911160897731551074903967243883427132918813748016269754522343505285898816777211761912392772914485521155521641049273446207578961939840619466145806859275053476560973295158703823395710210329314709715239251736552384080845836048778667318931418338422443891025911884723433084701207771901944593286624979917391350564662632723703007964229849154756196890615252286533089643184902706926081744149289517418249153634178342075381874131646013444796894582106870531535803666254579602632453103741452569793905551901541856173251385047414840392753585581909950158046256810542678368121278509960520957624737942914600310646609792665012858397381435755902851312071248102599442308951327039250818892493767423329663783709190716162023529669217300939783171415808233146823000766917789286154006042281423733706462905243774854543127239500245873582012663666430583862778167369547603016344242729592244544608279405999759391099769165589722584216017468464576217318557948461765770700913220460557598574717173408252913596242281190298966500668625620138188265530628036538314433100326660047110143
static const uint64_t P_ARRAY[MAX_P_LEN] = {
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0x93c467e37db0c7a4, 0xd1be3f810152cb56, 0xa1cecc3af65cc019, 0x0c03df34709affbd,
  0x8e4b59fa03a9f0ee, 0xd0649ccb621057d1, 0x1056ae9132135a08, 0xe43b4673d74bafea,
  0x58deb878cc86d733, 0xdbe7bf38154b36cf, 0x8a96d1567899aaae, 0x0c09d4c8b6b7b86f,
  0xd2a1ea1de62ff864, 0x3ec7c27182797722, 0x5e6ac2f0bd61c746, 0x961542a3ce3bea5d,
  0xb54fe70e63e6d09f, 0x8fc28658e80567a4, 0x7cfde60ee741e5d8, 0x5a7bd46931ced822,
  0x0365594964b83989, 0x6fcaabccc9b31959, 0xc083f22ad3ee591c, 0x32fab2c7448f2a05,
  0x7db2db49ee52e018, 0x2741e53865f004cc, 0x8e704b7c5c40bf30, 0x4c4d8c4f13edf604,
  0x7c555302d2238d8c, 0xe11df2424f1b66c2, 0xc5d238d0744db679, 0xaf2890487031f9c0,
  0xaea1c4bb6fe9554e, 0xe528fdf1b05e5b25, 0x6223b2f09215f371, 0x9f9c7ccc69ddf172,
  0xd0d6234217fcc003, 0x7f18b93ef5389130, 0xb7a661e5c26e5421, 0x4068bbcafea32a67,
  0x818bd3075ad1f5c7, 0xe9cc3d1737fb2817, 0x1baf84dbb6612b78, 0x81c1a48e439cd03a,
  0x92bf52225a2b38e6, 0x542e9f722bce15a3, 0x81b5753ea8427633, 0x81ccae83512b3051,
  0x1b32e5e8d8036214, 0x9ad030aaba5f3a57, 0x98bb22aa7ec1b6d0, 0xf17903f4e22d8407,
  0x34aa85973f79a93f, 0xfb82a75c47c03d43, 0xd2f9ca02d03199ba, 0xceddd4533a52566a,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
};

// Max P value in Hacl_Bignum4096 format
static const uint64_t P_ARRAY_REVERSE[MAX_P_LEN] = {
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xceddd4533a52566a, 0xd2f9ca02d03199ba, 0xfb82a75c47c03d43, 0x34aa85973f79a93f,
  0xf17903f4e22d8407, 0x98bb22aa7ec1b6d0, 0x9ad030aaba5f3a57, 0x1b32e5e8d8036214,
  0x81ccae83512b3051, 0x81b5753ea8427633, 0x542e9f722bce15a3, 0x92bf52225a2b38e6,
  0x81c1a48e439cd03a, 0x1baf84dbb6612b78, 0xe9cc3d1737fb2817, 0x818bd3075ad1f5c7,
  0x4068bbcafea32a67, 0xb7a661e5c26e5421, 0x7f18b93ef5389130, 0xd0d6234217fcc003,
  0x9f9c7ccc69ddf172, 0x6223b2f09215f371, 0xe528fdf1b05e5b25, 0xaea1c4bb6fe9554e,
  0xaf2890487031f9c0, 0xc5d238d0744db679, 0xe11df2424f1b66c2, 0x7c555302d2238d8c,
  0x4c4d8c4f13edf604, 0x8e704b7c5c40bf30, 0x2741e53865f004cc, 0x7db2db49ee52e018,
  0x32fab2c7448f2a05, 0xc083f22ad3ee591c, 0x6fcaabccc9b31959, 0x0365594964b83989,
  0x5a7bd46931ced822, 0x7cfde60ee741e5d8, 0x8fc28658e80567a4, 0xb54fe70e63e6d09f,
  0x961542a3ce3bea5d, 0x5e6ac2f0bd61c746, 0x3ec7c27182797722, 0xd2a1ea1de62ff864,
  0x0c09d4c8b6b7b86f, 0x8a96d1567899aaae, 0xdbe7bf38154b36cf, 0x58deb878cc86d733,
  0xe43b4673d74bafea, 0x1056ae9132135a08, 0xd0649ccb621057d1, 0x8e4b59fa03a9f0ee,
  0x0c03df34709affbd, 0xa1cecc3af65cc019, 0xd1be3f810152cb56, 0x93c467e37db0c7a4,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
};

// MAX_4096 - P + 1 in Hacl_Bignum256 format
static const uint64_t P_ARRAY_INVERSE_OFFSET[MAX_P_LEN] = {
  0x0000000000000001, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x31222bacc5ada995, 0x2d0635fd2fce6645, 0x047d58a3b83fc2bc, 0xcb557a68c08656c0,
  0x0e86fc0b1dd27bf8, 0x6744dd55813e492f, 0x652fcf5545a0c5a8, 0xe4cd1a1727fc9deb,
  0x7e33517caed4cfae, 0x7e4a8ac157bd89cc, 0xabd1608dd431ea5c, 0x6d40addda5d4c719,
  0x7e3e5b71bc632fc5, 0xe4507b24499ed487, 0x1633c2e8c804d7e8, 0x7e742cf8a52e0a38,
  0xbf974435015cd598, 0x48599e1a3d91abde, 0x80e746c10ac76ecf, 0x2f29dcbde8033ffc,
  0x6063833396220e8d, 0x9ddc4d0f6dea0c8e, 0x1ad7020e4fa1a4da, 0x515e3b449016aab1,
  0x50d76fb78fce063f, 0x3a2dc72f8bb24986, 0x1ee20dbdb0e4993d, 0x83aaacfd2ddc7273,
  0xb3b273b0ec1209fb, 0x718fb483a3bf40cf, 0xd8be1ac79a0ffb33, 0x824d24b611ad1fe7,
  0xcd054d38bb70d5fa, 0x3f7c0dd52c11a6e3, 0x90355433364ce6a6, 0xfc9aa6b69b47c676,
  0xa5842b96ce3127dd, 0x830219f118be1a27, 0x703d79a717fa985b, 0x4ab018f19c192f60,
  0x69eabd5c31c415a2, 0xa1953d0f429e38b9, 0xc1383d8e7d8688dd, 0x2d5e15e219d0079b,
  0xf3f62b3749484790, 0x75692ea987665551, 0x241840c7eab4c930, 0xa7214787337928cc,
  0x1bc4b98c28b45015, 0xefa9516ecdeca5f7, 0x2f9b63349defa82e, 0x71b4a605fc560f11,
  0xf3fc20cb8f650042, 0x5e3133c509a33fe6, 0x2e41c07efead34a9, 0x6c3b981c824f385b,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
};

// Cofactor R
// 9019518416950528558373478086511232658951474842525520401496114928154304263969655687927867442562559311457926593510757267649063628681241064260953609180947464800958467390949485096429653122916928704841547265126247408167856620024815508684472819746384115369148322548696439327979752948311712506113890045287907335656308945630141969472484100558565879585476547782717283106837945923693806973017510492730838409381014701258202694245760602718602550739205297257940969992371799325870179746191672464736721424617639973324090288952006260483222894269928179970153634220390287255837625331668555933039199194619824375869291271098935000699785346405055160394688637074599519052655517388596327473273906029869030988064607361165803129718773877185415445291671089029845994683414682274353665003204293107284473196033588697845087556526514092678744031772226855409523354476737660407619436531080189837076164818131039104397776628128325247709678431023369197272126578394856752060591013812807437681624251867074769638052097737959472027002770963255207757153746376691827309573603635608169799503216990026029763868313819255248026666854405409059422844776556067163611304891154793770115766608153679099327786
static const uint64_t R_ARRAY[MAX_P_LEN] = {
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x00000000000000bc,
  0x93c467e37db0c7a4, 0xd1be3f810152cb56, 0xa1cecc3af65cc019, 0x0c03df34709b8af6,
  0xa64c0cedcf2d559d, 0xa9d97f095c3076c6, 0x86037619148d2c86, 0xc317102afa214803,
  0x1f04440ac0ff0c9a, 0x417a89212512e760, 0x7b2501daa4d38a2c, 0x1410c4836149e2bd,
  0xb8c8260e627c4646, 0x963effe9e16e495d, 0x48bd215c6d8ec9d1, 0x667657a2a1c8506f,
  0x2113ffad19a6b2bc, 0x7c45760456719183, 0x309f874bc9ace570, 0xffda877aa2b23a2d,
  0x6f291c1554ca2eb1, 0x2f12cd009b8b8734, 0xa64ad51eb893bd89, 0x1750b85162241d90,
  0x8f0c9709879758e7, 0xe8233eab3bf2d6ab, 0x53afa32aa153ad66, 0x82e5a0648897c9be,
  0x18a0d50bece030c3, 0x432336ad9163e33f, 0x8e7daf498f14bb28, 0x52affa814841eb18,
  0xdd5f0e89516d5577, 0x76285c16071d2111, 0x94ee1c3f34642036, 0xab886e3ec28882ce,
  0x4003dea335b4d935, 0xbae4b58235b9fb2b, 0xab713c8f705a1c7d, 0xe42220209d6bbcac,
  0xc467318601565272, 0xe4a63e38e2499754, 0xae493ac1a8e83469, 0xeef35ca27c271bc7,
  0x92eee21156e617b9, 0x22ea8f713c22cf28, 0x2dc5d6385bb12868, 0xeb781278fa0ab2a8,
  0x958fccb5ffe2e5c3, 0x61fc174420122b01, 0x63ca4a46308c8c46, 0xc91ea7457c136a7d,
  0x9fd4a7f529fd4a7f, 0x529fd4a7f529fd4a, 0x7f529fd4a7f529fd, 0x4a7f529fd4a7f52a,
};

// cofactor R in Hacl_Bignum4096 format
static const uint64_t R_ARRAY_REVERSE[MAX_P_LEN] = {
  0x4a7f529fd4a7f52a, 0x7f529fd4a7f529fd, 0x529fd4a7f529fd4a, 0x9fd4a7f529fd4a7f,
  0xc91ea7457c136a7d, 0x63ca4a46308c8c46, 0x61fc174420122b01, 0x958fccb5ffe2e5c3,
  0xeb781278fa0ab2a8, 0x2dc5d6385bb12868, 0x22ea8f713c22cf28, 0x92eee21156e617b9,
  0xeef35ca27c271bc7, 0xae493ac1a8e83469, 0xe4a63e38e2499754, 0xc467318601565272,
  0xe42220209d6bbcac, 0xab713c8f705a1c7d, 0xbae4b58235b9fb2b, 0x4003dea335b4d935,
  0xab886e3ec28882ce, 0x94ee1c3f34642036, 0x76285c16071d2111, 0xdd5f0e89516d5577,
  0x52affa814841eb18, 0x8e7daf498f14bb28, 0x432336ad9163e33f, 0x18a0d50bece030c3,
  0x82e5a0648897c9be, 0x53afa32aa153ad66, 0xe8233eab3bf2d6ab, 0x8f0c9709879758e7,
  0x1750b85162241d90, 0xa64ad51eb893bd89, 0x2f12cd009b8b8734, 0x6f291c1554ca2eb1,
  0xffda877aa2b23a2d, 0x309f874bc9ace570, 0x7c45760456719183, 0x2113ffad19a6b2bc,
  0x667657a2a1c8506f, 0x48bd215c6d8ec9d1, 0x963effe9e16e495d, 0xb8c8260e627c4646,
  0x1410c4836149e2bd, 0x7b2501daa4d38a2c, 0x417a89212512e760, 0x1f04440ac0ff0c9a,
  0xc317102afa214803, 0x86037619148d2c86, 0xa9d97f095c3076c6, 0xa64c0cedcf2d559d,
  0x0c03df34709b8af6, 0xa1cecc3af65cc019, 0xd1be3f810152cb56, 0x93c467e37db0c7a4,
  0x00000000000000bc, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000001, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
};

// Generator G
// 119359756198641231858139651428439585561105914902686985078252796680474637856752833978884422594516170665312423393830118608408063594508087813277769835084746883589963798527237870817233369094387978405585759195339509768803496494994109693743279157584139079471178850751266233150727771094796709619646350222242437970473900636242584673413224137139139346254912172628651028694427789523683070264102332413084663100402635889283790741342401259356660761075766365672754329863241692760862540151023800163269173550320623249398630247531924855997863109776955214403044727497968354022277828136634059011708099779241302941071701051050378539485717425482151777277387633806111112178267035315726401285294598397677116389893642725498831127977915200359151833767358091365292230363248410124916825814514852703770457024102738694375502049388804979035628232209959549199366986471874840784466132903083308458356458177839111623113116525230200791649979270165318729763550486200224695556789081331596212761936863634467236301450039399776963661755684863012396788149479256016157814129329192490798309248914535389650594573156725696657302152874510063002532052622638033113978672254680147128450265983503193865576932419282003012093526302631221491418211528781074474515924597472841036553107847
static const uint64_t G_ARRAY[MAX_P_LEN] = {
  0x1d41e49c477e15ea, 0xeef0c5e4ac08d4a4, 0x6c268cd3424fc01d, 0x13769bdb43673218,
  0x587bc86c4c1448d0, 0x06a03699f3abae5f, 0xeb19e296f5d143cc, 0x5e4a3fc89088c9f4,
  0x523d166ee3ae9d5f, 0xb03c0bdd77add5c0, 0x17f6c55e2ec92c22, 0x6fef5c6c1df2e7c3,
  0x6d90e7eaade09824, 0x1d3409983bccd2b5, 0x379e9391fbc62f9f, 0x8d939d1208b16036,
  0x7c13426412218959, 0x5ec85c8cdbe5f9d3, 0x07f46912c04932f8, 0xc16815a76b4682bd,
  0x6bdc0ed52b00d8d3, 0x0f59c731d5a7ffae, 0x8165d53cf96649aa, 0xc2b743da56f14f19,
  0xdacc5236f29b1ab9, 0xf9befc69697293d5, 0xdead8b5bf5de9bab, 0x6de67c45719e5634,
  0x4a3cbdf3609824b1, 0xb578e34eaeb6dd31, 0x90ab3571d6d671c5, 0x12282c1da7bd36b4,
  0x251d2584fadea80b, 0x9e141423074dd9b5, 0xfb83acbdead4c87a, 0x58fff517f977a830,
  0x80370a3b0cf98a1b, 0xc2978c47aac29611, 0xfd6c40e2f9875c35, 0xd50443a9aa3f4961,
  0x1dcd3a0d6ff3cb3f, 0xacf31471bdb61860, 0xb92c594d4e46569b, 0xb39feeadff1fd64c,
  0x836a6d6db85c6ba7, 0x241766b7ab56bf73, 0x9633b054147f7170, 0x921412e948d9e474,
  0x02d15bb1c2573186, 0x12c121c36b80eb84, 0x33c08e7d0b7149e3, 0xab0a8735a92edce8,
  0xff943e28a2dceacf, 0xcc69ec318909cb04, 0x7be1c5858844b5ad, 0x44f22eeb289e4cc5,
  0x54f7a5e2f3dea026, 0x877ff92851816071, 0xce028eb868d965cc, 0xb2d2295a8c55bd1c,
  0x070b39b09ae06b37, 0xd29343b9d8997dc2, 0x44c468b980970731, 0x736ee018bbadb987,
};

// G in Hacl_Bignum4096 format
static const uint64_t G_ARRAY_REVERSE[MAX_P_LEN] = {
  0x736ee018bbadb987, 0x44c468b980970731, 0xd29343b9d8997dc2, 0x070b39b09ae06b37,
  0xb2d2295a8c55bd1c, 0xce028eb868d965cc, 0x877ff92851816071, 0x54f7a5e2f3dea026,
  0x44f22eeb289e4cc5, 0x7be1c5858844b5ad, 0xcc69ec318909cb04, 0xff943e28a2dceacf,
  0xab0a8735a92edce8, 0x33c08e7d0b7149e3, 0x12c121c36b80eb84, 0x02d15bb1c2573186,
  0x921412e948d9e474, 0x9633b054147f7170, 0x241766b7ab56bf73, 0x836a6d6db85c6ba7,
  0xb39feeadff1fd64c, 0xb92c594d4e46569b, 0xacf31471bdb61860, 0x1dcd3a0d6ff3cb3f,
  0xd50443a9aa3f4961, 0xfd6c40e2f9875c35, 0xc2978c47aac29611, 0x80370a3b0cf98a1b,
  0x58fff517f977a830, 0xfb83acbdead4c87a, 0x9e141423074dd9b5, 0x251d2584fadea80b,
  0x12282c1da7bd36b4, 0x90ab3571d6d671c5, 0xb578e34eaeb6dd31, 0x4a3cbdf3609824b1,
  0x6de67c45719e5634, 0xdead8b5bf5de9bab, 0xf9befc69697293d5, 0xdacc5236f29b1ab9,
  0xc2b743da56f14f19, 0x8165d53cf96649aa, 0x0f59c731d5a7ffae, 0x6bdc0ed52b00d8d3,
  0xc16815a76b4682bd, 0x07f46912c04932f8, 0x5ec85c8cdbe5f9d3, 0x7c13426412218959,
  0x8d939d1208b16036, 0x379e9391fbc62f9f, 0x1d3409983bccd2b5, 0x6d90e7eaade09824,
  0x6fef5c6c1df2e7c3, 0x17f6c55e2ec92c22, 0xb03c0bdd77add5c0, 0x523d166ee3ae9d5f,
  0x5e4a3fc89088c9f4, 0xeb19e296f5d143cc, 0x06a03699f3abae5f, 0x587bc86c4c1448d0,
  0x13769bdb43673218, 0x6c268cd3424fc01d, 0xeef0c5e4ac08d4a4, 0x1d41e49c477e15ea,
};

#endif

#ifdef USE_TEST_PRIMES

// Small Prime Q
// Q = 2^256 - 189
// 65521
static const uint64_t Q_ARRAY[MAX_Q_LEN] = {
  0x0000000000000000,
  0x0000000000000000,
  0x0000000000000000,
  0x000000000000fff1,

};

// Max Q value in Hacl_Bignum256 format
static const uint64_t Q_ARRAY_REVERSE[MAX_Q_LEN] = {
  0x000000000000fff1,
  0x0000000000000000,
  0x0000000000000000,
  0x0000000000000000,
};

// MAX_256 - Q + 1 in Hacl_Bignum256 format
static const uint64_t Q_ARRAY_INVERSE_OFFSET[MAX_Q_LEN] = {
  0xffffffffffff000f,
  0xffffffffffffffff,
  0xffffffffffffffff,
  0xffffffffffffffff,
};

// Large Prime P
// 18446744073704586917
static const uint64_t P_ARRAY[MAX_P_LEN] = {
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0xffffffffffb43ea5,
};

// Max P value in Hacl_Bignum4096 format
static const uint64_t P_ARRAY_REVERSE[MAX_P_LEN] = {
  0xffffffffffb43ea5, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
};

// MAX_4096 - P + 1 in Hacl_Bignum256 format
static const uint64_t P_ARRAY_INVERSE_OFFSET[MAX_P_LEN] = {
  0x00000000004bc15b, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
};

// Cofactor R
// 281539415968996
static const uint64_t R_ARRAY[MAX_P_LEN] = {
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0001000f00e10ce4,
};

// cofactor R in Hacl_Bignum4096 format
static const uint64_t R_ARRAY_REVERSE[MAX_P_LEN] = {
  0x0001000f00e10ce4, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
};

// Generator G
// 15463152587872997502
static const uint64_t G_ARRAY[MAX_P_LEN] = {
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0xd6982759f3d5107e,
};

// G in Hacl_Bignum4096 format
static const uint64_t G_ARRAY_REVERSE[MAX_P_LEN] = {
  0xd6982759f3d5107e, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
  0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
};

#endif

static const uint64_t ZERO_MOD_P_ARRAY[MAX_P_LEN] = {0UL};
static const uint64_t ONE_MOD_P_ARRAY[MAX_P_LEN] = {1UL};
static const uint64_t TWO_MOD_P_ARRAY[MAX_P_LEN] = {2UL};

static const uint64_t ZERO_MOD_Q_ARRAY[MAX_Q_LEN] = {0UL};
static const uint64_t ONE_MOD_Q_ARRAY[MAX_Q_LEN] = {1UL};
static const uint64_t TWO_MOD_Q_ARRAY[MAX_Q_LEN] = {2UL};

#ifdef __cplusplus
}
#endif
#endif /* __ELECTIONGUARD_CPP_CONSTANTS_H_INCLUDED__ */