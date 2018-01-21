#pragma once

#include "ImageView.h"
#include "BlauImage.h"
#include "BlauFeatureExtractor.h"
// CImageFrameWnd �������Դϴ�.

class CImageFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CImageFrameWnd)
public:
	CImageFrameWnd::CImageFrameWnd();
	CImageFrameWnd::CImageFrameWnd(const ByteImage &image, const char *name);
		// ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CImageFrameWnd();
	CImageView& GetImageView() { return m_view; };

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void PostNcDestroy();

	CImageView	m_view;
};


