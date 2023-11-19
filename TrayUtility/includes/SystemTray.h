// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include "MenuItem.h"
#include "MouseButton.h"

using std::vector;
using std::string;

namespace TrayUtility
{
	class SystemTray
	{
	private:
		using IconInteractionCallback = void (*)(MouseButton button);
		HWND hwnd;
		NOTIFYICONDATA nid;
		HICON hIcon;
		IconInteractionCallback on_click_callback;
		vector<MenuItem*> menu_items;
		void UpdateShellIcon();
	public:
		SystemTray();
		~SystemTray();
		/// <summary>
		/// Opens the context menu for the tray icon.
		/// </summary>
		void OpenContextMenu();
		/// <summary>
		/// Creates a tray icon.
		/// </summary>
		/// <param name="label">The label of the tray icon</param>
		/// <param name="unique_class_name">The unique class name of the tray icons window</param>
		/// <param name="on_click">The on click callback event</param>
		/// <returns></returns>
		bool Create(const wchar_t* label, const wchar_t* unique_class_name, IconInteractionCallback on_click);
		/// <summary>
		/// Adds a menu item to the tray icon.
		/// </summary>
		/// <param name="label">The menu items text</param>
		/// <param name="on_click">The on click callback event</param>
		void AddMenuItem(const wchar_t* label, MenuItemClickCallback on_click);
		/// <summary>
		/// Adds a menu item to the tray icon.
		/// </summary>
		/// <param name="item"></param>
		void AddMenuItem(MenuItem* item);
		/// <summary>
		/// Removes a menu item from the tray icon.
		/// </summary>
		/// <param name="item"></param>
		void RemoveMenuItem(MenuItem* item);
		/// <summary>
		/// Removes a menu item from the tray icon.
		/// </summary>
		/// <param name="index"></param>
		void RemoveMenuItem(unsigned int index);
		/// <summary>
		/// Sets the icon of the tray icon.
		/// </summary>
		/// <param name="icon_path"></param>
		/// <returns></returns>
		bool SetIcon(const wchar_t* icon_path);
		/// <summary>
		/// Sets the icon of the tray icon.
		/// </summary>
		/// <param name="icon"></param>
		/// <returns></returns>
		bool SetIcon(HICON icon);
		/// <summary>
		/// Sets the icon of the tray icon.
		/// </summary>
		/// <param name="icon_resource"></param>
		/// <returns></returns>
		bool SetIcon(LPWSTR icon_resource);
		/// <summary>
		/// Sets the tooltip of the tray icon.
		/// </summary>
		/// <param name="tooltip"></param>
		void SetTooltip(const wchar_t* tooltip);
		/// <summary>
		/// Sets the tooltip of the tray icon.
		/// </summary>
		/// <param name="tooltip"></param>
		void SetTooltip(wchar_t* tooltip);
	};
}