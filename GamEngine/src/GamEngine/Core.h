#pragma once

#ifdef GE_PLATFORM_WINDOWS
	#ifdef GE_BUILD_DLL
		#define GE_API __declspec (dllexport)
	#else
		#define GE_API __declspec(dllimport)
	#endif
#else
	#error Unsupported Platform. Only Windows is Supported!
#endif
