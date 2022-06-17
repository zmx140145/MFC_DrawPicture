#pragma once


// CMyDlg 对话框

class CMyDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg)

public:
	CMyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDlg();
	//CString m_String;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BEZIERACC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEdit;
	afx_msg void OnClickedOk();
	afx_msg void OnDestroy();
};
