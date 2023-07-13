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
const tesseract = require("tesseract.js")

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

  export type ResTuple = {
    bitmap: Bitmap
    err: RequestError
  }

  export function PreviewBitmap(source: string): ResTuple {
    return myModule.PreviewBitmap(source)
  }

  export function GetText(source: string) {
    const { bitmap, err }: ResTuple = myModule.PreviewBitmap(source)
    
    if (err) {
      console.log("An error was received, code: " + err.code)
      return
    }

    tesseract.recognize(
      bitmap.bitmapBuffer,
      'eng',
      { logger: m => console.log(m) }
    ).then(({ data: { text } }) => {
      console.log(text);
    })
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