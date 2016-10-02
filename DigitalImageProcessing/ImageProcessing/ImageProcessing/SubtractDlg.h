#pragma once


// CSubtractDlg 대화 상자입니다.

class CSubtractDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSubtractDlg)

public:
	CSubtractDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSubtractDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 샘플 값
	int i_Constant;
};
