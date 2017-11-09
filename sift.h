//
// Created by 王威 on 2017/10/10.
//
#ifndef SIFT_H
#define SIFT_H
#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

typedef double pixel_t;                             //【1】像素类型

#define INIT_SIGMA 0.5                               //【2】初始sigma
#define SIGMA 1.6

#define INTERVALS 3                                  //【3】高斯金字塔中每组图像中有三层/张图片

#define RATIO 10                                     //【4】半径r
#define MAX_INTERPOLATION_STEPS 5                    //【5】最大空间间隔
#define DXTHRESHOLD 0.03                             //【6】|D(x^)| < 0.03   0.03极值点太多

#define ORI_HIST_BINS 36                             //【7】bings=36
#define ORI_SIGMA_TIMES 1.5
#define ORI_WINDOW_RADIUS 3.0 * ORI_SIGMA_TIMES
#define ORI_SMOOTH_TIMES 2
#define ORI_PEAK_RATIO 0.8
#define FEATURE_ELEMENT_LENGTH 128
#define DESCR_HIST_BINS 8
#define IMG_BORDER 5
#define DESCR_WINDOW_WIDTH 4
#define DESCR_SCALE_ADJUST 3
#define DESCR_MAG_THR 0.2
#define INT_DESCR_FCTR 512.0
/*********************************************************************************************
*模块说明：
*        关键点/特征点的结构体声明
*注意点1：
*        在高斯金字塔构建的过程中，一幅图像可以产生好几组(octave)图像，一组图像包含几层(inteval)
*        图像
*********************************************************************************************/
struct Keypoint
{
    int    octave;                                        //【1】关键点所在组
    int    interval;                                      //【2】关键点所在层
    double offset_interval;                               //【3】调整后的层的增量

    int    x;                                             //【4】x,y坐标,根据octave和interval可取的层内图像
    int    y;
    double scale;                                         //【5】空间尺度坐标scale = sigma0*pow(2.0, o+s/S)

    double dx;                                            //【6】特征点坐标，该坐标被缩放成原图像大小
    double dy;

    double offset_x;
    double offset_y;

    //============================================================
    //1---高斯金字塔组内各层尺度坐标，不同组的相同层的sigma值相同
    //2---关键点所在组的组内尺度
    //============================================================
    double octave_scale;                                  //【1】offset_i;
    double ori;                                           //【2】方向
    int    descr_length;
    double descriptor[FEATURE_ELEMENT_LENGTH];            //【3】特征点描述符
    double val;                                           //【4】极值
};
/*********************************************************************************
*模块说明：
*        SIFT算法内,所有成员函数的声明
*********************************************************************************/
void read_features(std::vector<Keypoint>&features, const char*file);
void write_features(const std::vector<Keypoint>&features, const char*file);

void testInverse3D();

void write_pyr(const std::vector<Mat>& pyr, const char* dir);
void DrawKeyPoints(Mat &src, std::vector<Keypoint>& keypoints);

const char* GetFileName(const char* dir, int i);

void ConvertToGray(const Mat& src, Mat& dst);
void DownSample(const Mat& src, Mat& dst);
void UpSample(const Mat& src, Mat& dst);

void GaussianTemplateSmooth(const Mat &src, Mat &dst, double);
void GaussianSmooth2D(const Mat &src, Mat &dst, double sigma);
void GaussianSmooth(const Mat &src, Mat &dst, double sigma);

void Sift(const Mat &src, std::vector<Keypoint>& features, double sigma=SIGMA, int intervals=INTERVALS);

void CreateInitSmoothGray(const Mat &src, Mat &dst, double);
void GaussianPyramid(const Mat &src, std::vector<Mat>&gauss_pyr, int octaves, int intervals, double sigma);

void Sub(const Mat& a, const Mat& b, Mat & c);

void DogPyramid(const std::vector<Mat>& gauss_pyr, std::vector<Mat>& dog_pyr, int octaves, int intervals);
void DetectionLocalExtrema(const std::vector<Mat>& dog_pyr, std::vector<Keypoint>& extrema, int octaves, int intervals);
void DrawSiftFeatures(Mat& src, std::vector<Keypoint>& features);

#endif