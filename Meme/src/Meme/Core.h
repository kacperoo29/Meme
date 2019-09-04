#pragma once

#include <memory>

#ifdef _WIN32
#if DYNAMIC_LINK
#ifdef _WINDLL
#define MEME_API __declspec(dllexport)
#else
#define MEME_API __declspec(dllimport)
#endif
#else
#define MEME_API
#endif

#endif

#define BIT(x) (1 << x)

#define ARRAYSIZE(_ARR) ((int32_t)(sizeof(_ARR)/sizeof(*_ARR)))
#define BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)


namespace Meme {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}


