#pragma once
#include <nan.h>
#include <iostream>
#include "entry.h"  // Native node addon library utility declarations
#include "../api.h" // Declares our libraries utilities

NAN_METHOD(PreviewBitmap)
{
  Nan::Utf8String windowName(Nan::To<v8::String>(info[0]).ToLocalChecked());
  v8::Local<v8::Boolean> v8IncludeFileHeader = Nan::To<v8::Boolean>(info[1]).ToLocalChecked();

  // Get underlying char* from Nan string
  const char *namePtr = windowName.operator*();
  bool includeFileHeader = v8IncludeFileHeader.operator*()->Value();

  // Call our custom API for polling a bitmap from a target window
  std::tuple<Bitmap *, Error *> r = PreviewBitmapInternal(namePtr);

  

// #if _DEBUG
//   std::cout << "ErrorCode: " << r.ErrorCode << std::endl;
//   std::cout << "BitmapBuffer Address: " << &(r.BitmapBuffer) << std::endl;
//   std::cout << "Size: " << r.Size << std::endl;
//   std::cout << "Width: " << r.Width << std::endl;
//   std::cout << "Height: " << r.Height << std::endl;
// #endif

  // int *err = r.ErrorCode;

  // // Create generic JS object to append to
  // v8::Local<v8::Object> jsObj = Nan::New<v8::Object>();

  // // Create propNames and values
  // v8::Local<v8::String> errorName = Nan::New("ErrorCode").ToLocalChecked();
  // v8::Local<v8::Number> errorValue = Nan::New(err == NULL ? 0 : *err);
  // delete err; // cleanup bc we are passing by value to v8 so this can be deleted

  // v8::Local<v8::String> bufferName = Nan::New("BitmapBuffer").ToLocalChecked();
  // v8::Local<v8::Object> bufferValue = Nan::NewBuffer(r.BitmapBuffer, (uint32_t)r.Size, DisposeNativeBitmap, NULL).ToLocalChecked();
  // // Creat width js prop
  // v8::Local<v8::String> widthName = Nan::New("Width").ToLocalChecked();
  // v8::Local<v8::Number> widthValue = Nan::New(r.Width);
  // // Create height js prop
  // v8::Local<v8::String> heightName = Nan::New("Height").ToLocalChecked();
  // v8::Local<v8::Number> heightValue = Nan::New(r.Height);

  // // Apply props to js obj
  // Nan::Set(jsObj, errorName, errorValue);
  // Nan::Set(jsObj, bufferName, bufferValue);
  // Nan::Set(jsObj, widthName, widthValue);
  // Nan::Set(jsObj, heightName, heightValue);

  // // Set obj as return
  // info.GetReturnValue().Set(jsObj);
}