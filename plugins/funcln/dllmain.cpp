// dllmain.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "funcln.h"
#include "stdexcept"
#include <cmath>

double funcln(double x)
{
	if (x < 0) {
		throw std::invalid_argument("ln should take positive argument");
	}
	else
		return std::log(x);
}

