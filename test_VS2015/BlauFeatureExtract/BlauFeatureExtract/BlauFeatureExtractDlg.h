
// BlauFeatureExtractDlg.h : ��� ����
//

#pragma once
#include "imageSrc\BlauImage.h"

// CBlauFeatureExtractDlg ��ȭ ����
class CBlauFeatureExtractDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CBlauFeatureExtractDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLAUFEATUREEXTRACT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLoadImage();
	afx_msg void OnBnClickedButtonSaveImage();
	afx_msg void OnBnClickedButtonSobel();
	afx_msg void OnBnClickedButtonCanny();
public:
	ByteImage Image_in;
	ByteImage Image_out;
	afx_msg void OnBnClickedButtonHough();
	afx_msg void OnBnClickedButtonHarris();
};
