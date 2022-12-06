#include <iostream>

using std::exception;
using std::cin;
using std::cout;
using std::endl;


class StackOverFlow  : exception{};
class StackUnderFlow : exception{};

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

  char keep_running;
  for (;;)
  {
    char selection;

    cout << "Push, pop or quit? u/o/q: ";
    cin >> selection;

    if (tolower(selection) == 'q')
    {
      break;
    }
    else if (tolower(selection) == 'u')
    {
      int n;
      cout << "Enter a number: ";
      cin >> n;
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