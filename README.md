# Tray Utility

A C++ simple library that allows you to create system tray icons for windows.

## Table of Contents

- [Create Tray Icon](#create-tray-icon)
- [Add Menu Items](#add-menu-items)
- [Set Tooltip](#set-tooltip)
- [Set Icon](#set-icon)
- [Icon Resource](#icon-resource)
- [Open Context Menu](#open-context-menu)
- [Example](#example)
- [Example Project](/TrayUtility/src/example.cpp)


## Create Tray Icon

First initialize the `SystemTray` object.

```c++
#include "SystemTray.h"
SystemTray* tray;
int main()
{
    tray = new SystemTray();

    // Tray Logic...

    delete(tray); // Make sure to delete the tray once your done with it.
}
```

Then create the tray icon.  
Create function parameters:

- Label
- Unique Class Name
- On Click Callback

```c++
bool success = tray->Create(L"Example Tray Icon", L"ExampleTrayIcon", [](MouseButton button)
{
    switch (button)
    {
        case Left:
        {
            // On left click
            break;
        }

        case Right:
        {
            // On right click
            break;
        }
    }
});
```

## Add Menu Items

Menu items can be created two ways, here is the easiest way to do it.

```c++
tray->AddMenuItem(L"Exit", [](MouseButton button) { /* Handle on click event */ });
```

However you can create the menu item by passing a menu item object.

```c++
MenuItem* item = new MenuItem();
item->label = L"Test";
item->on_click_callback = [](MouseButton button) { /* Handle on click event */};
tray->AddMenuItem(item);
```

## Set Tooltip

```c++
tray->SetTooltip(L"New Tooltip");
```

## Set Icon

add the icon with the icons path.

```c++
tray->SetIcon(L"icon.ico");
```

add the icon with the icon resource.  
Make sure that this is defined in the resources.h and the application Resource.rc files

```c++
tray->SetIcon(MAKEINTRESOURCE(ICON_RESOURCE));
```

add the icon from the HICON

```c++
HICON icon = LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(ICON_RESOURCE));
tray->SetIcon(icon);
```

### Icon Resource

resource.h

```c++
#define ICON_RESOURCE 101
```

Application.rc:

```c++
MAINAPPICON ICON "icon.ico" // The exe/app icon
ICON_RESOURCE ICON "icon.ico" // the tray icon
```

## Open Context Menu

```c++
tray->OpenContextMenu();
```

# Example

```c++
// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "SystemTray.h"
#include "resource.h"
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
	tray->AddMenuItem(L"Exit", [](MouseButton button) { PostQuitMessage(0); });

	tray->SetTooltip(L"Test");
	tray->SetIcon(L"icon.ico");

	if (!success)
	{
		// Handle failed system tray icon creation.
	}
	delete(tray);
}
```
