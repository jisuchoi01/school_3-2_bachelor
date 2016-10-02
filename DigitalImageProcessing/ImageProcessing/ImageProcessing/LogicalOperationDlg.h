#pragma once
#include "afxwin.h"

// ���� ��ư ���ð�
#define OR 0
#define XOR 1
#define NOR 2

// CLogicalOperationDlg ��ȭ �����Դϴ�.

class CLogicalOperationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogicalOperationDlg)

public:
	CLogicalOperationDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLogicalOperationDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGICAL_OPERATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
