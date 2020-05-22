#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
Mat srcImage1, dstImage1, dstImage2;
int h_time=1, s_time=1, v_time=1;
String imagePath = "C:/Users/admin/Pictures/1.2.png";
void hsv_trackbar(int, void*);
int main()
{
	//imaread(path,[flag])
	srcImage1 = imread(imagePath, 1);
	imshow("原图", srcImage1);

	cvtColor(srcImage1, dstImage1, COLOR_RGB2HSV);
	dstImage2 = dstImage1.clone();
	/*
	Hue（色调、色相）
	Saturation（饱和度、色彩纯净度）
	Value（明度）
	*/
	//imshow("HSV", dstImage1);

	namedWindow("HSV");
	createTrackbar("H：", "HSV", &h_time, 10, hsv_trackbar);
	createTrackbar("S：", "HSV", &s_time, 10, hsv_trackbar);
	createTrackbar("V：", "HSV", &v_time, 10, hsv_trackbar);
	hsv_trackbar(1, 0);

	vector<Mat> channels;
	split(dstImage1, channels);//分离HSV
	imshow("V2GRAY", channels[0]);
	imshow("S2GRAY", channels[1]);
	imshow("H2GRAY", channels[2]);
	waitKey(0);
	return 0;
}
void hsv_trackbar(int, void*) {
	for (int i = 0; i < dstImage1.rows; i++)
		for (int j = 0; j < dstImage1.cols; j++) {
			int h = dstImage2.at<Vec3b>(i, j)[0];
			int s = dstImage2.at<Vec3b>(i, j)[1];
			int v = dstImage2.at<Vec3b>(i, j)[2];
			if(h_time!=0)
				dstImage1.at<Vec3b>(i, j)[0] = h / h_time;
			if (s_time != 0)
				dstImage1.at<Vec3b>(i, j)[1] = s / s_time;
			if (v_time != 0)
				dstImage1.at<Vec3b>(i, j)[2] = v / v_time;
		}
	imshow("HSV", dstImage1);
}


