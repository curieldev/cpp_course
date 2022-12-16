add_executable(BankProject "${CMAKE_CURRENT_SOURCE_DIR}/main.cc")

add_subdirectory(banklib)
add_subdirectory(bank_utils)
target_link_libraries(BankProject PUBLIC BankUtils BankLib)
target_include_directories(BankProject PUBLIC
                          "${CMAKE_CURRENT_SOURCE_DIR}/banklib"
                          "${CMAKE_CURRENT_SOURCE_DIR}/bank_utils"
                          )
                          
                          