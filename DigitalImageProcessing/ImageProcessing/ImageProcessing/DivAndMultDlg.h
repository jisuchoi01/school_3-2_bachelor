#pragma once
#include "afxwin.h"

#define OPT_DIV 0
#define OPT_MULT 1

// CDivAMult ��ȭ �����Դϴ�.

class CDivAndMultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDivAndMultDlg)

public:
	CDivAndMultDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDivAndMultDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIV_MULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	int i_Constant;
	int opt;
	CButton btn_DivRadio;
	CButton btn_MultRadio;
	afx_msg void OnBnClickedDiv();
	afx_msg void OnBnClickedMult();
};
