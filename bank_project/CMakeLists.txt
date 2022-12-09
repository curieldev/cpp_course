cmake_minimum_required(VERSION 3.2)

project(CPP_COURSE)

set(CMAKE_CXX_STANDARD 11)

add_executable(BankProject "${PROJECT_SOURCE_DIR}/main.cc")

add_subdirectory(banklib)
target_link_libraries(BankProject PUBLIC BankLib)
target_include_directories(BankProject PUBLIC
                          "${PROJECT_SOURCE_DIR}/banklib"
                          )