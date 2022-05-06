#pragma once

typedef HANDLE(*CreateToolhelp32Snapshot_t)(DWORD, DWORD);
CreateToolhelp32Snapshot_t CreateToolhelp32Snapshot_og;

typedef BOOL(*EnumWindows_t)(WNDENUMPROC, LPARAM);
EnumWindows_t EnumWindows_og;

typedef UINT(*GetSystemFirmwareTable_t)(DWORD, DWORD, PVOID, DWORD);
GetSystemFirmwareTable_t GetSystemFirmwareTable_og;

HANDLE CreateToolhelp32Snapshot_hk(DWORD flags, DWORD processid){
	return 0;
}

BOOL EnumWindowsHide(HWND hWnd, LPARAM lparam) {
	return TRUE;
}

BOOL EnumWindows_hk(WNDENUMPROC cb, LPARAM param) {
	return TRUE; // EnumWindows_og(EnumWindowsHide, param);
}

UINT GetSystemFirmwareTable_hk(DWORD FirmwareTableProviderSignature, DWORD FirmwareTableID, PVOID pFirmwareTableBuffer, DWORD BufferSize) {
	return 0;
}

namespace Bypass {

	Memory::Hook EnumWindows;
	Memory::Hook CreateToolhelp32Snapshot;
	Memory::Hook GetSystemFirmwareTable;

	bool Initialize() {

		Bypass::EnumWindows = Memory::Hook("user32.dll", "EnumWindows", EnumWindows_hk, &EnumWindows_og);
		Bypass::CreateToolhelp32Snapshot = Memory::Hook("kernel32.dll", "CreateToolhelp32Snapshot", CreateToolhelp32Snapshot_hk, &CreateToolhelp32Snapshot_og);
		Bypass::GetSystemFirmwareTable = Memory::Hook("kernel32.dll", "GetSystemFirmwareTable", GetSystemFirmwareTable_hk, &GetSystemFirmwareTable_og);

		LOG("Bypass Loaded");

		return true;
	}

	bool Shutdown() {

		Bypass::EnumWindows.Unload();
		Bypass::CreateToolhelp32Snapshot.Unload();
		Bypass::GetSystemFirmwareTable.Unload();

		LOG("Bypass Unloaded");

		return true;
	}
}