
// ImageProcessingDoc.cpp : CImageProcessingDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"

/* ���̾�α� */
#include "DownSampleDlg.h"
#include "UpSampleDlg.h"
#include "QuantizationDlg.h"
#include "ConstantDlg.h"

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
END_MESSAGE_MAP()


// CImageProcessingDoc ����/�Ҹ�

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
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CImageProcessingDoc ����

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


// CImageProcessingDoc ���


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	CFile File; // ���� ��ü ����

	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// ���� ���� ��ȭ���ڿ��� ������ ������ �����ϰ� �б� ��� ����

	// �� å������ ������ ũ�� 256*256, 512*512, 640*480���� ����Ѵ�.
	if (File.GetLength() == 256 * 256) { // RAW ������ ũ�� ����

		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) { // RAW ������ ũ�� ����
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) { // RAW ������ ũ�� ����
		m_height = 480;
		m_width = 640;
	}
	else {
		AfxMessageBox(_T("Not Support Image Size")); // �ش� ũ�Ⱑ ���� ���
		return 0;
	}
	m_size = m_width * m_height; // ������ ũ�� ���

	m_InputImage = new unsigned char[m_size];
	// �Է� ������ ũ�⿡ �´� �޸� �Ҵ�

	for (int i = 0; i < m_size; i++)
		m_InputImage[i] = 255; // �ʱ�ȭ
	File.Read(m_InputImage, m_size); // �Է� ���� ���� �б�
	File.Close(); // ���� �ݱ�

	return TRUE;
}


BOOL CImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFile File; // ���� ��ü ����
	CFileDialog SaveDlg(FALSE, (LPCTSTR)"raw", NULL, OFN_HIDEREADONLY);
	// raw ������ �ٸ� �̸����� �����ϱ⸦ ���� ��ȭ���� ��ü ����

	if (SaveDlg.DoModal() == IDOK) {
		// DoModal ��� �Լ����� �����ϱ� ����
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate |
			CFile::modeWrite);
		// ���� ����
		File.Write(m_InputImage, m_size); // ���� ����
		File.Close(); // ���� �ݱ�
	}

	return TRUE;

}


void CImageProcessingDoc::OnDownSampling(void)
{
	int i, j;
	CDownSampleDlg dlg;
	if (dlg.DoModal() == IDOK) // ��ȭ������ Ȱ��ȭ ����
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		// ��� ������ ���� ���̸� ���
		m_Re_width = m_width / dlg.m_DownSampleRate;
		// ��� ������ ���� ���̸� ���
		m_Re_size = m_Re_height * m_Re_width;
		// ��� ������ ũ�⸦ ���

		m_OutputImage = new unsigned char[m_Re_size];
		// ��� ������ ���� �޸� �Ҵ�

		for (i = 0; i < m_Re_height; i++) {
			for (j = 0; j < m_Re_width; j++) {
				m_OutputImage[i*m_Re_width + j]
					= m_InputImage[(i*dlg.m_DownSampleRate*m_width) + dlg.m_DownSampleRate*j];
				// ��� ������ ����
			}
		}
	}
}


void CImageProcessingDoc::OnUpSampling()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	int i, j;

	CUpSampleDlg dlg;
	if (dlg.DoModal() == IDOK) { // DoModal ��ȭ������ Ȱ��ȭ ����
		m_Re_height = m_height * dlg.m_UpSampleRate;
		// Ȯ�� ������ ���� ���� ���
		m_Re_width = m_width * dlg.m_UpSampleRate;
		// Ȯ�� ������ ���� ���� ���
		m_Re_size = m_Re_height * m_Re_width;
		// Ȯ�� ������ ũ�� ���
		m_OutputImage = new unsigned char[m_Re_size];
		// Ȯ�� ������ ���� �޸� �Ҵ�

		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0; // �ʱ�ȭ

		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[i*dlg.m_UpSampleRate*m_Re_width +
					dlg.m_UpSampleRate*j] = m_InputImage[i*m_width + j];
			} // ���ġ�Ͽ� ���� Ȯ��
		}
	}
}



/* ����ȭ */
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

		// ��Ʈ ������ �ٽ� ����
		for (i = 0; i < m_size; i++)
		{
			m_OutputImage[i] = m_InputImage[i] >> sb << sb;
		}
	}
}


void CImageProcessingDoc::OnSumConstant()
{
	CConstantDlg dlg; // ��� ���� �Է¹޴� ��ȭ����

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) 
	{
		for (i = 0; i < m_size; i++) 
		{
			// ��� ���� 255���� ũ�� 255 ���
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;

			// ��� ���� ȭ�� ������ ����
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
		}
	}
}

/* && ���� */
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
		for (i = 0; i<m_size; i++) 
			m_OutputImage[i] = (m_InputImage[i] & (unsigned char)dlg.m_Constant);
	}
}
