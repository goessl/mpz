#ifndef BIGINT_H
#define BIGINT_H



#include <gmp.h>
#include <map>
#include <string>
#include <ostream>



class Mpz {
private:
    mpz_t x;
    //https://gmplib.org/manual/Random-State-Initialization
    static gmp_randstate_t randState;
    static bool isRandStateInitialized;

public:
    //Construction
    //https://gmplib.org/manual/Initializing-Integers
    //https://gmplib.org/manual/Simultaneous-Integer-Init-_0026-Assign
    Mpz();
    explicit Mpz(const long n);
    explicit Mpz(const unsigned long n);
    explicit Mpz(const std::string& s);
    explicit Mpz(const mpz_t& x);
    Mpz(const Mpz& other); //copy
    Mpz(Mpz&& other); //move
    ~Mpz();

    void realloc() const;

    Mpz& operator=(const Mpz& other); //copy
    Mpz& operator=(Mpz&& other); //move



    //https://gmplib.org/manual/Integer-Random-Numbers
    static Mpz rand(const Mpz& n);



    //Conversion
    //https://gmplib.org/manual/Miscellaneous-Integer-Functions
    [[nodiscard]] bool fits_ul() const;
    [[nodiscard]] bool fits_sl() const;
    [[nodiscard]] bool fits_ui() const;
    [[nodiscard]] bool fits_si() const;
    [[nodiscard]] bool fits_us() const;
    [[nodiscard]] bool fits_ss() const;
    //https://gmplib.org/manual/Miscellaneous-Integer-Functions
    [[nodiscard]] bool is_odd() const;
    [[nodiscard]] bool is_even() const;
    [[nodiscard]] size_t size_in_base(const int base=2) const;
    //https://gmplib.org/manual/Converting-Integers
    explicit operator unsigned long() const;
    explicit operator long() const;
    explicit operator double() const;
    [[nodiscard]] std::string to_string(const int base=10) const;



    //Ordering
    //https://gmplib.org/manual/Integer-Comparisons
    explicit operator bool() const;

    friend bool operator==(const long lhs, const Mpz& rhs);
    friend bool operator==(const unsigned long lhs, const Mpz& rhs);
    friend bool operator==(const Mpz& lhs, const long rhs);
    friend bool operator==(const Mpz& lhs, const unsigned long rhs);
    friend bool operator==(const Mpz& lhs, const Mpz& rhs);

    friend int operator<=>(const long lhs, const Mpz& rhs);
    friend int operator<=>(const unsigned long lhs, const Mpz& rhs);
    friend int operator<=>(const Mpz& lhs, const long rhs);
    friend int operator<=>(const Mpz& lhs, const unsigned long rhs);
    friend int operator<=>(const Mpz& lhs, const Mpz& rhs);

    friend int sgn(const Mpz& s);



    //Arithmetic
    //https://gmplib.org/manual/Integer-Arithmetic
    friend Mpz operator-(const Mpz& x);

    friend Mpz operator+(const unsigned long lhs, const Mpz& rhs);
    friend Mpz operator+(const Mpz& lhs, const unsigned long rhs);
    friend Mpz operator+(const Mpz& lhs, const Mpz& rhs);
    Mpz& operator+=(const unsigned long other);
    Mpz& operator+=(const Mpz& other);
    Mpz& operator++(); //prefix
    Mpz operator++(const int n); //postfix

    friend Mpz operator-(const unsigned long lhs, const Mpz& rhs);
    friend Mpz operator-(const Mpz& lhs, const unsigned long rhs);
    friend Mpz operator-(const Mpz& lhs, const Mpz& rhs);
    Mpz& operator-=(const unsigned long other);
    Mpz& operator-=(const Mpz& other);
    Mpz& operator--(); //prefix
    Mpz operator--(const int n); //postfix

    friend Mpz operator*(const long lhs, const Mpz& rhs);
    friend Mpz operator*(const unsigned long lhs, const Mpz& rhs);
    friend Mpz operator*(const Mpz& lhs, const long rhs);
    friend Mpz operator*(const Mpz& lhs, const unsigned long rhs);
    friend Mpz operator*(const Mpz& lhs, const Mpz& rhs);
    Mpz& operator*=(const long other);
    Mpz& operator*=(const unsigned long other);
    Mpz& operator*=(const Mpz& other);

    //https://gmplib.org/manual/Integer-Division
    friend Mpz operator/(const Mpz& lhs, const unsigned long rhs); //Signedness issues!!!
    friend Mpz operator/(const Mpz& lhs, const Mpz& rhs);
    Mpz& operator/=(const unsigned long other);
    Mpz& operator/=(const Mpz& other);

    //TODO: mpz_mod?, mpz_mod_ui?
    friend Mpz operator%(const Mpz& lhs, const unsigned long rhs); //Signedness issues!!!
    friend Mpz operator%(const Mpz& lhs, const Mpz& rhs);
    Mpz& operator%=(const unsigned long other);
    Mpz& operator%=(const Mpz& other);



    //bitwise
    //https://gmplib.org/manual/Integer-Logic-and-Bit-Fiddling
    friend Mpz operator&(const Mpz& lhs, const Mpz& rhs);
    Mpz& operator&=(const Mpz& other);

    friend Mpz operator|(const Mpz& lhs, const Mpz& rhs);
    Mpz& operator|=(const Mpz& other);

    friend Mpz operator^(const Mpz& lhs, const Mpz& rhs);
    Mpz& operator^=(const Mpz& other);

    friend Mpz operator<<(const Mpz& lhs, const unsigned long rhs);
    Mpz& operator<<=(const unsigned long other);

    friend Mpz operator>>(const Mpz& lhs, const unsigned long rhs);
    Mpz& operator>>=(const unsigned long other);



    //Functions
    //https://gmplib.org/manual/Integer-Arithmetic
    friend Mpz abs(const Mpz& x);

    //https://gmplib.org/manual/Integer-Exponentiation
    friend Mpz pow(const Mpz& b, const unsigned long e);
    friend Mpz powul(const unsigned long b, const unsigned long e);
    //https://gmplib.org/manual/Integer-Roots
    friend Mpz root(const Mpz& x, const unsigned long n);
    friend Mpz sqrt(const Mpz& x);
    //https://gmplib.org/manual/Number-Theoretic-Functions
    friend Mpz gcd(const Mpz& a, const Mpz& b);
    friend Mpz gcd(const Mpz& a, const unsigned long b);

    friend Mpz lcm(const Mpz& a, const Mpz& b);
    friend Mpz lcm(const Mpz& a, const unsigned long b);

    friend Mpz fac(const unsigned long n);
    friend Mpz fac2(const unsigned long n);

    friend Mpz bin(const Mpz& n, const unsigned long k);
    friend Mpz bin(const unsigned long n, unsigned long k);

    friend Mpz fib(const unsigned long n);



    //IO
    friend std::ostream& operator<<(std::ostream& os, const Mpz& x);
};


Mpz pow(Mpz b, Mpz e);
Mpz powul(const unsigned long b, const unsigned long e);
Mpz fac(const unsigned long n);
Mpz fac2(const unsigned long n);
Mpz bin(const unsigned long n, const unsigned long k);
Mpz fib(const unsigned long n);
std::map<Mpz, unsigned long> factorise(Mpz n);



#endif //BIGINT_H
