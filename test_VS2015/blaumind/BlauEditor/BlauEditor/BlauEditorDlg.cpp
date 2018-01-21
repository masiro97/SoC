
// BlauEditorDlg.cpp : ���� ����
//

#include "stdafx.h"

#pragma comment(lib, "winmm.lib")

#include "BlauEditor.h"
#include "BlauEditorDlg.h"
#include "afxdialogex.h"

#include "ImageSrc/ImageFrameWndManager.h"
#include "ImageSrc/LoadImageFromFileDialog.h"
#include "ImageSrc/MyImageFunc.h"
#include "BlauFunction.h"

#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ByteImage gImageBuf;
BITMAPINFO gBmpInfo;

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
bool Enhanced = false;
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlauEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CAM, m_pic);
	DDX_Control(pDX, IDC_PROGRESS1, progress);
}

BEGIN_MESSAGE_MAP(CBlauEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON_START, &CBlauEditorDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CBlauEditorDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_DETECT, &CBlauEditorDlg::OnBnClickedButtonDetect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_ENHANCE, &CBlauEditorDlg::OnBnClickedCheckEnhance)
	ON_BN_CLICKED(IDC_CHECK_TRACKON, &CBlauEditorDlg::OnBnClickedCheckTrackon)
	ON_BN_CLICKED(IDC_CHECK_SHOW_POINT, &CBlauEditorDlg::OnBnClickedCheckShowPoint)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CBlauEditorDlg::OnNMCustomdrawProgress1)
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
	progress.SetPos(0);
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

void YUY2ToRGB24(int nWidth, int nHeight, const BYTE* pYUY2, BYTE* pRGB24)
{
	int nSize = nHeight * (nWidth / 2);

	int idxSrc = 0;
	int idxDst = 0;

	BYTE y1, u, y2, v;
	BYTE r, g, b;

	for (int i = 0; i<nSize; i++)
	{
		y1 = pYUY2[idxSrc];
		u = pYUY2[idxSrc + 1];
		y2 = pYUY2[idxSrc + 2];
		v = pYUY2[idxSrc + 3];

		// ù ��° �ȼ�
		b = CLIP((76284 * (y1 - 16) + 132252 * (u - 128)) >> 16);
		g = CLIP((76284 * (y1 - 16) - 53281 * (v - 128) - 25625 * (u - 128)) >> 16);
		r = CLIP((76284 * (y1 - 16) + 104595 * (v - 128)) >> 16);

		pRGB24[idxDst] = b;
		pRGB24[idxDst + 1] = g;
		pRGB24[idxDst + 2] = r;

		idxDst += 3;

		// �� ��° �ȼ�
		b = CLIP((76284 * (y2 - 16) + 132252 * (u - 128)) >> 16);
		g = CLIP((76284 * (y2 - 16) - 53281 * (v - 128) - 25625 * (u - 128)) >> 16);
		r = CLIP((76284 * (y2 - 16) + 104595 * (v - 128)) >> 16);

		pRGB24[idxDst] = b;
		pRGB24[idxDst + 1] = g;
		pRGB24[idxDst + 2] = r;

		idxDst += 3;
		idxSrc += 4;
	}
}

ByteImage gBgImage, gBinImage;

LRESULT ProcessCamFrame(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	if (gBmpInfo.bmiHeader.biCompression == BI_RGB) // RGB ����
	{
		memcpy(gImageBuf.GetPtr(), lpVHdr->lpData,
			gBmpInfo.bmiHeader.biHeight*gBmpInfo.bmiHeader.biWidth*gImageBuf.GetChannel());
	}
	else if (gBmpInfo.bmiHeader.biCompression == MAKEFOURCC('Y', 'U', 'Y', '2')) // 16��Ʈ ����
	{
		YUY2ToRGB24(gBmpInfo.bmiHeader.biWidth, gBmpInfo.bmiHeader.biHeight,
			lpVHdr->lpData, gImageBuf.GetPtr());
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

static bool stop = false;
static bool show_tracked_locations = true;
static bool show_keypoints = true;

void CBlauEditorDlg::OnBnClickedButtonStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	GetDlgItem(IDC_STATIC_CAM)->SetWindowPos(NULL, 0, 0, 640, 480, SWP_NOZORDER | SWP_NOMOVE);
	m_webCam.StartCam(GetDlgItem(IDC_STATIC_CAM), 640, 480, gBmpInfo);
	gImageBuf = ByteImage(gBmpInfo.bmiHeader.biWidth, gBmpInfo.bmiHeader.biHeight, 3);

	m_webCam.SetCallBackOnFrame(ProcessCamFrame);

		// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	string model_image1 = "model1.bmp";
	string model_image2 = "0";
	string model_image3 = "0";
	string model_image4 = "0";

	//detector_Init
	if (detector_Init(model_image1, model_image2, model_image3, model_image4) == -1)  return;

	//tracker_Init
	tracker_Init(model_image1, model_image2, model_image3, model_image4);
	
	//queue of model Init
	queue_Init(model_image1, model_image2, model_image3, model_image4);

}

CWinThread *p1 = NULL;
void CBlauEditorDlg::OnBnClickedButtonStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_webCam.StopCam();
	KillTimer(100);
	stop = true;
	
	CloseImage("BLAUMIND");
	//CloseHandle(p1);
}

ByteImage forshow;

UINT CBlauEditorDlg::ThreadFirst(LPVOID _mothod) {

	CBlauEditorDlg *fir = (CBlauEditorDlg*)_mothod;

	static DWORD frameCount = 0;            //������ ī��Ʈ��
	static float timeElapsed = 0.0f;            //�帥 �ð�
	static DWORD lastTime = timeGetTime();   //������ �ð�(temp����)

	ByteImage frame = ByteImage(gImageBuf.Width, gImageBuf.Height, 3);
	ByteImage gray_frame = ByteImage(frame.Width, frame.Height);
	do {
		frame = gImageBuf;

		frame.Flip();

		gray_frame = ByteImage(RGB2Gray(frame));
		
		if(Enhanced) AutoContrastControl(&gray_frame);
		detect_and_draw(&gray_frame, show_tracked_locations, show_keypoints);
		
		//if()
		forshow = gray_frame;//for showImage
		
	
	} while (!stop);

	frame.~BlauImage();
	gray_frame.~BlauImage();

	end_point();
	return 0;
}

void CBlauEditorDlg::OnBnClickedButtonDetect()
{
	forshow= gImageBuf;
	SetTimer(100, 1.0 / 30.0, 0);
	stop = false;
	p1 = AfxBeginThread(ThreadFirst,this);

	if(p1 == NULL){
	AfxMessageBox("Error");
	}
	p1->m_bAutoDelete = FALSE;
	p1->ResumeThread();
}


void CBlauEditorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CTime timer;
	timer = CTime::GetCurrentTime();
	CString strTimer;
	strTimer = timer.Format("%H�� %M�� %S ��");

	switch (nIDEvent) {

	case 100:
		//1�ʸ��� ó���� ����
		ShowImage(forshow, "BLAUMIND");
		
		break;


		CDialogEx::OnTimer(nIDEvent);
	}
}


void CBlauEditorDlg::OnBnClickedCheckEnhance()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(Enhanced == false)
		Enhanced = true;
	else Enhanced = false;
}


void CBlauEditorDlg::OnBnClickedCheckTrackon()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}


void CBlauEditorDlg::OnBnClickedCheckShowPoint()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CBlauEditorDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	/*for (int i = 0;i<100;i++)
	{
		progress.SetPos(i);
		Sleep(50);   //��ȭ�� ���̸� ���� ���� ����
	}
	*/

	//progress.SetStep(2); //���������� �ܰ������� ����
	//progress.StepIt();
}
