#include <iostream>
#include "sift.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main()
{
    double dur;
    clock_t start,end;
    start = clock();

    cv::Mat src = imread("../lena.jpg");

    if(src.empty())
    {
        cout << "the image open error! "<<endl;
        getchar();
        return -1;
    }

    if(src.channels()!=3) return -2;

    std::vector<Keypoint> features;

    Sift(src, features, 1.6);       //【1】SIFT特征点检测和特征点描述

    DrawKeyPoints(src, features);  //【2】画出关键点(特征点)

    DrawSiftFeatures(src, features); //【3】画出SIFT特征点

    write_features(features, "../descriptor.txt"); //【4】将特征点写入文本

    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));

    cv::imshow("src", src);
    cv::waitKey();

    return 0;
}