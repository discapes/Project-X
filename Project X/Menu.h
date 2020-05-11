#pragma once
#include <Windows.h>
#include "imgui/imgui_impl_dx9.h"


namespace Menu {
	extern bool isOpen;
	void init(IDirect3DDevice9* device, HWND hwnd);
	void render();
	void setStyle();
}
