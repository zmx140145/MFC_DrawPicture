
// DrawPicture.h: DrawPicture 应用程序的主头文件
//
#pragma once
#include<vector>
#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号

typedef struct ENode //边表结点
{
	int xbot;//直线下端点的 x 坐标
	int ytop;//直线上端点的 y 坐标
	double fm;//斜率倒数
	struct ENode * next;//连接下一条边
} EdgeNode, *pEdgeNode;
typedef struct Edge//边表定义
{
	pEdgeNode* base; //表头数组基地址
	int size; //表头数组长度，取决于 ymax
}EdgeTable;
typedef struct aeNode {//活动边结点
	int ytop;//与当前扫描线 yi 相交的边界边的上端点的 y 坐标
	double xi;//当前扫描线 yi 与边界边的交点的 x 坐标
	double fm;//直线斜率倒数
	struct aeNode * next;//连接下一个边
} AENode, *pAENode;
typedef struct Pixel//像素点
{
	int x, y;
	Pixel* next;
} PIXEL;
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
	COLORREF SelectColor;
	EdgeTable* ET;
	Pixel* px;
	pAENode Top;
	//扫描多边形
	void FillPoints(CDC* pDC, PIXEL* pixels, COLORREF color);
	//记录两点之间
	void FillBetweenTwoAet(pAENode top, PIXEL* pixels, int y, CDC* pDC);
	void FreeAE(pAENode top);


	void polygonFill(EdgeTable* ET, pAENode top, PIXEL* pixels, CDC* pDC);
	void UpdateAeNode(pAENode top);
	void DeletAeNode(pAENode* top, int y);
	void SortAENode(pAENode* top);
	int createET(std::vector<CPoint>& points, EdgeTable * ET);

	void DrawPolygon(CDC * pDC, std::vector<CPoint>& points, CBitmap * map);


	//初始化aet
	int initAET(EdgeTable*ET);
	void FreeET(EdgeTable & ET);
	int initET(EdgeTable & ET);
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
	void Bezier_ComputeCoefficients(int n, int* c);
	void drawBezier(CDC * pDC, CPoint * curve, int m, int function, int ControllCount);
	void Bezier2(CPoint * pCtrPs, int nCtrPs, int m, CPoint * curve);
	void Bezier2_CalculateThisRound(float * x, float * y, int * nCtrPs, float t, CPoint * curve);
	void Bezier(CPoint * pCtrPs, int nCtrPs, int m, CPoint *curve);
	void Bezier_ComputePoint(float t, CPoint *pt, int nCtrPs, CPoint * pCtrPs, int *c);
	void DrawDottedLine(CDC * pDC, std::vector<CPoint>& points, COLORREF color, CBitmap * map, CPoint * AnotherPoint, bool DeleteInputFalse);



	
	DECLARE_MESSAGE_MAP()
//	afx_msg void On1rect();
};

extern CDrawPictureApp theApp;


