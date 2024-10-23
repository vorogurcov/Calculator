#pragma once
// FuncSin.h - Contains declarations of sin function


#ifdef FUNCSIN_EXPORTS
#define FUNCSIN_API __declspec(dllexport)
#else
#define FUNCSIN_API __declspec(dllimport)
#endif
#define _USE_MATH_DEFINES
extern "C" FUNCSIN_API double funcsin(double arg);