#pragma once
// funccos.h - Contains declarations of sin function


#ifdef FUNCCOS_EXPORTS
#define FUNCCOS_API __declspec(dllexport)
#else
#define FUNCCOS_API __declspec(dllimport)
#endif
#define _USE_MATH_DEFINES
extern "C" FUNCCOS_API double funccos(double arg);