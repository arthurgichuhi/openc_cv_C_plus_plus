#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<vector<int>>colors{
    {0,62,0,35,255,255},
    {82,126,73,179,255,255},
    // {0,0,255,179,255,255}
};

vector<Scalar>colorValues{
    {232, 123, 28},//Orange
    {16, 1, 110},//blue
    //{73, 73, 74}//grey
    };

Mat img;

void getContours(Mat mask){
    vector<vector<Point>>contours;
    vector<Vec4i>hierachy;
    findContours(mask,contours,hierachy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    // drawContours(img,contours,-1,Scalar(255,0,255),2);

    vector<vector<Point>>conPoly(contours.size());
    vector<Rect>boundRect(contours.size());

    for(int i=0;i<contours.size();i++){
        int area=contourArea(contours[i]);
        if( area > 1000){
            
            float peri=arcLength(contours[i],true);
            approxPolyDP(contours[i],conPoly[i],0.02*peri,true);
            boundRect[i]=boundingRect(conPoly[i]);
            drawContours(img,conPoly,i,Scalar(255,0,255),2);
            // circle(img,{boundRect[i].x,boundRect[i].y},10,Scalar(255,255,255),FILLED);
            // putText(img,object,{boundRect[i].x,boundRect[i].y-5},FONT_HERSHEY_COMPLEX,1,Scalar(0,255,0),1);
            // rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(0,0,0),2);
        }
    }
}

void findColor(Mat img){
    Mat imgHsv;
    cvtColor(img,imgHsv,COLOR_BGR2HSV);

    for(int i=0;i<colors.size();i++){
        Scalar lower(colors[i][0],colors[i][1],colors[i][2]);
        Scalar upper(colors[i][3],colors[i][4],colors[i][5]);
        Mat mask;
        inRange(imgHsv,lower,upper,mask);
        getContours(mask);
        // imshow(to_string(i),mask);
    }

}


int main(){
    
    VideoCapture cap(0);
    while(true){
        cap.read(img);
        findColor(img);
        imshow("Image",img);
        waitKey(1);
    }
    return 0;
}
