/*
  Authored by Chase Roth 7/11/2023
  See repository root directory for more information.
*/

#include "api.h"
#include "img-get.h"

std::tuple<Bitmap *, Error *> PreviewBitmapInternal(const char *source)
{
  return GetNativeWindowBitmap(source, true);
}

void DisposeNativeBitmap(char *data, void *hint)
{
  free(data);
}