#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Student
{
  private:
    int     roll;
    string  name;
    float   marks[3];
    
  public:
    Student (int roll, string name, float marks[3])
    {
      this->roll      = roll;
      this->name      = name;
      this->marks[0]  = marks[0];
      this->marks[1]  = marks[1];
      this->marks[2]  = marks[2];
    }

    float total(void)
    {
      return marks[0] + marks[1] + marks[2];
    }

    float grade(void)
    {
      return (marks[0] + marks[1] + marks[2])/3;
    }

    string getName()
    {
      return name;
    }
};

int main (int argc, char *argv[])
{
  int     roll;
  string  name;
  float   marks[3];

  cout << "Enter Student's Roll Number: ";
  cin >> roll;
  cout << "Enter Student's Name: ";
  cin >> name;
  cout << "Enter Student's Marks (3): ";
  cin >> marks[0] >> marks[1] >> marks[2];

  Student wario(roll, name, marks);

  cout << "Grade: " << wario.grade() << endl;
  cout << "Total: " << wario.total() << endl;
  cout << "Student: " << wario.getName();

}