#pragma once

#include <vector>
#include "ImageFrameWnd.h"
#include "ImageSrc\/BlauImage.h"

class CImageFrameWndManager
{
public:
	CImageFrameWndManager(void);
	~CImageFrameWndManager(void);

	void Add(CImageFrameWnd* pImageWnd);
	CImageFrameWnd* FindWnd(const char* name);
	void Delete(CImageFrameWnd* pImageWnd);
	void CloseAll();

protected:
	std::vector <CImageFrameWnd* > m_vpImageWnd;
};

void ShowImage(const ByteImage& input, const char *name = NULL);
void CloseImage(const char* name);
void CloseAllImages();
