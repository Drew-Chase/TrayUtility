// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "SystemTray.h"
#include <stdio.h>

int main()
{
	auto tray = new SystemTray();
	tray->Test([](const char* text, int value)
	{
		printf("%s %d\n", text, value);
	});

	delete(tray);
}