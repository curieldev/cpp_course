#include <iostream>

using std::cout;
using std::string;
using std::endl;

class Employee
{
  private:
    int    id;
    string name;
  
  public:
    Employee (int id, string name)
    {
      this->id   = id;
      this->name = name;
    }

    int getId()
    {
      return id;
    }

    string getName()
    {
      return name;
    }
};

class FullTime : public Employee
{
  private:
    int salary;
  
  public:
    FullTime (int id, string name, int salary) : Employee(id, name)
    {
      this->salary = salary;
    }

    int getSalary()
    {
      return salary;
    }
};

class PartTime : public Employee
{
  private:
    int wage;
  
  public:
    PartTime (int id, string name, int wage) : Employee(id, name)
    {
      this->wage = wage;
    }

    int getWage()
    {
      return wage;
    }
};

int main (int argc, char *argv[])
{
  FullTime full(5, "Jose", 3500);
  PartTime part(11, "Epifanio", 100);

  cout << "Salary of " << full.getName() << " is $" << full.getSalary() << endl;
  cout << "Daily wage of " << part.getName() << " is $" << part.getWage() << endl;
}