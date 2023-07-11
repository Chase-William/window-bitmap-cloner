/*
  Authored by Chase Roth 7/11/2023
  See repository root directory for more information.
*/

#include "api.h"
#include "img-get.h"

std::tuple<Bitmap *, Error *> PreviewBitmapInternal(const char *source)
{
  return GetNativeWindowBitmap(source, false);
}

std::tuple<ScannedSegment *, Error *> ScanInternal(const char* source, ScanSegment segments[])
{
  auto result = GetNativeWindowBitmap(source, false);

  // If an error exist, return with error
  Error *err = std::get<1>(result);
  if (err) {
    return std::make_tuple(nullptr, err);
  }

  // No errors, process bitmap
  throw 0;
}

void DisposeNativeBitmap(char *data, void *hint)
{
  free(data);
}