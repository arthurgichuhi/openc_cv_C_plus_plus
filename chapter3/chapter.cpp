#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
//Resizing and Cropping Images
int main(){
    string path="Resources/test.png";
    Mat img=imread(path);
    Mat imgResize,imgCrop;

    //Image Resizing
    resize(img,imgResize,Size(),0.5,0.5);

    //Image Crop
    Rect roi(200,50,300,320);
    imgCrop=img(roi);

    imshow("Image",img);
    imshow("Image Resize", imgResize);
    imshow("Image Crop",imgCrop);
    waitKey(0);
    return 0;
}