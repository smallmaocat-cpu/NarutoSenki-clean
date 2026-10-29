/* 替身 tiffio.h：游戏不使用 TIFF，提供类型与空实现让 cocos2d-x 编译通过 */
#ifndef STUB_TIFFIO_H
#define STUB_TIFFIO_H
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t   uint8;
typedef uint16_t  uint16;
typedef uint32_t  uint32;
typedef uint64_t  uint64;
typedef int8_t    int8;
typedef int16_t   int16;
typedef int32_t   int32;
typedef int64_t   int64;

typedef void*      thandle_t;
typedef uint64_t   toff_t;
typedef int64_t    tmsize_t;
typedef struct tiff TIFF;
typedef uint32_t   ttag_t;
typedef uint32_t   tdir_t;

#define TIFFTAG_IMAGEWIDTH      256
#define TIFFTAG_IMAGELENGTH     257
#define TIFFTAG_BITSPERSAMPLE   258
#define TIFFTAG_SAMPLESPERPIXEL 277
#define TIFFTAG_PLANARCONFIG    284
#define ORIENTATION_TOPLEFT     1

static inline TIFF* TIFFClientOpen(const char*, const char*, thandle_t,
    tmsize_t (*)(thandle_t, void*, tmsize_t),
    tmsize_t (*)(thandle_t, void*, tmsize_t),
    toff_t   (*)(thandle_t, toff_t, int),
    int      (*)(thandle_t),
    toff_t   (*)(thandle_t),
    int      (*)(thandle_t, void**, toff_t*),
    void     (*)(thandle_t, void*, toff_t)) { return 0; }

static inline int  TIFFGetField(TIFF*, ttag_t, ...) { return 0; }
static inline void* _TIFFmalloc(tmsize_t) { return 0; }
static inline void _TIFFfree(void*) {}
static inline int  TIFFReadRGBAImageOriented(TIFF*, uint32, uint32, uint32*, int, int) { return 0; }
static inline void TIFFClose(TIFF*) {}
#endif
