// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#pragma once
#include <Windows.h>
#include "MouseButton.h"
class SystemTray
{
private:
	using IconInteractionCallback = void (*)(MouseButton button);
	HWND hwnd;
	NOTIFYICONDATA nid;
public:
	SystemTray();
	~SystemTray();
	bool Create(const wchar_t* label, const wchar_t* unique_class_name, IconInteractionCallback callback);
};
