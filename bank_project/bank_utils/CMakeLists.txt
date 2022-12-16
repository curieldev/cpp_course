add_library(BankUtils bank_utils.cc)
target_link_libraries(BankUtils PUBLIC BankLib)
target_include_directories(BankUtils PUBLIC
                          "${CMAKE_CURRENT_SOURCE_DIR}/../banklib"
                          )