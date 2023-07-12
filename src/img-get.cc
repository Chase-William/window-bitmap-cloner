/*
  Authored by Chase Roth 7/25/2021
  See repository root directory for more information.
*/

#pragma once
#include <iostream>
#include <array>
#include <stdio.h>
#include "img-get.h"
#include <cstring>

const float INCH_TO_METER_RATIO = 39.3701f;

std::tuple<Bitmap *, Error *> GetNativeWindowBitmap(const char* windowName, bool includeFileHeader)
{
  HWND hwndSrc = NULL;
  HBITMAP hbmpTarget = NULL; // Handle to target bmpBuffer
  HDC hdcSrcWindow = NULL;   // Source window device-context handle
  HDC hdcTarget = NULL;
  char *bmpBuffer = NULL;
  int size = 0; // Initialize size otherwise unitialized memory is use and has undefined behavior
  int width = 0, height = 0;
  int err = 0;

  try
  {
    hwndSrc = FindWindowA(NULL, windowName);
    hdcSrcWindow = GetDC(hwndSrc);        // Source window device-context handle
    hdcTarget = CreateCompatibleDC(NULL); // Get in-memory DC, not connected to a device
    BITMAP bmpObj;                        // Actual Bitmap object from GetObject()
    if (!hwndSrc)
    {
      throw Errors::FailedToFindWindow;
    }
    RECT srcClientRect; // Bitmap Dimensions
    DWORD dwSizeofDIB = 0;
    char *lpPixels = NULL;
    DWORD dwBmpSize = 0;

    // Get dimensions of bmpBuffer from source window
    if (!GetClientRect(hwndSrc, &srcClientRect))
    {
      throw Errors::FailedToGetClientRect;
    }

    width = srcClientRect.right - srcClientRect.left;
    height = srcClientRect.bottom - srcClientRect.top;

    // Create compatible bmpBuffer with the source window DC
    hbmpTarget = CreateCompatibleBitmap(hdcSrcWindow, width, height);
    // Sets our HBITMAP as the new bmpBuffer the DC uses
    SelectObject(hdcTarget, hbmpTarget);
    // Retreive bit data by blocks
    if (!BitBlt(
            hdcTarget, // DC target
            0, 0,
            width, height, // Dimensions of bmpBuffer
            hdcSrcWindow,  // DC source
            0, 0,
            SRCCOPY // Operation type, copy & paste
            ))
    {
      throw Errors::BitBlockTransferFailed;
    }

    // Get the BITMAP from the HBITMAP
    GetObject(hbmpTarget, sizeof(BITMAP), &bmpObj);

    long dpiX = 0, dpiY = 0;
    // Get DPI of screen vertical / horizontal
    HDC screen = GetDC(NULL);
    dpiX = (GetDeviceCaps(screen, LOGPIXELSX));
    dpiY = (GetDeviceCaps(screen, LOGPIXELSY));
    ReleaseDC(NULL, screen);

    BITMAPFILEHEADER bmfHeader;
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bmpObj.bmWidth;
    bi.biHeight = bmpObj.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = dpiX * INCH_TO_METER_RATIO;
    bi.biYPelsPerMeter = dpiY * INCH_TO_METER_RATIO;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;
    // aligning bits for words?
    dwBmpSize = ((bmpObj.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpObj.bmHeight;
    // Add the size of the headers to the size of the bmpBuffer to get the total file size.
    if (includeFileHeader)
    { // Include the header into the needed buff size if needed
      dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
      size = dwSizeofDIB;
    }
    else
    {
      size = dwBmpSize;
    }

    // Allocate bitmap buffer
    bmpBuffer = (char *)malloc(size);

    if (includeFileHeader)
    { // Calc offset if including the header
      // Offset to where the actual bmpBuffer bits start.
      bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
      // Get offset in bytes from file start
      DWORD pixelOffset = dwSizeofDIB - dwBmpSize;
      // Set pixel buffer pointer based on offset
      lpPixels = bmpBuffer + pixelOffset;
    }
    else
    {
      lpPixels = bmpBuffer;
    }

    // Gets the "bits" from the bmpBuffer, and copies them into a buffer
    // that's pointed to by lpPixels.
    GetDIBits(
        hdcTarget,
        hbmpTarget,
        0,
        (UINT)bmpObj.bmHeight,
        lpPixels,
        (BITMAPINFO *)&bi,
        DIB_RGB_COLORS);

    if (includeFileHeader)
    { // Copy over header info if desired
      // Size of the file.
      bmfHeader.bfSize = dwSizeofDIB;
      // bfType must always be BM for Bitmaps.
      bmfHeader.bfType = 0x4D42; // BM.
      // Finish filling out buffer of entire bmpBuffer
      std::memcpy(bmpBuffer, &bmfHeader, sizeof(bmfHeader));
      std::memcpy(bmpBuffer + sizeof(bmfHeader), &bi, sizeof(bi));
    }
  }
  catch (Errors errCode)
  {
    std::cout << "Error thrown when cloning bitmap; error code: " << errCode << std::endl;
  }

  if (hbmpTarget)
  {
    if (!DeleteObject(hbmpTarget))
    { // Cleanup HBITMAP
      std::cout << "Failed to delete: hbmpTarget" << std::endl;
    }
  }
  ReleaseDC(NULL, hdcTarget);       // Cleanup hdc target
  ReleaseDC(hwndSrc, hdcSrcWindow); // Cleanup hdc from the source window handle

  if (err)
  { // If an error exist, return error without bitmap
    return std::make_tuple(nullptr, new Error(err));
  }
  // Success path, return bitmap, not errors
  return std::make_tuple(new Bitmap(bmpBuffer, size, width, height), nullptr);
}