// Ideas to improve project
// TODO:
// Change raw pointers to smart pointers
// Add const where needed.
// DONE:
// Change defines to constexpr
// Improve input handling, validate names, etc.
// Make a function to be DRY requesting input to user.

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


// User libraries
#include "bank.h"
#include "bank_utils.h"

int main (int argc, char **argv)
{
  Bank neoBank;
  BankOperation chosenOperation;

  do
  {
    displayMenu();
    chosenOperation = readOperation();
    doOperation(&neoBank, chosenOperation);
  }
  while(chosenOperation != BankOperation::Quit);
  return 0;
}
