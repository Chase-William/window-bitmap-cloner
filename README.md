This is an example application using `win32` and `Node.js` to clone bitmaps from native window windows. 

### Example Usage

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
5. Run `npm run init:all` to setup dependencies and configuration
6. Run `npm run build:node` to build the project

> Note: Visual Studios C++ Desktop Toolkit is required.

### Example Uses

#### Notpad
![ex1](https://github.com/Chase-William/window-bitmap-cloner/assets/46757278/3e9977d0-51cc-4264-8899-00d6c35aa51b)

#### A Video Game in Unreal Engine 4
![ex2](https://github.com/Chase-William/window-bitmap-cloner/assets/46757278/e3d04617-95ea-42ca-aa56-14897fcafa7b)

#### FireFox
![ex3](https://github.com/Chase-William/window-bitmap-cloner/assets/46757278/9202a256-8a32-486f-b01e-341dfd1fb89f)

#### Auto Hotkey Spy Program

I recommend getting this little tool if you need to plug information easily about various windows. Download [here](https://www.autohotkey.com/).

![ex4](https://github.com/Chase-William/window-bitmap-cloner/assets/46757278/3f6ef007-36bc-43b2-af44-923d3ac0fe97)

> Note: Some windows like Google Chrome do not work and present a completely black bitmap.
