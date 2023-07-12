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
// const myModule = require("./binding.node");

export namespace BitmapTextScanner {

  export enum Errors {
    FailedToFindWindow = 1,
    FailedToGetClientRect = 2,
    BitBlockTransferFailed = 3,
    TesseractInitializationFailure = 4,
    SourceUndefined = 5
  }
  
  export interface Area {
    left: number;
    top: number;
    width: number;
    height: number;
  }

  // export function GetWindowBitmap(windowName: string, includeFileHeader: boolean): Bitmap {
  //   return myModule.GetWindowBitmap(windowName, includeFileHeader);
  // }  

  export function PreviewBitmap(source: string): { bitmap: Bitmap, err: RequestError } {
    return myModule.PreviewBitmap(source)
  }

  // export function TestMethod(): string {
  //   return myModule.TestMethod()
  // }

  export class RequestError {
    code: number
  }

  export class Bitmap {
    bitmapBuffer: ArrayBuffer
    width: number
    height: number
  }
}