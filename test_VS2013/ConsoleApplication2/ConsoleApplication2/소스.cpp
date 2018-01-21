#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2\imgproc\imgproc.hpp>
#include "FAST.h"

int main()
{
	CvCapture* capture = cvCaptureFromCAM(0); //���� �νĵ� ��ķ ã��
	//cvNamedWindow("BlauCV_Test", 0); // ȭ���� �׷��� �����츦 ����
	//cvResizeWindow("BlauCV_Test", 640, 480); // ����� �����Ѵ�.

	IplImage* CamImg = 0;
	IplImage* IGray = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 1);
	IplImage* ImgOut = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);

	while (1) {
		cvGrabFrame(capture);
		CamImg = cvRetrieveFrame(capture); // ���� �νĵ� ����� �޾ƿ���image�� �ִ´�.

		cvCvtColor(CamImg, IGray, CV_RGB2GRAY);

		FAST(IGray, ImgOut);

		cvShowImage("CAM", CamImg); // image�� �ִ� ����� �����쿡 �׸���.
		cvShowImage("ImgOUt", ImgOut); // 
		if (cvWaitKey(10) >= 0) // �̰� ���� �߿��ѵ� �� WaitKey �Լ��� ������ �ƹ� �͵� �ȱ׸���.
			break;
	}

	cvReleaseCapture(&capture); // �Ҵ�޾Ҵ� ��ķ�� �����ϰ�,
	cvDestroyWindow("OpenCvCamtest"); // �����츦 �����Ѵ�. 

	return 0;
}