#include <iostream>
#include <string>
#include <limits>

#include "bank.h"
#include "bank_utils.h"

void doOperation(Bank &bank, const BankOperation operation)
{
  switch (operation)
  {
    case BankOperation::OpenAccount:
    {
      std::string firstName, lastName;
      int balance;

      readName("First Name: ", firstName);
      readName("Last Name: ", lastName);
      balance = readInt("Initial Balance: ", 0, INT_MAX);
      bank.openAccount(firstName, lastName, balance);

      std::cout << "Account was created successfully." << std::endl << std::endl;
      break;
    }
    case BankOperation::AccountBalance:
    {
      unsigned int id;
      int balance;

      id      = readInt("Enter Account ID: ", 1, INT_MAX);
      balance = bank.get_balance(id);

      if (balance == ACCOUNT_DOES_NOT_EXIST)
        std::cout << "Account was not found." << std::endl << std::endl;
      else
        std::cout << "Account Balance: " << balance << std::endl << std::endl;

      break;
    }
    case BankOperation::Deposit:
    {
      unsigned int id;
      int amount, deposit_result;

      id             = readInt("Enter Account ID: ", 1, INT_MAX);
      amount         = readInt("Enter amount: ", 1, INT_MAX);
      deposit_result = bank.deposit(id, amount);

      if (deposit_result == ACCOUNT_DOES_NOT_EXIST)
        std::cout << "Account was not found." << std::endl << std::endl;
      else if (deposit_result == OUT_OF_BOUNDS)
        std::cout << "Bank cannot handle this much." << std::endl << std::endl;
      else
        std::cout << "Deposit was successful." << std::endl << std::endl;

      break;
    }
    case BankOperation::Withdraw:
    {
      unsigned int id;
      int amount, withdraw_result;

      id              = readInt("Enter Account ID: ", 1, INT_MAX);
      amount          = readInt("Enter amount: ", 1, INT_MAX);
      withdraw_result = bank.withdraw(id, amount);

      if (withdraw_result == ACCOUNT_DOES_NOT_EXIST)
        std::cout << "Account was not found." << std::endl << std::endl;
      else if (withdraw_result == OUT_OF_BOUNDS)
        std::cout << "Insufficient funds." << std::endl << std::endl;
      else
        std::cout << "Withdraw was successful." << std::endl << std::endl;

      break;
    }
    case BankOperation::CloseAccount:
    {
      unsigned int id;
      int operation_result;

      id = readInt("Enter Account ID: ", 1, INT_MAX);
      operation_result = bank.close_account(id);

      if (operation_result == ACCOUNT_DOES_NOT_EXIST)
        std::cout << "Account was not found." << std::endl << std::endl;
      else
        std::cout << "Account successfully removed." << std::endl << std::endl;

      break;
    }
    case BankOperation::DisplayAllAccounts:
    {
      bank.display_all_accounts();
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


bool isNameValid (const std::string &str)
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

void readName (const std::string &prompt, std::string &result)
{
  do
  {
    std::cout << prompt;
    std::getline(std::cin, result);
  } while (!isNameValid(result));
}

bool isStringInt (const std::string &str)
{
  int i = (str[0] == '-') ? 1 : 0;
  for (; i < str.size(); i++)
  {
    if (!isdigit(str[i]))
    {
      std::cout << "Enter a valid number. Only integer numbers ";
      std::cout << "are allowed." << std::endl << std::endl;
      return false;
    }
  }

  return true;
}

bool isNumberValid (const long long num, const int min, const int max)
{
  bool isValid = (num >= min && num <= max);

  if (!isValid)
  {
    std::cout << "Enter a valid number. [" << min << ',' << max << ']';
    std::cout << std::endl << std::endl;
  }

  return isValid;
}

int readInt (const std::string &prompt, const int min = INT_MIN, 
             const int max = INT_MAX)
{
  std::string input;
  do
  {
    std::cout << prompt;
    std::getline(std::cin, input);
  } while (!(isStringInt(input) && isNumberValid(stoll(input), min, max)));

  std::cout << std::endl;
  return stoi(input);
}

BankOperation readOperation()
{
  return static_cast<BankOperation>(readInt("Select: ", OPERATION_MIN_VALUE, 
                                    OPERATION_MAX_VALUE));
}

void displayMenu()
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