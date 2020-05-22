#include <opencv2/opencv.hpp>
using namespace cv;
Mat srcImage1,dstImage1, dstImage2;
String imagePath = "C:/Users/admin/Pictures/1.1.png";
int main()
{
	//imaread(path,[flag])
	srcImage1 = imread(imagePath, 1);
	imshow("原图", srcImage1);


	//均值滤波 （输入图像，目标图像，内核的大小，锚点）

	blur(srcImage1, dstImage1, Size(5, 5), Point(-1, -1));
	imshow("均值滤波(5,5)", dstImage1);

	blur(srcImage1, dstImage1, Size(11, 11), Point(-1, -1));
	imshow("均值滤波(11, 11)", dstImage1);

	blur(srcImage1, dstImage1, Size(17, 17), Point(-1, -1));
	imshow("均值滤波(17, 17)", dstImage1);


	//中值滤波 （输入图像，目标图像，正方形滤波模板尺寸大小[大于1的奇数]）
	medianBlur(srcImage1, dstImage2, 5);
	imshow("中值滤波5", dstImage2);

	medianBlur(srcImage1, dstImage2, 11);
	imshow("中值滤波11", dstImage2);

	medianBlur(srcImage1, dstImage2, 17);
	imshow("中值滤波17", dstImage2);

	waitKey(0);
	return 0;
}


