
// ImageProcessingDoc.cpp : CImageProcessingDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"

/* 다이얼로그 */
#include "DownSampleDlg.h"
#include "UpSampleDlg.h"
#include "QuantizationDlg.h"
#include "ConstantDlg.h"
#include "SubtractDlg.h"
#include "DivAndMultDlg.h"
#include "LogicalOperationDlg.h"

/* 그 외 유틸 */
#include <string>
using namespace std; // 표준이므로 std 안에 string 이 정의되어 있습니다. 

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_UP_SAMPLING, &CImageProcessingDoc::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CImageProcessingDoc::OnQuantization)
	ON_COMMAND(ID_SUM_CONSTANT, &CImageProcessingDoc::OnSumConstant)
	ON_COMMAND(ID_AND_OPERATE, &CImageProcessingDoc::OnAndOperate)
	ON_COMMAND(ID_SUB_CONSTANT, &CImageProcessingDoc::OnSubConstant)
	ON_COMMAND(ID_DIV_AND_MULT, &CImageProcessingDoc::OnDivAndMult)
	ON_COMMAND(ID_LOGICAL_OPERATION, &CImageProcessingDoc::OnLogicalOperation)
	ON_COMMAND(ID_HOMEWORK1, &CImageProcessingDoc::OnHomework1)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProcessingDoc::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CImageProcessingDoc::OnBinarization)
END_MESSAGE_MAP()


// CImageProcessingDoc 생성/소멸

CImageProcessingDoc::CImageProcessingDoc()
	: m_InputImage(NULL)
	, m_width(0)
	, m_height(0)
	, m_size(0)
	, m_OutputImage(NULL)
	, m_Re_width(0)
	, m_Re_height(0)
	, m_Re_size(0)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingDoc 진단

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc 명령


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	CFile File; // 파일 객체 선언

	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// 파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택

	// 이 책에서는 영상의 크기 256*256, 512*512, 640*480만을 사용한다.
	if (File.GetLength() == 256 * 256) { // RAW 파일의 크기 결정

		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) { // RAW 파일의 크기 결정
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) { // RAW 파일의 크기 결정
		m_height = 480;
		m_width = 640;
	}
	else {
		AfxMessageBox(_T("Not Support Image Size")); // 해당 크기가 없는 경우
		return 0;
	}
	m_size = m_width * m_height; // 영상의 크기 계산

	m_InputImage = new unsigned char[m_size];
	// 입력 영상의 크기에 맞는 메모리 할당

	for (int i = 0; i < m_size; i++)
		m_InputImage[i] = 255; // 초기화
	File.Read(m_InputImage, m_size); // 입력 영상 파일 읽기
	File.Close(); // 파일 닫기

	return TRUE;
}


BOOL CImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFile File; // 파일 객체 선언
	CFileDialog SaveDlg(FALSE, (LPCTSTR)"raw", NULL, OFN_HIDEREADONLY);
	// raw 파일을 다른 이름으로 저장하기를 위한 대화상자 객체 선언

	if (SaveDlg.DoModal() == IDOK) {
		// DoModal 멤버 함수에서 저장하기 수행
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate |
			CFile::modeWrite);
		// 파일 열기
		File.Write(m_InputImage, m_size); // 파일 쓰기
		File.Close(); // 파일 닫기
	}

	return TRUE;

}


void CImageProcessingDoc::OnDownSampling(void)
{
	int i, j;
	CDownSampleDlg dlg;
	if (dlg.DoModal() == IDOK) // 대화상자의 활성화 여부
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		// 축소 영상의 세로 길이를 계산
		m_Re_width = m_width / dlg.m_DownSampleRate;
		// 축소 영상의 가로 길이를 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 축소 영상의 크기를 계산

		m_OutputImage = new unsigned char[m_Re_size];
		// 축소 영상을 위한 메모리 할당

		for (i = 0; i < m_Re_height; i++) {
			for (j = 0; j < m_Re_width; j++) {
				m_OutputImage[i*m_Re_width + j]
					= m_InputImage[(i*dlg.m_DownSampleRate*m_width) + dlg.m_DownSampleRate*j];
				// 축소 영상을 생성
			}
		}
	}
}


void CImageProcessingDoc::OnUpSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int i, j;

	CUpSampleDlg dlg;
	if (dlg.DoModal() == IDOK) { // DoModal 대화상자의 활성화 여부
		m_Re_height = m_height * dlg.m_UpSampleRate;
		// 확대 영상의 세로 길이 계산
		m_Re_width = m_width * dlg.m_UpSampleRate;
		// 확대 영상의 가로 길이 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 확대 영상의 크기 계산
		m_OutputImage = new unsigned char[m_Re_size];
		// 확대 영상을 위한 메모리 할당

		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0; // 초기화

		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[i*dlg.m_UpSampleRate*m_Re_width +
					dlg.m_UpSampleRate*j] = m_InputImage[i*m_width + j];
			} // 재배치하여 영상 확대
		}
	}
}

/* 양자화 */
void CImageProcessingDoc::OnQuantization()
{
	CQuantizationDlg dlg;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		int i, sb;
		sb = 8 - dlg.m_QuantBit;

		// 비트 버리고 다시 땡김
		for (i = 0; i < m_size; i++)
		{
			m_OutputImage[i] = m_InputImage[i] >> sb << sb;
		}
	}
}

/* 상수 덧셈 */
void CImageProcessingDoc::OnSumConstant()
{
	CConstantDlg dlg; // 상수 값을 입력받는 대화상자

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			// 출력 값이 255보다 크면 255 출력
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;

			// 상수 값과 화소 값과의 덧셈
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
		}
	}
}

// 화소값 뺄셈
void CImageProcessingDoc::OnSubConstant()
{
	CSubtractDlg dlg; // 상수 값을 입력받는 대화상자

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	// 확인 버튼을 눌렀을 때
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			// 출력 값이 255보다 크면 255 출력
			if (m_InputImage[i] - dlg.i_Constant < 0)
				m_OutputImage[i] = 0;

			// 상수 값과 화소 값과의 뺄셈
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] - dlg.i_Constant);
		}
	}
}


// 나눗셈 곱셈
void CImageProcessingDoc::OnDivAndMult()
{
	CDivAndMultDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		switch (dlg.opt)
		{
		case OPT_DIV:
			for (i = 0; i < m_size; i++)
			{
				// 상수 값과 화소 값 나눗셈
				if (m_InputImage[i] / dlg.i_Constant < 0)
					m_OutputImage[i] = 0;

				else
					m_OutputImage[i]
					= (unsigned char)(m_InputImage[i] / dlg.i_Constant);
			}
			break;
		case OPT_MULT:
			for (i = 0; i < m_size; i++)
			{
				// 상수 값과 화소 값 곱셈
				if (m_InputImage[i] * dlg.i_Constant > 255)
					m_OutputImage[i] = 255;

				else
					m_OutputImage[i]
					= (unsigned char)(m_InputImage[i] * dlg.i_Constant);
			}
			break;
		default:
			break;
		} // switch end
	} // if end
}

// & 연산 
void CImageProcessingDoc::OnAndOperate()
{
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
			m_OutputImage[i] = (m_InputImage[i] & (unsigned char)dlg.m_Constant);
	}
}

// XOR, OR, NOR
void CImageProcessingDoc::OnLogicalOperation()
{
	CLogicalOperationDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		switch (dlg.opt)
		{
		case OR:
			for (i = 0; i < m_size; i++)
				m_OutputImage[i] = (m_InputImage[i] |
				(unsigned char)dlg.i_Constant);
			break;

		case XOR:
			for (i = 0; i < m_size; i++)
				m_OutputImage[i] = (m_InputImage[i] ^
				(unsigned char)dlg.i_Constant);
			break;

		case NOR:
			for (i = 0; i < m_size; i++)
				m_OutputImage[i] = !m_InputImage[i];
			break;

		default:
			break;
		}
	}
}

// 과제 1 : 입력영상 평균 128, 표준편차 30으로 변환시키기

// 평균 구하는 함수
double GetAverage(unsigned char data[], int size)
{
	double Average = 0;

	// 평균 구함
	for (int i = 0; i < size; i++)
		Average += data[i];
	Average /= size;

	return Average;
}

// 표준 편차 구하는 함수
double GetDiviation(unsigned char data[], int size, double Average)
{
	double StandardDiviation = 0, diff = 0;
	// 편차 구함
	for (int i = 0; i < size; i++)
	{
		diff = data[i] - Average;
		diff *= diff;
		StandardDiviation += diff;
	}
	StandardDiviation /= size;
	StandardDiviation = sqrt(StandardDiviation);
	return StandardDiviation;
}

void test()
{
	int m_size = 5;
	unsigned char t[5] = {1, 2, 3, 4, 5 };
	double Average = 0, StandardDiviation = 0, diff = 0;

	double AfterAverage = 0, AfterStandardDiviation = 0;

	Average = GetAverage(t, 5);
	StandardDiviation = GetDiviation(t,5,Average);
	for (int i = 0; i < 5; i++)
		t[i] *= 2;

	printf("test %lf\n",Average);
	Average = GetAverage(t, 5);
	printf("test %lf\n\n", Average);

	StandardDiviation = GetDiviation(t, 5, Average);

}

void CImageProcessingDoc::OnHomework1()
{
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_size];

	// 변환 전 평균, 편차 변수
	double Average = 0, StandardDiviation = 0;
	
	// 변환 후 평균, 편차 변수
	double AfterAverage = 0, AfterStandardDiviation = 0;

	// 평균과 편차 구함
	Average = GetAverage(m_InputImage, m_size);
	StandardDiviation = GetDiviation(m_InputImage, m_size, Average);
	

	// 영상 변환
	for (int i = 0; i < m_size; i++)
		m_OutputImage[i] = (m_InputImage[i] - Average) * (30 / StandardDiviation) + 128;

	// 변환된 영상의 평균과 편차 구함
	AfterAverage = GetAverage(m_OutputImage, m_size);
	AfterStandardDiviation = GetDiviation(m_OutputImage, m_size, AfterAverage);
	
	// 디버깅 결과 출력
	printf("원래 평균 : %lf\n", Average);
	printf("원래 편차 : %lf\n", StandardDiviation);
	printf("현재 편차 : %lf\n", AfterStandardDiviation);
	printf("현재 평균 : %lf\n\n", AfterAverage);
}


void CImageProcessingDoc::OnGammaCorrection()
{
	CConstantDlg dlg;

	double temp = 0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_size];

	if (dlg.DoModal() == IDOK)
	{
		for (int i = 0; i < m_size; i++)
		{
			temp = pow(m_InputImage[i], 1 / dlg.m_Constant);
			// 감마 값 계산
			if (temp < 0)
				m_OutputImage[i] = 0;
			else if (temp > 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)temp;
		}
	}
}


void CImageProcessingDoc::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
