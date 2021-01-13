#include <iostream>
#include <opencv2/opencv.hpp> 
using namespace std;
using namespace cv; 
Mat rotate_image(Mat src,int angle)
    { 
  Point2f center((src.cols-1)/2.0,(src.rows-1)/2.0); 
    Mat rot = getRotationMatrix2D(center, angle, 1.0); 
    Rect2f grid = RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
     rot.at<double>(0,2) += grid.width/2.0 - src.cols/2.0;
     rot.at<double>(1,2) += grid.height/2.0 - src.rows/2.0; 
    Mat final_image; 
    warpAffine(src, final_image, rot, grid.size()); 
    return final_image;
    } 
int main() 
    { 
    cout<<"Enter Image File Path : "; 
    string image; 
    getline(cin,image); 
    Mat src = imread(image,IMREAD_UNCHANGED); 
    if(src.empty())
        {
      cout<<"Image is not Loading"<<endl;       return -1; 
        }
     cout<<"Enter Angle : "; 
    int angle; 
    cin>>angle; 
    angle = angle%360;
     Mat rotimg = rotate_image(src,angle);    if(rotimg.empty())
        { 
        cout<<"Unable to rotate the image"<<endl; 
        return -1;
         } 
    imshow("Original Image", src);    imshow("Rotated Image", rotimg); 
    waitKey(0); 
    return 0;
    }
