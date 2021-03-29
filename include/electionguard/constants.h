#ifndef __ELECTIONGUARD_CPP_CONSTANTS_H_INCLUDED__
#define __ELECTIONGUARD_CPP_CONSTANTS_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum MAX_IDENIFIER_LENGTH { MAX_IDENIFIER_LENGTH = 256 };
enum MAX_P_LEN { MAX_P_LEN = 64 };
enum MAX_Q_LEN { MAX_Q_LEN = 4 };

static const uint8_t MAX_P_LEN_DOUBLE = 128;
static const uint8_t MAX_Q_LEN_DOUBLE = 8;

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

// Max P value in Hacl_Bignum4096 format
static const uint64_t P_ARRAY_REVERSE[MAX_P_LEN] = {
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
  0xceddd45334dbc6b5, 0xd2f9ca02d03199ba, 0xfb82a75c47c03d43, 0x34aa85973f79a93f,
  0xf17903f4e234ea60, 0x98bb22aa7ec1b6d0, 0x9ad030aaba5f3a57, 0x1b32e5e8d8036214,
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

// 1044388881413152506691752710716624382579964249047383780384233483283953907971553643537729993126875883902173634017777416360502926082946377942955704498542097614841825246773580689398386320439747911160897731551074903967243883427132918813748016269754522343505285898816777211761912392772914485521155521641049273446207578961939840619466145806859275053476560973295158703823395710210329314709715239251736552384080845836048778667318931418338422443891025911884723433084701207771901944593286624979917391350564662632723703007964229849154756196890615252286533089643184902706926081744149289517418249153634178342075381874131646013444796894582106870531535803666254579602632453103741452569793905551901541856173251385047414840392753585581909950158046256810542678368121278509960520957624737942914600310646609792665012858397381435755902851312071248102599442308951327039250818892493767423329663783709190716162023529669217300939783171415808233146823000766917789286154006042281423733706462905243774854543127239500245873582012663666430583862778167369547603016344242729592244544608279405999759391099775667746401633668308698186721172238255007962658564443858927634850415775348839052026675785694826386930175303143450046575460843879941791946313299322976993405829119
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
  0x1b32e5e8d8036214, 0x9ad030aaba5f3a57, 0x98bb22aa7ec1b6d0, 0xf17903f4e234ea60,
  0x34aa85973f79a93f, 0xfb82a75c47c03d43, 0xd2f9ca02d03199ba, 0xceddd45334dbc6b5,
  0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff};

// Max Q value in Hacl_Bignum256 format
static const uint64_t Q_ARRAY_REVERSE[MAX_Q_LEN] = {0xFFFFFFFFFFFFFF43, 0xFFFFFFFFFFFFFFFF,
                                                    0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};

// Qinv = 2^256 - Q in Hacl_Bignum256 format
static const uint64_t Q_ARRAY_INVERSE_REVERSE[MAX_Q_LEN] = {0x00000000000000bd, 0x0000000000000000,
                                                            0x0000000000000000, 0x0000000000000000};

// Q = 2^256 - 189
// 115792089237316195423570985008687907853269984665640564039457584007913129639747
static const uint64_t Q_ARRAY[MAX_Q_LEN] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFF43};

// G in Hacl_Bignum4096 format
static const uint64_t G_ARRAY_REVERSE[MAX_P_LEN] = {
  0xb0c73abf03e8e0aa, 0x94b38ac417cddf40, 0x40d9992197d80a6e, 0x82dc54775ab83538,
  0x10c136f8691101ad, 0x8e61369ba0ddbadb, 0x00e8a317ae1e1d82, 0x288a89c931cf564f,
  0xdba8a12c5ca82757, 0xd4809ef34abeb83f, 0x76ebd2d95a3dee96, 0x8f299bcb29005200,
  0xe9f61c11a07bf421, 0xc3b1cbdb50f759d0, 0xbf7cd02d9661385a, 0x801328b2c6a60526,
  0xf6bc80662ba06207, 0xcaec94c95e96d628, 0x76c94b2008926b38, 0x93ad97b8fe09274e,
  0x09af5e71114a005f, 0xc0cdbdb76b6ad45f, 0x5a5d1cedeee01e4b, 0x0c7e71fcb2255254,
  0xbaad96aac96b0dbe, 0xc9b11ab6c59bce62, 0x72ceb313fdab069c, 0xeb276fb3685f3716,
  0xdf23f1db8355bde1, 0x501fa2342b728263, 0xfb1918b2a2a30e69, 0xf7f72da39a2284fd,
  0x8090c35da9355e6c, 0x322b37c50af18215, 0x86d24900742062c1, 0xf6932825bf45de83,
  0x7aaa0e9fd8785702, 0xd8e41422b64d2cba, 0x1e221c41f55bba31, 0xa6750e7c8750b514,
  0xf09d40ac20c2ab74, 0x872e62b5d1b13a98, 0xb3c39aa08b829b28, 0xcc3eda17dbfc47b8,
  0xfdebeef58570669a, 0x7f3dabcbad8eb9d8, 0xfa7b6c87f4554cb5, 0x26e050af50a03c65,
  0xd7f736fcba6c032e, 0x6b0e2a05be6af78f, 0xdd4b795f78de07d8, 0x4e65633480b396e1,
  0x25ef356fe5bb5931, 0xd3b308da86d1c3a5, 0x4a62dcbb93b1ddd8, 0xb706fa55d5038ffb,
  0x6387b98ee0e3def1, 0xcfb0cfb65363b256, 0x840ec7d4ec804794, 0xa142cdf33f6ef853,
  0x750d6798f5196cf2, 0xd45ec4cc64cfd15e, 0x8d2a3141825b33d5, 0x037de384f98f6e03,
};

// 14245109091294741386751154342323521003543059865261911603340669522218159898070093327838595045175067897363301047764229640327930333001123401070596314469603183633790452807428416775717923182949583875381833912370889874572112086966300498607364501764494811956017881198827400327403252039184448888877644781610594801053753235453382508543906993571248387749420874609737451803650021788641249940534081464232937193671929586747339353451021712752406225276255010281004857233043241332527821911604413582442915993833774890228705495787357234006932755876972632840760599399514028393542345035433135159511099877773857622699742816228063106927776147867040336649025152771036361273329385354927395836330206311072577683892664475070720408447257635606891920123791602538518516524873664205034698194561673019535564273204744076336022130453963648114321050173994259620611015189498335966173440411967562175734606706258335095991140827763942280037063180207172918769921712003400007923888084296685269233298371143630883011213745082207405479978418089917768242592557172834921185990876960527013386693909961093302289646193295725135238595082039133488721800071459503353417574248679728577942863659802016004283193163470835709405666994892499382890912238098413819320185166580019604608311466
static const uint64_t G_ARRAY[MAX_P_LEN] = {
  0x37de384f98f6e038, 0xd2a3141825b33d5d, 0x45ec4cc64cfd15e7, 0x50d6798f5196cf2a,
  0x142cdf33f6ef8538, 0x40ec7d4ec804794c, 0xfb0cfb65363b2566, 0x387b98ee0e3def1b,
  0x706fa55d5038ffb4, 0xa62dcbb93b1ddd8d, 0x3b308da86d1c3a52, 0x5ef356fe5bb59314,
  0xe65633480b396e1d, 0xd4b795f78de07d86, 0xb0e2a05be6af78fd, 0x7f736fcba6c032e2,
  0x6e050af50a03c65f, 0xa7b6c87f4554cb57, 0xf3dabcbad8eb9d8f, 0xdebeef58570669ac,
  0xc3eda17dbfc47b8b, 0x3c39aa08b829b288, 0x72e62b5d1b13a98f, 0x09d40ac20c2ab74a,
  0x6750e7c8750b5141, 0xe221c41f55bba31d, 0x8e41422b64d2cba7, 0xaaa0e9fd8785702f,
  0x6932825bf45de838, 0x6d24900742062c13, 0x22b37c50af182158, 0x090c35da9355e6cf,
  0x7f72da39a2284fdf, 0xb1918b2a2a30e695, 0x01fa2342b728263d, 0xf23f1db8355bde1e,
  0xb276fb3685f37167, 0x2ceb313fdab069cc, 0x9b11ab6c59bce62b, 0xaad96aac96b0dbe0,
  0xc7e71fcb22552545, 0xa5d1cedeee01e4bc, 0x0cdbdb76b6ad45f0, 0x9af5e71114a005f9,
  0x3ad97b8fe09274e7, 0x6c94b2008926b38c, 0xaec94c95e96d628f, 0x6bc80662ba062078,
  0x01328b2c6a60526b, 0xf7cd02d9661385ac, 0x3b1cbdb50f759d0e, 0x9f61c11a07bf4218,
  0xf299bcb290052007, 0x6ebd2d95a3dee96d, 0x4809ef34abeb83fd, 0xba8a12c5ca827572,
  0x88a89c931cf564f0, 0x0e8a317ae1e1d828, 0xe61369ba0ddbadb1, 0x0c136f8691101ad8,
  0x2dc54775ab835384, 0x0d9992197d80a6e9, 0x4b38ac417cddf40b, 0x0c73abf03e8e0aa};

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