#ifndef __TEXTURE_MANAGER_HPP
#define __TEXTURE_MANAGER_HPP 1

/* Klasa koja se koristi sa učitavanje tekstura. Ideja iz kodova sa časa. */

#include <vector>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>

/* Svaka slika u bmp formatu pocinje sa dva zaglavlja koja su ilustrovana sledećim dvema klasama */

class BITMAPFILEHEADER {
public:
    BITMAPFILEHEADER() = default;

    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offsetbits;
};

class BITMAPINFOHEADER {
public:
    BITMAPINFOHEADER() = default;

    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitcount;
    unsigned int compression;
    unsigned int sizeimage;
    int xpelspermeter;
    int ypelspermeter;
    unsigned int colorsused;
    unsigned int colorsimportant;
};

/* Klasa koja sluzi sa smeštanje podataka o slici */

class Texture {
public:
    Texture(int width = 0, int height = 0)
    : _width(width), _height(height)
    {
        /* U slučaju greške prekida se program. */
        assert(width >= 0 && height >= 0);

        if (width == 0 || height == 0)
            _pixels = NULL;
        else {
            _pixels = (char *)malloc(3 * width * height * sizeof(char));
            assert(_pixels != NULL);
        }
    }

    void read(const char *filename);
    void free_image();
    int getWidth() const;
    int getHeight() const;
    char *getPixels() const;
private:
    int _width;
    int _height;
    char* _pixels; // Niz u kojem se cuvaju podaci za sve piksele u obliku (R, G, B)
};

#endif