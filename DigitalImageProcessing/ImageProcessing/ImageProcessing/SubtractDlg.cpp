// SubtractDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "SubtractDlg.h"
#include "afxdialogex.h"


// CSubtractDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSubtractDlg, CDialogEx)

CSubtractDlg::CSubtractDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SUB, pParent)
	, i_Constant(0)
{

}

CSubtractDlg::~CSubtractDlg()
{
}

void CSubtractDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, i_Constant);
}


BEGIN_MESSAGE_MAP(CSubtractDlg, CDialogEx)
END_MESSAGE_MAP()


// CSubtractDlg �޽��� ó�����Դϴ�.
