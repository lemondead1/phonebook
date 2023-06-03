cmake_minimum_required(VERSION 3.9)
project(phonebook)

set(CMAKE_CXX_STANDARD 11)

add_executable(phonebook main.cpp Person.cpp Person.h Date.cpp Date.h Phonebook.cpp Phonebook.h)
