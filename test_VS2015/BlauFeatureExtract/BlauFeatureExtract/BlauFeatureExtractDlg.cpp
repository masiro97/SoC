
// BlauFeatureExtractDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "imageSrc\BlauFeatureExtract.h"
#include "afxdialogex.h"
#include "imageSrc\Features.h"
#include "imageSrc\MyImageFunc.h"
#include "imageSrc\ImageFrameWndManager.h"
#include "imageSrc\LoadImageFromFileDialog.h"
#include <math.h>
#include "BlauFeatureExtractDlg.h"
#include "imageSrc\CannyThrsDlg.h"
#include "imageSrc\HoughParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CBlauFeatureExtractDlg ��ȭ ����



CBlauFeatureExtractDlg::CBlauFeatureExtractDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BLAUFEATUREEXTRACT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlauFeatureExtractDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBlauFeatureExtractDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD_IMAGE, &CBlauFeatureExtractDlg::OnBnClickedButtonLoadImage)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_IMAGE, &CBlauFeatureExtractDlg::OnBnClickedButtonSaveImage)
	ON_BN_CLICKED(IDC_BUTTON_SOBEL, &CBlauFeatureExtractDlg::OnBnClickedButtonSobel)
	ON_BN_CLICKED(IDC_BUTTON_CANNY, &CBlauFeatureExtractDlg::OnBnClickedButtonCanny)
	ON_BN_CLICKED(IDC_BUTTON_HOUGH, &CBlauFeatureExtractDlg::OnBnClickedButtonHough)
	ON_BN_CLICKED(IDC_BUTTON_HARRIS, &CBlauFeatureExtractDlg::OnBnClickedButtonHarris)
END_MESSAGE_MAP()


// CBlauFeatureExtractDlg �޽��� ó����

BOOL CBlauFeatureExtractDlg::OnInitDialog()
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

void CBlauFeatureExtractDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBlauFeatureExtractDlg::OnPaint()
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
HCURSOR CBlauFeatureExtractDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBlauFeatureExtractDlg::OnBnClickedButtonLoadImage()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Image_in = LoadImageFromDialog();
	ShowImage(Image_in, "�Է� ����");
}


void CBlauFeatureExtractDlg::OnBnClickedButtonSaveImage()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Image_out.SaveImage("Result.bmp");
}


void CBlauFeatureExtractDlg::OnBnClickedButtonSobel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (Image_in.GetChannel() == 3)
		SobelEdge(RGB2Gray(Image_in), Image_out);
	else
		SobelEdge(Image_in, Image_out);
	ShowImage(Image_out, "Sobel �����");
}


void CBlauFeatureExtractDlg::OnBnClickedButtonCanny()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CCannyThrsDlg cannyDlg;
	if (cannyDlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		CannyEdge(RGB2Gray(Image_in), Image_out, cannyDlg.m_nThresholdHi, cannyDlg.m_nThresholdLo);
		ShowImage(Image_out, "ĳ�� ��輱 �����");
	}
}


void CBlauFeatureExtractDlg::OnBnClickedButtonHough()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ByteImage imageEdge;
	CHoughParam houghDlg;
	if (houghDlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		if (houghDlg.m_nEdgeMethod == 0)
		{
			if (Image_in.GetChannel() == 3)
				SobelEdge(RGB2Gray(Image_in), imageEdge);
			else
				SobelEdge(Image_in, imageEdge);
		}
		else
		{
			if (Image_in.GetChannel() == 3)
				CannyEdge(RGB2Gray(Image_in), imageEdge, 60, 30);
			else
				CannyEdge(Image_in, imageEdge, 60, 30);
		}
		//		ShowImage(imageEdge, "��輱 ����");

		double arrRho[100];
		double arrTheta[100];
		int nLine = HoughLines(imageEdge, houghDlg.m_nTNum, houghDlg.m_NTVal, houghDlg.m_dResTheta, 100, arrRho, arrTheta);

		Image_out = Image_in;
		// ���� �׸���
		for (int i = 0; i<nLine; i++)
		{
			if (arrTheta[i] == 90) // ������
			{
				DrawLine(Image_out, arrRho[i], 0, arrRho[i], Image_out.GetHeight() - 1, 255, 0, 0);
			}
			else
			{
				int x1 = 0;
				int y1 = (int)(arrRho[i] / cos(arrTheta[i] * M_PI / 180) + 0.5);
				int x2 = Image_out.GetWidth() - 1;
				int y2 = (int)((arrRho[i] - x2*sin(arrTheta[i] * M_PI / 180)) / cos(arrTheta[i] * M_PI / 180) + 0.5);
				DrawLine(Image_out, x1, y1, x2, y2, 255, 0, 0);
			}
		}
		ShowImage(Image_out, "���� ���� ���");
	}
}


void CBlauFeatureExtractDlg::OnBnClickedButtonHarris()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	double cornerX[1000]; // �ִ� �ڳ��� ��: 1000
	double cornerY[1000];

	int numCorner;
	if (Image_in.GetChannel() == 3)
		numCorner = HarrisCorner(RGB2Gray(Image_in), 1e8, 0.04, 1000, cornerX, cornerY);
	else
		numCorner = HarrisCorner(Image_in, 1e9, 0.04, 1000, cornerX, cornerY);

	// ����� �ڳʸ� ���� ǥ��
	BYTE colorCross[3] = { 0, 0, 255 };
	if (Image_in.GetChannel() == 3)
		Image_out = Image_in;
	else
		Image_out = Gray2RGB(Image_in);

	for (int n = 0; n<numCorner; n++)
	{
		if (Image_in.GetChannel() == 3)
			DrawCross(Image_out, cornerX[n], cornerY[n], colorCross);
		else
			DrawCross(Image_out, cornerX[n], cornerY[n], colorCross);
	}
	ShowImage(Image_out, "�ڳ� ���� ���");
}
