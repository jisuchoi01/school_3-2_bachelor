// StressTransformDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "StressTransformDlg.h"
#include "afxdialogex.h"


// CStressTransformDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CStressTransformDlg, CDialogEx)

CStressTransformDlg::CStressTransformDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STRESS_TRANSFORM, pParent)
	, m_iStart(0)
	, m_iEnd(0)
{

}

CStressTransformDlg::~CStressTransformDlg()
{
}

void CStressTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iStart);
	DDV_MinMaxInt(pDX, m_iStart, 0, 255);
	DDX_Text(pDX, IDC_EDIT2, m_iEnd);
	DDV_MinMaxInt(pDX, m_iEnd, 0, 255);
}


BEGIN_MESSAGE_MAP(CStressTransformDlg, CDialogEx)
END_MESSAGE_MAP()


// CStressTransformDlg �޽��� ó�����Դϴ�.
