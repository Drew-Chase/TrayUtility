// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "SystemTray.h"
#include "../resource.h"
using namespace TrayUtility;

SystemTray* tray;

int main()
{
	tray = new SystemTray();
	bool success = tray->Create(L"Example Tray Icon", L"ExampleTrayIcon", [](MouseButton button)
	{
		switch (button)
		{
			case Left:
			{
				MessageBoxW(NULL, L"Left click!", L"Tray Icon", MB_OK | MB_ICONINFORMATION);
				break;
			}

			case Right:
			{
				tray->OpenContextMenu();
				break;
			}

			default:
				break;
		}
	});
	tray->AddMenuItem(L"Open", [](MouseButton button) { MessageBoxW(NULL, L"Open!", L"Tray Icon", MB_OK | MB_ICONINFORMATION); });
	tray->AddMenuItem(L"Other", [](MouseButton button) { MessageBoxW(NULL, L"Other!", L"Tray Icon", MB_OK | MB_ICONINFORMATION); });
	tray->AddMenuItem(L"Exit", [](MouseButton button) { PostQuitMessage(0); });

	tray->SetTooltip(L"Test");
	tray->SetIcon(L"icon.ico");
	tray->SetIcon(MAKEINTRESOURCE(APPICON));

	if (success)
	{
		// This code just keeps the application open and is not necessary for the system tray to work.
		HHOOK hook = SetWindowsHookExW(WH_KEYBOARD, [](int passthrough, WPARAM state, LPARAM flag) -> LRESULT { return CallNextHookEx(NULL, passthrough, state, flag); }, NULL, NULL);
		MSG msg;
		while (GetMessageW(&msg, NULL, NULL, NULL) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		UnhookWindowsHookEx(hook);
	}
	delete(tray);
}