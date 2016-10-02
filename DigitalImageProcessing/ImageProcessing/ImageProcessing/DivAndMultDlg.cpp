// DivAMult.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DivAndMultDlg.h"
#include "afxdialogex.h"

// CDivAMult ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDivAndMultDlg, CDialogEx)

// ���̾�α� ǥ�� ������
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


// CDivAMult �޽��� ó�����Դϴ�.

// ������ üũ	
void CDivAndMultDlg::OnBnClickedDiv()
{
	opt = OPT_DIV;
	btn_MultRadio.SetCheck(false);
}

// ���� üũ
void CDivAndMultDlg::OnBnClickedMult()
{
	opt = OPT_MULT;
	btn_DivRadio.SetCheck(false);
}
