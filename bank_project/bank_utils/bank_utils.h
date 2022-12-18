#ifndef BANK_UTILS_LIB_H
#define BANK_UTILS_LIB_H

#include "bank.h"

constexpr std::streamsize IGNORE_CHARS = 256;

void displayMenu();
BankOperation readOperation();
int readInt (const std::string &prompt, const int min, 
             const int max);
bool isNumberValid (const long long num, const int min, const int max);
bool isStringInt (const std::string &str);
void readName (const std::string &prompt, std::string &result);
bool isNameValid (const std::string &str);
void doOperation(Bank &bank, const BankOperation operation);

#endif  // BANK_UTILS_LIB_H