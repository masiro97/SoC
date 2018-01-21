// test_cv.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <opencv\cv.h>           //����ó�� ���� ���̺귯���� ����ϱ� ���� ���
#include <opencv\highgui.h>      //������ ĸ�� �ް� ������� �����ֱ� ���� ����ϴ� ���

	void main()

	{

		IplImage* image = 0;                           //����ü(?) �� �����ͷ� �̹����� �ް� �� �����͸� �̿��ؼ� �̹����� ó����

		CvCapture* capture = cvCaptureFromCAM(0);              //ī�޶�κ��� ��Ʈ��(?)�� ����. (0�� ī�޶󿬰�?)

		cvNamedWindow("rabbit", 0);                 //������ ����. ���ڴ� �������� ũ�⸦ ��Ÿ�� 0:������ ������, 1:�ڵ� ���� ������

		cvResizeWindow("rabbit", 320, 240);        //�������� ũ�⸦ ������ �� ����



		while (1) {                                       //ī�޶�� ���� �� �������� �޾ƿ��� ���ؼ� ���ѷ����� ������.

			cvGrabFrame(capture);                  //�Էµ� ������ �� �������� ���,

			image = cvRetrieveFrame(capture);    //���� ���������κ��� �̹����� ����


			cvShowImage("rabbit", image);        //������ �̹����� �����쿡 ������


			if (cvWaitKey(10) >= 0)

				break;

		}


		cvReleaseCapture(&capture);             //ī�޶���� ���� ����

		cvDestroyWindow("rabbit");               //������ ����

	}

	




