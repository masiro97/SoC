
// BlauEditor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CBlauEditorApp:
// �� Ŭ������ ������ ���ؼ��� BlauEditor.cpp�� �����Ͻʽÿ�.
//

class CBlauEditorApp : public CWinApp
{
public:
	CBlauEditorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CBlauEditorApp theApp;