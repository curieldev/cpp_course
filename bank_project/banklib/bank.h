#ifndef BANK_LIB_H
#define BANK_LIB_H

#include <iostream>
#include <fstream>
#include <vector>

constexpr char BANK_DB[]   = "bank_storage.csv";
constexpr char ID_RECORD[] = "id_record.data";

constexpr unsigned char OPERATION_MIN_VALUE = 1;
constexpr unsigned char OPERATION_MAX_VALUE = 7;

constexpr int ACCOUNT_DOES_NOT_EXIST = -1;
constexpr int INVALID_INDEX          = -1;
constexpr int INSUFFICIENT_FUNDS     = -2;

enum class BankOperation
{
  OpenAccount = OPERATION_MIN_VALUE,
  AccountBalance,
  Deposit,
  Withdraw,
  CloseAccount,
  DisplayAllAccounts,
  Quit
};

class BankAccount
{
  private:
    unsigned int id;
    std::string first_name;
    std::string last_name;
    int balance;

  public:
    unsigned int get_id();
    int get_balance();
    void deposit (unsigned int amount);
    int withdraw (unsigned int amount);
    friend std::ostream & operator << (std::ostream &out, BankAccount &account);
    friend std::ofstream & operator << (std::ofstream &outputFile, 
                                        BankAccount &account);
    friend std::ifstream & operator >> (std::ifstream &inputFile, 
                                        BankAccount &account);
    BankAccount (const std::string &first_name, const std::string &last_name,
                 const int balance, const unsigned int id);
};

class Bank
{
  private:
    std::vector<BankAccount> Accounts;
    static unsigned int last_id;

    int find_account_index(unsigned int id);
    void syncData();

  public:
    Bank();
    ~Bank ();
    void open_account(std::string new_fname, std::string new_lname, 
                      int new_balance);
    void display_all_accounts();
    int deposit(unsigned int id, unsigned int amount);
    int withdraw(unsigned int id, unsigned int amount);
    int get_balance(unsigned int id);
    int close_account(unsigned int id);
};


#endif  // BANK_LIB_H