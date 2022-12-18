// Ideas to improve project
// TODO:
// 
// DONE:
// Add limits for deposit and withdraw to avoid overflow
// Add const where needed.
// Change raw pointers to references
// Update extraction operator overload,
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
  BankOperation doThis;

  do
  {
    displayMenu();
    doThis = readOperation();
    doOperation(neoBank, doThis);
  }
  while(doThis != BankOperation::Quit);
  return 0;
}
