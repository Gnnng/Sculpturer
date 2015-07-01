//
//  Bmp.cpp
//  Sculpturer
//
//  Created by Gong Deli on 7/1/15.
//  Copyright (c) 2015 Gong Deli. All rights reserved.
//

#include "Bmp.h"

bool SaveImage(char* szPathName, void* lpBits, int w, int h)
{
    BITMAPINFOHEADER BMIH;
    BITMAPFILEHEADER bmfh;
    
    FILE *pFile = fopen(szPathName, "wb");
    
    if(pFile == NULL)
    {
        return false;
    }
    
    BMIH.HeaderSize = sizeof(BITMAPINFOHEADER);
    BMIH.Width = w;
    BMIH.Height = h;
    BMIH.Planes = 1;
    BMIH.BitCount = 24;
    BMIH.Compression = BI_RGB;
    BMIH.SizeImage = w * h* 3;
    
    int nBitsOffset = sizeof(BITMAPFILEHEADER) + BMIH.HeaderSize;
    long lImageSize = BMIH.SizeImage;
    long lFileSize = nBitsOffset + lImageSize;
    bmfh.Signature = 'B'+('M'<<8);
    bmfh.BitsOffset = nBitsOffset;
    bmfh.Size = lFileSize;
    bmfh.Reserved =0;
    
    for(int i = 0; i < w * h; i++) {
        auto r = (unsigned char *)(lpBits) + i * 3;
        auto b = r + 2;
        std::swap(*r, *b);
    }
    unsigned int nWrittenFileHeaderSize = fwrite(&bmfh, 1, sizeof(BITMAPFILEHEADER), pFile);
    unsigned int nWrittenInfoHeaderSize = fwrite(&BMIH, 1, sizeof(BITMAPINFOHEADER), pFile);
    unsigned int nWrittenDIBDataSize = fwrite(lpBits, 1, lImageSize, pFile);
    
    fclose(pFile);
    
    return true;
    
}
