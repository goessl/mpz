cmake_minimum_required(VERSION 3.29)
project(mpz)

set(CMAKE_CXX_STANDARD 26)


#Library
add_library(mpz STATIC
        mpz.cpp
        mpz.h
)

#Test
add_executable(mpz_test main.cpp
        mpz.h)

target_link_libraries(mpz_test /Users/goessl/Nextcloud/code/c/mpz/cmake-build-debug/libmpz.a)

include_directories(/usr/local/include)
target_link_libraries(mpz_test /usr/local/lib/libgmp.dylib)
target_link_libraries(mpz_test /usr/local/lib/libgmpxx.dylib)
