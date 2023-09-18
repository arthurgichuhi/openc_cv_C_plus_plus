#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat img,imgHsv,imgDilate,mask;

array<Rect> getContours(Mat mask){
    vector<vector<Point>>contours;
    vector<Vec4i>hierachy;
    array<Rect>result;
    findContours(mask,contours,hierachy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    //drawContours(img,contours,-1,Scalar(255,0,255),2);

    vector<vector<Point>>conPoly(contours.size());
    vector<Rect>boundRect(contours.size());

    for(int i=0;i<contours.size();i++){
        int area=contourArea(contours[i]);
        if( area > 1000){
            
            float peri=arcLength(contours[i],true);
            approxPolyDP(contours[i],conPoly[i],0.02*peri,true);
            // drawContours(img,conPoly,i,Scalar(255,0,255),2);

            boundRect[i]=boundingRect(conPoly[i]);

            // circle(img,{boundRect[i].x,boundRect[i].y},10,Scalar(255,255,255),FILLED);
            // putText(img,object,{boundRect[i].x,boundRect[i].y-5},FONT_HERSHEY_COMPLEX,1,Scalar(0,255,0),1);
            // rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(0,0,0),2);
        }
    }
    return boundRect;
}

int main(){
    VideoCapture cap(0);
    vector<Rect>points;

    while (true){
        cap.read(img);
        //find color
        cvtColor(img,imgHsv,COLOR_BGR2HSV);
        Scalar lower(0,120,90);
        Scalar upper(179,255,255);
        inRange(imgHsv,lower,upper,mask);
        //
        Mat kernel=getStructuringElement(MORPH_RECT,Size(3,3));
        dilate(mask,imgDilate,kernel);
        getContours(mask);
        for(int i=0;getContours(mask).size();i++){
            circle(img,{getContours(mask)[i].x,getContours(mask)[i].y},10,Scalar(255,0,255),FILLED);
        }
        // getContours(imgDilate,img);
        imshow("Image",img);
        waitKey(1);
    }
    return 0;
}