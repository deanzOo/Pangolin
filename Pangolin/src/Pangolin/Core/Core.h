#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#ifndef PL_PLATFORM_WINDOWS
			#define PL_PLATFORM_WINDOWS
		#endif
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MAC__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define PL_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define PL_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define PL_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define PL_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif

#ifdef PL_PLATFORM_WINDOWS
	#if PL_DYNAMIC_LINK
		#ifdef PL_BUILD_DLL
			#define Pangolin_API __declspec(dllexport)
		#else
			#define Pangolin_API __declspec(dllimport)
		#endif
	#else
		#define PL_API
	#endif
#else
	#error Pangolin only supports Windows!
#endif

#ifdef PL_DEBUG
	#define PL_ENABLE_ASSERTS
#endif

#ifdef PL_ENABLE_ASSERTS
	#define PL_CORE_ASSERT(x, ...) { if (!(x)) { PL_CORE_ERROR("Assertion Failed!\n\t{0}"); PL_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
	#define PL_CLIENT_ASSERT(x, ...) { if (!(x)) { PL_CORE_ERROR("Assertion Failed\n\t{0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PL_CORE_ASSERT(x, ...)  {}
	#define PL_CLIENT_ASSERT(x, ...) {}
#endif

#define BIT(x) (1 << x)

#define PL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Pangolin {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> create_scope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> create_ref(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}