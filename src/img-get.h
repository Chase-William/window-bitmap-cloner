/*
  Authored by Chase Roth 7/25/2021
  See repository root directory for more information.
*/

#pragma once
#include <string>
#include <Windows.h>
#include "types.h"

/*
  Gets a bitmap buffer from a specific window.
  Param - srcWindowName, name of window to find and get bitmap from
  Param - size, size of the bitmap buffer being returned
  Return, pointer to the head of the bitmap buffer
*/
std::tuple<Bitmap *, Error *> GetNativeWindowBitmap(const char* windowName, bool includeFileHeader);