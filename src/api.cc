/*
  Authored by Chase Roth 7/11/2023
  See repository root directory for more information.
*/

#pragma once
#include "api.h"
#include "img-get.h"

std::tuple<Bitmap *, Error *> Scanner::PreviewBitmap()
{
  // Return error if source is undefined
  if (!Scanner::source)
  {
    return std::make_tuple(nullptr, new Error(Errors::SourceUndefined));
  }
  return GetNativeWindowBitmap(Scanner::source, true);
}

void Scanner::SetScanSegments(ScanSegment segments[])
{
  // Clean up old alloc if not null
  if (Scanner::segments)
  {
    delete Scanner::segments;
  }
  Scanner::segments = segments;
}

ScanSegment *Scanner::GetScanSegments()
{
  return Scanner::segments;
}

std::tuple<ScannedSegment *, Error *> Scanner::Scan(ScanSegment segments[] = NULL)
{
  // Return error if source is undefined
  if (!Scanner::source) {
    return std::make_tuple(nullptr, new Error(Errors::SourceUndefined));
  }
  auto result = GetNativeWindowBitmap(Scanner::source, false);

  // If an error exist, return with error
  Error *err = std::get<1>(result);
  if (err) {
    return std::make_tuple(nullptr, err);
  }

  // No errors, process bitmap

}