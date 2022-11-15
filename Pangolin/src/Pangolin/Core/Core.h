#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define GE_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MAC__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define GE_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define GE_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define GE_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define GE_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif

#ifdef GE_PLATFORM_WINDOWS
	#if GE_DYNAMIC_LINK
		#ifdef GE_BUILD_DLL
			#define Pangolin_API __declspec(dllexport)
		#else
			#define Pangolin_API __declspec(dllimport)
		#endif
	#else
		#define GE_API
	#endif
#else
	#error Pangolin only supports Windows!
#endif

#ifdef GE_DEBUG
	#define GE_ENABLE_ASSERTS
#endif

#ifdef GE_ENABLE_ASSERTS
	#define GE_CORE_ASSERT(x, ...) { if (!(x)) { GE_CORE_ERROR("Assertion Failed!"); GE_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
	#define GE_CLIENT_ASSERT(x, ...) { if (!(x)) { GE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GE_CORE_ASSERT(x, ...)  {}
	#define GE_CLIENT_ASSERT(x, ...) {}
#endif

#define BIT(x) (1 << x)

#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Pangolin {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
}