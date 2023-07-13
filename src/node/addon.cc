#pragma once
#include "entry.h" // Contains our functions
#include <iostream>

// Logger header files
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"

void Initialize(v8::Local<v8::Object> exports)
{
  Nan::Set(exports, Nan::New<v8::String>("PreviewBitmap").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(PreviewBitmap)).ToLocalChecked());
}

extern "C" NODE_MODULE_EXPORT void
NODE_MODULE_INITIALIZER(v8::Local<v8::Object> exports,
                        v8::Local<v8::Value> module,
                        v8::Local<v8::Context> context)
{
  /* Perform addon initialization steps here. */

  Initialize(exports);

  // Init Logging Library
  plog::init(plog::debug, "log.txt");
}