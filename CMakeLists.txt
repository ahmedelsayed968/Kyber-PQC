cmake_minimum_required(VERSION 3.26)
project(Kyber C)

set(CMAKE_C_STANDARD 11)

add_executable(Kyber main.c
        toy.h
        toy.c
        Poly.h
        definitions.h
        Poly.c
        Cipher.h
        Cipher.c)
