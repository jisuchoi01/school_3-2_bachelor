// UpSampleDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "UpSampleDlg.h"
#include "afxdialogex.h"


// CUpSampleDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUpSampleDlg, CDialogEx)

CUpSampleDlg::CUpSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpSampleDlg::IDD, pParent)
	, m_UpSampleRate(0)
{

}

CUpSampleDlg::~CUpSampleDlg()
{
}

void CUpSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_UpSampleRate);
}


BEGIN_MESSAGE_MAP(CUpSampleDlg, CDialogEx)
END_MESSAGE_MAP()


// CUpSampleDlg �޽��� ó�����Դϴ�.
