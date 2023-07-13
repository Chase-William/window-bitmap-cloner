#pragma once
#include <nan.h>
#include <iostream>
#include "entry.h"  // Native node addon library utility declarations
#include "../api.h" // Declares our libraries utilities
#include "plog/Log.h"

NAN_METHOD(PreviewBitmap)
{
  Nan::Utf8String windowName(Nan::To<v8::String>(info[0]).ToLocalChecked());

  // Get underlying char* from Nan string
  const char *namePtr = windowName.operator*();

  // Call our custom API for polling a bitmap from a target window
  std::tuple<Bitmap *, Error *> r = PreviewBitmapInternal(namePtr);

  // Retrieve Error
  Error *err = std::get<1>(r);
  // If an error exist, create the error return obj and return it
  if (err)
  {
    v8::Local<v8::Object> rootObj = Nan::New<v8::Object>();
    v8::Local<v8::Object> errObj = Nan::New<v8::Object>();
    v8::Local<v8::String> errName = Nan::New("code").ToLocalChecked();
    v8::Local<v8::Number> errValue = Nan::New(err->ErrorCode);
    Nan::Set(errObj, errName, errValue);
    Nan::Set(rootObj, Nan::New("err").ToLocalChecked(), errObj);
    
    // Set res obj
    info.GetReturnValue().Set(rootObj);    

    delete err;
    return;
  }

  // Get bitmap
  Bitmap *bitmap = std::get<0>(r);

  // Create Root Res Obj
  v8::Local<v8::Object> rootObj = Nan::New<v8::Object>();
  v8::Local<v8::Object> bitmapObj = Nan::New<v8::Object>();

  // Create Props
  v8::Local<v8::String> bufferName = Nan::New("bitmapBuffer").ToLocalChecked();
  v8::Local<v8::Object> bufferValue = Nan::NewBuffer(bitmap->BitmapBuffer, (uint32_t)bitmap->Size, DisposeNativeBitmap, NULL)
                                          .ToLocalChecked();
  v8::Local<v8::String> widthName = Nan::New("width").ToLocalChecked();
  v8::Local<v8::Number> widthValue = Nan::New(bitmap->Width);
  v8::Local<v8::String> heightName = Nan::New("height").ToLocalChecked();
  v8::Local<v8::Number> heightValue = Nan::New(bitmap->Height);

  // Bind
  Nan::Set(bitmapObj, bufferName, bufferValue);
  Nan::Set(bitmapObj, widthName, widthValue);
  Nan::Set(bitmapObj, heightName, heightValue);
  Nan::Set(rootObj, Nan::New("bitmap").ToLocalChecked(), bitmapObj);

  info.GetReturnValue().Set(rootObj);

  // Log info
  PLOGI << "PreviewBitmap, BufferSize: " << bitmap->Size << " Width: " << bitmap->Width << " Height: " << bitmap->Height;

  delete bitmap;
}