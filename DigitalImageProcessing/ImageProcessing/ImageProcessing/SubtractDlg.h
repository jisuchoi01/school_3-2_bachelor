#pragma once


// CSubtractDlg ��ȭ �����Դϴ�.

class CSubtractDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSubtractDlg)

public:
	CSubtractDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSubtractDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ���� ��
	int i_Constant;
};
