// LogicalOperationDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "LogicalOperationDlg.h"
#include "afxdialogex.h"


// CLogicalOperationDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLogicalOperationDlg, CDialogEx)

CLogicalOperationDlg::CLogicalOperationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGICAL_OPERATION, pParent)
{

}

CLogicalOperationDlg::~CLogicalOperationDlg()
{
}

void CLogicalOperationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OR, btn_ORRadio);
	DDX_Control(pDX, IDC_XOR, btn_XORRadio);
	DDX_Control(pDX, IDC_NOR, btn_NORRadio);
	DDX_Text(pDX, IDC_EDIT1, i_Constant);
}


BEGIN_MESSAGE_MAP(CLogicalOperationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_OR, &CLogicalOperationDlg::OnBnClickedOr)
	ON_BN_CLICKED(IDC_XOR, &CLogicalOperationDlg::OnBnClickedXor)
	ON_BN_CLICKED(IDC_NOR, &CLogicalOperationDlg::OnBnClickedNor)
END_MESSAGE_MAP()


// CLogicalOperationDlg �޽��� ó�����Դϴ�.


void CLogicalOperationDlg::OnBnClickedOr()
{
	opt = 0;
	btn_XORRadio.SetCheck(FALSE);
	btn_NORRadio.SetCheck(FALSE);
}


void CLogicalOperationDlg::OnBnClickedXor()
{
	opt = 1;
	btn_ORRadio.SetCheck(FALSE);
	btn_NORRadio.SetCheck(FALSE);
}


void CLogicalOperationDlg::OnBnClickedNor()
{
	opt = 2;
	btn_XORRadio.SetCheck(FALSE);
	btn_ORRadio.SetCheck(FALSE);
}
