#include <iostream>

using std::ostream;
using std::cout;

class Rational
{
  int numerator;
  int denominator;

  public:
    Rational (void)
    {
      this->numerator   = 1;
      this->denominator = 1;
    }

    Rational (int numerator, int denominator)
    {
      this->denominator = denominator;
      this->numerator   = numerator;
    }

    Rational operator + (Rational r)
    {
      Rational result;

      result.numerator    = this->numerator * r.denominator + r.numerator * this->denominator;
      result.denominator  = this->denominator * r.denominator;

      return result;
    }

    friend ostream & operator << (ostream &os, Rational &r);
};

ostream & operator << (ostream &os, Rational &r)
{
  os << r.numerator << "/" << r.denominator;
  return os;
}

int main (int argc, char *argv[])
{
  Rational r1(13, 5), r2(9, 7), r3;
  r3 = r1 + r2;

  cout << "The sum of " << r1 << " and " << r2 << " is " << r3;
}
