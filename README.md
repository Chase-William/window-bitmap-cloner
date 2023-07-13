This is an example application using `win32` and `Node.js` to clone bitmaps from native windows. 

### How it Works

```ts
// Import the library index file
const { BitmapTextScanner } = require('./dist/index');
// Call the PreviewBitmap function and provide the window title
const res = BitmapTextScanner.PreviewBitmap(your window title);
```

1. The function `PreviewBitmap` is called and is provided the window title
2. The call is delegated to the [`nan`](https://github.com/nodejs/nan) `PreviewBitmap` function written in C++ acting as the glue between the `Node.js` enviroment and the `img-get.cc` file.
3. The underlying `const char*` *(a c styled string)* is retreived from the js object in the C++ space and passed to `PreviewBitmapInternal()` containing pure C++ and `win32`.
4. A bunch of intermediate steps to clone the bitmap from the window take place; checkout *file here* to see for yourself.
5. The result from `PreviewBitmapInternal()` is received and converted into javascript v8 engine objects and returned.
