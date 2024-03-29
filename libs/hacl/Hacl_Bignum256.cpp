#include "Hacl_Bignum256.hpp"

#include "Hacl_Bignum256.h"

#include <stdexcept>

using std::out_of_range;
using std::vector;

namespace hacl
{
    struct handle_destructor {
        void operator()(Hacl_Bignum_MontArithmetic_bn_mont_ctx_u64 *handle) const
        {
            Hacl_Bignum256_mont_ctx_free(handle);
        }
    };

    typedef std::unique_ptr<Hacl_Bignum_MontArithmetic_bn_mont_ctx_u64, handle_destructor>
      HaclBignumContext256;

    struct Bignum256::Impl {
        HaclBignumContext256 context;
        Impl(uint64_t *elem)
        {
            HaclBignumContext256 ctx{Hacl_Bignum256_mont_ctx_init(elem)};
            context = std::move(ctx);
        }
    };

    Bignum256::Bignum256(uint64_t *elem) : pimpl(new Impl(elem)) {}
    Bignum256::~Bignum256() {}

    uint64_t Bignum256::add(uint64_t *a, uint64_t *b, uint64_t *res)
    {
        return Hacl_Bignum256_add(a, b, res);
    }

    void Bignum256::addMod(uint64_t *n, uint64_t *a, uint64_t *b, uint64_t *res)
    {
        Hacl_Bignum256_add_mod(n, a, b, res);
    }

    uint64_t Bignum256::sub(uint64_t *a, uint64_t *b, uint64_t *res)
    {
        return Hacl_Bignum256_sub(a, b, res);
    }

    void Bignum256::subMod(uint64_t *n, uint64_t *a, uint64_t *b, uint64_t *res)
    {
        Hacl_Bignum256_sub_mod(n, a, b, res);
    }

    void Bignum256::mul(uint64_t *a, uint64_t *b, uint64_t *res) { Hacl_Bignum256_mul(a, b, res); }

    bool Bignum256::mod(uint64_t *n, uint64_t *a, uint64_t *res)
    {
        return Hacl_Bignum256_mod(n, a, res);
    }

    bool Bignum256::modExp(uint64_t *n, uint64_t *a, uint32_t bBits, uint64_t *b, uint64_t *res,
                           bool useConstTime /* = true */)
    {
        if (bBits <= 0) {
            return false;
        }
        if (useConstTime) {
            return Hacl_Bignum256_mod_exp_consttime(n, a, bBits, b, res);
        }
        return Hacl_Bignum256_mod_exp_vartime(n, a, bBits, b, res);
    }

    bool Bignum256::modInvPrime(uint64_t *n, uint64_t *a, uint64_t *res)
    {
        return Hacl_Bignum256_mod_inv_prime_vartime(n, a, res);
    }

    uint64_t *Bignum256::fromBytes(uint32_t len, uint8_t *bytes)
    {
        return Hacl_Bignum256_new_bn_from_bytes_be(len, bytes);
    }

    void Bignum256::toBytes(uint64_t *bytes, uint8_t *res)
    {
        return Hacl_Bignum256_bn_to_bytes_be(bytes, res);
    }

    uint64_t Bignum256::lessThan(uint64_t *a, uint64_t *b) { return Hacl_Bignum256_lt_mask(a, b); }

    void Bignum256::mod(uint64_t *a, uint64_t *res) const
    {
        Hacl_Bignum256_mod_precomp(pimpl->context.get(), a, res);
    }

    void Bignum256::modExp(uint64_t *a, uint32_t bBits, uint64_t *b, uint64_t *res,
                           bool useConstTime /* = true */) const
    {
        if (bBits <= 0) {
            throw out_of_range("hacl::Bignum256->modExp:: bbits <= 0");
        }
        if (useConstTime) {
            return Hacl_Bignum256_mod_exp_consttime_precomp(pimpl->context.get(), a, bBits, b, res);
        }
        return Hacl_Bignum256_mod_exp_vartime_precomp(pimpl->context.get(), a, bBits, b, res);
    }

    void Bignum256::modInvPrime(uint64_t *a, uint64_t *res) const
    {
        Hacl_Bignum256_mod_inv_prime_vartime_precomp(pimpl->context.get(), a, res);
    }

} // namespace hacl