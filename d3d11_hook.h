#pragma once

#include <d3d11.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <DXGI.h>

#include "memeory.h"

#pragma comment(lib, "d3d11.lib")

#include "menu.h"

typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace D3D11_Hook {
	bool Initialize();
	bool Shutdown();

	HRESULT Present_hk(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

	extern D3D11PresentHook Present;
	extern HWND hwnd;
	extern HMODULE hmodule;

	extern bool Initialized;
	extern Memory::Hook present_hook;
}