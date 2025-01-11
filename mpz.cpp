#include "mpz.h"



Mpz::Mpz() {
    mpz_init(x);
}

Mpz::Mpz(const long n) {
    mpz_init_set_si(x, n);
}
Mpz::Mpz(const unsigned long n) {
    mpz_init_set_ui(x, n);
}

Mpz::Mpz(const std::string& s) {
    if(mpz_init_set_str(x, s.c_str(), 0)) {
        mpz_clear(x);
        throw std::invalid_argument("Invalid string for Mpz initialization");
    }
}

Mpz::Mpz(const mpz_t& x) {
    mpz_init_set(this->x, x);
}

Mpz::Mpz(const Mpz& other) {
    mpz_init_set(x, other.x);
}
Mpz::Mpz(Mpz&& other) {
    mpz_init(x);
    mpz_swap(x, other.x);
}

Mpz::~Mpz() {
    mpz_clear(x);
}


void Mpz::realloc() const {
    mpz_realloc2((mpz_ptr)&x, size_in_base());
}


Mpz& Mpz::operator=(const Mpz& other) {
    if(this != &other) {
        mpz_set(x, other.x);
    }
    return *this;
}
Mpz& Mpz::operator=(Mpz&& other) {
    if(this != &other) {
        mpz_swap(x, other.x);
    }
    return *this;
}



gmp_randstate_t Mpz::randState;
bool Mpz::isRandStateInitialized = false;

Mpz Mpz::rand(const Mpz& n) {
    if(sgn(n) < 0) {
        throw std::invalid_argument("Upper bound must be positive");
    }
    if(!isRandStateInitialized) {
        gmp_randinit_default(randState);
        gmp_randseed_ui(randState, static_cast<unsigned long>(std::time(nullptr)));
        isRandStateInitialized = true;
    }

    Mpz x;
    mpz_urandomm(x.x, randState, n.x);
    return x;
}



[[nodiscard]] bool Mpz::fits_ul() const {
    return mpz_fits_ulong_p(x);
}
[[nodiscard]] bool Mpz::fits_sl() const {
    return mpz_fits_slong_p(x);
}
[[nodiscard]] bool Mpz::fits_ui() const {
    return mpz_fits_uint_p(x);
}
[[nodiscard]] bool Mpz::fits_si() const {
    return mpz_fits_sint_p(x);
}
[[nodiscard]] bool Mpz::fits_us() const {
    return mpz_fits_ushort_p(x);
}
[[nodiscard]] bool Mpz::fits_ss() const {
    return mpz_fits_sshort_p(x);
}

[[nodiscard]] bool Mpz::is_odd() const {
    return mpz_odd_p(x);
}
[[nodiscard]] bool Mpz::is_even() const {
    return mpz_even_p(x);
}

size_t Mpz::size_in_base(const int base) const {
    return mpz_sizeinbase(x, base);
}



Mpz::operator unsigned long() const {
    if(!fits_ul()) {
        throw std::bad_cast();
    }
    return mpz_get_ui(x);
}
Mpz::operator long() const {
    if(!fits_sl()) {
        throw std::bad_cast();
    }
    return mpz_get_si(x);
}
Mpz::operator double() const {
    return mpz_get_d(x);
}

std::string Mpz::to_string(const int base) const {
    std::string s;
    s.resize(size_in_base(base)+2);
    mpz_get_str(&s[0], base, x);
    s.resize(strlen(s.c_str()));
    return s;
}



Mpz::operator bool() const {
    return *this != 0l;
}


bool operator==(const long lhs, const Mpz& rhs) {
    return lhs <=> rhs == 0;
}
bool operator==(const unsigned long lhs, const Mpz& rhs) {
    return lhs <=> rhs == 0;
}

bool operator==(const Mpz& lhs, const long rhs) {
    return lhs <=> rhs == 0;
}
bool operator==(const Mpz& lhs, const unsigned long rhs) {
    return lhs <=> rhs == 0;
}

bool operator==(const Mpz& lhs, const Mpz& rhs) {
    return lhs <=> rhs == 0;
}


int operator<=>(const long lhs, const Mpz& rhs) {
    return -(rhs <=> lhs);
}
int operator<=>(const unsigned long lhs, const Mpz& rhs) {
    return -(rhs <=> lhs);
}

int operator<=>(const Mpz& lhs, const long rhs) {
    return mpz_cmp_si(lhs.x, rhs);
}
int operator<=>(const Mpz& lhs, const unsigned long rhs) {
    return mpz_cmp_ui(lhs.x, rhs);
}

int operator<=>(const Mpz& lhs, const Mpz& rhs) {
    return mpz_cmp(lhs.x, rhs.x);
}


int sgn(const Mpz& s) {
    return mpz_sgn(s.x);
}



//Arithmetic
Mpz operator-(const Mpz& x) {
    Mpz r;
    mpz_neg(r.x, x.x);
    return r;
}


//+
//https://en.cppreference.com/w/cpp/language/operators
//standard implementation would copy whole of lhs
//Mpz operator+(Mpz lhs, const unsigned long rhs) {
//    lhs += rhs;
//    return lhs;
//}
Mpz operator+(const unsigned long lhs, const Mpz& rhs) {
    return rhs + lhs;
}

Mpz operator+(const Mpz& lhs, const unsigned long rhs) {
    Mpz r;
    mpz_add_ui(r.x, lhs.x, rhs);
    return r;
}
Mpz operator+(const Mpz& lhs, const Mpz& rhs) {
    Mpz r;
    mpz_add(r.x, lhs.x, rhs.x);
    return r;
}

Mpz& Mpz::operator+=(const unsigned long other) {
    mpz_add_ui(x, x, other);
    return *this;
}
Mpz& Mpz::operator+=(const Mpz& other) {
    mpz_add(x, x, other.x);
    return *this;
}

Mpz& Mpz::operator++() {
    *this += 1;
    return *this;
}
Mpz Mpz::operator++(const int n) {
    const Mpz old = *this;
    ++*this;
    return old;
}


Mpz operator-(const unsigned long lhs, const Mpz& rhs) {
    Mpz r;
    mpz_ui_sub(r.x, lhs, rhs.x);
    return r;
}
Mpz operator-(const Mpz& lhs, const unsigned long rhs) {
    Mpz r;
    mpz_sub_ui(r.x, lhs.x, rhs);
    return r;
}
Mpz operator-(const Mpz& lhs, const Mpz& rhs) {
    Mpz r;
    mpz_sub(r.x, lhs.x, rhs.x);
    return r;
}

Mpz& Mpz::operator-=(const unsigned long other) {
    mpz_sub_ui(x, x, other);
    return *this;
}
Mpz& Mpz::operator-=(const Mpz& other) {
    mpz_sub(x, x, other.x);
    return *this;
}

Mpz& Mpz::operator--() {
    *this -= 1;
    return *this;
}
Mpz Mpz::operator--(const int n) {
    const Mpz old = *this;
    --*this;
    return old;
}


Mpz operator*(const long lhs, const Mpz& rhs) {
    return rhs * lhs;
}
Mpz operator*(const unsigned long lhs, const Mpz& rhs) {
    return rhs * lhs;
}

Mpz operator*(const Mpz& lhs, const long rhs) {
    Mpz r;
    mpz_mul_si(r.x, lhs.x, rhs);
    return r;
}
Mpz operator*(const Mpz& lhs, const unsigned long rhs) {
    Mpz r;
    mpz_mul_ui(r.x, lhs.x, rhs);
    return r;
}
Mpz operator*(const Mpz& lhs, const Mpz& rhs) {
    Mpz r;
    mpz_mul(r.x, lhs.x, rhs.x);
    return r;
}

Mpz& Mpz::operator*=(const long other) {
    mpz_mul_si(x, x, other);
    return *this;
}
Mpz& Mpz::operator*=(const unsigned long other) {
    mpz_mul_ui(x, x, other);
    return *this;
}
Mpz& Mpz::operator*=(const Mpz& other) {
    mpz_mul(x, x, other.x);
    return *this;
}


Mpz operator/(const Mpz& lhs, const unsigned long rhs) {
    Mpz r;
    mpz_tdiv_q_ui(r.x, lhs.x, rhs);
    return r;
}
Mpz operator/(const Mpz& lhs, const Mpz& rhs) {
    Mpz r;
    mpz_tdiv_q(r.x, lhs.x, rhs.x);
    return r;
}

Mpz& Mpz::operator/=(const unsigned long other) {
    mpz_tdiv_q_ui(x, x, other);
    return *this;
}
Mpz& Mpz::operator/=(const Mpz& other) {
    mpz_tdiv_q(x, x, other.x);
    return *this;
}


Mpz operator%(const Mpz& lhs, const unsigned long rhs) {
    Mpz r;
    mpz_tdiv_r_ui(r.x, lhs.x, rhs);
    return r;
}
Mpz operator%(const Mpz& lhs, const Mpz& rhs) {
    Mpz r;
    mpz_tdiv_r(r.x, lhs.x, rhs.x);
    return r;
}

Mpz& Mpz::operator%=(const unsigned long other) {
    mpz_tdiv_r_ui(x, x, other);
    return *this;
}
Mpz& Mpz::operator%=(const Mpz& other) {
    mpz_tdiv_r(x, x, other.x);
    return *this;
}




Mpz operator&(const Mpz& lhs, const Mpz& rhs) {
    Mpz r;
    mpz_and(r.x, lhs.x, rhs.x);
    return r;
}

Mpz& Mpz::operator&=(const Mpz& other) {
    mpz_and(x, x, other.x);
    return *this;
}


Mpz operator|(const Mpz& lhs, const Mpz& rhs) {
    Mpz r;
    mpz_ior(r.x, lhs.x, rhs.x);
    return r;
}

Mpz& Mpz::operator|=(const Mpz& other) {
    mpz_ior(x, x, other.x);
    return *this;
}


Mpz operator^(const Mpz& lhs, const Mpz& rhs) {
    Mpz r;
    mpz_xor(r.x, lhs.x, rhs.x);
    return r;
}

Mpz& Mpz::operator^=(const Mpz& other) {
    mpz_xor(x, x, other.x);
    return *this;
}


Mpz operator<<(const Mpz& lhs, const unsigned long rhs) {
    Mpz r;
    mpz_mul_2exp(r.x, lhs.x, rhs);
    return r;
}

Mpz& Mpz::operator<<=(const unsigned long rhs) {
    mpz_mul_2exp(x, x, rhs);
    return *this;
}


Mpz operator>>(const Mpz& lhs, const unsigned long rhs) {
    Mpz r;
    mpz_fdiv_q_2exp(r.x, lhs.x, rhs);
    return r;
}

Mpz& Mpz::operator>>=(const unsigned long rhs) {
    mpz_fdiv_q_2exp(x, x, rhs);
    return *this;
}



//Functions
Mpz abs(const Mpz& x) {
    Mpz r;
    mpz_abs(r.x, x.x);
    return r;
}


Mpz pow(const Mpz& b, const unsigned long e) {
    Mpz r;
    mpz_pow_ui(r.x, b.x, e);
    return r;
}

Mpz pow(Mpz b, Mpz e) {
    if(sgn(e) < 0) {
        throw std::invalid_argument("Mpz::pow: negative power");
    }
    if(b==0l && e!=0l) {
        return Mpz{};
    }

    Mpz result{1l};
    while(e > 0l) {
        if(e % 2) {
            result *= b;
        }
        b *= b;
        e /= 2;
    }
    return result;
}

Mpz powul(const unsigned long b, const unsigned long e) {
    Mpz r;
    mpz_ui_pow_ui(r.x, b, e);
    return r;
}


Mpz root(const Mpz& x, const unsigned long n) {
    Mpz r;
    mpz_root(r.x, x.x, n);
    return r;
}

Mpz sqrt(const Mpz& x) {
    Mpz r;
    mpz_sqrt(r.x, x.x);
    return r;
}


Mpz gcd(const Mpz& a, const Mpz& b) {
    Mpz r;
    mpz_gcd(r.x, a.x, b.x);
    return r;
}

Mpz gcd(const Mpz& a, const unsigned long b) {
    Mpz r;
    mpz_gcd_ui(r.x, a.x, b);
    return r;
}


Mpz lcm(const Mpz& a, const Mpz& b) {
    Mpz r;
    mpz_lcm(r.x, a.x, b.x);
    return r;
}

Mpz lcm(const Mpz& a, const unsigned long b) {
    Mpz r;
    mpz_lcm_ui(r.x, a.x, b);
    return r;
}


Mpz fac(const unsigned long n) {
    Mpz r;
    mpz_fac_ui(r.x, n);
    return r;
}

Mpz fac2(const unsigned long n) {
    Mpz r;
    mpz_2fac_ui(r.x, n);
    return r;
}


Mpz bin(const Mpz& n, const unsigned long k) {
    Mpz r;
    mpz_bin_ui(r.x, n.x, k);
    return r;
}

Mpz bin(const unsigned long n, const unsigned long k) {
    Mpz r;
    mpz_bin_uiui(r.x, n, k);
    return r;
}


Mpz fib(const unsigned long n) {
    Mpz r;
    mpz_fib_ui(r.x, n);
    return r;
}



std::map<Mpz, unsigned long> factorise(Mpz n) {
    if(n == 0l) {
        return {{Mpz(), 1}};
    }

    std::map<Mpz, unsigned long> f;
    if(n < 0l) {
        f[Mpz{-1l}] = 1;
        n = abs(n);
    }
    const Mpz isqrt = sqrt(n);
    for(Mpz i{2l}; i<=isqrt; ++i) {
        while(n%i == 0l) {
            n /= i;
            ++f[i];
        }
    }
    if(n > 1l) {
        ++f[n];
    }

    return f;
}



//IO
std::ostream& operator<<(std::ostream& os, const Mpz& x) {
    //implemented in libgmpxx.dylib
    return os << x.x;
}
