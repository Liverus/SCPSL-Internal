#include "d3d11_hook.h"

namespace D3D11_Hook {
	D3D11PresentHook Present;
	HWND hwnd;
	HMODULE hmodule;

	bool Initialized = false;
	Memory::Hook present_hook;
}

WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) || Menu::Opened)
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT D3D11_Hook::Present_hk(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{

	if (!Initialized)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {

			pDevice->GetImmediateContext(&pContext);

			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			hwnd = sd.OutputWindow;

			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);

			pBackBuffer->Release();

			oWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

			ImGui::CreateContext();

			auto io = ImGui::GetIO();
			io.IniFilename = NULL;

			ImGui_ImplWin32_Init(hwnd);
			ImGui_ImplDX11_Init(pDevice, pContext);

			Menu::Style();

			Initialized = true;
		}
	}


	if (GetAsyncKeyState(VK_INSERT) & 0x1) {
		Menu::Opened = !Menu::Opened;
	}

	if (Menu::Opened) {
		Menu::Render();
		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	return Present(pSwapChain, SyncInterval, Flags);
}

bool D3D11_Hook::Shutdown() {
	// remove hook

	//D3D11_Device->Release();
	//D3D11_Context->Release();
	//SwapChain->Release();

	return true;
}

bool D3D11_Hook::Initialize()
{
	hmodule = GetModuleHandleA(NULL);
	hwnd = FindWindowA(0, "SCPSL");

	D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	DXGI_SWAP_CHAIN_DESC sd;
	{
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.Windowed = ((GetWindowLongPtr(hwnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		sd.BufferDesc.Width = 1;
		sd.BufferDesc.Height = 1;
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 1;
	}

	IDXGISwapChain* SwapChain;
	ID3D11Device* D3D11_Device;
	ID3D11DeviceContext* D3D11_Context;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, sizeof(levels) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION, &sd, &SwapChain, &D3D11_Device, &obtainedLevel, &D3D11_Context);
	
	if (FAILED(hr))
	{
		MessageBoxA(hwnd, "Failed to create device and swapchain.", "Fatal Error", MB_ICONERROR);
		return false;
	}

	void** SwapChain_vtable = *(void***)SwapChain;

	present_hook = Memory::Hook(SwapChain_vtable[8], Present_hk, &Present);

	return true;
}