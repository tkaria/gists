project(SMHasher)

cmake_minimum_required(VERSION 2.4)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-g -fno-strict-aliasing -Wall")

add_library(
  SMHasherSupport
  AvalancheTest.cpp
  Bitslice.cpp
  Bitvec.cpp
  City.cpp
  crc.cpp
  DifferentialTest.cpp
  Hashes.cpp
  KeysetTest.cpp
  lookup3.cpp
  md5.cpp
  MurmurHash1.cpp
  MurmurHash2.cpp
  MurmurHash3.cpp
  Platform.cpp
  Random.cpp
  sha1.cpp
  SpeedTest.cpp
  Stats.cpp
  SuperFastHash.cpp
  Types.cpp
)

add_executable(
  SMHasher
  main.cpp
)

target_link_libraries(
  SMHasher
  SMHasherSupport
)
