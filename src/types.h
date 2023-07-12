/*
  Authored by Chase Roth 7/11/2023
  See repository root directory for more information.
*/

#pragma once
#include <tuple>
#include <iostream>

enum Errors : int {
  FailedToFindWindow = 1,
  FailedToGetClientRect = 2,
  BitBlockTransferFailed = 3,
  TesseractInitializationFailure = 4,
  SourceUndefined = 5
};

class ScanSegment {
  public:
  
  // Unique identifier for this scan segment
  std::string Key;
  // Rectangle used for OCR
  int Left, Top, Right, Bottom;

  ScanSegment(std::string key, int left, int top, int right, int bottom) :
    Key(key),
    Left(left),
    Top(top),
    Right(right),
    Bottom(bottom)
  { }
};

class ScannedSegment : ScanSegment {
  public:
  
  // Recognized text from OCR
  std::string Text;

  ScannedSegment(std::string key, int left, int top, int right, int bottom, std::string text) :
    ScanSegment(key, left, top, right, left),
    Text(text)
  { }
};

class Error {
public:
  int ErrorCode;
  Error(int code) : 
    ErrorCode(code) 
  { }
};

/* Contains a pointer to a bitmap with helpful metadata. */
class Bitmap {
public:
  char *BitmapBuffer;
  unsigned long Size;
  int Width, Height;

  Bitmap(char *bitmapBuffer, unsigned long size, int width, int height) : 
    BitmapBuffer(bitmapBuffer),
    Size(size),
    Width(width),
    Height(height)
  { }
};