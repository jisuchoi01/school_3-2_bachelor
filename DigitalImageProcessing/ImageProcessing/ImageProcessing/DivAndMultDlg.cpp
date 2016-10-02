// DivAMult.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DivAndMultDlg.h"
#include "afxdialogex.h"

// CDivAMult 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDivAndMultDlg, CDialogEx)

// 다이얼로그 표준 생성자
CDivAndMultDlg::CDivAndMultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIV_MULT, pParent)
{
	opt = OPT_DIV;
}

CDivAndMultDlg::~CDivAndMultDlg()
{
}

void CDivAndMultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIV, btn_DivRadio);
	DDX_Control(pDX, IDC_MULT, btn_MultRadio);
	DDX_Text(pDX, IDC_EDIT1, i_Constant);
}


BEGIN_MESSAGE_MAP(CDivAndMultDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DIV, &CDivAndMultDlg::OnBnClickedDiv)
	ON_BN_CLICKED(IDC_MULT, &CDivAndMultDlg::OnBnClickedMult)
END_MESSAGE_MAP()


// CDivAMult 메시지 처리기입니다.

// 나누기 체크	
void CDivAndMultDlg::OnBnClickedDiv()
{
	opt = OPT_DIV;
	btn_MultRadio.SetCheck(false);
}

// 곱셈 체크
void CDivAndMultDlg::OnBnClickedMult()
{
	opt = OPT_MULT;
	btn_DivRadio.SetCheck(false);
}
