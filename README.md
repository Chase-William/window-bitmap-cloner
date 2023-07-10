### Objective: 
Perform OCR to withdraw text from segment(s) of a bitmap.
### Project Style: 
Library

### Key Operations:
- Be able to clone bitmaps from win32 Windows and Screens.
- Allow calling applications to preview bitmap.
- Ability for calling applications to provide bounding boxes of a bitmap for scanning.
- Output recognized text associated with the bounding box of the bitmap.

### Technologies:
- Tesseract OCR
- Win32 API

### Languages:
- C++

### `ScanSegment` Type:

This type represents a segment of a bitmap to be scanned.

```ts
// Used when providing segments to scan
ScanSegment {
  key: string, // Unique identifier for bounding area, if not provided, use sequence index
  rect: Rectangle, // Bounding box for OCR scanning
}

// Used when receiving scan results
ScannedSegment {
  key: string,
  rect: Rectangle,
  text: string // Identified text
}
```

### Internal State:

| Name | Data TYpe | Desciption | Why | 
| --- | --- | --- | --- |
| source | `string` | Bitmap cloning source *(i.e., a screen or window)*. | Reduce redudent method parameters by allowing the source to be set once as state. |
| segments | `ScanSegment`[] | Segments to be scanned upon request. | Reduce redudent method parameters by allowing scan segments to be set as default state. |

### API Methods:

#### PreviewBitmap(): `Bitmap` or similar type

Provides a cloned bitmap from the targeted screen or window.

#### SetScanSegments(`ScanSegment[]` segments): `void`

Set the default scan segments to be used when scanning.

#### GetScanSegments(): `ScanSegment[]`

Gets the current value of the internal state *segments*.

#### Scan(`ScanSegment[]` segments = null): `ScannedSegment[]`

Scans the current *source* and returns a collection of `ScannedSegment`s based on the *segments* parameter. If the *segments* argument is provided, it's value with be used instead of the internal *segments* state value. 

> WARNING: Failure to set the state *segments* before invocation will result in an exception.
