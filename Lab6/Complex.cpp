#include "Complex.hpp"

Complex::Complex(double r, double i)
{
	_real = r;
	_img = i;
}
double Complex::_getReal()
{
	return _real;
}
double Complex::_getImg()
{
	return _img;
}
void Complex::_setReal(double n) //Assuming passed in is an dobule
{
	_real = n;
}
void Complex::_setImg(double n)
{
	_img = n;
}
void Complex::print(std::ostream& stream)
{
	char s = '+';
	if (this->_getImg() < 0) s = '\0';
	stream << this->_getReal() << s << this->_getImg() << 'i' << std::endl;
}
Complex Complex::add(Complex n)
{
	return Complex(this->_getReal() + n._getReal(), this->_getImg() + n._getImg());
}
Complex Complex::operator-(const Complex& n2) const
{
	Complex temp(0,0);
	temp._real = this->_real - n2._real;
	temp._img = this->_img - n2._img;
	return temp;
}