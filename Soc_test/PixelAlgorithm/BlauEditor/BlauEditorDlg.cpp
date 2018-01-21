
// BlauEditorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "BlauEditor.h"
#include "BlauEditorDlg.h"
#include "afxdialogex.h"
#include "ImageFrameWnd.h"
#include "ImageFrameWndManager.h"
#include "LoadImageFromFileDialog.h"
#include "MyImageFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


ByteImage ImgIn1;
ByteImage ImgIn2;
ByteImage ImgOut;

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBlauEditorDlg ��ȭ ����



CBlauEditorDlg::CBlauEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BLAUEDITOR_DIALOG, pParent)
	
	, m_bImgOperand(FALSE)
	, m_nOperator(0)
	, m_dOperandVal(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlauEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_IMAGE, m_bImgOperand);
	DDX_Radio(pDX, IDC_RADIO_PLUS, m_nOperator);
	DDX_Text(pDX, IDC_EDIT_CONST_VAL, m_dOperandVal);
}

BEGIN_MESSAGE_MAP(CBlauEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD1, &CBlauEditorDlg::OnBnClickedButtonLoad1)
	ON_BN_CLICKED(IDC_BUTTON_LOAD2, &CBlauEditorDlg::OnBnClickedButtonLoad2)
	ON_BN_CLICKED(IDC_RADIO_IMAGE, &CBlauEditorDlg::OnBnClickedRadioImage)
	ON_BN_CLICKED(IDC_RADIO_CONST, &CBlauEditorDlg::OnBnClickedRadioConst)
END_MESSAGE_MAP()


// CBlauEditorDlg �޽��� ó����

BOOL CBlauEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CBlauEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CBlauEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CBlauEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBlauEditorDlg::OnBnClickedButtonLoad1()
{
	ImgIn1 = LoadImageFromDialog();
	if (!ImgIn1.IsEmpty()) ShowImage(ImgIn1, "�Է� ����1");
}


void CBlauEditorDlg::OnBnClickedButtonLoad2()
{
	ImgIn2 = LoadImageFromDialog();
	if (!ImgIn2.IsEmpty()) ShowImage(ImgIn2, "�Է� ����2");
}


void CBlauEditorDlg::OnBnClickedRadioImage()
{
	GetDlgItem(IDC_BUTTON_LOAD2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_CONST_VAL)->EnableWindow(FALSE);

	if (!ImgIn2.IsEmpty()) ShowImage(ImgIn2, "�Է� ����2");
}


void CBlauEditorDlg::OnBnClickedRadioConst()
{
	GetDlgItem(IDC_BUTTON_LOAD2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CONST_VAL)->EnableWindow(TRUE);
	CloseImage("�Է� ����2");
}


bool CBlauEditorDlg::_ImageOpImage()
{
	int nWidth = ImgIn1.GetWidth();
	int nHeight = ImgIn1.GetHeight();
	int nCh = ImgIn1.GetChannel();

	if (m_nOperator != 6 &&
		(nWidth != ImgIn2.GetWidth() ||
			nHeight != ImgIn2.GetHeight() ||
			nCh != ImgIn2.GetChannel()))
	{
		AfxMessageBox("�Է� ������ �԰��� �ٸ��ϴ�.");
		return false;
	}

	switch (m_nOperator)
	{
	case 0: // +
		ImgOut = ImgIn1 + ImgIn2;
		break;
	case 1: // -
		ImgOut = ImgIn1 - ImgIn2;
		break;
	case 2: // *
		ImgOut = ImgIn1 * ImgIn2;
		break;
	case 3: // /
		ImgOut = ImgIn1 / ImgIn2;
		break;
	case 4: // &
		ImgOut = ImgIn1 & ImgIn2;
		break;
	case 5: // |
		ImgOut = ImgIn1 | ImgIn2;
		break;
	case 6: // ~
		ImgOut = ~ImgIn1;
		break;
	case 7: // ^
		ImgOut = ImgIn1 ^ ImgIn2;
		break;
	default:
		break;
	}

	return true;
}

bool CBlauEditorDlg::_ImageOpConst()
{
	switch (m_nOperator)
	{
	case 0: // +
		ImgOut = ImgIn1 + m_dOperandVal;
		break;
	case 1: // -
		ImgOut = ImgIn1 - m_dOperandVal;
		break;
	case 2: // *
		ImgOut = ImgIn1 * m_dOperandVal;
		break;
	case 3: // /
		ImgOut = ImgIn1 / m_dOperandVal;
		break;
	case 4: // &
		ImgOut = ImgIn1 & m_dOperandVal;
		break;
	case 5: // |
		ImgOut = ImgIn1 | m_dOperandVal;
		break;
	case 6: // ~
		ImgOut = ~ImgIn1;
		break;
	case 7: // ^
		ImgOut = ImgIn1 ^ m_dOperandVal;
		break;
	default:
		break;
	}

	return true;
}
