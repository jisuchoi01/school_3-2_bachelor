
// ImageProcessingDoc.h : CImageProcessingDoc Ŭ������ �������̽�
//


#pragma once


class CImageProcessingDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	
	unsigned char*m_InputImage;
	int m_width;
	int m_height;
	int m_size;
	
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	
	unsigned char*m_OutputImage;
	unsigned char* m_HistogramImage;
	int m_Re_width;
	int m_Re_height;
	int m_Re_size;
	void OnDownSampling(void);
	afx_msg void OnUpSampling();
	afx_msg void OnQuantization();
	afx_msg void OnSumConstant();
	afx_msg void OnAndOperate();
	afx_msg void OnSubConstant();
	afx_msg void OnDivAndMult();
	afx_msg void OnLogicalOperation();
	afx_msg void OnHomework1();
	afx_msg void OnGammaCorrection();
	afx_msg void OnBinarization();
	afx_msg void OnNegaTransform();
	afx_msg void OnStressTransform();
	afx_msg void OnDefaultStretching();
	afx_msg void OnDrawHistogram();
	afx_msg void OnEqualization();
	afx_msg void OnEmbossing();
	double** OnMaskProcess(unsigned char *Target, double Mask[3][3]);
	double** OnScale(double **Target, int height, int width);
	double** Image2DMem(int height, int width);
	double** m_tempImage;
	afx_msg void OnBlurring();
	afx_msg void OnSharpening();
	afx_msg void OnHomework2();
};
