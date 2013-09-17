#include <iostream.h>

class Rational
{
public:
Rational (int Num1, int Num2);
Rational();
void output();

friend Rational Add(Rational Num1, Rational Num2);
friend Rational Subtract(Rational Num1, Rational Num2);
friend Rational Product(Rational Num1, Rational Num2);
friend Rational Division(Rational Num1, Rational Num2);
friend Rational Reduce(Rational Num1, Rational Num2);
friend bool Equal(Rational Num1, Rational Num2);
friend bool LessThan(Rational Num1, Rational Num2);
private:
int numerator, denominator;
};

int main()
{
cout<<"This is Chapter 6 Project 9 - Writing A Rational Number Class"<<endl;
Rational Num1(1,4);
Rational Num2;
return 0;
}

Rational::Rational()
{
cout<<"Please Enter The Numerator: ";
cin>>numerator;
cout<<"Please Enter The Denominator: ";
cin>>denominator;
cout<<endl;
}

Rational::Rational(int Num1, int Num2)
{
numerator = Num1;
denominator = Num2;
}

void Rational::output()
{
cout<<numerator<<"/"<<denominator;
}

Rational Add(Rational Num1, Rational Num2)
{
Rational Add;

((Num1.numerator * Num2.denominator + Num1.denominator * Num2.numerator) / (Num1.denominator * Num2.denominator));
return Add;
}

Rational Subtract(Rational Num1, Rational Num2)
{
Rational Subtract;
((Num1.numerator * Num2.denominator - Num1.denominator * Num2.numerator) / (Num1.denominator * Num2.denominator));
return Subtract;
}

Rational Product(Rational Num1, Rational Num2)
{
Rational Product;
((Num1.numerator * Num1.denominator) / (Num2.numerator * Num2.denominator));
return Product;
}

Rational Division(Rational Num1, Rational Num2)
{
Rational Division;
((Num1.numerator * Num2.denominator) / (Num2.numerator * Num1.denominator));
return Division;
}

bool Equal(Rational Num1, Rational Num2)
{
bool Equal = false;

if ((Num1.numerator/Num1.denominator)==(Num2.numerator/Num2.denominator))
Equal = true;
return Equal;
}

bool LessThan(Rational Num1, Rational Num2)
{
bool LessThan = false;
if ((Num1.numerator * Num2.denominator)<(Num2.numerator * Num1.denominator))
LessThan = false;
return LessThan;
}
