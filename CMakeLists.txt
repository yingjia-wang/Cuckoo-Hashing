project(CuckooHashing)

set(CMAKE_CXX_STANDARD 11)

add_executable(CuckooHashing  bench/CuckooHashing_test.cpp)
add_executable(CuckooHashingSlots bench/CuckooHashingSlots_test.cpp)