#pragma once

#include "Core.h"

namespace gamEngine {
	class GE_API App
	{
	public:
		App();
		void Run();
	};

	App* CreateApp();
}


