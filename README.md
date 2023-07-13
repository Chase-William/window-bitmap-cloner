This is an example application using `win32` and `Node.js` to clone bitmaps from native windows. 

### How it Works

```ts
// Import the library index file
const { BitmapTextScanner } = require('./dist/index');
// Call the PreviewBitmap function and provide the window title
const res = BitmapTextScanner.PreviewBitmap(your window title);
```

1. The function `PreviewBitmap` is called and is provided the window title.
2. The call is delegated to the [`nan`](https://github.com/nodejs/nan) `PreviewBitmap` function written in C++ acting as the glue between the `Node.js` enviroment and the `img-get.cc` file.
3. The underlying `const char*` *(a c styled string)* is retreived from the js object in the C++ space and passed to `PreviewBitmapInternal()` containing pure C++ and `win32`.
4. A bunch of intermediate steps to clone the bitmap from the window take place; checkout *file here* to see for yourself.
5. The result from `PreviewBitmapInternal()` is received and converted into javascript v8 engine objects and returned.

### Setup

1. Recommended installation of `Node.js` 18 or later
2. Follow `vcpkg`'s simple installation [here](https://vcpkg.io/en/getting-started)
3. Inside the `vcpkg` root dir, run `vcpkg install plog` in the cmdline
4. Clone the repository
5. Run `npm run init:all` *(uses yarn)*
6. Run `npm run build:node`
