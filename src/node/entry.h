#pragma once

/*
  Fix nan.h not found issue: https://github.com/Microsoft/vscode-cpptools/issues/946#issuecomment-519949926
*/

#include <nan.h>

NAN_METHOD(PreviewBitmap);