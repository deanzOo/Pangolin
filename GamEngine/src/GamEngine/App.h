#pragma once

#include "Core.h"

namespace GamEngine {
	class GE_API App
	{
	public:
		App();
		void Run();
	};

	App* CreateApp();
}


