package exp2;

import java.util.ArrayList;
import java.util.List;

import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.MatOfPoint;
import org.opencv.core.Rect;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.highgui.HighGui;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;

public class LicensePlatesDetection {
	static {
		System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
	}
	final static String imagePath = ".\\images\\car2.jpg";

	public static void main(String[] args) {

		// 读入原图
		Mat srcImage = Imgcodecs.imread(imagePath);
		HighGui.imshow("原图", srcImage);
		// 高斯模糊
		Mat gausImage = srcImage.clone();
		Imgproc.GaussianBlur(srcImage, gausImage, new Size(3, 3), 5, 5);
		HighGui.imshow("高斯模糊", gausImage);

		// 灰度化
		Mat grayImage = srcImage.clone();
		Imgproc.cvtColor(gausImage, grayImage, Imgproc.COLOR_BGR2GRAY);
		HighGui.imshow("灰图", grayImage);

		// Sobel算子
		Mat sobelImage = srcImage.clone();
		Imgproc.Sobel(grayImage, sobelImage, 0, 1, 0);
		HighGui.imshow("Sobel算子", sobelImage);

		// 二值化
		Mat binaryImage = srcImage.clone();
		Imgproc.threshold(sobelImage, binaryImage, 90, 255, Imgproc.THRESH_BINARY);
		HighGui.imshow("二值化", binaryImage);

		// 开运算(先腐蚀，再膨胀)
//		Mat morphologyExImage=srcImage.clone();
//		Imgproc.morphologyEx(binaryImage, morphologyExImage, Imgproc.MORPH_CLOSE, Imgproc.getStructuringElement( Imgproc.MORPH_RECT,new Size(1,1)));
//		HighGui.imshow("开运算", morphologyExImage);

		Mat erodeImage = srcImage.clone();
		Imgproc.erode(binaryImage, erodeImage, Imgproc.getStructuringElement(Imgproc.MORPH_RECT, new Size(3, 3)));
		HighGui.imshow("腐蚀", erodeImage);

		Mat dilateImage = srcImage.clone();
		Imgproc.dilate(erodeImage, dilateImage, Imgproc.getStructuringElement(Imgproc.MORPH_RECT, new Size(20, 20)));
		HighGui.imshow("膨胀", dilateImage);

		// 取轮廓
		Mat flagImage = srcImage.clone();
		List<MatOfPoint> contours = new ArrayList<>();
		Mat hierarchy = new Mat();
		Imgproc.findContours(dilateImage, contours, hierarchy, Imgproc.RETR_EXTERNAL, Imgproc.CHAIN_APPROX_NONE);
		System.out.println("轮廓数量：" + contours.size());
		Imgproc.drawContours(flagImage, contours,-1, new Scalar(0,255,0));
		HighGui.imshow("轮廓", flagImage);

		//识别车牌，仅对提供的两个车牌识别有效!!!
		Mat licenseImage = srcImage.clone();
		MatOfPoint t=contours.get(0);
		for (int i = 1; i < contours.size(); i++) {
			//筛选面积最大的
			if (Imgproc.contourArea(contours.get(i)) > Imgproc.contourArea(t)) {
				t=contours.get(i);
			}
//			if (Imgproc.contourArea(contours.get(i)) > 1000) {
//				Rect r = Imgproc.boundingRect(contours.get(i));
//				if(r.width>2*r.height)
//				Imgproc.rectangle(licenseImage, r, new Scalar(0, 255, 0));
//				// System.out.println(r.height+" "+r.width);
//			}
		}
		
//		MatOfPoint t = new MatOfPoint();
//		for(int i=0;i<contours.size();i++) {
//			if(Imgproc.contourArea(contours.get(i))>5000) {
//				MatOfPoint2f point2f=new MatOfPoint2f(contours.get(i).toArray());
//				RotatedRect rect = Imgproc.minAreaRect(point2f);
//				Imgproc.boxPoints(rect, t);
//				contours.set(i, t);
//			}
//		}

		
		Rect r = Imgproc.boundingRect(t);
		Imgproc.rectangle(licenseImage, r, new Scalar(0, 255, 0));
		HighGui.imshow("车牌标记", licenseImage);

		HighGui.waitKey(0);
	}
}
