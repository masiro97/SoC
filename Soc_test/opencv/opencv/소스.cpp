#include <opencv/cv.h>         // ���� ó���� ���� header. ��� ���� opencv/ �� ������.

#include <opencv/highgui.h>  // ī�޶�� ������ �Է¹ްų� �̹����� �о���̰� ȭ�鿡 �����ֱ� ���� header 



void main()

{

	IplImage* image = 0;  //�̹��� ����üIplImage 

	CvCapture* capture = cvCaptureFromCAM(0);  // 0 ��° ����� ī�޶�κ��� ��Ʈ�� ���

	cvNamedWindow("T9-camera", 0);            // T9-camera ��� �̸��� �����츦 ����, 0 �� ������ �����츦 ���� 

	cvResizeWindow("T9-camera", 320, 240); // T9-camera ��� �̸��� ������ ũ�⸦ ���� width = 320, height = 240 



	while (1) {  //ī�޶�κ��� �� ������ �޾ƿ����� while ���ѷ������� 

		cvGrabFrame(capture);  //ī�޶�κ��� �� ������ ��� 

		image = cvRetrieveFrame(capture);    // ���� ���������κ��� IplImage �� ������ ���� �޾� image �� �ֱ� 

		cvShowImage("T9-camera", image);   // "T9-camera" �����쿡 image �� �����ֱ� 

		if (cvWaitKey(10) >= 0) //esc Ű�� �������� ���� 

			break;

	}



	cvReleaseCapture(&capture);  //capture�� release�Ͽ� ī�޶���� ���� ���� 

	cvDestroyWindow("T9-camera");  //������ �Ҹ� 

}


