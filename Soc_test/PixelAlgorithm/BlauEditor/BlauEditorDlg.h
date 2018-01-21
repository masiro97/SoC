
// BlauEditorDlg.h : ��� ����
//

#pragma once

// CBlauEditorDlg ��ȭ ����
class CBlauEditorDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CBlauEditorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLAUEDITOR_DIALOG };
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
	BOOL m_bImgOperand;
	int m_nOperator;
	double m_dOperandVal;
	afx_msg void OnBnClickedButtonLoad1();
	afx_msg void OnBnClickedButtonLoad2();
	afx_msg void OnBnClickedRadioImage();
	afx_msg void OnBnClickedRadioConst();
	bool CBlauEditorDlg::_ImageOpImage();
	bool CBlauEditorDlg::_ImageOpConst();
};
