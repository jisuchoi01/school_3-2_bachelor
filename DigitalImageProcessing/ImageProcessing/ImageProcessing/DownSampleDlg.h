#pragma once


// CDownSampleDlg ��ȭ �����Դϴ�.

class CDownSampleDlg : public CDialog
{
	DECLARE_DYNAMIC(CDownSampleDlg)

public:
	CDownSampleDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDownSampleDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_DownSampleRate;
};
