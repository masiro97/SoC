
// BlauFeatureExtract.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

	// �� ��ȣ�Դϴ�.
#include "resource.h"
// CBlauFeatureExtractApp:
// �� Ŭ������ ������ ���ؼ��� BlauFeatureExtract.cpp�� �����Ͻʽÿ�.
//

class CBlauFeatureExtractApp : public CWinApp
{
public:
	CBlauFeatureExtractApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CBlauFeatureExtractApp theApp;