#pragma once


// CUpSampleDlg ��ȭ �����Դϴ�.

class CUpSampleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpSampleDlg)

public:
	CUpSampleDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUpSampleDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_UpSampleRate;
};
