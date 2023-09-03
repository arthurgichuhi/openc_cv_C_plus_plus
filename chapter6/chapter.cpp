#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat imgHsv,mask;

int hmin=0, smin=0,vmin=0;
int hmax=179, smax=240, vmax=255;

void onTrackBar(int value,void* userData){
        hmin=getTrackbarPos("Hue-min","Trackbars");
        hmax=getTrackbarPos("Hue-max","Trackbars");
        smin=getTrackbarPos("Saturation-min","Trackbars");
        smax=getTrackbarPos("Saturation-max","Trackbars");
        vmin=getTrackbarPos("Value-min","Trackbars");
        vmax=getTrackbarPos("Value-max","Trackbars");
    }

int main(){
    string path="Resources/lambo.png";
    
    Mat img=imread(path);

    cvtColor(img,imgHsv,COLOR_BGR2HSV);

    namedWindow("Trackbars",(480,240));

    createTrackbar("Hue-min","Trackbars",nullptr,179,onTrackBar);
    createTrackbar("Hue-max","Trackbars",nullptr,179,onTrackBar);
    createTrackbar("Saturation-min","Trackbars",nullptr,255,onTrackBar);
    createTrackbar("Saturation-max","Trackbars",nullptr,255,onTrackBar);
    createTrackbar("Value-min","Trackbars",nullptr,255,onTrackBar);
    createTrackbar("Value-max","Trackbars",nullptr,255,onTrackBar);

    while(true){
        Scalar lower(hmin,smin,vmin);
        Scalar upper(hmax,smax,vmax);

        inRange(imgHsv,lower,upper,mask);
        
        imshow("Image",img);
        imshow("Image HSV",imgHsv);
        imshow("Image Mask",mask);
        waitKey(1);
    }
    return 0;
}