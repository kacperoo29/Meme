#pragma once


#ifdef _WINDLL
#define MEME_API __declspec(dllexport)
#else
#define MEME_API __declspec(dllimport)
#endif

#define BIT(x) (1 << x)

