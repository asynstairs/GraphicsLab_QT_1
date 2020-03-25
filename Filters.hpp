#pragma once
#include "qimage.h"

class Filters{
public:
     Filters();
    ~Filters();
    virtual QImage CalculateNewImagePixMap(const QImage& photo, int radius) = 0;
};

class Invert_Filter : public Filters
{
public:
     Invert_Filter() {};
    ~Invert_Filter() {};
    QImage CalculateNewImagePixMap(const QImage& photo, int radius);
};

class Matrix_Filter :public Filters {
public:
    float* vector;
    int mRadius;

    Matrix_Filter(int radius = 1) : mRadius(radius) {};
    QImage CalculateNewImagePixMap(const QImage& photo, int radius);
    QColor CalculateNewPixelColor(QImage photo, int x, int y, int radius);
};

class Blur_Filter : public Matrix_Filter {
public:
    Blur_Filter() {
        int size = 2 * mRadius + 1;
        vector = new float[size * size];
        
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                vector[i * size + j] = 1.0f / (size * size);
    }
};

class Gaussian_Blur_Filter : public Matrix_Filter {
public:
     Gaussian_Blur_Filter() {
        CreateGaussianVector(3,2);
     }
    ~Gaussian_Blur_Filter() {};

    void CreateGaussianVector(int radius, int sigma);
};

class Gray_Scale_Filter : public Filters {
    public:
     Gray_Scale_Filter() {};
    ~Gray_Scale_Filter() {};
    QColor CalculateNewPixelColor(QImage photo, int x, int y);
    QImage CalculateNewImagePixMap(const QImage& photo, int radius);
};

class Sepia_Filter : public Filters {
public:
     Sepia_Filter() {};
    ~Sepia_Filter() {};
    QColor CalculateNewPixelColor(QImage photo, int x, int y);
    QImage CalculateNewImagePixMap(const QImage& photo, int radius);
};

class Brightness_Filter : public Filters {
public:
     Brightness_Filter() {};
    ~Brightness_Filter() {};
    QColor CalculateNewPixelColor(QImage photo, int x, int y);
    QImage CalculateNewImagePixMap(const QImage& photo, int radius);
};

class Sharpness_Filter: public Matrix_Filter {
public:
     Sharpness_Filter() {
        CreateSharpnessVector(1);
     };
    ~Sharpness_Filter() {};
    void CreateSharpnessVector(int radius);
};

class Sobel_Filter{
public:
    float* vectorX;
    float* vectorY;
    float* vector;
    QColor CalculateNewPixelColor(QImage photo, int x, int y, int radius);
    void CreateSobelVector(int radius);
    
     Sobel_Filter() {
        CreateSobelVector(1);
     }
    ~Sobel_Filter() {};
    QImage CalculateNewImagePixMap(const QImage& photo, int radius);
};

/* ----------- LAB --------------*/

class Embossing_Filter {
public:
    float* vector;
    int mRadius;
    QColor CalculateNewPixelColor(QImage photo, int x, int y, int radius);
    QImage CalculateNewImagePixMap(const QImage& photo, int radius);
    void CreateEmbossingVector(int radius);
    
     Embossing_Filter(int radius = 1): mRadius(radius) {
        CreateEmbossingVector(mRadius);
     }
    ~Embossing_Filter() {
        delete [] vector;
    };
};

class Roration_Filter: public Filters{
public:
     Roration_Filter(){};
    ~Roration_Filter(){};
    QImage CalculateNewImagePixMap(const QImage& photo, int radius);  // radius = angle
};
