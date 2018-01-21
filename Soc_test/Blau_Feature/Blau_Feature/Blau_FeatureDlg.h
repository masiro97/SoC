
// Blau_FeatureDlg.h : ��� ����
//

#pragma once
#include "imageSrc\BlauImage.h"

// CBlau_FeatureDlg ��ȭ ����
class CBlau_FeatureDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CBlau_FeatureDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLAU_FEATURE_DIALOG };
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
	ByteImage Image_in;
	ByteImage Image_out;
	afx_msg void OnBnClickedButtonSobel();
	afx_msg void OnBnClickedButtonLoadInput();
	afx_msg void OnBnClickedButtonSaveImage();
};
