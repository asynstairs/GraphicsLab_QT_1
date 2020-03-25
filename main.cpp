#include "Filters.hpp"
#include <QtCore/QCoreApplication>
#include "qimage.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    string s;
    QImage photo;
    int    position;
    bool   end = false;

    for (int i = 0; i < argc; i++){
        if ((!strcmp(argv[i], "-p")) && (i + 1 < argc)){
            s = argv[i + 1];
        }
    }

    photo.load(QString(s.c_str()));
    photo.save("Starting.PNG");
    
    cout << "\v\t 0.Path to the IMAGE (exit).\n";
    cout << "\v\t 1.Invert.\n";
    cout << "\v\t 2.Blur.\n";
    cout << "\v\t 3.Gaussian Blur.\n";
    cout << "\v\t 4.Gray Scale.\n";
    cout << "\v\t 5.Sepia.\n";
    cout << "\v\t 6.Brightness.\n";
    cout << "\v\t 7.Sharpness.\n";
    cout << "\v\t 8.Sobel.\n";
    cout << "\v\t 9.Embossing.\n";
    cout << "\v\t 10.Rotation.\n";

    while (end != true){
            cin >>   position;
            switch ( position ) {
                case 0: {
                cout << "/nPath: " << (s.c_str()) << endl << endl;
                end = true;
                break;
                }
                case 1: {
                    Invert_Filter* invert_obj = new Invert_Filter();
                    QImage invert_photo = invert_obj->CalculateNewImagePixMap(photo, 0);
                    invert_photo.save("Invert_Photo.PNG");
                    cout << "\tSaved Invert_Photo.PNG.\n";
                    //system("Invert_Photo.PNG");
                    break;
                }
                case 2: {
                    Blur_Filter* blur_obj = new Blur_Filter();
                    QImage blur_photo = blur_obj->CalculateNewImagePixMap(photo, 4);
                    blur_photo.save("Blur_Photo.PNG");
                    cout << "\tSaved Blur_Photo.PNG.\n";
                    //system("Blur_Photo.PNG");
                    break;
                }
                case 3: {
                    Gaussian_Blur_Filter* gauss_obj = new Gaussian_Blur_Filter();
                    QImage gauss_photo = gauss_obj->CalculateNewImagePixMap(photo, 15);
                    gauss_photo.save("Gauss_Photo.PNG");
                    cout << "\tSaved Gauss_Photo.PNG.\n";
                    //system("Gauss_Photo.PNG");
                    break;
                    }
                case 4: {
                    Gray_Scale_Filter* gray_obj = new Gray_Scale_Filter();
                    QImage gray_photo = gray_obj->CalculateNewImagePixMap(photo, 0);
                    gray_photo.save("Gray_Photo.PNG");
                    cout << "\tSaved Gray_Photo.PNG.\n";
                     // system("Gray_Photo.PNG");
                    break;
                  }
                  case 5: {
                    Sepia_Filter* sepia_obj = new Sepia_Filter();
                    QImage sepia_photo = sepia_obj->CalculateNewImagePixMap(photo, 0);
                    sepia_photo.save("Sepia_Photo.PNG");
                    cout << "\tSaved Sepia_Photo.PNG.\n";
                     // system("Sepia_Photo.PNG");
                    break;
                  }
                  case 6: {
                    Brightness_Filter* brightness_obj = new Brightness_Filter();
                    QImage brightness_photo = brightness_obj->CalculateNewImagePixMap(photo, 0);
                    brightness_photo.save("Brightness_Photo.PNG");
                    cout << "\tSaved Brightness_Photo.PNG.\n";
                      //system("Brightness_Photo.PNG");
                    break;
                  }
                  case 7: {
                    Sharpness_Filter* sharpness_obj = new Sharpness_Filter();
                    QImage sharpness_photo = sharpness_obj->CalculateNewImagePixMap(photo, 2);
                    sharpness_photo.save("Sharpness_Photo.PNG");
                    cout << "\tSaved Sharpness_Photo.PNG.\n";
                   // system("Sharpness_Photo.PNG");
                    break;
                   }
                  case 8: {
                    Sobel_Filter* sobel_obj = new Sobel_Filter();
                    QImage sobel_photo = sobel_obj->CalculateNewImagePixMap(photo, 1);
                    sobel_photo.save("Sobel_Photo.PNG");
                    cout << "\tSaved Sobel_Photo.PNG.\n";
                       // system("Sobel_Photo.PNG");
                    break;
                   }
                  case 9: {
                    Embossing_Filter* emb_obj = new Embossing_Filter();
                    QImage emb_photo = emb_obj->CalculateNewImagePixMap(photo, 1);
                    emb_photo.save("Embossing_Photo.PNG");
                    cout << "\tSaved Embossing_Photo.PNG.\n";
                    //system("Sobel_Photo.PNG");
                    break;
                   }
                  case 10:{
                    Roration_Filter* rot_obj = new Roration_Filter();
                    QImage rot_photo = rot_obj->CalculateNewImagePixMap(photo, 1);
                    rot_photo.save("Rotation_Photo.PNG");
                    cout << "\tSaved Rotation_Photo.PNG\n";
                    break;
                   }
            }
    }
    cout << "\n\treturn 0;\n";
    return 0;
}


