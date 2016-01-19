/*
* File Name : main.cpp
*
* Created by "Jeong Ji-Ung" on 2012. 11. 30. ��.
* Copyright 2012. All rights reserved.
*/
#include "CMetamorphosis.h"

bool						gbEnable;								// �̹��� ���� ������ �����ϸ� true, �ƴϸ� false
float						gAlpha;									// �̹����� ���� ������ ���������� ǥ���ϱ� ���� ����ġ ��. (1 - alpha)

IplImage					*gSrc_A, *gSrc_B;						// ���� A, ���� B
IplImage					*gImage_A, *gImage_B;					// �̹���A, �̹���B
IplImage					*gMorp_A, *gMorp_B;						// ������ �̹���.
IplImage*					gDst;									// ������ A �� ������ B�� �պ�.

CvSize						gSize_A, gSize_B;						// ���� �̹����� ������

CLineListManager			gLine_A, gLine_B;

CvPoint						gSt, gEd;								// ���콺 ���� ��ǥ, ���콺 �� ��ǥ


void onMouse_A(int event, int x, int y, int flags, void* param)
{
	// TODO: �̹��� A�� ���� �׸��� ���� ��ǥ�� ����.
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		gSt = cvPoint(x, y);
		gEd = cvPoint(x, y);
	}
	else if (event == CV_EVENT_MOUSEMOVE && flags == CV_EVENT_FLAG_LBUTTON)
	{
		gEd = cvPoint(x, y);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		gEd = cvPoint(x, y);
		gLine_A.entry(gSt, gEd);				// ����Ʈ�� ������ �߰�

		// ���콺 ��ǥ �ʱ�ȭ
		gSt = cvPoint(-10, -10);
		gEd = cvPoint(-10, -10);
	}

	// gSrc_A���� ���� �̹��� ����.
	cvCopy(gSrc_A, gImage_A);

	// ���� �׷��� ���� �׸�.
	cvLine(gImage_A, gSt, gEd, cvScalar(255, 255, 255));
	cvCircle(gImage_A, gSt, 3, cvScalar(0, 0, 255), -1);
	cvCircle(gImage_A, gEd, 3, cvScalar(0, 0, 255), -1);

	gLine_A.drawLine(gImage_A);

	cvShowImage("A", gImage_A);
}


void onMouse_B(int event, int x, int y, int flags, void* param)
{
	// TODO: �̹��� B�� ���� �׸��� ���� ��ǥ�� ����.
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		gSt = cvPoint(x, y);
		gEd = cvPoint(x, y);
	}
	else if (event == CV_EVENT_MOUSEMOVE && flags == CV_EVENT_FLAG_LBUTTON)
	{
		gEd = cvPoint(x, y);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		gEd = cvPoint(x, y);
		gLine_B.entry(gSt, gEd);				// ����Ʈ�� ������ �߰�

		// ���콺 ��ǥ �ʱ�ȭ
		gSt = cvPoint(-10, -10);
		gEd = cvPoint(-10, -10);
	}

	// gSrc_B���� ���� �̹��� ����.
	cvCopy(gSrc_B, gImage_B);

	// ���� �׷��� ���� �׸�.
	cvLine(gImage_B, gSt, gEd, cvScalar(255, 255, 255));
	cvCircle(gImage_B, gSt, 3, cvScalar(0, 0, 255), -1);
	cvCircle(gImage_B, gEd, 3, cvScalar(0, 0, 255), -1);

	gLine_B.drawLine(gImage_B);

	cvShowImage("B", gImage_B);
}


void metamorphosis()
{
	if (gLine_A.getListHeader() == NULL || gLine_B.getListHeader() == NULL)
		return;

	// TODO: �̰����� ������ �Ͼ.
	morphing(gImage_A->width, gImage_A->height, gLine_A.getListHeader(), gLine_B.getListHeader(), gSrc_A, gMorp_A, gAlpha);
	//gLine_B.drawLine(gMorp_A);
	morphing(gImage_B->width, gImage_B->height, gLine_B.getListHeader(), gLine_A.getListHeader(), gSrc_B, gMorp_B, (1 - gAlpha));
	//gLine_A.drawLine(gMorp_B);

	synthesis(gMorp_A, gMorp_B, gDst, gAlpha);
}


void initImage(char* _pInputA, char* _pInputB)
{
	// �̹��� �ε�.
	gSrc_A = cvLoadImage(_pInputA);
	gSrc_B = cvLoadImage(_pInputB);

	// �ε��� �̹����� �������� �ʰų�, �߸� �ε�Ǿ��� ��� ���α׷� ����.
	if (gSrc_A == NULL || gSrc_B == NULL)
		return;

	// ���� �̹��� A�� B�� ����� ����.
	gSize_A = cvGetSize(gSrc_A);
	gSize_B = cvGetSize(gSrc_B);

	// ȭ�鿡 ���� �� �̹��� A�� B�� ���� A�� B�� ������� ����.
	gImage_A = cvCreateImage(gSize_A, 8, 3);
	gImage_B = cvCreateImage(gSize_B, 8, 3);

	// �����Ǵ� ������ ������ IplImage�� ��ü�� ���� A�� B�� ������� ����.
	gMorp_A = cvCreateImage(gSize_A, 8, 3);
	gMorp_B = cvCreateImage(gSize_B, 8, 3);

	// A�� B�� ���� ������ �ռ��Ǿ� ������ ����� �����ִ� �̹���. ����A�� ������� �ʱ�ȭ.
	gDst = cvCreateImage(gSize_A, 8, 3);

	// ó�� �����Ǵ� ������ ���������� �ʱ�ȭ.
	cvSet(gMorp_A, cvScalar(0, 0, 0));
	cvSet(gMorp_B, cvScalar(0, 0, 0));
	cvSet(gDst, cvScalar(0, 0, 0));

	// ����A, B�� ȭ�鿡 ������ �̹��� A, B�� ����.
	cvCopy(gSrc_A, gImage_A);
	cvCopy(gSrc_B, gImage_B);
}


void release()
{
	gLine_A.clear();
	gLine_B.clear();

	cvReleaseImage(&gSrc_A);
	cvReleaseImage(&gSrc_B);
	cvReleaseImage(&gImage_A);
	cvReleaseImage(&gImage_B);
	cvReleaseImage(&gDst);
}


void main()
{
	char					inputA[128];
	char					inputB[128];

	printf("�̹��� A ��� �Է� : ");
	scanf("%s", &inputA);
	printf("�̹��� B ��� �Է� : ");
	scanf("%s", &inputB);

	initImage(inputA, inputB);

	gbEnable = false;
	gAlpha = 0;

	CvVideoWriter*			writer = cvCreateVideoWriter("metamorphosis.avi", 0, 10, cvSize(gDst->width, gDst->height), 1);

	gSt = cvPoint(-10, -10);
	gEd = cvPoint(-10, -10);

	while (true)
	{
		int					key;

		cvShowImage("A", gImage_A);
		cvShowImage("B", gImage_B);

		cvSetMouseCallback("A", onMouse_A);
		cvSetMouseCallback("B", onMouse_B);

		if (gbEnable == false)
		{
			key = cvWaitKey();

			if (key == 32)
				gbEnable = true;
			else if (key == 96)
			{
				printf("�̹��� A ��� �Է� : ");
				scanf("%s", &inputA);
				printf("�̹��� B ��� �Է� : ");
				scanf("%s", &inputB);

				release();
				initImage(inputA, inputB);
			}
			else
				break;
		}
		else if (gbEnable == true)
		{
			metamorphosis();

			cvShowImage("Morp A", gMorp_A);
			cvShowImage("Morp B", gMorp_B);
			cvShowImage("dst", gDst);

			cvWriteFrame(writer, gDst);

			cvWaitKey(10);

			gAlpha += 0.05;
			if (gAlpha > 1.0)
			{
				gbEnable = false;
				gAlpha = 0;
			}
		}
	}

	release();

	cvReleaseVideoWriter(&writer);
}