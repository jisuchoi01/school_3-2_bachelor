
// ImageProcessingView.cpp : CImageProcessingView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DOWN_SAMPLING, &CImageProcessingView::OnDownSampling)
	ON_COMMAND(ID_QUANTIZATION, &CImageProcessingView::OnQuantization)
	ON_COMMAND(ID_UP_SAMPLING, &CImageProcessingView::OnUpSampling)
	ON_COMMAND(ID_SUM_CONSTANT, &CImageProcessingView::OnSumConstant)
	ON_COMMAND(ID_AND_OPERATE, &CImageProcessingView::OnAndOperate)
	ON_COMMAND(ID_SUB_CONSTANT, &CImageProcessingView::OnSubConstant)
	ON_COMMAND(ID_DIV_AND_MULT, &CImageProcessingView::OnDivAndMult)
	ON_COMMAND(ID_LOGICAL_OPERATION, &CImageProcessingView::OnLogicalOperation)
END_MESSAGE_MAP()

// CImageProcessingView ����/�Ҹ�

CImageProcessingView::CImageProcessingView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingView �׸���

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	int i, j;
	unsigned char R, G, B;
	// �Է� ���� ���
	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = pDoc->m_InputImage[i*pDoc->m_width + j];
			G = B = R;
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}

	// ��ҵ� ���� ���
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i*pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}
}


// CImageProcessingView �μ�

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CImageProcessingView ����

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView �޽��� ó����


void CImageProcessingView::OnDownSampling()
{
	// TODO: Add your command handler code here
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnDownSampling(); // Doc Ŭ������ OnDownSampling �Լ� ȣ��

	Invalidate(TRUE); // ȭ�� ����

}


void CImageProcessingView::OnUpSampling()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnUpSampling(); // Doc Ŭ������ OnUpSampling �Լ� ȣ��

	Invalidate(TRUE); // ȭ�� ����

}


void CImageProcessingView::OnQuantization()
{
	// TODO: Add your command handler code here
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnQuantization(); // Doc Ŭ������ OnQuantization �Լ� ȣ��

	Invalidate(TRUE); // ȭ�� ����

}

// ȭ�Ұ� ��� ����
void CImageProcessingView::OnSumConstant()
{
	// ��ť��Ʈ Ŭ���� ����
	CImageProcessingDoc* pDoc = GetDocument();

	// �ν��Ͻ� �ּҸ� ������
	ASSERT_VALID(pDoc);

	// �Լ� ȣ��
	pDoc->OnSumConstant();

	Invalidate(TRUE);
}

// ȭ�Ұ� ��� ����
void CImageProcessingView::OnSubConstant()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnSubConstant();
	Invalidate(TRUE);
}

// ������ ����
void CImageProcessingView::OnDivAndMult()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnDivAndMult();
	Invalidate(TRUE);
}

// & ����
void CImageProcessingView::OnAndOperate()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate();
	Invalidate(TRUE);
}



void CImageProcessingView::OnLogicalOperation()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnLogicalOperation();
	Invalidate(TRUE);
}
