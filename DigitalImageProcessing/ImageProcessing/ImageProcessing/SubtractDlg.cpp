// SubtractDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "SubtractDlg.h"
#include "afxdialogex.h"


// CSubtractDlg 대화 상자입니다.

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


// CSubtractDlg 메시지 처리기입니다.
