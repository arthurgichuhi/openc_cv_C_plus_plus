#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(){
    //creating an image of size 512*512
    Mat img(512,512,CV_8UC3,Scalar(255,255,255));

    //circle
    circle(img,Point(256,256),175,Scalar(0,69,255),FILLED);
    //rectangle using Rect
    // rectangle(img,Rect(150,200,10,30),Scalar(255,255,255),3);
    //rectangle using points
    rectangle(img,Point(100,220),Point(420,280),Scalar(255,255,255),2);
    line(img,Point(110,290),Point(400,290),Scalar(255,255,255),3);
    putText(img,"Gichuhi Open C++",Point(102,256),FONT_HERSHEY_COMPLEX,1,Scalar(255,255,255),2);
    imshow("Image",img);
    waitKey(0);
    return 0;
}