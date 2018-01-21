
// MDIImageViewerView.cpp : CMDIImageViewerView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MDIImageViewer.h"
#endif

#include "MDIImageViewerDoc.h"
#include "MDIImageViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMDIImageViewerView

IMPLEMENT_DYNCREATE(CMDIImageViewerView, CView)

BEGIN_MESSAGE_MAP(CMDIImageViewerView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMDIImageViewerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMDIImageViewerView ����/�Ҹ�

CMDIImageViewerView::CMDIImageViewerView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMDIImageViewerView::~CMDIImageViewerView()
{
}

BOOL CMDIImageViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMDIImageViewerView �׸���
bool _DrawImage(HDC hdc, const ByteImage& image, int nSrcx, int nSrcy, int nSrcw, int nSrcH, int nDstX, int nDstY, int nDstW, int nDstH) {

	if (image.IsEmpty()) return false;//�� �����̸� �ٷ� ����
	static BYTE bmiBuf[sizeof(BITMAPINFOHEADER) + 1024];
	int nWidth = image.GetWStep() / image.GetChannel();
	int nHeight = image.GetHeight();
	int nBPP = image.GetChannel() * 8;

	//256�� ȸ���� �Ǵ� Ʈ�� �÷� ���� ��� ����

	ASSERT((BITMAPINFO*)bmiBuf && nWidth > 0 && nHeight > 0 && (nBPP == 8 || nBPP == 24));
	BITMAPINFOHEADER *bmih = &(((BITMAPINFO*)bmiBuf)->bmiHeader);
	memset(bmih, 0, sizeof(bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = nWidth;
	bmih->biHeight = -nHeight;  //������ �Ʒ��� ���
	bmih->biPlanes = 1;
	bmih->biBitCount = nBPP;
	bmih->biCompression = BI_RGB; //���� ��� ����

	static const RGBQUAD GrayPalette[256] = { {0,0,0,0},{1,1,1,0},{255,255,255,0} };
	if (nBPP == 8) {
		memcpy(((BITMAPINFO*)bmiBuf)->bmiColors, GrayPalette, 256 * sizeof(RGBQUAD));

		SetStretchBltMode(hdc, COLORONCOLOR);
		::StretchDIBits(hdc, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH, image.GetPtr(), (LPBITMAPINFO)&(((BITMAPINFO*)bmiBuf)->bmiHEADER), DIB_RGB_COLORS, SRCCOPY);
		return true;
	}
}
void CMDIImageViewerView::OnDraw(CDC* /*pDC*/)
{
	CMDIImageViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	ByteImage& m_image = pDoc->m_image;
	if (m_image.IsEmpty()) return;

	_DrawImage(pDC->m_hDC, m_image, 0, 0, m_image.GetWidth(), m_image.GetHeight(), 0, 0, m_image.GetWidth(), m_image.GetHeight());
}


// CMDIImageViewerView �μ�


void CMDIImageViewerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMDIImageViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMDIImageViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMDIImageViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CMDIImageViewerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMDIImageViewerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMDIImageViewerView ����

#ifdef _DEBUG
void CMDIImageViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CMDIImageViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDIImageViewerDoc* CMDIImageViewerView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIImageViewerDoc)));
	return (CMDIImageViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMDIImageViewerView �޽��� ó����
