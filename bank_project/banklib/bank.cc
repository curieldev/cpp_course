#include "bank.h"

unsigned int Bank::last_id = 0;

BankAccount::BankAccount (std::string first_name = "", 
                          std::string last_name = "",
                          int balance = 0, 
                          unsigned int id = 0)
{
  first_name_ = first_name;
  last_name_  = last_name;
  balance_    = balance;
  id_ = id;
}

unsigned int BankAccount::get_id()
{
  return id_;
}

int BankAccount::get_balance()
{
  return balance_;
}

void BankAccount::deposit (unsigned int amount)
{
  balance_ += amount;
}

int BankAccount::withdraw (unsigned int amount)
{
  if ((balance_ - static_cast<int>(amount)) < 0)
    return INSUFFICIENT_FUNDS;
  
  balance_ -= amount;
  return 0;
}

std::ostream & operator << (std::ostream &os, BankAccount &account)
{
  os << "Account ID: " << account.id_ << std::endl;
  os << "First Name: " << account.first_name_ << std::endl;
  os << "Last Name:  " << account.last_name_ << std::endl;
  os << "Balance:    " << account.balance_ << std::endl;
  return os;
}

std::ofstream & operator << (std::ofstream &ofs, BankAccount &account)
{
  ofs << account.id_ << ' ' << account.first_name_ << ' ';
  ofs << account.last_name_ << ' ' << account.balance_ << std::endl;
  return ofs;
}

std::ifstream & operator >> (std::ifstream &ifs, BankAccount &account)
{
  ifs >> account.id_ >> account.first_name_;
  ifs >> account.last_name_ >> account.balance_;
  ifs >> std::ws;
  return ifs;
}

int Bank::find_account_index(unsigned int id)
{
  int index = INVALID_INDEX;

  for (int i = 0; i < Accounts.size(); i++)
  {
    if (Accounts[i].get_id() == id)
    {
      index = i;
      break;
    }
  }
  return index;
}

void Bank::syncData()
{
  std::ofstream outFile;

  if (Accounts.size() == 0 || last_id == 0)
    return;

  outFile.open(BANK_DB, std::ios::trunc);
  if (outFile.is_open())
  {
    for (int i = 0; i < Accounts.size(); i++)
    {
      outFile << Accounts[i];
    }
    outFile.close();
  }

  outFile.open(ID_RECORD, std::ios::trunc);
  if (outFile.is_open())
  {
    outFile << last_id;
    outFile.close();
  }
}

Bank::Bank()
{
  std::ifstream inputFile;

  inputFile.open(BANK_DB);
  if (inputFile.is_open())
  {
    BankAccount readAccount;

    while (!inputFile.eof())
    {
      inputFile >> readAccount;
      Accounts.push_back(readAccount);
    }
    inputFile.close();
  }

  inputFile.open(ID_RECORD);
  if (inputFile.is_open())
  {
    inputFile >> last_id;
  }
}

Bank::~Bank ()
{
  syncData();
}

void Bank::open_account(std::string new_fname, std::string new_lname, 
                  int new_balance)
{
  BankAccount new_account(new_fname, new_lname, new_balance, ++last_id);
  Accounts.push_back(new_account);
  syncData();
}

void Bank::display_all_accounts()
{
  std::cout << "Stored Accounts." << std::endl;
  for (int i = 0; i < Accounts.size(); i++)
  {
    std::cout << Accounts[i] << std::endl;
  }
  std::cout << std::endl;
}

int Bank::close_account(unsigned int id)
{
  int account_index = find_account_index(id);

  if (account_index == INVALID_INDEX)
    return ACCOUNT_DOES_NOT_EXIST;

  Accounts.erase(Accounts.begin() + account_index);
  syncData();
  return 0;
}

int Bank::deposit(unsigned int id, unsigned int amount)
{
  int account_index = find_account_index(id);

  if (account_index == INVALID_INDEX)
    return ACCOUNT_DOES_NOT_EXIST;

  Accounts[account_index].deposit(amount);
  
  syncData();
  return 0;
}

int Bank::withdraw(unsigned int id, unsigned int amount)
{
  int account_index = find_account_index(id);

  if (account_index == INVALID_INDEX)
    return ACCOUNT_DOES_NOT_EXIST;

  syncData();
  return Accounts[account_index].withdraw(amount);
}

int Bank::get_balance(unsigned int id)
{

  int account_index = find_account_index(id);

  if (account_index == INVALID_INDEX)
    return ACCOUNT_DOES_NOT_EXIST;

  return Accounts[account_index].get_balance();
}