#ifndef BANK_LIB_H
#define BANK_LIB_H

#include <iostream>
#include <fstream>
#include <vector>

#define BANK_DB                   "bank_storage.csv"
#define ID_RECORD                 "id_record.data"

#define OPERATION_MIN_VALUE       1
#define OPERATION_MAX_VALUE       7

#define ACCOUNT_DOES_NOT_EXIST    (-1)
#define INVALID_INDEX             (-1)
#define INSUFFICIENT_FUNDS        (-2)


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
    unsigned int id_;
    std::string first_name_;
    std::string last_name_;
    int balance_;

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
    BankAccount (std::string first_name, std::string last_name,
                 int balance, unsigned int id);
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