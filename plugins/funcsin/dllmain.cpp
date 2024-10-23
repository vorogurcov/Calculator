// dllmain.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "funcsin.h"
#include <cmath>

double funcsin(double x)
{
	return std::sin(x * M_PI / 180);
}