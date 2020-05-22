#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
Mat srcImage, dstImage1, dstImage2;
int h_time = 1, s_time = 1, v_time = 1;
String imagePath = "C:/Users/admin/Pictures/car2.jpg";
int main() {
	srcImage = imread(imagePath, 1);
	imshow("原图", srcImage);

	// 高斯模糊
	Mat gausImage = srcImage.clone();
	GaussianBlur(srcImage, gausImage, Size(3, 3), 0, 0);
	imshow("高斯模糊", gausImage);

	// 灰度化
	Mat grayImage = srcImage.clone();
	cvtColor(gausImage, grayImage, COLOR_BGR2GRAY);
	 imshow("灰图", grayImage);

	// Sobel算子
	Mat sobelImage = srcImage.clone();
	Sobel(grayImage, sobelImage, CV_8UC1, 1, 0);
	imshow("Sobel算子", sobelImage);

	// 二值化
	Mat binaryImage = srcImage.clone();
	threshold(sobelImage, binaryImage, 90, 255, THRESH_BINARY);
	imshow("二值化", binaryImage);

	// 开运算(先腐蚀，再膨胀)
//		Mat morphologyExImage=srcImage.clone();
//		Imgproc.morphologyEx(binaryImage, morphologyExImage, Imgproc.MORPH_CLOSE, Imgproc.getStructuringElement( Imgproc.MORPH_RECT,new Size(1,1)));
//		HighGui.imshow("开运算", morphologyExImage);

	Mat erodeImage = srcImage.clone();
	erode(binaryImage, erodeImage, getStructuringElement(MORPH_RECT, Size(3, 2)));
	imshow("腐蚀", erodeImage);

	Mat dilateImage = srcImage.clone();
	dilate(erodeImage, dilateImage, getStructuringElement(MORPH_RECT, Size(22, 22)));
	imshow("膨胀", dilateImage);

	
	// 取轮廓,显示全部轮廓
	Mat flagImage = srcImage.clone();
	vector<vector<Point>> contours;
	Mat hierarchy ;
	findContours(dilateImage, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	drawContours(flagImage, contours, -1, Scalar(0, 255, 0));//绿线画出所有的轮廓
	imshow("轮廓", flagImage);


	//识别车牌(找出面积最大且宽高比例符合要求)，仅对提供的两个车牌识别有效!!!
	double maxArea = 0;
	int targetIndex;
	for (int i = 1; i < contours.size(); i++) {
		double area = contourArea(contours[i]);
		Rect rect = boundingRect(contours[i]);
		double scaleWH = (double)rect.width / rect.height;//这个比例范围是目测的
		if (area > maxArea&&scaleWH > 1.5 && scaleWH < 3.5) {
			maxArea = area;
			targetIndex = i;
		}
	}

	//显示车牌轮廓
	Mat licenseImage = srcImage.clone();
	Rect r = boundingRect(contours[targetIndex]);
	rectangle(licenseImage,r,Scalar(0, 255, 0));
	imshow("车牌标记", licenseImage);

	waitKey(0);
	return 0;
 }