#pragma once


// CCannyThrsDlg ��ȭ �����Դϴ�.

class CCannyThrsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCannyThrsDlg)

public:
	CCannyThrsDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCannyThrsDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CANNY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_nThresholdHi;
	int m_nThresholdLo;
};
