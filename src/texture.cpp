#include "texture.hpp"

int Texture::getWidth() const
{
    return _width;
}

int Texture::getHeight() const
{
    return _height;
}

char *Texture::getPixels() const
{
    return _pixels;
}

void Texture::read(const char *filename)
{
    FILE *file;
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    unsigned char r, g, b;

    free(_pixels);
    _pixels = nullptr;

    /* Otvara se fajl sa teksturom */
    assert((file = fopen(filename, "rb")) != NULL);

    /* Učitavaju se podaci iz prvog zaglavlja */
    fread(&bfh.type, 2, 1, file);
    fread(&bfh.size, 4, 1, file);
    fread(&bfh.reserved1, 2, 1, file);
    fread(&bfh.reserved2, 2, 1, file);
    fread(&bfh.offsetbits, 4, 1, file);

    /* Učitavaju se podaci iz drugog zaglavlja. */
    fread(&bih.size, 4, 1, file);
    fread(&bih.width, 4, 1, file);
    fread(&bih.height, 4, 1, file);
    fread(&bih.planes, 2, 1, file);
    fread(&bih.bitcount, 2, 1, file);
    fread(&bih.compression, 4, 1, file);
    fread(&bih.sizeimage, 4, 1, file);
    fread(&bih.xpelspermeter, 4, 1, file);
    fread(&bih.ypelspermeter, 4, 1, file);
    fread(&bih.colorsused, 4, 1, file);
    fread(&bih.colorsimportant, 4, 1, file);

    /* Od podataka iz drugog zaglavlja koriste se samo širina i visina */
    _width = bih.width;
    _height = bih.height;

    /* Pošto se koriste samo R, G i B komponente, alocira se niz dužine 24 */
    if (bih.bitcount == 24)
        _pixels = new char[3 * bih.width * bih.height ];
    else
    {
        std::cerr << "read(): Only images with 24 bits per pixel are supported" << std::endl;
        exit(EXIT_FAILURE);
    }

    assert(_pixels != nullptr);

    /* Učitavaju se podaci o pikselima i smeštaju u alocirani niz.
     * Pretpostavlja se da učitana 3 bajta = 24 bita predstavljaju R, G i B komponentu boje */
    for (int i = 0; i < bih.width * bih.height; i++)
    {
        /* U bmp formatu boje se čitaju u B, G, R redosledu */
        fread(&b, sizeof(char), 1, file);
        fread(&g, sizeof(char), 1, file);
        fread(&r, sizeof(char), 1, file);

        _pixels[3 * i] = r;
        _pixels[3 * i + 1] = g;
        _pixels[3 * i + 2] = b;
    }

    fclose(file);
}

void Texture::free_image()
{
    delete _pixels;
}