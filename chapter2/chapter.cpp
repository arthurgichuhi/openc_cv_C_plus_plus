#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    string path="Resources/test.png";
    Mat img=imread(path);
    Mat imgGray,imgBlur,imgCanny,imgCanny2,imgDilate,imgErode;
    //converting BGR to Gray image
    cvtColor(img,imgGray,COLOR_BGR2GRAY);
    //Gaussian blur
    GaussianBlur(img,imgBlur,Size(3,3),3,0);
    //Canny Image
    Canny(imgBlur,imgCanny,25,75);

    //dilate kernel
    Mat dilateKernel=getStructuringElement(MORPH_RECT,Size(3,3));
    //dilate Image
    dilate(imgCanny,imgDilate,dilateKernel);

    //erode kernel
    Mat erodeKernel=getStructuringElement(MORPH_ERODE,Size(3,3));
    //erode image
    erode(imgDilate,imgErode,erodeKernel);


    imshow("Image",img);
    // imshow("Image Gray",imgGray);
    // imshow("Image Blur",imgBlur);
    imshow("Image Canny",imgCanny);
    imshow("Image Dilate",imgDilate);
    imshow("Image Eroded",imgErode);
    waitKey(0);
    return 0;
}