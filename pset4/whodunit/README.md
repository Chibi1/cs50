# Questions

## What's `stdint.h`?

A header which defines an integer type with a width of a specified number of bits

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To specify exactly the width of the integer type to either 8, 16 or 32.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

8 bits, 32 bits, 32 bits and 16 bits.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

Decimal: 66, 77

## What's the difference between `bfSize` and `biSize`?

bfSize is the size in bytes of the bitmap file, while biSize is the size in bytes of the structure.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the image is top down and its origin is in the upperleft corner. However, when in this style, the structure cannot be compressed.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If no file is found to point to then the `fopen` will return `NULL`.

## Why is the third argument to `fread` always `1` in our code?

Every element to be read is of size 1 bytes.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

padding = 3

## What does `fseek` do?

Move the pointer within  a specific file to a specified position.

## What is `SEEK_CUR`?

The file pointers current position.

## Whodunit?

Professor Plum with the candle stick in the library.
