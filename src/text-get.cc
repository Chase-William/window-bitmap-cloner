
#include <vector>
#include "types.h"
#include "img-get.h"

// Tesseract OCR headers
// #include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

std::tuple<std::vector<Sector *>, Error *> Scan(const char *source, const char *tessData, std::vector<Sector *> sectors)
{
  auto r = GetNativeWindowBitmap(source, false);
  // Return if an error exist
  Error *err = std::get<1>(r);
  if (err)
  {
    // log
    // return std::make_tuple(nullptr, err);
  }

  // Perform OCR
  // tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

  // Initialize with English lib
  // if (api->Init(tessData, "eng"))
  // {
  //   return std::make_tuple(nullptr, new Error(Errors::TesseractInitializationFailure))
  // }

  Bitmap *bitmap = std::get<0>(r);
  const l_uint8 *buffer = (l_uint8 *)bitmap->BitmapBuffer;

  // Pix *img = pixReadMemBmp(buffer, bitmap->Size);
  // api->SetImage(img);

  int length = sectors.size();
  Sector *sector = NULL;
  for (int i = 0; i < length; i++)
  {
    sector = sectors[i];
    // api->SetRectangle(sector->Left, sector->Top, sector->Width, sector->Height);
    // sectors[i].Text = api->GetUTF8Text();
  }

  // api->End();
  // delete api;
  // pixDestroy(&img);

  return std::make_tuple(sectors, nullptr);
}