#include <string>

#include "bank.h"

unsigned int Bank::last_id = 0;

BankAccount::BankAccount (const std::string &first_name = "", 
                          const std::string &last_name = "",
                          const int balance = 0, 
                          const unsigned int id = 0)
{
  this->first_name = first_name;
  this->last_name  = last_name;
  this->balance    = balance;
  this->id         = id;
}

unsigned int BankAccount::get_id()
{
  return this->id;
}

int BankAccount::get_balance()
{
  return this->balance;
}

int BankAccount::deposit (unsigned int amount)
{
  if ((this->balance > 0) && (static_cast<int>(amount) > INT_MAX - this->balance))
    return OUT_OF_BOUNDS;

  this->balance += amount;
  return OK;
}

int BankAccount::withdraw (unsigned int amount)
{
  if ((this->balance - static_cast<int>(amount)) < 0)
    return OUT_OF_BOUNDS;
  
  this->balance -= amount;
  return OK;
}

std::ostream & operator << (std::ostream &os, BankAccount &account)
{
  os << "Account ID: " << account.id << std::endl;
  os << "First Name: " << account.first_name << std::endl;
  os << "Last Name:  " << account.last_name << std::endl;
  os << "Balance:    " << account.balance << std::endl;
  return os;
}

std::ofstream & operator << (std::ofstream &ofs, BankAccount &account)
{
  ofs << account.id << ',' << account.first_name << ',';
  ofs << account.last_name << ',' << account.balance << std::endl;
  return ofs;
}

std::ifstream & operator >> (std::ifstream &ifs, BankAccount &account)
{
  ifs >> account.id;
  ifs.ignore(1, ',');
  std::getline(ifs, account.first_name, ',');
  std::getline(ifs, account.last_name, ',');
  ifs >> account.balance;
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

void Bank::openAccount(const std::string &firstName, 
                        const std::string &lastname, const int balance)
{
  BankAccount newAccount(firstName, lastname, balance, ++last_id);
  Accounts.push_back(newAccount);
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
  int depositResult;
  int account_index = find_account_index(id);

  if (account_index == INVALID_INDEX)
    return ACCOUNT_DOES_NOT_EXIST;

  depositResult = Accounts[account_index].deposit(amount);
  
  if (depositResult == OK)
    syncData();

  return depositResult;
}

int Bank::withdraw(unsigned int id, unsigned int amount)
{
  int withdrawResult;
  int account_index = find_account_index(id);

  if (account_index == INVALID_INDEX)
    return ACCOUNT_DOES_NOT_EXIST;

  withdrawResult = Accounts[account_index].withdraw(amount);
  if (withdrawResult == OK)
    syncData();

  return withdrawResult;
}

int Bank::get_balance(unsigned int id)
{

  int account_index = find_account_index(id);

  if (account_index == INVALID_INDEX)
    return ACCOUNT_DOES_NOT_EXIST;

  return Accounts[account_index].get_balance();
}