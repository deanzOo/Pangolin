#pragma once

#ifdef GE_PLATFORM_WINDOWS
	
#else
	#error Unsupported Platform. Only Windows is Supported!
#endif

#ifdef GE_ENABLE_ASSERTS
	#define GE_CORE_ASSERT(x, ...) { if (!(x)) { GE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GE_CLIENT_ASSERT(x, ...) { if (!(x)) { GE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GE_CORE_ASSERT(x, ...)  {}
	#define GE_CLIENT_ASSERT(x, ...) {}
#endif

#define BIT(x) (1 << x)

#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)