#include <iostream>

using std::cout;
using std::endl;

#define PI  3.14159f

class Shape
{
  public:
    virtual float area (void)      = 0;
    virtual float perimeter (void) = 0;
};

class Rectangle : public Shape
{
  private:
    float length;
    float width;
  
  public:
    Rectangle (float length = 1, float width = 1)
    {
      this->length = length;
      this->width  = width;
    }

    float area (void)
    {
      return length * width;
    }

    float perimeter (void)
    {
      return 2 * (length + width);
    }
};

class Circle : public Shape
{
  private:
    float radius;
  
  public:
    Circle (float radius = 1)
    {
      this->radius = radius;
    }

    float area (void)
    {
      return PI * radius * radius;
    }

    float perimeter (void)
    {
      return 2 * PI * radius;
    }
};

int main (int argc, char* argv[])
{
  Shape *shape = new Rectangle(10, 5);
  cout << "Area of Rectangle: " << shape->area() << endl;
  cout << "Perimeter of Rectangle: " << shape->perimeter() << endl;

  shape = new Circle(10);
  cout << "Area of Circle: " << shape->area() << endl;
  cout << "Perimeter of Circle: " << shape->perimeter() << endl;
}