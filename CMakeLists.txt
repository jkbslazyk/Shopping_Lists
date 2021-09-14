cmake_minimum_required(VERSION 3.17)
project(SlazykJakub-etap3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SlazykJakub-etap3 main.cpp List.cpp List.h Product.cpp Product.h byWeight.cpp byWeight.h byUnit.cpp byUnit.h byLiters.cpp byLiters.h Vector.h)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stdin1.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stdin2.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stdin3.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
