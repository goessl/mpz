#include <cassert>
#include <iostream>
#include <random>
#include <unordered_map>

#include "mpz.h"


using namespace std;



void test_mpz_add_sub() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<long> dist(-0xFF-1, 0xFF/2);
    uniform_int_distribution<unsigned long> udist(0x00, 0xFF);

    //+
    cout << "Testing +" << endl;
    for(unsigned int i=0; i<1000; ++i) {
        const Mpz a{dist(rng)}, b{dist(rng)};
        const unsigned long c{udist(rng)};

        //unsigned long + Mpz
        assert(static_cast<long>(c+a) == c+static_cast<long>(a));
        //Mpz + unsigned long
        assert(static_cast<long>(a+c) == static_cast<long>(a)+c);
        //Mpz + Mpz
        assert(static_cast<long>(a+b) == static_cast<long>(a)+static_cast<long>(b));
    }
    //+= && ++
    cout << "Testing += & ++" << endl;
    for(unsigned int i=0; i<1000; ++i) {
        Mpz a{dist(rng)};
        Mpz b{dist(rng)};
        const long c{dist(rng)};
        Mpz d;

        //Mpz += unsigned long
        d = a;
        a += c;
        assert(a == d+c);
        //Mpz += Mpz
        d = a;
        a += b;
        assert(a == d+b);
        //++Mpz
        b = a;
        d = ++a;
        assert(a==b+1 && d==a);
        //Mpz++
        b = a;
        d = a++;
        assert(a==b+1 && d==a-1);
    }

    //-
    cout << "Testing -" << endl;
    for(unsigned int i=0; i<1000; ++i) {
        const Mpz a{dist(rng)}, b{dist(rng)};
        const unsigned long c{udist(rng)};

        //-Mpz
        assert(static_cast<long>(-a) == -static_cast<long>(a));
        //unsigned long - Mpz
        assert(static_cast<long>(c-a) == c-static_cast<long>(a));
        //Mpz - unsigned long
        assert(static_cast<long>(a-c) == static_cast<long>(a)-c);
        //Mpz - Mpz
        assert(static_cast<long>(a-b) == static_cast<long>(a)-static_cast<long>(b));
    }
    //-= && --
    cout << "Testing -= & --" << endl;
    for(unsigned int i=0; i<1000; ++i) {
        Mpz a{dist(rng)};
        Mpz b{dist(rng)};
        const long c{dist(rng)};
        Mpz d;

        //Mpz -= unsigned long
        d = a;
        a -= c;
        assert(a == d-c);
        //Mpz -= Mpz
        d = a;
        a -= b;
        assert(a == d-b);
        //--Mpz
        b = a;
        d = --a;
        assert(a==b-1 && d==a);
        //Mpz--
        b = a;
        d = a--;
        assert(a==b-1 && d==a+1);
    }
}

void test_mpz_mul_div() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<long> dist(-0xFF-1, 0xFF/2);
    uniform_int_distribution<unsigned long> udist(0x00, 0xFF);

    //*
    cout << "Testing *" << endl;
    for(unsigned int i=0; i<1000; ++i) {
        const Mpz a{dist(rng)}, b{dist(rng)};
        const long c{dist(rng)};
        const unsigned long d{udist(rng)};

        //long * Mpz
        assert(static_cast<long>(c*a) == c*static_cast<long>(a));
        //unsigned long * Mpz
        assert(static_cast<long>(d*a) == d*static_cast<long>(a));
        //Mpz * long
        assert(static_cast<long>(a*c) == static_cast<long>(a)*c);
        //Mpz * unsigned long
        assert(static_cast<long>(a*d) == static_cast<long>(a)*d);
        //Mpz + Mpz
        assert(static_cast<long>(a*b) == static_cast<long>(a)*static_cast<long>(b));
    }
    //*=
    cout << "Testing *=" << endl;
    for(unsigned int i=0; i<1000; ++i) {
        Mpz a{dist(rng)}, b{dist(rng)};
        const long c{dist(rng)};
        const unsigned long d{udist(rng)};
        Mpz e;

        //Mpz *= long
        e = a;
        a *= c;
        assert(a == e*c);
        //Mpz *= unsigned long
        e = a;
        a *= d;
        assert(a == e*d);
        //Mpz *= Mpz
        e = a;
        a *= b;
        assert(a == e*b);
    }

    ///
    cout << "Testing /" << endl;
    for(unsigned int i=0; i<1000; ++i) {
        Mpz a, b;
        unsigned long c;
        do {
            a = Mpz{dist(rng)};
            b = Mpz{dist(rng)};
            c = udist(rng);
        } while(!a || !b || !c);

        //Mpz / unsigned long
        assert(static_cast<long>(a/c) == static_cast<long>(a)/static_cast<long>(c));
        //Mpz / Mpz
        assert(static_cast<long>(a/b) == static_cast<long>(a)/static_cast<long>(b));
    }
    ///=
    cout << "Testing /=" << endl;
    for(unsigned int i=0; i<1000; ++i) {
        Mpz a{dist(rng)}, b;
        unsigned long c;
        do {
            b = Mpz{dist(rng)};
            c = udist(rng);
        } while(!b || !c);
        Mpz e;

        //Mpz /= unsigned long
        e = a;
        a /= c;
        assert(a == e/c);
        //Mpz /= Mpz
        e = a;
        a /= b;
        assert(a == e/b);
    }


    //%
    cout << "Testing %" << endl;
    for(unsigned int i=0; i<1000; ++i) {
        Mpz a{dist(rng)}, b;
        unsigned long c;
        do {
            b = Mpz{dist(rng)};
            c = udist(rng);
        } while(!b || !c);

        //Mpz % unsigned long
        assert(static_cast<long>(a%c) == static_cast<long>(a)%static_cast<long>(c));
        //Mpz + Mpz
        assert(static_cast<long>(a%b) == static_cast<long>(a)%static_cast<long>(b));
    }
    //%=
    cout << "Testing %=" << endl;
    for(unsigned int i=0; i<1000; ++i) {
        Mpz a{dist(rng)}, b;
        unsigned long c;
        do {
            b = Mpz{dist(rng)};
            c = udist(rng);
        } while(!b || !c);
        Mpz e;

        //Mpz *= unsigned long
        e = a;
        a %= c;
        assert(a == e%c);
        //Mpz %= Mpz
        e = a;
        a %= b;
        assert(a == e%b);
    }
}



template<typename T>
constexpr bool areClose(const T a, const T b, const T rtol=1e-5, const T atol=1e-8) {
    static_assert(std::is_floating_point_v<T>, "T must be a floating-point type.");
    return abs(a - b) <= atol + rtol * abs(b);
}

void test_mpz_pow() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<long> dist(-16, +15);
    uniform_int_distribution<unsigned long> udist(0x00, 10);

    for(unsigned int i=0; i<1000; ++i) {
        const Mpz a{dist(rng)}, b{udist(rng)};
        const unsigned long c=udist(rng), d=udist(rng);

        assert(areClose(static_cast<double>(powul(c, d)), pow(static_cast<double>(c), static_cast<double>(d))));
        assert(areClose(static_cast<double>(pow(a, b)), pow(static_cast<double>(a), static_cast<double>(b))));
    }
}






unordered_map<void*, size_t> allocation_map;

void* custom_alloc(const size_t size) {
    void* ptr = malloc(size);
    if(ptr) {
        allocation_map[ptr] = size;
    }
    return ptr;
}

void* custom_realloc(void* ptr, size_t old_size, const size_t new_size) {
    if(ptr) {
        allocation_map.erase(ptr);
    }
    void* new_ptr = realloc(ptr, new_size);
    if(new_ptr) {
        allocation_map[new_ptr] = new_size;
    }
    return new_ptr;
}

void custom_free(void* ptr, size_t size) {
    if(ptr) {
        allocation_map.erase(ptr);
    }
    free(ptr);
}

void report_unfreed_memory() {
    if(!allocation_map.empty()) {
        cerr << "Memory leaks detected:" << endl;
        for(const auto& [ptr, size] : allocation_map) {
            cerr << "  Address: " << ptr << ", Size: " << size << " bytes" << endl;
        }
    } else {
        cerr << "No memory leaks detected." << endl;
    }
}




int main() {
    mp_set_memory_functions(custom_alloc, custom_realloc, custom_free);

    test_mpz_add_sub();
    test_mpz_mul_div();
    test_mpz_pow();


    {
        const auto start{std::chrono::steady_clock::now()};
        const Mpz f = fib(4'192'540);
        const auto end{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> duration{end - start};
        cout << f << endl;
        cout << "Took " << duration.count() << " s." << endl;
    }
    report_unfreed_memory();

    return 0;
}
