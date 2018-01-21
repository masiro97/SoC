#pragma once

#include "BlauImage.h"

// CImageView ���Դϴ�.

class CImageView : public CView
{
	DECLARE_DYNCREATE(CImageView)

public:
	CImageView();           // ���� ����� ������, ImageFrameWnd�� ������������ ���� public
	virtual ~CImageView();
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	void CImageView::SetImage(const ByteImage& input);
	BOOL CImageView::CreateEx(CWnd *pWnd);


	ByteImage m_image;

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};

