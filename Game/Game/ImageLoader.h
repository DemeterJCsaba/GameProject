#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <FImg\FreeImage.h>

BYTE* LoadImage(const char* filename, unsigned int* width, unsigned int* height, unsigned int* bits);

#endif // !IMAGELOADER_H