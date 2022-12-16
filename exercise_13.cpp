#include <iostream>

using std::exception;
using std::cin;
using std::cout;
using std::endl;


class StackOverFlow  : exception
{
  // Nothing to do.
};

class StackUnderFlow : exception
{
  // Nothing to do.
};

class Stack
{
  private:
    int *stack;
    int size;
    int top = -1;
  
  public:
    Stack (int stack_size)
    {
      size  = stack_size;
      stack = new int[size];
    }

    ~Stack ()
    {
      delete [] stack;
    }

    void push (int x)
    {
      if (top == (size - 1))
        throw StackOverFlow();
      
      stack[++top] = x;
    }

    int pop (void)
    {
      if (top == -1)
        throw StackUnderFlow();
      
      return stack[top--];
    }
};

int main (int argc, char **argv)
{
  int stack_size;

  cout << "Stack Exercise" << endl;
  cout << "Enter stack size: ";
  cin >> stack_size;

  Stack steak(stack_size);

  for (;;)
  {
    char selection;

    cout << "Options.";
    cout << "(u) Push" << endl;
    cout << "(o) Pop" << endl;
    cout << "(q) Quit" << endl;
    cout << "Select: ";
    cin >> selection;
    cout << endl;

    if (tolower(selection) == 'q')
    {
      break;
    }
    else if (tolower(selection) == 'u')
    {
      int n;
      cout << "Enter a number: ";
      cin >> n;
      cout << endl;
      steak.push(n);
    }
    else if (tolower(selection) == 'o')
    {
      cout << "Popped: " << steak.pop() << endl;
    }
    else 
    {
      cout << "Enter a valid option (u) for push, (o) for pop." << endl;
      continue;
    }
  }
  
  return 0;
}