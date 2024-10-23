// dllmain.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "funcln.h"
#include <cmath>

double funcln(double x)
{
	return std::log(x);
}

