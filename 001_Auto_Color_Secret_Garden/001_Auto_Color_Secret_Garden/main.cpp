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

	//��1������ԭʼͼ��ֵͼģʽ����
	Mat srcImage = imread("secretgarden.jpg", 0);
	//imshow("ԭʼͼ",srcImage);

	//��2����ʼ�����ͼ
	Mat dstImage1 = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	Mat dstImage2 = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	//��3��srcImageȡ������ֵ200���ǲ���
	srcImage = srcImage > 200;
	//imshow( "ȡ��ֵ���ԭʼͼ", srcImage );

	//��4�����������Ͳ�νṹ
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//��5����������
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	Mat temp;
	//ʹ�ø÷���ͳ����ͨ�����ĸ���Ϊ���ص�ֵ��1����1֮���ֵ����������
	int num_1 = connectedComponents(srcImage, temp, 4, CV_32S) - 1;

	//��6���������ж���������� �������ɫ���Ƴ�ÿ�����������ɫ
	int index = 0;
	int num_0 = 0; // ͳ��ͼ��������ͨ�����ĸ���
	for (; index >= 0; index = hierarchy[index][0])
	{
		//Ϊͼ��������ɫ����QColor(R, G, B)������Ŀ��һ��QT��Դ���ɫ�ʴ��䷽��
		Scalar color1(sin(rand()*0.3) * 128 + 127, sin(rand()*0.6) * 128 + 127, sin(rand()*0.4) * 128 + 127);
		Scalar color2(rand() % 127 + 128, rand() % 127 + 128, rand() % 127 + 128);
		//�˾�����OpenCV3��Ϊ��
		drawContours(dstImage1, contours, index, color1, FILLED, 8, hierarchy);
		drawContours(dstImage2, contours, index, color2, FILLED, 8, hierarchy);

		if (index > num_0) {
			num_0 = index;
		}
	}

	printf("ͼ��������ͨ�����ĸ���num0��%d \n", num_0);
	printf("ͼ��������ͨ�����ĸ���num1��%d \n", num_1);
	printf("ͼ��������ͨ�����ĸ���num2��%d \n", contours.size());

	//��7����ʾ��������ͼ
	imshow( "����ͼ��1", dstImage1);
	imshow( "����ͼ��2", dstImage2);

	//��8����ʾ������С���ͼ��
	//Mat resizeImage1, resizeImage2;
	//resize(dstImage1, resizeImage1, Size(), 0.15, 0.15);
	//resize(dstImage2, resizeImage2, Size(), 0.15, 0.15);
	//imshow("������С���ͼ��1", resizeImage1);
	//imshow("������С���ͼ��2", resizeImage2);

	imwrite("demo011.jpg", dstImage1);
	imwrite("demo022.jpg", dstImage2);

	waitKey(0);

}

