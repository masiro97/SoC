
// BlauFeatureExtractor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CBlauFeatureExtractorApp:
// �� Ŭ������ ������ ���ؼ��� BlauFeatureExtractor.cpp�� �����Ͻʽÿ�.
//

class CBlauFeatureExtractorApp : public CWinApp
{
public:
	CBlauFeatureExtractorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CBlauFeatureExtractorApp theApp;