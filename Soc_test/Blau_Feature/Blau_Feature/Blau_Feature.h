
// Blau_Feature.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CBlau_FeatureApp:
// �� Ŭ������ ������ ���ؼ��� Blau_Feature.cpp�� �����Ͻʽÿ�.
//

class CBlau_FeatureApp : public CWinApp
{
public:
	CBlau_FeatureApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CBlau_FeatureApp theApp;