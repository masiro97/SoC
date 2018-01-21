#pragma once
#include "BlauImage.h"
#include <vfw.h>
#pragma comment (lib,"vfw32.lib")

// ī�޶� ĸ�� Ŭ����
class BlauCam
{
public:
	BlauCam();
	virtual ~BlauCam();

	bool StartCam(CWnd* wnd, int nWidth, int nHeight, BITMAPINFO& bmpInfo);
	void StopCam();
	BOOL SetCallBackOnFrame(LRESULT(*fpProc)(HWND, LPVIDEOHDR));

protected:
	HWND      m_hCam;
};