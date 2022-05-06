#pragma once

#include "include.h"
#include "d3d11_hook.h"

namespace Menu {
	bool Initialize();
	bool Shutdown();

	void Render();
	void Populate();
	void Style();
	
	extern bool Opened;
}