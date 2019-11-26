/*
	Graffiti: Show image files of any type on the console window.
	This is an abuse of the win32 api and should not be used :).
	Usage: 
		#include "graffiti.h"
		graffiti(100, 100, "filename.jpg")
*/

#pragma once
#include <stdio.h>
#include "windows.h"

#ifndef STB_IMAGE_IMPLEMENTATION
// User friendly error messages
#define STBI_FAILURE_USERMSG 
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

bool graffiti(const char* filePath, int xPos, int yPos)
{
	int x, y, n;
	auto data = stbi_load(filePath, &x, &y, &n, 4);
	if (!data) {
		printf("Error loading %s: %s\n", filePath, stbi_failure_reason());
		return false;
	}
	auto hBmp = CreateBitmap(x, y, 1, 32, data);
	stbi_image_free(data);
	HWND wnd = GetConsoleWindow();
	HDC dc = GetDC(wnd);
	HDC srcDc = CreateCompatibleDC(dc);
	SelectObject(srcDc, hBmp);
	BitBlt(dc, xPos, yPos, x, y, srcDc, 0, 0, SRCCOPY);
	DeleteDC(srcDc);
	ReleaseDC(wnd, dc);
	DeleteObject(hBmp);
	return true;
}
