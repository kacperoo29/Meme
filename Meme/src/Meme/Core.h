#pragma once


#ifdef _WINDLL
#define MEME_API __declspec(dllexport)
#else
#define MEME_API __declspec(dllimport)
#endif

#define BIT(x) (1 << x)

#define ARRAYSIZE(_ARR) ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)

