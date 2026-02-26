#pragma once
#include <iostream>
#include <string>
#include <cstdio>

class Complex
{
public:
	double _getReal();
	double _getImg();
	void _setReal(double n);
	void _setImg(double n);
	static Complex read(std::istream& stream)
	{
		char sign, i;
		double img, real;
		stream >> real >> sign >> img >> i;
		if (sign == '-') img = -img;
		return Complex(real, img);
	}
	void print(std::ostream& stream);
	Complex add(Complex n);
	Complex(double r, double i);
	Complex operator-(const Complex& n2) const;

private:
	double _real = 0;
	double _img = 0;
};