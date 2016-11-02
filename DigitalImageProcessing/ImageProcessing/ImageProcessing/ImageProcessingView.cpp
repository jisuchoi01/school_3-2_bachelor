
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
	ON_COMMAND(ID_HOMEWORK1, &CImageProcessingView::OnHomework1)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProcessingView::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CImageProcessingView::OnBinarization)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CImageProcessingView::OnNegaTransform)
	ON_COMMAND(ID_STRESS_TRANSFORM, &CImageProcessingView::OnStressTransform)
	ON_COMMAND(ID_DEFAULT_STRETCHING, &CImageProcessingView::OnDefaultStretching)
	ON_COMMAND(ID_DRAW_HISTOGRAM, &CImageProcessingView::OnDrawHistogram)
	ON_COMMAND(ID_EQUALIZATION, &CImageProcessingView::OnEqualization)
	ON_COMMAND(ID_EMBOSSING, &CImageProcessingView::OnEmbossing)
	ON_COMMAND(ID_BLURRING, &CImageProcessingView::OnBlurring)
	ON_COMMAND(ID_SHARPENING, &CImageProcessingView::OnSharpening)
	ON_COMMAND(ID_HOMEWORK2, &CImageProcessingView::OnHomework2)
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
	
	int i, j, value;
	unsigned char R, G, B;
	
    // �Է� ���� ���
	for (i = 0; i < pDoc->m_height; i++) 
	{
		for (j = 0; j < pDoc->m_width; j++) 
		{
			R = pDoc->m_InputImage[i*pDoc->m_width + j];
			G = B = R;
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}

	// ��ҵ� ���� ���
	for (i = 0; i < pDoc->m_Re_height; i++) 
	{
		for (j = 0; j < pDoc->m_Re_width; j++) 
		{
			R = pDoc->m_OutputImage[i*pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}

	// ������׷��� ���� 0~255
	// ������׷��� ũ�� ���� MAX=255�� ����ȭ�Ͽ� ���
	// ����Ʈ�׷��� ũ�� : 256*256 ����
	unsigned char LOW, HIGH;
	double MAX, MIN, DIF;
	
	double m_HIST[256];
	double m_Sum_Of_HIST[256];
	unsigned char m_Scale_HIST[256];
	
	pDoc->m_Re_height = 256;
	pDoc->m_Re_width = 256;
	pDoc->m_Re_size = pDoc->m_Re_height * pDoc->m_Re_width;

	LOW = 0;
	HIGH = 255;

	// �ʱ�ȭ
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	// �� �� ����
	for (i = 0; i < pDoc->m_size; i++)
	{
		value = (int) pDoc->m_InputImage[i];
		m_HIST[value]++;
	}

	// ����ȭ
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	// �ִ밪
	for (i = 0; i<256; i++)
		if (m_HIST[i] > MAX)
			MAX = m_HIST[i];

	// �ְ�
	for (i = 0; i<256; i++)
		if (m_HIST[i] < MIN)
			MIN = m_HIST[i];

	// ����ȭ ���
	DIF = MAX - MIN;

	// ����ȭ�� ������׷�
	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);

	// ����ȭ�� ������׷� ���
	unsigned char* Histogram = new unsigned char[pDoc->m_Re_size + (256 * 20)];

	for (i = 0; i < pDoc->m_Re_size; i++)
		Histogram[i] = 255;

	// ����ȭ�� ������׷��� ���� ��� �迭�� ���� ��(0)���� ǥ��
	for (i = 0; i<256; i++) {
		for (j = 0; j<m_Scale_HIST[i]; j++) {
			Histogram[pDoc->m_Re_width*(pDoc->m_Re_height - j - 1) + i] = 0;
		}
	}

	// ������׷��� ���
	for (i = pDoc->m_Re_height; i < pDoc->m_Re_height + 5; i++)
		for (j = 0; j < 256; j++)
			Histogram[pDoc->m_Re_height * i + j] = 255;

	// �� �Ʒ� �κп� ������׷��� ���� ǥ��
	for (i = pDoc->m_Re_height + 5; i < pDoc->m_Re_height + 20; i++)
		for (j = 0; j<256; j++)
			Histogram[pDoc->m_Re_height * i + j] = j;

	pDoc->m_Re_height = pDoc->m_Re_height + 20;
	pDoc->m_Re_size = pDoc->m_Re_height * pDoc->m_Re_width;

	// ��ҵ� ���� ���
	for (i = 0; i < pDoc->m_Re_height; i++)
	{
		for (j = 0; j < pDoc->m_Re_width; j++)
		{
			R = Histogram[i*pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + (2 * pDoc->m_width), i + 5, RGB(R, G, B));
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

// ����
void CImageProcessingView::OnHomework1()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnHomework1();
	Invalidate(TRUE);
}


void CImageProcessingView::OnGammaCorrection()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnGammaCorrection();
	Invalidate(TRUE);
}

// ����ȭ
void CImageProcessingView::OnBinarization()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnBinarization();
	Invalidate(TRUE);// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

// ���� ����
void CImageProcessingView::OnNegaTransform()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();
	Invalidate(TRUE);
}

// �κ� ����
void CImageProcessingView::OnStressTransform()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnStressTransform();
	Invalidate(TRUE);
}



void CImageProcessingView::OnDefaultStretching()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnDefaultStretching();
	Invalidate(TRUE);
}

// ������׷� �׸���
void CImageProcessingView::OnDrawHistogram()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnDrawHistogram();
	Invalidate(TRUE);
}

// ��Ȱȭ
void CImageProcessingView::OnEqualization()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnEqualization();
	Invalidate(TRUE);
}

// ������
void CImageProcessingView::OnEmbossing()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossing();

	Invalidate(TRUE);

}

// ����
void CImageProcessingView::OnBlurring()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurring();

	Invalidate(TRUE);
}

// ������
void CImageProcessingView::OnSharpening()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpening();

	Invalidate(TRUE);
}

// ���� 2 : �޵�� ���� ����
void CImageProcessingView::OnHomework2()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHomework2();

	Invalidate(TRUE);
}
