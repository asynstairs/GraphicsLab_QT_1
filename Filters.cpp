#include "Filters.hpp"
#include <iostream>
//#include "math.h"
#include <cmath>

    template <class T>
    T Clamp(T v, int max, int min)
    {
        if (v > max) {
            return max;
        }
        else {
            if (v < min) {
                return min;
            }
        }
        return v;
    }

    /*-------------- FILTERS CLASS ---------------*/

    Filters ::  Filters( void ) {};

    Filters :: ~Filters( void ) {};

    /*-------------- INVERT FILTER ---------------*/

    QImage Invert_Filter :: CalculateNewImagePixMap(const QImage & photo, int radius) {
        QImage result_Image(photo);
        for (int x = 0; x< photo.width();x++)
            for (int y = 0; y < photo.width(); y++) {
                QColor photo_color = photo.pixelColor(x, y);
                photo_color.setRgb(
                    255 - photo_color.red(),
                    255 - photo_color.green(),
                    255 - photo_color.blue());
                result_Image.setPixelColor(x, y, photo_color);

            }
        return result_Image;
    }

    /*-------------- MATRIX FILTER ---------------*/

    QImage Matrix_Filter :: CalculateNewImagePixMap(const QImage & photo, int radius) {
        QImage result_Image(photo);
        for (int x = 0; x < photo.width(); x++)
            for (int y = 0; y < photo.width(); y++) {
                    result_Image.setPixelColor(x, y, CalculateNewPixelColor(photo, x, y, radius));
            }
        return result_Image;
    }

    QColor Matrix_Filter :: CalculateNewPixelColor(QImage photo, int x, int y, int radius) {
        int returnR = 0;
        int returnG = 0;
        int returnB = 0;
        int size = 2 * radius + 1;

        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                int idx = (i + radius) * size + j + radius;
                    QColor color = photo.pixelColor(Clamp<int>(x + j, photo.width()  - 1, 0),
                                                    Clamp<int>(y + i, photo.height() - 1, 0));
                    returnR += color.red()   * vector[idx];
                    returnG += color.green() * vector[idx];
                    returnB += color.blue()  * vector[idx];
            }
            return QColor(Clamp(returnR, 255, 0),
                          Clamp(returnG, 255, 0),
                          Clamp(returnB, 255, 0));
            }
    }

    /*-------------- GAUSSIAN BLUR FILTER ---------------*/

    void Gaussian_Blur_Filter :: CreateGaussianVector(int radius, int sigma) {
        const int SIZE = 2 * radius + 1;
        float     norm = 0;
        
        vector = new float[SIZE * SIZE];
        
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                int idx = (i + radius) * SIZE + (j + radius);
                    vector[idx] = exp(-(i * i + j * j) / (sigma * sigma));
                    norm += vector[idx];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                vector[i * SIZE + j] /= norm;
            }
        }

    }

    /*-------------- SHARPNESS FILTER ---------------*/

    void Sharpness_Filter :: CreateSharpnessVector(int radius) {
        const int SIZE = 2 * radius + 1;
        float     norm = 0;
            vector = new float[SIZE * SIZE];
                vector[0] =  0;  vector[3] = -1; vector[6] =  0;
                vector[1] = -1;  vector[4] =  5; vector[7] = -1;
                vector[2] =  0;  vector[5] = -1; vector[8] =  0;

            for (int i = -radius; i < radius; i++) {
                for (int j = -radius; j < radius; j++) {
                        int idx = (i + radius) * SIZE + (j + radius);
                            norm += vector[idx];
                }
            }

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    vector[i * SIZE + j] /= norm;
                }
            }
    }

    /*-------------- GRAY SCALE FILTER ---------------*/

    QColor Gray_Scale_Filter :: CalculateNewPixelColor(QImage photo, int x, int y) {
        QColor color = photo.pixelColor(x, y);
        float intensivity;
            intensivity = color.red() * 0.36 + color.green() * 0.53 + color.blue() * 0.11;
            color.setRgb(intensivity, intensivity, intensivity);
        return color;
    }

    QImage Gray_Scale_Filter :: CalculateNewImagePixMap(const QImage & photo, int radius) {
        QImage result(photo);
        for (int x = 0; x < photo.width(); x++) {
            for (int y = 0 ; y < photo.height(); y++) {
                QColor color = CalculateNewPixelColor(photo, x, y);
                result.setPixelColor(x, y, color);
            }
        }
        return result;
    }

    /*-------------- SEPIA FILTER ---------------*/

    QColor Sepia_Filter :: CalculateNewPixelColor(QImage photo, int x, int y) {
        float intensivity;
        const int K = 20; //brightness up

        QColor color = photo.pixelColor(x, y);
        intensivity = color.red() * 0.36 + color.green() * 0.53 + color.blue() * 0.11;
        
        color.setRgb(intensivity + 2   * K,
                     intensivity + 0.5 * K,
                     intensivity - 1   * K);
        return color;
    }

    QImage Sepia_Filter :: CalculateNewImagePixMap(const QImage & photo, int radius) {
        QImage result(photo);
        for (int x = 0; x < photo.width(); x++) {
            for (int y = 0; y < photo.height(); y++) {
                QColor color = CalculateNewPixelColor(photo, x, y);
                    result.setPixelColor(x, y, color);
            }
        }
        return result;
    }

    /*-------------- BRIGHTNESS FILTER ---------------*/

    QColor Brightness_Filter :: CalculateNewPixelColor(QImage photo, int x, int y) {
        const int K = 80;
        QColor color = photo.pixelColor(x, y);
        
        color.setRgb(Clamp<int>(color.red()   + K , 255, 0),
                     Clamp<int>(color.green() + K,  255, 0),
                     Clamp<int>(color.blue()  + K,  255, 0));
        return color;
    }

    QImage  Brightness_Filter :: CalculateNewImagePixMap(const QImage & photo, int radius) {
        QImage result_Image(photo);
        for (int i = 0; i < photo.width(); i++) {
            for (int j = 0; j < photo.height(); j++) {
                QColor color = CalculateNewPixelColor(photo, i, j);
                    result_Image.setPixelColor(i, j, color);
            }
        }
        return result_Image;
    }

    /*-------------- SOBEL FILTER ---------------*/

    void Sobel_Filter :: CreateSobelVector(int radius) {
        const uint SIZE = 2 * radius + 1;
        vector = new float[SIZE * SIZE];

        vectorX = new float[SIZE * SIZE];
            vectorX[0] = -1; vectorX[3] = -2; vectorX[6] = -1;
            vectorX[1] =  0; vectorX[4] =  0; vectorX[7] =  0;
            vectorX[2] =  1; vectorX[5] =  2; vectorX[8] =  1;

        vectorY = new float[SIZE * SIZE];
            vectorY[0] = -1; vectorY[3] = 0; vectorY[6] = 1;
            vectorY[1] = -2; vectorY[4] = 0; vectorY[7] = 2;
            vectorY[2] = -1; vectorY[5] = 0; vectorY[8] = 1;
    }

    QColor Sobel_Filter :: CalculateNewPixelColor(QImage photo, int x, int y, int radius) {
        const uint SIZE = 2 * radius + 1;
        int returnR = 0;
        int returnG = 0;
        int returnB = 0;
        
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                int idx = (i + radius) * SIZE + j + radius;
                    QColor color = photo.pixelColor(Clamp<int>(x + j, photo.width()  - 1, 0),
                                                    Clamp<int>(y + i, photo.height() - 1, 0));
                    returnR += color.red()   * vectorX[idx] + color.red()   * vectorY[idx];
                    returnG += color.green() * vectorX[idx] + color.green() * vectorY[idx];
                    returnB += color.blue()  * vectorX[idx] + color.blue()  * vectorY[idx];
            }
        }
        return QColor(Clamp(returnR, 255, 0),
                      Clamp(returnG, 255, 0),
                      Clamp(returnB, 255, 0));
    }

    QImage Sobel_Filter :: CalculateNewImagePixMap(const QImage& photo, int radius) {
       QImage result_Image(photo);
       for (int x = 0; x < photo.width(); x++) {
           for (int y = 0; y < photo.height(); y++) {
               result_Image.setPixelColor(x, y, CalculateNewPixelColor(photo,x,y,radius));
           }
       }
       return result_Image;
    }

        /* ------------- LAB ----------------*/

/*-------------- EMBOSSING FILTER ---------------*/

    void Embossing_Filter :: CreateEmbossingVector(int radius) {
        const int SIZE = radius * 2 + 1;
        
        vector = new float[SIZE * SIZE];
            vector[0] = 0; vector[3] =  1; vector[6] =  0;
            vector[1] = 1; vector[4] =  0; vector[7] = -1;
            vector[2] = 0; vector[5] = -1; vector[8] =  0;
    }

    QColor Embossing_Filter :: CalculateNewPixelColor(QImage photo, int x, int y, int radius) {
        const int K    = 30;
        int returnR    = 0;
        int returnG    = 0;
        int returnB    = 0;
        int norm       = 1;
        const int SIZE = 2 * radius + 1;
        
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                int idx = (i + radius) * SIZE + j + radius;
                QColor color = photo.pixelColor(Clamp<int>(x + j, photo.width()  - 1, 0),
                                                Clamp<int>(y + i, photo.height() - 1, 0));
                returnR += color.red()   * vector[idx] / norm;
                returnG += color.green() * vector[idx] / norm;
                returnB += color.blue()  * vector[idx] / norm;
            }
            returnR += K; //*
            returnG += K; //* Brightness up
            returnB += K; //*
        }
        return QColor(Clamp(returnR, 255, 0),
                      Clamp(returnG, 255, 0),
                      Clamp(returnB, 255, 0));
    }

    QImage Embossing_Filter :: CalculateNewImagePixMap(const QImage & photo, int radius) {
        QImage result_Image(photo);
        for (int x = 0; x < photo.width(); x++) {
            for (int y = 0; y < photo.height(); y++) {
                result_Image.setPixelColor(x, y, CalculateNewPixelColor(photo, x, y, radius));
            }
        }
        return result_Image;
    }

/*-------------- Roration filter  ---------------*/

QImage Roration_Filter :: CalculateNewImagePixMap(const QImage & photo, int radius) {
    QImage result_Image(photo);
    uint x,y,x0,y0;
    x0 = photo.width()  / 2;
    y0 = photo.height() / 2;
    //float angle = radius;
    float angle = 3.14/4; //radian
    
    for (int k = 0; k < photo.width(); k++) {
        for (int l = 0; l < photo.height(); l++) {
            x = (k - x0) * cos(angle) - (l - y0) * sin(angle) + x0;
            y = (k - x0) * sin(angle) + (l - y0) * cos(angle) + y0;
            result_Image.setPixelColor(k, l, photo.pixelColor(Clamp(x, photo.width()  - 2, 0),                                                                            Clamp(y, photo.height() - 2, 0)));
        }
    }
    return result_Image;
}



