#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void DetectFace(Mat);
CascadeClassifier faceCascade;
int main(){
	faceCascade.load("D:/Program Files/OpenCV/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");
	VideoCapture cap(0);
	if (!cap.isOpened()){
		cout << "打开摄像头失败！" <<endl;
		return -1;
	}

	Mat frame,grayFrame;
	//Mat edges;

	bool stop = false;
	while (!stop){
		cap >> frame;

		//cvtColor(frame, edges, COLOR_BGR2GRAY);
		//GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		//Canny(edges, edges, 0, 30, 3);
		//imshow("人脸检测", frame);


		DetectFace(frame);
		if (waitKey(30) >= 0)
			stop = true;
	}
	return 0;
}
void DetectFace(Mat img) {
	vector<Rect> faces;
	Mat imgGray;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);//直方图均匀化

	faceCascade.detectMultiScale(imgGray, faces, 1.2, 5, 0, Size(30, 30));

	if (faces.size() > 0) {
		for (size_t i = 0; i < faces.size(); i++) {
			//putText(img, "kailang", Point(faces[i].x, faces[i].y - 10), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0));
			rectangle(img, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 255, 0), 1, 8);
		}
	}
	namedWindow("Face Detection", WINDOW_AUTOSIZE);
	imshow("Face Detection", img);
}


