// dllmain.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "funccos.h"
#include <cmath>

double funccos(double x)
{
	return std::cos(x * M_PI / 180);
}