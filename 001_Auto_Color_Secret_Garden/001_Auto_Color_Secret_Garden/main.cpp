#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>

using namespace cv;
using namespace std;

int main()
{
	srand((unsigned)time(0));

	//【1】载入原始图二值图模式载入
	Mat srcImage = imread("secretgarden.jpg", 0);
	//imshow("原始图",srcImage);

	//【2】初始化结果图
	Mat dstImage1 = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	Mat dstImage2 = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	//【3】srcImage取大于阈值200的那部分
	srcImage = srcImage > 200;
	//imshow( "取阈值后的原始图", srcImage );

	//【4】定义轮廓和层次结构
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//【5】查找轮廓
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	Mat temp;
	//使用该方法统计连通分量的个数为返回的值减1（减1之后的值包括背景）
	int num_1 = connectedComponents(srcImage, temp, 4, CV_32S) - 1;

	//【6】遍历所有顶层的轮廓， 以随机颜色绘制出每个连接组件颜色
	int index = 0;
	int num_0 = 0; // 统计图像里面连通分量的个数
	for (; index >= 0; index = hierarchy[index][0])
	{
		//为图像设置颜色——QColor(R, G, B)——项目是一个QT开源库的色彩搭配方案
		Scalar color1(sin(rand()*0.3) * 128 + 127, sin(rand()*0.6) * 128 + 127, sin(rand()*0.4) * 128 + 127);
		Scalar color2(rand() % 127 + 128, rand() % 127 + 128, rand() % 127 + 128);
		//此句代码的OpenCV3版为：
		drawContours(dstImage1, contours, index, color1, FILLED, 8, hierarchy);
		drawContours(dstImage2, contours, index, color2, FILLED, 8, hierarchy);

		if (index > num_0) {
			num_0 = index;
		}
	}

	printf("图像里面连通分量的个数num0：%d \n", num_0);
	printf("图像里面连通分量的个数num1：%d \n", num_1);
	printf("图像里面连通分量的个数num2：%d \n", contours.size());

	//【7】显示最后的轮廓图
	imshow( "轮廓图：1", dstImage1);
	imshow( "轮廓图：2", dstImage2);

	//【8】显示调整大小后的图像
	//Mat resizeImage1, resizeImage2;
	//resize(dstImage1, resizeImage1, Size(), 0.15, 0.15);
	//resize(dstImage2, resizeImage2, Size(), 0.15, 0.15);
	//imshow("调整大小后的图像：1", resizeImage1);
	//imshow("调整大小后的图像：2", resizeImage2);

	imwrite("demo011.jpg", dstImage1);
	imwrite("demo022.jpg", dstImage2);

	waitKey(0);

}

