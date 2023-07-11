#pragma once
#include <tuple>
#include <iostream>

enum WinImgGetError : int {
  Success = 0,
  FailedToFindWindow = 1,
  FailedToGetClientRect = 2,
  BitBlockTransferFailed = 3,
  TesseractInitializationFailure = 4
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
  int *ErrorCode;
  Error(int *code) : 
    ErrorCode(code) 
  { }
};

/* Contains a pointer to a bitmap with helpful metadata. */
class Bitmap {
public:
  char *BitmapBuffer;
  unsigned long Size;
  long Width;
  long Height;

  Bitmap(char *bitmapBuffer, unsigned long size, long width, long height) : 
    BitmapBuffer(bitmapBuffer),
    Size(size),
    Width(width),
    Height(height)
  { }
};