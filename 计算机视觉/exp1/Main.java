package exp1;

import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Size;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;

public class Main {
	static {
		System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
	}
	public static void main(String[] args) {
		String imagePath = ".\\images\\test.jpg";
		// imaread(path,[flag])
		Mat srcImage1 = Imgcodecs.imread(imagePath, 1);
		// 以灰度模式读入
		Mat srcImage2 = Imgcodecs.imread(imagePath, 0);
		Mat dstImage1 = srcImage1.clone();
		Mat dstImage2 =srcImage1.clone();
		Mat dstImage3 = srcImage1.clone();

		HighGui.imshow("原图", srcImage1);
		HighGui.imshow("灰图", srcImage2);

		// 直方图均衡化
		Imgproc.equalizeHist(srcImage2, dstImage1);
		HighGui.imshow("直方图均衡", dstImage1);

		// 平滑滤波分为线性和非线性
		// 线性滤波器：均值滤波
		/*
		 * InputArray src: 输入图像，可以是Mat类型，图像深度是CV_8U、CV_16U、CV_16S、CV_32F以及CV_64F其中的某一个。
		 * OutputArray dst: 输出图像，深度和类型与输入图像一致 Size ksize: 滤波模板kernel的尺寸，一般使用Size(w,
		 * h)来指定，如Size(3,3) Point anchor=Point(-1, -1):
		 * 字面意思是锚点，也就是处理的像素位于kernel的什么位置，默认值为(-1, -1)即位于kernel中心点，如果没有特殊需要则不需要更改 int
		 * borderType=BORDER_DEFAULT: 用于推断图像外部像素的某种边界模式，有默认值BORDER_DEFAULT
		 */
		Imgproc.blur(srcImage1, dstImage2, new Size(5, 5), new Point(-1, -1));

		HighGui.imshow("均值滤波", dstImage2);

		// 非线性滤波器：中值滤波
		/*
		 * InputArray src:
		 * 输入图像，图像为1、3、4通道的图像，当模板尺寸为3或5时，图像深度只能为CV_8U、CV_16U、CV_32F中的一个，如而对于较大孔径尺寸的图片，
		 * 图像深度只能是CV_8U。 OutputArray dst:
		 * 输出图像，尺寸和类型与输入图像一致，可以使用Mat::Clone以原图像为模板来初始化输出图像dst int ksize:
		 * 滤波模板的尺寸大小，必须是大于1的奇数
		 */
		Imgproc.medianBlur(srcImage1, dstImage3, 11);
		HighGui.imshow("中值滤波", dstImage3);

		HighGui.waitKey(0);

	}

}
