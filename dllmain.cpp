#include "include.h"

// SL-AC.dll Bypass
#include "bypass.hpp"

decltype(GetModuleHandle)* GetModuleHandle_Copy;
decltype(GetProcAddress)* GetProcAddress_Copy;
decltype(GetAsyncKeyState)* GetAsyncKeyState_Copy;

il2cpp_init_t il2cpp_init_og;

void il2cpp_init_hk(const char* name) {

    il2cpp_init_og(name);

    void* game_assembly = GetModuleHandle_Copy("GameAssembly.dll");

    IL2CPP::Initialize(game_assembly);
    IL2CPP::Attach();

    Cheat::Initialize();
}

int main(HMODULE mod)
{
	FILE* f;
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);

    // Initialize Memeory
	Memory::Initialize();

    // Initialize Bypass
    Bypass::Initialize();

    GetModuleHandle_Copy = Memory::CopyFunction<decltype(GetModuleHandle)*>(GetModuleHandle);
    GetProcAddress_Copy = Memory::CopyFunction<decltype(GetProcAddress)*>(GetProcAddress);
    // GetAsyncKeyState_Copy = Memory::CopyFunction<decltype(GetAsyncKeyState)*>(GetAsyncKeyState);

    LOG("Waiting for GameAssembly.dll...")

    while (!GetModuleHandle_Copy("GameAssembly.dll"));

    LOG("Game Assembly Found! Hooking il2cpp_init...")

    Memory::Hook("GameAssembly.dll", "il2cpp_init", il2cpp_init_hk, &il2cpp_init_og);

    LOG("Waiting for Window and IL2CPP Init...")

    while (!(FindWindowA(0, "SCPSL") && Cheat::Initialized)) {};

    LOG("Found Window! Menu init...");

    Menu::Initialize();

    while (true) {};

    Cheat::Shutdown();
    Menu::Shutdown();

	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)main, hModule, NULL, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

