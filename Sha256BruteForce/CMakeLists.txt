cmake_minimum_required(VERSION 3.2)

project(Sha256BruteForce LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(Sha256BruteForce)

set_target_properties(Sha256BruteForce PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON

  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug/LRab_1
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release/LRab_1

  AUTOUIC ON
  AUTOMOC ON
)

find_package(Qt5 REQUIRED COMPONENTS Core Concurrent)

set(SRC
  src/main.cpp
  src/MenuHandler.cpp
  src/Sha256Gen.cpp
)


target_include_directories(Sha256BruteForce
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(Sha256BruteForce PRIVATE ${SRC})

target_link_libraries(Sha256BruteForce Qt5::Core Qt5::Concurrent)
