#pragma once
// funcln.h - Contains declarations of sin function


#ifdef FUNCLN_EXPORTS
#define FUNCLN_API __declspec(dllexport)
#else
#define FUNCLN_API __declspec(dllimport)
#endif
#define _USE_MATH_DEFINES
extern "C" FUNCLN_API double funcln(double arg);