#pragma once


// CQuantizationDlg ��ȭ �����Դϴ�.

class CQuantizationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQuantizationDlg)

public:
	CQuantizationDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CQuantizationDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_QuantBit;
};
