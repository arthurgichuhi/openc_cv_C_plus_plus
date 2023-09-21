#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat img,imgBlur,imgCanny,imgGray,imgThresh,imgDil,imgErode,imgWarp;

vector<Point>initialPoints,docPoints;

int w=420,h=596;

Mat preprocessing(Mat img){
    cvtColor(img,imgGray,COLOR_BGR2GRAY);
    GaussianBlur(imgGray,imgBlur,Size(3,3),3,0);
    Canny(imgGray,imgCanny,25,75);
    Mat kernel=getStructuringElement(MORPH_RECT,Size(3,3));
    dilate(imgCanny,imgDil,kernel);
    return imgDil;
}
vector<Point>getContours(Mat mask){
    vector<vector<Point>>contours;
    vector<Vec4i>hierachy;
    findContours(mask,contours,hierachy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    vector<vector<Point>>conPoly(contours.size());
    vector<Rect>boundRect(contours.size());
    vector<Point>biggest;
    int maxArea=0;
    for(int i=0;i<contours.size();i++){
        int area=contourArea(contours[i]);
        if( area > 1000){
            float peri=arcLength(contours[i],true);
            approxPolyDP(contours[i],conPoly[i],peri*0.002,true);
            if(area>maxArea && conPoly[i].size()==4){
                //drawContours(img,conPoly,i,Scalar(255,0,255),2);
                maxArea=area;
                biggest={conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3]};
            }
        } 
    }
    return biggest;
}

void drawPoints(vector<Point>points, Scalar color){
    for(int i=0;i<points.size();i++){
        circle(img,points[i],10,color,FILLED);
        putText(img,to_string(i),points[i],FONT_HERSHEY_PLAIN,5,color,5);
    }
}

Mat getWarp(Mat imgSrc,vector<Point>points,float w,float h){
    Mat imgWarped;
    Point2f src[4]={{points[0]},{points[1]},{points[2]},{points[3]}};
    Point2f dst[4]={{0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h}};
    Mat matrix=getPerspectiveTransform(src,dst);
    warpPerspective(imgSrc,imgWarped,matrix,Point(w,h));
    return imgWarped;
}

vector<Point>reorderPoints(vector<Point>points){
    vector<Point>newPoints;
    vector<int>sumPoints,subPoints;
    for(int i=0;i<points.size();i++){
        sumPoints.push_back(points[i].x+points[i].y);
        subPoints.push_back(points[i].x-points[i].y);
    }
    newPoints.push_back(points[min_element(sumPoints.begin(),sumPoints.end())-sumPoints.begin()]);
    newPoints.push_back(points[max_element(subPoints.begin(),subPoints.end())-subPoints.begin()]);
    newPoints.push_back(points[min_element(subPoints.begin(),subPoints.end())-subPoints.begin()]);
    newPoints.push_back(points[max_element(sumPoints.begin(),sumPoints.end())-sumPoints.begin()]);
    return newPoints;
}

int main (){
    string path="Resources/paper.jpg";
    img=imread(path);
    resize(img,img,Size(),0.5,0.5);
    //preprocessing
    imgThresh=preprocessing(img);
    //Get contours 
    initialPoints=getContours(imgThresh);
    docPoints=reorderPoints(initialPoints);
    //Warp
    imgWarp=getWarp(img,docPoints,w,h);
    //crop imgWarp
    int cropValue=5;
    Rect roi(cropValue,cropValue,w-(2*cropValue),h-(2*cropValue));
    Mat croppedImage=imgWarp(roi);
    drawPoints(docPoints,Scalar(0,255,0));

    imshow("Paper",img);
    imshow("Warped",imgWarp);
    imshow("Cropped",croppedImage);
    waitKey(0);
    return 0;
}