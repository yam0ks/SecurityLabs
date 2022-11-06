cmake_minimum_required(VERSION 3.2)

project(FileSystem LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(FileSystem)

find_package(Qt5 REQUIRED COMPONENTS Widgets Xml)
find_package(libzippp REQUIRED)

set_target_properties(FileSystem PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON

  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug/FileSystem
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release/FileSystem
  AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms

  AUTOUIC ON
  AUTOMOC ON
)

set(SRC
  src/main.cpp
  src/DiskManager.cpp
  src/FileManager.cpp
  src/FormatParser.cpp
  src/Console.cpp include/Console.h
  src/TextDialog.cpp include/TextDialog.h
  src/ZipDialog.cpp include/ZipDialog.h
  src/FormatDialog.cpp include/FormatDialog.h
)

target_include_directories(FileSystem
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(FileSystem PRIVATE ${SRC})

target_link_libraries(FileSystem PRIVATE Qt5::Widgets Qt5::Xml libzippp::libzippp)
