/*
 * File Name : CLineList.h
 *
 * Created by "Jeong Ji-Ung" on 2012. 11. 30. ��.
 * Copyright 2012. All rights reserved.
 */
#pragma once
#include <opencv2\opencv.hpp>


/*
 * CLASS NAME : CLineList
 * CREATED BY "JEONG JI-UNG"
 * TODO : ���� �̹����� ��������� ���� �����ϴ� Ŭ����. ���Ḯ��Ʈ ���.
 */
class CLineList
{
public:
	CLineList();
	CLineList(float _sx, float _sy, float _ex, float _ey);
	CLineList(CvPoint _st, CvPoint _ed);
	~CLineList();

public:
	CvPoint					mStartPoint;
	CvPoint					mEndPoint;

private:
	CLineList*				mNext;
	CLineList*				mPrev;

public:
	void					destroy();
	void					setPrev(CLineList* _pPrev);
	void					setNext(CLineList* _pNext);
	
	CLineList*				getPrev();
	CLineList*				getNext();
};


/*
 * CLASS NAME : CLineListManager
 * CREATED BY "JEONG JI-UNG"
 * TODO : CLineList�� �����ϴ� �Ŵ��� Ŭ����. ���� �̹����� ���� �׸��� ����Ʈ ����, �����ϴ� ���� ���� ��.
 */
class CLineListManager
{
public:
	CLineListManager();
	~CLineListManager();

public:
	CLineList*				mpLine;

public:
	void					entry(float _sx, float _sy, float _ex, float _ey);			// ����Ʈ �߰�
	void					entry(CvPoint _st, CvPoint _ed);
	void					clear();													// ��� ����Ʈ ����
	
	CLineList*				getListHeader();											// ����Ʈ�� ����� ��ȯ.

	void					drawLine(CvArr* _pImg);										// ����Ʈ�� �߰��Ǿ� �ִ� ���� �׸�.
};