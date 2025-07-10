#pragma once

#ifdef MYFUNLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MYFUNLIBRARY_API __declspec(dllimport)
#endif

extern "C" MYFUNLIBRARY_API double MYFUN(const double X);