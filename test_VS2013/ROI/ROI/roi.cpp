#include <opencv\cv.h>           //����ó�� ���� ���̺귯���� ����ϱ� ���� ���

#include <opencv\highgui.h>      //������ ĸ�� �ް� ������� �����ֱ� ���� ����ϴ� ���




void main()

{

	IplImage* image = 0;                           //����ü(?) �� �����ͷ� �̹����� �ް� �� �����͸� �̿��ؼ� �̹����� ó����
	image = cvLoadImage("jolly1.jpg", 1);

	IplImage* view = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3 );

	int x=140 ,
		y=23 ,
		width=115 ,
		height=142 ;

	CvRect Rec;
	Rec = cvRect(x,y,width,height);
	view = image;

	cvDrawRect(view, cvPoint(x, y), cvPoint(x + width, y + height), cvScalar(0, 255, 0));

	do{
		cvShowImage("ROI Image", view);

		if (cvWaitKey(10) >= 0)

			break;

	

	} while (1);
}

