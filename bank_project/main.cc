// Ideas to improve project
//
// Change defines to constexpr
// Find a way to not return multiple values as pointer parameters.
// Change raw pointers to smart pointers
// Improve input handling, validate names, etc.
// Make a function to be DRY requesting input to user.
// Add const where needed.

// Banking System Project
// Features:
// Open account
// Account Balance
// Make a deposit
// Withdraw
// Close account
// Show all accounts

// Pseudocode
// Display Menu
// Get selection
// Perform operation
// Repeat as needed

// Standard libraries
#include <iostream>
#include <string>

// User libraries
#include "bank.h"

constexpr std::streamsize IGNORE_CHARS = 256;

void display_menu();
BankOperation get_operation();
void perform_operation(Bank * const bank, BankOperation operation);
void get_account_data(std::string * const fname, std::string * const lname, 
                      int * const balance);
void get_account_id(unsigned int * const id);
void get_transaction_data(unsigned int * const id, int * const amount);

int main (int argc, char **argv)
{
  Bank neoBank;
  BankOperation chosenOperation;

  do
  {
    display_menu();
    chosenOperation = get_operation();
    perform_operation(&neoBank, chosenOperation);
  }
  while(chosenOperation != BankOperation::Quit);
  return 0;
}



void perform_operation(Bank * const bank, BankOperation operation)
{
  switch (operation)
  {
    case BankOperation::OpenAccount:
    {
      std::string new_fname;
      std::string new_lname;
      int new_balance;
      get_account_data(&new_fname, &new_lname, &new_balance);
      bank->open_account(new_fname, new_lname, new_balance);
      std::cout << "Account was created successfully." << std::endl;
      std::cout << std::endl;
      break;
    }
    case BankOperation::AccountBalance:
    {
      unsigned int id;
      int balance;
      get_account_id(&id);
      balance = bank->get_balance(id);

      if (balance == ACCOUNT_DOES_NOT_EXIST)
        std::cout << "Account was not found." << std::endl << std::endl;
      else
        std::cout << "Account Balance: " << balance << std::endl << std::endl;

      break;
    }
    case BankOperation::Deposit:
    {
      unsigned int id;
      int amount;
      int deposit_result;

      get_transaction_data(&id, &amount);
      deposit_result = bank->deposit(id, amount);

      if (deposit_result == ACCOUNT_DOES_NOT_EXIST)
        std::cout << "Account was not found." << std::endl << std::endl;
      else
        std::cout << "Deposit was successful." << std::endl << std::endl;

      break;
    }
    case BankOperation::Withdraw:
    {
      unsigned int id;
      int amount;
      int withdraw_result;
      get_transaction_data(&id, &amount);
      withdraw_result = bank->withdraw(id, amount);

      if (withdraw_result == ACCOUNT_DOES_NOT_EXIST)
      {
        std::cout << "Account was not found." << std::endl << std::endl;
      }
      if (withdraw_result == INSUFFICIENT_FUNDS)
      {
        std::cout << "Insufficient funds." << std::endl << std::endl;
      }
      else
      {
        std::cout << "Withdraw was successful." << std::endl << std::endl;
      }

      break;
    }
    case BankOperation::CloseAccount:
    {
      unsigned int id;
      int operation_result;
      get_account_id(&id);
      operation_result = bank->close_account(id);

      if (operation_result == ACCOUNT_DOES_NOT_EXIST)
        std::cout << "Account was not found." << std::endl << std::endl;
      else
        std::cout << "Account successfully removed." << std::endl << std::endl;

      break;
    }
    case BankOperation::DisplayAllAccounts:
    {
      bank->display_all_accounts();
      break;
    }
    case BankOperation::Quit:
    {
      // Do nothing.
      break;
    }

    default:
      break;
  }
}

void get_transaction_data(unsigned int * const id, int * const amount)
{
  get_account_id(id);

  while (true)
  {
    std::cout << "Enter amount: ";
    std::cin >> *amount;
    std::cout << std::endl;
    std::cin.ignore(IGNORE_CHARS, '\n');

    if(std::cin.fail())
    {
      std::cin.clear();
      std::cout << "Enter a valid number." << std::endl << std::endl;
      continue;
    }

    if (*amount < 0)
    {
      std::cout << "Amount must be a positive number.";
      std::cout << std::endl << std::endl;
      continue;
    }

    break;
  }
  std::cout << std::endl;
}

void get_account_id(unsigned int * const id)
{
  while (true)
  {
    std::cout << "Enter Account ID: ";
    std::cin >> *id;
    std::cout << std::endl;
    std::cin.ignore(IGNORE_CHARS, '\n');

    if(std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(IGNORE_CHARS, '\n');
      std::cout << "Enter a valid number." << std::endl << std::endl;
      continue;
    }

    if (*id < 1)
    {
      std::cout << "Balance must be a positive number." << std::endl;
      continue;
    }

    break;
  }
}

bool isNameValid (std::string &str)
{
  for (int i = 0; i < str.size(); i++)
  {
    if (!(isalpha(str[i]) || isblank(str[i])))
    {
      std::cout << "Enter a valid name. Only alphabetic letters and spaces ";
      std::cout << "are allowed." << std::endl << std::endl;
      return false;
    }
  }
  return true;
}

void readName (const std::string &prompt, std::string * const result)
{
  do
  {
    std::cout << prompt;
    std::getline(std::cin, *result);
    // std::cin.ignore(IGNORE_CHARS, '\n');
  } while (!isNameValid(*result));
}

void get_account_data(std::string * const fname, std::string * const lname, 
                      int * const balance)
{
  readName("First Name: ", fname);
  readName("Last Name: ", lname);

  while (true)
  {
    std::cout << "Initial Balance: ";
    std::cin >> *balance;
    std::cin.ignore(IGNORE_CHARS, '\n');

    if(std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(IGNORE_CHARS, '\n');
      std::cout << "Enter a valid number." << std::endl << std::endl;
      continue;
    }

    if (*balance < 0)
    {
      std::cout << "Balance must be a positive number.";
      std::cout << std::endl << std::endl;
      continue;
    }

    break;
  }
  std::cout << std::endl;
}

BankOperation get_operation()
{
  int user_selection;
  for(;;)
  {
    std::cout << "Select: ";
    std::cin >> user_selection;
    std::cin.ignore(IGNORE_CHARS, '\n');

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(IGNORE_CHARS, '\n');
    }

    if (user_selection < OPERATION_MIN_VALUE ||
        user_selection > OPERATION_MAX_VALUE)
      std::cout << "Enter a valid option (1-7)" << std::endl << std::endl;
    else
      break;
  }
  std::cout << std::endl;
  return static_cast<BankOperation>(user_selection);
}

void display_menu()
{
  std::cout << "[BANKING SYSTEM]" << std::endl;
  std::cout << "(1) Open Account" << std::endl;
  std::cout << "(2) Account Balance" << std::endl;
  std::cout << "(3) Deposit" << std::endl;
  std::cout << "(4) Withdraw" << std::endl;
  std::cout << "(5) Close Account" << std::endl;
  std::cout << "(6) Display All Accounts" << std::endl;
  std::cout << "(7) Quit" << std::endl;
}
