#include "stdafx.h"
#include "BlauCam.h"

///////////////////////////////////////////////////////////////////////////////
// ī�޶� ĸ�� Ŭ���� 
///////////////////////////////////////////////////////////////////////////////
BlauCam::BlauCam() :
	m_hCam(NULL)
{

}

BlauCam::~BlauCam()
{
	if (m_hCam)
		StopCam();
}

bool BlauCam::StartCam(CWnd* wnd, int nWidth, int nHeight, BITMAPINFO& bmpInfo)
{
	// ĸ�� ������ ����� �������� ũ�� �� ��ġ ����
	m_hCam = capCreateCaptureWindow("Cam Capture", WS_CHILD | WS_VISIBLE,
		0, 0, nWidth, nHeight, wnd->m_hWnd, NULL);

	if (!capDriverConnect(m_hCam, 0))
	{
		AfxMessageBox("����� ī�޶� ã�� �� �����ϴ�.");
		return false;
	}

	//   capDlgVideoFormat(m_hCam);
	capGetVideoFormat(m_hCam, &bmpInfo, sizeof(BITMAPINFO));

	// ĸ�� ������ ũ�⸦ ��� ������ ����
	bmpInfo.bmiHeader.biWidth = nWidth;
	bmpInfo.bmiHeader.biHeight = nHeight;
	bmpInfo.bmiHeader.biSizeImage = nWidth*nHeight*bmpInfo.bmiHeader.biBitCount / 8;
	if (!capSetVideoFormat(m_hCam, &bmpInfo, sizeof(BITMAPINFO)))
	{
		// ������ �����ϸ� ���� ������ �ǵ���
		capGetVideoFormat(m_hCam, &bmpInfo, sizeof(BITMAPINFO));
	}

	// ĸ�� ������ 24��Ʈ RGB�� �� �� �ֵ��� ����
	bmpInfo.bmiHeader.biBitCount = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	if (!capSetVideoFormat(m_hCam, &bmpInfo, sizeof(BITMAPINFO)))
	{
		// ������ �����ϸ� ���� ������ �ǵ���
		capGetVideoFormat(m_hCam, &bmpInfo, sizeof(BITMAPINFO));
	}

	capOverlay(m_hCam, TRUE);
	capPreviewRate(m_hCam, 30);
	capPreview(m_hCam, TRUE);

	return true;
}

void BlauCam::StopCam()
{
	capCaptureAbort(m_hCam);
	capDriverDisconnect(m_hCam);
	m_hCam = NULL;
}

BOOL BlauCam::SetCallBackOnFrame(LRESULT(*fpProc)(HWND, LPVIDEOHDR))
{
	return capSetCallbackOnFrame(m_hCam, fpProc);
}