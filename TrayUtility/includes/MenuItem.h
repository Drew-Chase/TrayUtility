// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#pragma once
#include "MouseButton.h"
namespace TrayUtility
{
	using MenuItemClickCallback = void (*)(MouseButton button);
	struct MenuItem
	{
		const wchar_t* label;
		unsigned int comandID;
		MenuItemClickCallback on_click_callback;
	};
}