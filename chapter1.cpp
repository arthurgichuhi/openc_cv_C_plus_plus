#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
//Reading Images

int main()
{   
    string path="Resources/cards.jpg";
    Mat img=imread(path);
    imshow("Image",img);
    cout << img <<endl;
    waitKey(0);
    return 0;
}

//Reading video files

// int main(){
//     string path="Resources/test_video.mp4";
//     VideoCapture cap(path);
//     Mat img;
//     while (true){
//         cap.read(img);
//         imshow("Video",img);
//         waitKey(20);
//     }
//     return 0;
// }

//Webcam feed
// int main(){
//     VideoCapture cap(0);
//     Mat img;
//     while(true){
//         cap.read(img);
//         imshow("Image",img);
//         waitKey(1);
//     }
//     return 0;
// }