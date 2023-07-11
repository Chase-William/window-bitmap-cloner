/*
  Authored by Chase Roth 7/11/2023
  See repository root directory for more information.
*/

#pragma once

#include <iostream>
#include <tuple>
#include <memory>
#include "types.h"

/*
  Clones a bitmap from the source or returns an error.
*/
std::tuple<Bitmap *, Error *> PreviewBitmapInternal(const char* source);

std::tuple<ScannedSegment *, Error *> ScanInternal(const char* source, ScanSegment segments[]);

/*
  Finalizer callback for releasing unmanaged resources.
*/
void DisposeNativeBitmap(char *data, void *hint);