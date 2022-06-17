
// DrawPicture.h: DrawPicture 应用程序的主头文件
//
#pragma once
#include<vector>
#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CDrawPictureApp:
// 有关此类的实现，请参阅 DrawPicture.cpp
//

class CDrawPictureApp : public CWinApp
{
public:
	CDrawPictureApp() noexcept;

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();



	//变量
	COLORREF SelectColor;


// 实现
	afx_msg void OnAppAbout();
	//dda画直线函数
	void DDALine(CDC * pDC, int x0, int y0, int x1, int y1, COLORREF color);
	void BRHCircle(CDC * pDC, int x0, int y0, int r, COLORREF color, bool isSoild);
	void DRHLineDrawRect(CDC * pDC, int x, int y, int x1, int y1, COLORREF color, bool isSoild);
    void CirclePointDraw(CDC * pDC, int x0, int y0, int x, int y, COLORREF color);
	void CirclePointSoildDraw(CDC * pDC, int x0, int y0, int x, int y, COLORREF color);
    //drH画直线函数
	void DRHLine(CDC * pDC, int x0, int y0, int x1, int y1, COLORREF color);
	/*----------------关于贝塞尔-------------------*/
	int m_nCtrPs = 0;//（控制点数目）
	int m_nSPs=0;//（采样点数目），
	std::vector<CPoint> PointsVec;
	CPoint *m_pCtrPs = NULL; // （控制点坐标），
	CPoint *m_curve = NULL; //（全部采样点坐标）。
	//记录两点之间
	int InitBezier();
	void computeCoefficients(int n, int* c);
	void drawBezier(CDC * pDC, CPoint * curve, int m, int function, int ControllCount);
	void Bezier2(CPoint * pCtrPs, int nCtrPs, int m, CPoint * curve);
	void Bezier2_CalculateThisRound(float * x, float * y, int * nCtrPs, float t, CPoint * curve);
	void Bezier(CPoint * pCtrPs, int nCtrPs, int m, CPoint *curve);
	void computePoint(float t, CPoint *pt, int nCtrPs, CPoint * pCtrPs, int *c);
	DECLARE_MESSAGE_MAP()
//	afx_msg void On1rect();
};

extern CDrawPictureApp theApp;


