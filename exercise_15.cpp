#include <iostream>
#include <fstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::vector;
using std::ws;


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

    string getName(void)
    {
      return name;
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
  ifs >> ws;
  return ifs;
}

int main (int argc, char **argv)
{
  vector<Item> items;

  ifstream itemsReadOnly;

  itemsReadOnly.open("items.csv");
  if (itemsReadOnly.is_open())
  {
    while (!itemsReadOnly.eof())
    {
      Item readItem;
      itemsReadOnly >> readItem;
      items.push_back(readItem);
    }
    itemsReadOnly.close();
  }


  while(true)
  {
    char selection;
    
    cout << "Options." << endl;
    cout << "(1) Display stored items" << endl;
    cout << "(2) Add new item" << endl;
    cout << "(3) Delete stored item" << endl;
    cout << "(4) Quit" << endl;
    cout << "Select: ";
    cin >> selection;
    cout << endl;

    if (selection == '1')
    {
      cout << "Stored items." << endl;
      int i;
      for (i = 0; i < items.size(); i++)
      {
        cout << items[i] << endl;
      }
      cout << endl;
    }
    else if (selection == '2')
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

      Item newItem(name, price, quantity);
      items.push_back(newItem);

      ofstream itemsWriteOnly;

      itemsWriteOnly.open("items.csv", ios::app);
      if (itemsWriteOnly.is_open())
      {
        itemsWriteOnly << newItem << endl;
        itemsWriteOnly.close();
      }

    }
    else if (selection == '3')
    {
      string name;
      cout << "Enter the name of the item to be deleted: ";
      cin >> name;
      cout << endl;

      vector<Item>::iterator item;
      for (item = items.begin(); item < items.end(); item++)
      {
        if (!name.compare((*item).getName()))
        {
          items.erase(item);
          cout << name << " has been removed from storage." << endl << endl;
          break;
        }
      }

      ofstream itemsWriteOnly;

      itemsWriteOnly.open("items.csv", ios::trunc);
      if (itemsWriteOnly.is_open())
      {
        for (int i = 0; i < items.size(); i++)
        {
          itemsWriteOnly << items[i] << endl;
        }
        itemsWriteOnly.close();
      }

    }
    else
    {
      break;
    }
  } 

  return 0;
}