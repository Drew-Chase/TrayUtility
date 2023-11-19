// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "SystemTray.h"
#include <string>

void TrayUtility::SystemTray::UpdateShellIcon()
{
	Shell_NotifyIconW(NIM_MODIFY, &nid);
}

TrayUtility::SystemTray::SystemTray()
{
	this->nid = { 0 };
	this->hIcon = nullptr;
	this->hwnd = nullptr;
	this->on_click_callback = nullptr;
}

TrayUtility::SystemTray::~SystemTray()
{
	if (!this->menu_items.empty())
	{
		this->menu_items.clear();
	}
}
bool TrayUtility::SystemTray::Create(const wchar_t* label, const wchar_t* unique_class_name, IconInteractionCallback on_click)
{
	this->on_click_callback = on_click;

	// Register the window class.
	HINSTANCE hInstance = GetModuleHandle(NULL); // Gets the module instance

	// Register the window class.
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = unique_class_name;
	wc.hInstance = hInstance;

	// Set the function pointer as user data during the creation of the window
	wc.cbWndExtra = sizeof(LONG_PTR);
	wc.lpfnWndProc = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
	{
		auto tray = reinterpret_cast<SystemTray*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		switch (msg)
		{
			case WM_CREATE:
			{
				break;
			}
			case WM_USER + 0x6897:
			{
				tray->hwnd = hwnd;
				switch (lParam)
				{
					case WM_LBUTTONUP:
					{
						tray->on_click_callback(MouseButton::Left);
						break;
					}
					case WM_RBUTTONUP:
					{
						tray->on_click_callback(MouseButton::Right);
						break;
					}
				}
				break;
			}
			case WM_COMMAND:
			{
				auto commandID = LOWORD(wParam);
				MouseButton button = MouseButton::Left;

				switch (lParam)
				{
					case WM_LBUTTONUP:
					{
						button = MouseButton::Left;
						break;
					}
					case WM_RBUTTONUP:
					{
						button = MouseButton::Right;
						break;
					}
				}

				for (auto item : tray->menu_items)
				{
					if (item->comandID == commandID)
					{
						item->on_click_callback(button);
					}
				}

				break;
			}
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	};

	if (!RegisterClassExW(&wc))
	{
		MessageBoxW(NULL, (L"Unable to register the window class. Error code: " + std::to_wstring(GetLastError())).c_str(), L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	// Create the window and parent it to the tray window.
	HWND explorerHandle = FindWindowW(L"Shell_TrayWnd", NULL);
	HWND window = CreateWindowExW(0, unique_class_name, L"", 0, 0, 0, 0, 0, explorerHandle, NULL, hInstance, this);

	// Set the function pointer as user data during the creation of the window
	SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	// Create the tray icon.
	this->nid.cbSize = sizeof(NOTIFYICONDATA);
	this->nid.hWnd = window;
	this->nid.uID = 0;
	this->nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_SHOWTIP;
	this->nid.uCallbackMessage = WM_USER + 0x6897;
	HICON icon = LoadIconW(hInstance, IDI_APPLICATION);
	if (icon)
	{
		this->nid.hIcon = icon;
	}
	wcscpy_s(this->nid.szTip, label);

	if (!Shell_NotifyIconW(NIM_ADD, &nid))
	{
		MessageBoxW(NULL, (L"Unable to create the system tray icon. Error code: " + std::to_wstring(GetLastError())).c_str(), L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void TrayUtility::SystemTray::AddMenuItem(MenuItem* item)
{
	item->comandID = this->menu_items.size() + 1;
	this->menu_items.push_back(item);
}

void TrayUtility::SystemTray::AddMenuItem(const wchar_t* label, MenuItemClickCallback on_click_callback)
{
	auto item = new MenuItem();
	item->label = label;
	item->comandID = this->menu_items.size() + 1;
	item->on_click_callback = on_click_callback;
	this->AddMenuItem(item);
}

void TrayUtility::SystemTray::RemoveMenuItem(MenuItem* item)
{
	int index = 0;
	for (auto i : this->menu_items)
	{
		if (i == item)
		{
			this->menu_items.erase(this->menu_items.begin() + index);
			delete(item);
			break;
		}
		index++;
	}
}

void TrayUtility::SystemTray::RemoveMenuItem(unsigned int index)
{
	MenuItem* item = this->menu_items.at(index);
	this->menu_items.erase(this->menu_items.begin() + index);
	delete(item);
}

bool TrayUtility::SystemTray::SetIcon(HICON icon)
{
	// Release the existing icon if it was loaded
	if (hIcon)
	{
		DestroyIcon(hIcon);
	}

	// Set the new icon
	hIcon = icon;
	nid.hIcon = icon;

	// Update the tray icon
	this->UpdateShellIcon();

	return icon != nullptr;
}

bool TrayUtility::SystemTray::SetIcon(const wchar_t* icon_path)
{
	// Load the icon from the file
	HICON icon = (HICON)LoadImageW(nullptr, icon_path, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);

	if (!icon)
	{
		// Handle the error, for example, show a message box
		MessageBoxW(NULL, L"Failed to load the icon from file", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	// Set the icon
	return SetIcon(icon);
}

bool TrayUtility::SystemTray::SetIcon(LPWSTR icon_resource)
{
	HICON icon = LoadIconW(GetModuleHandle(NULL), icon_resource);
	return SetIcon(icon);
}

void TrayUtility::SystemTray::SetTooltip(const wchar_t* tooltip)
{
	wcscpy_s(this->nid.szTip, const_cast<wchar_t*>(tooltip));
	this->UpdateShellIcon();
}

void TrayUtility::SystemTray::SetTooltip(wchar_t* tooltip)
{
	wcscpy_s(this->nid.szTip, const_cast<wchar_t*>(tooltip));
	this->UpdateShellIcon();
}

void TrayUtility::SystemTray::OpenContextMenu()
{
	POINT pt;
	GetCursorPos(&pt);

	HMENU menu = CreatePopupMenu();
	for (auto item : this->menu_items)
	{
		AppendMenuW(menu, MF_STRING, item->comandID, item->label);
	}
	TrackPopupMenu(menu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, this->hwnd, NULL);
}