/*
  Authored by Chase Roth 7/30/2021
  See repository root directory for more information.
  Type-Script front end for using this API.
*/

/*
  This path must be a valid relative path from the calling main.js executing dir to the binding native addon
  -- First Line for Node
  -- Second for Electron
*/

const myModule = require("../build/Release/binding");

export namespace BitmapTextScanner {

  export enum Errors {
    FailedToFindWindow = 1,
    FailedToGetClientRect = 2,
    BitBlockTransferFailed = 3,
    TesseractInitializationFailure = 4,
    SourceUndefined = 5
  }


  export function PreviewBitmap(source: string): ResTuple {
    return myModule.PreviewBitmap(source)
  }

  export class RequestError {
    code: number
  }

  export class Bitmap {
    bitmapBuffer: ArrayBuffer
    width: number
    height: number
  }
}