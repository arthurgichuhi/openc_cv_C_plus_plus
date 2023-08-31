#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;



Mat imgHsv,mask;

int hmin=0, smin=0,vmin=0;
int hmax=19, smax=240, vmax=255;

int main(){
    string path="Resources/lambo.png";
    
    Mat img=imread(path);

    cvtColor(img,imgHsv,COLOR_BGR2HSV);

    namedWindow("Trackbars",(480,240));

    createTrackbar("Hue-min","Trackbars",&hmin,179);

    while(true){
        Scalar lower(hmin,smin,vmin);
        Scalar upper(hmax,smax,vmax);

        inRange(imgHsv,lower,upper,mask);
        
        imshow("Image",img);
        imshow("Image HSV",imgHsv);
        waitKey(1);
    }
    return 0;
}