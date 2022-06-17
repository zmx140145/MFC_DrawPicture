
// DrawPictureView.h: CDrawPictureView 类的接口
//

#pragma once
#include "CMyDlg.h"

class CDrawPictureView : public CView
{
protected: // 仅从序列化创建
	CDrawPictureView() noexcept;
	DECLARE_DYNCREATE(CDrawPictureView)

// 特性
public:
	CDrawPictureDoc* GetDocument() const;
	bool  m_bCurveDrawing;
	CMyDlg Dlg; //创建对话框对象
	CString m_str; //存储对话框传来的控件内容信息
// 操作
public:
	
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDrawPictureView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
private:
	CPoint pStart, pEnd;
	CPoint point;
	int m_nWhich=0;

	CString BmpName;                               //保存图像文件文件名
	CString EntName;                               //保存图像文件扩展名
	CBitmap m_bitmap;                              //创建位图对象
	
	void ShowBmp(CDC* pDC, CString BmpName);    //用来显示指定位图bmp的函数
	

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void On1line();
	afx_msg void On1rect();
	afx_msg void On1cricle();
	afx_msg void On1free();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void On1color();
	afx_msg void On2color();
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void On1delete();

	afx_msg void On1save();
	afx_msg void On1open();

	afx_msg void OnBezier();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // DrawPictureView.cpp 中的调试版本
inline CDrawPictureDoc* CDrawPictureView::GetDocument() const
   { return reinterpret_cast<CDrawPictureDoc*>(m_pDocument); }
#endif

