#pragma once

#include <iostream>
#include <tuple>
#include <types.h>

class Scanner {
  public:

  // Screen or window name as bitmap source
  std::string source;
  // TODO: add ScanSegments

  /*
    Clones a bitmap from the source or returns an error.
  */
  std::tuple<Bitmap, Error> PreviewBitmap();

  // TODO: make error a pointer, and change it's error member to a value instead..
  // therefore it is all allocated in one place and nullptr for no error works
};