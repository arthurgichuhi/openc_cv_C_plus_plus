#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat imgBlur,imgGray,imgCanny,imgDilate,imgErode;

void getContours(Mat imgDil,Mat img){
    vector<vector<Point>>contours;
    vector<Vec4i>hierachy;

    findContours(imgDil,contours,hierachy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    //drawContours(img,contours,-1,Scalar(255,0,255),2);

    vector<vector<Point>>conPoly(contours.size());
    vector<Rect>boundRect(contours.size());
    int objCor;
    string object;
    for(int i=0;i<contours.size();i++){
        int area=contourArea(contours[i]);
        if( area > 1000){
            
            float peri=arcLength(contours[i],true);
            approxPolyDP(contours[i],conPoly[i],0.02*peri,true);
            drawContours(img,conPoly,i,Scalar(255,0,255),2);

            boundRect[i]=boundingRect(conPoly[i]);
            objCor=(int)conPoly[i].size();

            if (objCor==3){object="Tri";}
            else if(objCor==4){object="Rect";}
            else if(objCor>4){object="Circle";}

            putText(img,object,{boundRect[i].x,boundRect[i].y-5},FONT_HERSHEY_COMPLEX,1,Scalar(0,255,0),1);
            rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(0,0,0),2);

            // cout << conPoly[i] <<endl;
            // cout << conPoly[i].size() <<endl;
        }
    }
}

int main()
{
    string path="Resources/shapes.png";
    Mat img=imread(path);

    cvtColor(img,imgGray,COLOR_BGR2GRAY);

    GaussianBlur(imgGray,imgBlur,Size(3,3),3,0);

    Canny(imgBlur,imgCanny,50,100);

    Mat kernel=getStructuringElement(MORPH_RECT,Size(3,3));
    dilate(imgCanny,imgDilate,kernel);

    getContours(imgDilate,img);

    imshow("Image",img);
    waitKey(0);

    return 0;
}