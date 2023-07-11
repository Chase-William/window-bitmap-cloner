/*
  Authored by Chase Roth 7/11/2023
  See repository root directory for more information.
*/

#pragma once

#include <iostream>
#include <tuple>
#include <types.h>
#include <memory>

class Scanner
{
public:
  // Screen or window name as bitmap source
  std::string *source = NULL;

  ScanSegment *segments = NULL;

  /*
    Clones a bitmap from the source or returns an error.
  */
  std::tuple<Bitmap *, Error *> PreviewBitmap();

  void SetScanSegments(ScanSegment segments[]);

  ScanSegment *GetScanSegments();

  std::tuple<ScannedSegment *, Error *> Scan(ScanSegment segments[] = NULL);
};