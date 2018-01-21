
// BlauEditorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "BlauEditor.h"
#include "BlauEditorDlg.h"
#include "afxdialogex.h"
#include "ImageSrc/ImageFrameWndManager.h"
#include "ImageSrc/LoadImageFromFileDialog.h"
#include "ImageSrc/MyImageFunc.h"
#include <windows.h>
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ByteImage gImageBuf;
BITMAPINFO gBmpInfo;

UINT CBlauEditorDlg::ThreadFirst(LPVOID _mothod) {

	CBlauEditorDlg *fir = (CBlauEditorDlg*)_mothod;

	//CBlauEditorDlg *pDlg = (CBlauEditorDlg*)AfxGetApp()->m_pMainWnd;
	//pDlg->mNumOutOut = 100;

	while (1) {

		//..�� ���� ������ ������ ������ �����ϼ���.
//		UpdateFPS();
		//CImageView *m = NULL;
		//m->OnLButtonDown(1, CPoint(100,100));
		// -> ���� ������ r, �߽� x,y�� ���� �׸�����
		//HDC hdc = ::GetDC(hWnd);
		//Ellipse(hdc, 50, 50, 150, 150);

		Sleep(10);
	}
	return 0;
}
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlauEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CAM, m_pic);
	DDX_Control(pDX, IDC_PROGRESS, progress);
}

BEGIN_MESSAGE_MAP(CBlauEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON_START, &CBlauEditorDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CBlauEditorDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CBlauEditorDlg::OnBnClickedButtonCapture)
	ON_BN_CLICKED(IDC_BUTTON, &CBlauEditorDlg::OnBnClickedButton)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS, &CBlauEditorDlg::OnNMCustomdrawProgress)
	ON_BN_CLICKED(IDC_BUTTON_AUTO, &CBlauEditorDlg::OnBnClickedButtonAuto)
	ON_BN_CLICKED(IDC_BUTTON_STEP, &CBlauEditorDlg::OnBnClickedButtonStep)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CBlauEditorDlg::OnBnClickedButtonReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CBlauEditorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBlauEditorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_FPS, &CBlauEditorDlg::OnBnClickedButtonFps)
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
	progress.SetRange(0, 100);
	progress.SetPos(50);
	
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

void CBlauEditorDlg::OnBnClickedButtonStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItem(IDC_STATIC_CAM)->SetWindowPos(NULL, 0, 0, 640, 480, SWP_NOZORDER | SWP_NOMOVE);
	m_webCam.StartCam(GetDlgItem(IDC_STATIC_CAM), 640, 480, gBmpInfo);
	gImageBuf = ByteImage(gBmpInfo.bmiHeader.biWidth, gBmpInfo.bmiHeader.biHeight, 3);
	SetTimer(100, 1.0 / 30.0, 0);
	m_webCam.SetCallBackOnFrame(ProcessCamFrame);


}


void CBlauEditorDlg::OnBnClickedButtonStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_webCam.StopCam();
}

void CBlauEditorDlg::OnBnClickedButtonCapture()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	ShowImage(gImageBuf.Flip(), "capture");

	
	CWinThread *p1 = NULL;
	p1 = AfxBeginThread(ThreadFirst, this);

	if (p1 == NULL) {

		AfxMessageBox("Error");
	}
	CloseHandle(p1);
}


void CBlauEditorDlg::OnBnClickedButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//ShowImage(gImageBuf.Flip(), "capture");
	ByteImage Img = RGB2Gray(gImageBuf.Flip());

	DrawLines(Img, 50, 1, 50, 200,10,255);

	ShowImage(Img, "capture");
}


void CBlauEditorDlg::OnNMCustomdrawProgress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	progress.SetRange(0, 100);  //�������� ����
	progress.SetStep(1);          //�󸶾� ������ �������� ����

	for (int a = 0; a <= 99; a++)
	{
		progress.StepIt();  //SetStep���� ������ ����� ����
		progress.GetPos();
		//Sleep(100);                 //��������(1000�� ������ 1�� delay)
	}


}


void CBlauEditorDlg::OnButtonAuto()
{
	for (int i = 0;i<100;i++)
	{
		progress.SetPos(i);
		Sleep(50);   //��ȭ�� ���̸� ���� ���� ����
	}
}

void CBlauEditorDlg::OnButtonStep()
{
	progress.SetStep(2); //���������� �ܰ������� ����
	progress.StepIt();

}

void CBlauEditorDlg::OnButtonReset()
{
	progress.SetPos(0);
}



void CBlauEditorDlg::OnBnClickedButtonAuto()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	for (int i = 0;i<100;i++)
	{
		progress.SetPos(i);
		Sleep(50);   //��ȭ�� ���̸� ���� ���� ����
	}
}


void CBlauEditorDlg::OnBnClickedButtonStep()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	progress.SetStep(2); //���������� �ܰ������� ����
	progress.StepIt();
}
//PBS_smoothS

void CBlauEditorDlg::OnBnClickedButtonReset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	progress.SetPos(0);
}


void CBlauEditorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CTime timer;
	timer = CTime::GetCurrentTime();
	CString strTimer;
	strTimer = timer.Format("%H�� %M�� %S ��");
	
	SetTimer(10, 1.0 / 30.0, 0);
	switch (nIDEvent) {

	case 100:
		//1�ʸ��� ó���� ����
		ShowImage(gImageBuf.Flip(), "Capture");

		break;

	case 10:
		//ó���� ����

		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CBlauEditorDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	KillTimer(0);
	CDialogEx::OnOK();
}


void CBlauEditorDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	KillTimer(0);
	CDialogEx::OnCancel();
}


void CBlauEditorDlg::OnBnClickedButtonFps()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// frame rate setting 
	DWORD dwFrames;
	DWORD dwCurrentTime;
	DWORD dwLastUpdateTime;
	DWORD dwElapsedTime;
	char  szFPS[32];
	// Zero out the frames per second variables:
	dwFrames = 0;
	dwCurrentTime = 0;
	dwLastUpdateTime = 0;
	dwElapsedTime = 0;
	szFPS[0] = '\0';

	// Calculate the number of frames per one second:
	dwFrames++;
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 1000)
	{
		sprintf(szFPS, ("FPS = %2.2f"), (float)(dwFrames * 1000.0 / dwElapsedTime));
		dwFrames = 0;
		dwLastUpdateTime = dwCurrentTime;
	}
	std::cout << szFPS << std::endl;


}

/*void UpdateFPS()
{

	static DWORD frameCount = 0;            //������ ī��Ʈ��
	static float timeElapsed = 0.0f;            //�帥 �ð�
	static DWORD lastTime = timeGetTime();   //������ �ð�(temp����)

	DWORD curTime = timeGetTime();      //���� �ð�
	float timeDelta = (curTime - lastTime)*0.001f;        //timeDelta(1�������� �帥 �ð�) 1�ʴ����� �ٲ��ش�.
	TCHAR pFPS[256];
	timeElapsed += timeDelta;

	frameCount++;

	if (timeElapsed >= 1.0f)         //�帥�ð��� 1���̻��̸� ���� �ϰ������ ó��
	{
		float fps = (float)frameCount / timeElapsed;
		//sprintf_s(pFPS, sizeof(pFPS), TEXT("���Ӽӵ� FPS: %f"), fps);     //FPS��� �ϴ� �ҽ�

		frameCount = 0;
		timeElapsed = 0.0f;
	}
	else
	{
		//�帥 �ð��� 1�ʰ� �ȵǸ� ������  
		//Sleep() �ص��ǰ� ���ص� �Ǳ�~ 
	}



	lastTime = curTime;
}
*/