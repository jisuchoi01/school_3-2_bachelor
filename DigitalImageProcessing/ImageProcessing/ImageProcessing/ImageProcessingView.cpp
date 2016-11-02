
// ImageProcessingView.cpp : CImageProcessingView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CImageProcessingView 생성/소멸

CImageProcessingView::CImageProcessingView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingView 그리기
void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	
	int i, j, value;
	unsigned char R, G, B;
	
    // 입력 영상 출력
	for (i = 0; i < pDoc->m_height; i++) 
	{
		for (j = 0; j < pDoc->m_width; j++) 
		{
			R = pDoc->m_InputImage[i*pDoc->m_width + j];
			G = B = R;
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}

	// 축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) 
	{
		for (j = 0; j < pDoc->m_Re_width; j++) 
		{
			R = pDoc->m_OutputImage[i*pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}

	// 히스토그램의 값은 0~255
	// 히스토그램의 크기 값을 MAX=255로 정규화하여 출력
	// 히스트그램의 크기 : 256*256 지정
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

	// 초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	// 빈도 수 조사
	for (i = 0; i < pDoc->m_size; i++)
	{
		value = (int) pDoc->m_InputImage[i];
		m_HIST[value]++;
	}

	// 정규화
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	// 최대값
	for (i = 0; i<256; i++)
		if (m_HIST[i] > MAX)
			MAX = m_HIST[i];

	// 최고값
	for (i = 0; i<256; i++)
		if (m_HIST[i] < MIN)
			MIN = m_HIST[i];

	// 정규화 계수
	DIF = MAX - MIN;

	// 정규화된 히스토그램
	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);

	// 정규화된 히스토그램 출력
	unsigned char* Histogram = new unsigned char[pDoc->m_Re_size + (256 * 20)];

	for (i = 0; i < pDoc->m_Re_size; i++)
		Histogram[i] = 255;

	// 정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현
	for (i = 0; i<256; i++) {
		for (j = 0; j<m_Scale_HIST[i]; j++) {
			Histogram[pDoc->m_Re_width*(pDoc->m_Re_height - j - 1) + i] = 0;
		}
	}

	// 히스토그램을 출력
	for (i = pDoc->m_Re_height; i < pDoc->m_Re_height + 5; i++)
		for (j = 0; j < 256; j++)
			Histogram[pDoc->m_Re_height * i + j] = 255;

	// 그 아래 부분에 히스토그램의 색을 표시
	for (i = pDoc->m_Re_height + 5; i < pDoc->m_Re_height + 20; i++)
		for (j = 0; j<256; j++)
			Histogram[pDoc->m_Re_height * i + j] = j;

	pDoc->m_Re_height = pDoc->m_Re_height + 20;
	pDoc->m_Re_size = pDoc->m_Re_height * pDoc->m_Re_width;

	// 축소된 영상 출력
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


// CImageProcessingView 인쇄

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageProcessingView 진단

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView 메시지 처리기


void CImageProcessingView::OnDownSampling()
{
	// TODO: Add your command handler code here
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnDownSampling(); // Doc 클래스에 OnDownSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신

}


void CImageProcessingView::OnUpSampling()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnUpSampling(); // Doc 클래스에 OnUpSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신

}


void CImageProcessingView::OnQuantization()
{
	// TODO: Add your command handler code here
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnQuantization(); // Doc 클래스에 OnQuantization 함수 호출

	Invalidate(TRUE); // 화면 갱신

}

// 화소값 상수 덧셈
void CImageProcessingView::OnSumConstant()
{
	// 도큐먼트 클래스 참조
	CImageProcessingDoc* pDoc = GetDocument();

	// 인스턴스 주소를 가져옴
	ASSERT_VALID(pDoc);

	// 함수 호출
	pDoc->OnSumConstant();

	Invalidate(TRUE);
}

// 화소값 상수 뺄셈
void CImageProcessingView::OnSubConstant()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnSubConstant();
	Invalidate(TRUE);
}

// 나눗셈 곱셈
void CImageProcessingView::OnDivAndMult()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnDivAndMult();
	Invalidate(TRUE);
}

// & 연산
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

// 과제
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

// 이진화
void CImageProcessingView::OnBinarization()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnBinarization();
	Invalidate(TRUE);// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

// 반전 영상
void CImageProcessingView::OnNegaTransform()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();
	Invalidate(TRUE);
}

// 부분 강조
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

// 히스토그램 그리기
void CImageProcessingView::OnDrawHistogram()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnDrawHistogram();
	Invalidate(TRUE);
}

// 평활화
void CImageProcessingView::OnEqualization()
{
	CImageProcessingDoc *pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->OnEqualization();
	Invalidate(TRUE);
}

// 엠보싱
void CImageProcessingView::OnEmbossing()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossing();

	Invalidate(TRUE);

}

// 블러링
void CImageProcessingView::OnBlurring()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurring();

	Invalidate(TRUE);
}

// 샤프닝
void CImageProcessingView::OnSharpening()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpening();

	Invalidate(TRUE);
}

// 과제 2 : 메디안 필터 구현
void CImageProcessingView::OnHomework2()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHomework2();

	Invalidate(TRUE);
}
