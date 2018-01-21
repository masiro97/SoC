// ImageFrameWnd.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageFrameWnd.h"

static int nFrameWndCount = 0;

// CImageFrameWnd

IMPLEMENT_DYNCREATE(CImageFrameWnd, CFrameWnd)


CImageFrameWnd::CImageFrameWnd()
{
}

CImageFrameWnd::CImageFrameWnd(const ByteImage &image, const char *name)
{
	m_view.SetImage(image);

	CString wndName;
	if (name)
		wndName = name;
	else
		wndName.Format("Image view %d",nFrameWndCount);

	CRect rect(30 * nFrameWndCount, 30 * nFrameWndCount,
		image.GetWidth() + 30 * nFrameWndCount, image.GetHeight() + 30 * nFrameWndCount);
	Create(NULL, wndName, WS_OVERLAPPEDWINDOW, rect);

	nFrameWndCount++;

	ShowWindow(SW_SHOW);
}

CImageFrameWnd::~CImageFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CImageFrameWnd, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CImageFrameWnd �޽��� ó�����Դϴ�.


int CImageFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_view.CreateEx(this);
	return 0;
}

#include "ImageFrameWndManager.h"
extern CImageFrameWndManager gImageFrameWndManager;
void CImageFrameWnd::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	gImageFrameWndManager.Delete(this);
	//	CFrameWnd::PostNcDestroy();
}
