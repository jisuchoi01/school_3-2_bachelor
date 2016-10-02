#pragma once
#include "afxwin.h"

#define OPT_DIV 0
#define OPT_MULT 1

// CDivAMult 대화 상자입니다.

class CDivAndMultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDivAndMultDlg)

public:
	CDivAndMultDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDivAndMultDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIV_MULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	int i_Constant;
	int opt;
	CButton btn_DivRadio;
	CButton btn_MultRadio;
	afx_msg void OnBnClickedDiv();
	afx_msg void OnBnClickedMult();
};
