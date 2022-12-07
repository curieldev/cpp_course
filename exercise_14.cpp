#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;

class Item
{
  private:
    string name;
    int price;
    int quantity;

  public:
    Item (void)
    {
      name = "";
      price = 0;
      quantity = 0;
    }
    Item (string name, int price, int quantity)
    {
      this->name     = name;
      this->price    = price;
      this->quantity = quantity;
    }

    friend ostream & operator << (ostream &os, Item &i);
    friend ofstream & operator << (ofstream &ofs, Item &i);
    friend ifstream & operator >> (ifstream &ifs, Item &i);
};

ostream & operator << (ostream &os, Item &i)
{
  os << "Item:     " << i.name << endl;
  os << "Price:    " << i.price << endl;
  os << "Quantity: " << i.quantity << endl;
  return os;
}

ofstream & operator << (ofstream &ofs, Item &i)
{
  ofs << i.name << ' ' << i.price << ' ' << i.quantity;
  return ofs;
}

ifstream & operator >> (ifstream &ifs, Item &i)
{
  ifs >> i.name >> i.price >> i.quantity;
  return ifs;
}

int main (int argc, char **argv)
{
  while(true)
  {
    char selection;
    
    cout << "Options." << endl;
    cout << "(a) Add new item" << endl;
    cout << "(d) Display stored items" << endl;
    cout << "(q) Quit" << endl;
    cout << "Select: ";
    cin >> selection;
    cout << endl;

    if (tolower(selection) == 'a')
    {
      string name;
      int price;
      int quantity;
      cout << "Name: ";
      cin >> name;
      cout << "Price: ";
      cin >> price;
      cout << "Quantity: ";
      cin >> quantity;
      cout << endl;

      Item item(name, price, quantity);

      ofstream itemsFile;

      itemsFile.open("items.csv", ios::app);
      if (itemsFile.is_open())
      {
        itemsFile << item;
        itemsFile.close();
      }

    }
    else if (tolower(selection) == 'd')
    {
      ifstream ifs;

      ifs.open("items.csv");
      if (ifs.is_open())
      {
        cout << "Stored items." << endl;
        while (!ifs.eof())
        {
          Item item;
          ifs >> item;
          cout << item << endl;
        }
        ifs.close();
      }
    }
    else
    {
      break;
    }
  } 

  return 0;
}