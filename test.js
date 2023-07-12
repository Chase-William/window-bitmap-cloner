const { BitmapTextScanner } = require('./dist/index');
const fs = require('fs');

console.log("Calling native node addon api for a bitmap from the specified window...");
const res = BitmapTextScanner.PreviewBitmap("ARK: Survival Evolved");

console.log(res)

if (res.err) {
  switch (res.err.code) {
    case BitmapTextScanner.Errors.FailedToFindWindow:
      console.log("FailedToFindWindow");
      break;
    case BitmapTextScanner.Errors.BitBlockTransferFailed:
      console.log("BitBlockTransferFailed");
      break;
    case BitmapTextScanner.Errors.FailedToGetClientRect:
      console.log("FailedToGetClientRect");
      break;
    case BitmapTextScanner.Errors.TesseractInitializationFailure:
      console.log("TesseractInitializationFailure");
      break;
    default:
      console.log("Something went wrong, the default switch should never be triggered...");
      break;
  }
}
else {
  const view = new Uint8Array(res.bitmap);
  console.log(view);

  fs.writeFileSync('res.bmp', view, (err) => {
    if (err) return console.log(err);
    console.log("Saved");
  });
}