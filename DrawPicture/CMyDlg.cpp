// CMyDlg.cpp: 实现文件
//

#include "pch.h"
#include "DrawPicture.h"
#include "CMyDlg.h"
#include "afxdialogex.h"


// CMyDlg 对话框

IMPLEMENT_DYNAMIC(CMyDlg, CDialog)

CMyDlg::CMyDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BEZIERACC, pParent)
	, m_strEdit(_T(""))
{
	//m_String = _T("");
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BEIZIER, m_strEdit);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_BN_CLICKED(ID_OK, &CMyDlg::OnClickedOk)

	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMyDlg 消息处理程序


void CMyDlg::OnClickedOk()
{
	UpdateData(TRUE);    //用界面内容更新变量
	int size=0;
	for (int i = 0; i < m_strEdit.GetLength(); i++)
	{
		size=size*10+((int)m_strEdit.GetAt(i)-48);
	}
	theApp.m_nSPs = size;
	DestroyWindow();
	

}





void CMyDlg::OnDestroy()
{
	CDialog::OnDestroy();
	delete this;
	// TODO: 在此处添加消息处理程序代码
}
