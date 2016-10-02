#pragma once
#include "afxwin.h"

// 라디오 버튼 선택값
#define OR 0
#define XOR 1
#define NOR 2

// CLogicalOperationDlg 대화 상자입니다.

class CLogicalOperationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogicalOperationDlg)

public:
	CLogicalOperationDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLogicalOperationDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGICAL_OPERATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	int i_Constant;
	unsigned int opt;
	CButton btn_ORRadio;
	CButton btn_XORRadio;
	CButton btn_NORRadio;
	afx_msg void OnBnClickedOr();
	afx_msg void OnBnClickedXor();
	afx_msg void OnBnClickedNor();
};
