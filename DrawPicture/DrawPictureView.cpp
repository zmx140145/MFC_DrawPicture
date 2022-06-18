
// DrawPictureView.cpp: CDrawPictureView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DrawPicture.h"
#endif

#include "DrawPictureDoc.h"
#include "DrawPictureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define boxlength 1000
#define boxwidth 500

// CDrawPictureView

IMPLEMENT_DYNCREATE(CDrawPictureView, CView)

BEGIN_MESSAGE_MAP(CDrawPictureView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_1Line, &CDrawPictureView::On1line)
	ON_COMMAND(ID_1Rect, &CDrawPictureView::On1rect)
	ON_COMMAND(ID_1Cricle, &CDrawPictureView::On1cricle)
	ON_COMMAND(ID_1Free, &CDrawPictureView::On1free)
//	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_1Color, &CDrawPictureView::On1color)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_2Color, &CDrawPictureView::On2color)
//	ON_WM_RBUTTONDOWN()
//	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_1Delete, &CDrawPictureView::On1delete)
	ON_COMMAND(ID_1Save, &CDrawPictureView::On1save)
	ON_COMMAND(ID_1OPen, &CDrawPictureView::On1open)
	
	ON_COMMAND(ID_Bezier, &CDrawPictureView::OnBezier)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_POLYGON, &CDrawPictureView::OnPolygon)
END_MESSAGE_MAP()

// CDrawPictureView 构造/析构

CDrawPictureView::CDrawPictureView() noexcept
{
	m_bCurveDrawing = false;

	// TODO: 在此处添加构造代码

}

CDrawPictureView::~CDrawPictureView()
{
	
}

BOOL CDrawPictureView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawPictureView 绘图

void CDrawPictureView::OnDraw(CDC* pDC)
{
	CDrawPictureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect r;	//创建矩形类对象
	GetClientRect(&r);	//获得显示窗口大小
	int x = r.right / 2;
	int y = r.bottom / 2;	//显示字符的起始点
	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);	//文本内容居中
	pDC->TextOut(x, y, m_str); //输出文本

	if (m_nWhich == 4) //自由画线
	{
		pEnd = point;

		CPen newPen;
		newPen.CreatePen(PS_SOLID, 3, theApp.SelectColor);
		pDC->SelectObject(newPen);

		int nLen = pDoc->m_aCurvePnts.GetCount();
		if (nLen > 0)
			pDC->MoveTo(pDoc->m_aCurvePnts[0]);
		for (int i = 1; i < nLen; i++)
		{
			pDC->LineTo(pDoc->m_aCurvePnts[i]);
		}


	}

	if (EntName.Compare(_T("bmp")) == 0)      //bmp格式
	{
		ShowBmp(pDC, BmpName);               //显示图片
	}
	
	// TODO: 在此处为本机数据添加绘制代码
}


// CDrawPictureView 打印

BOOL CDrawPictureView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawPictureView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawPictureView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDrawPictureView 诊断

#ifdef _DEBUG
void CDrawPictureView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawPictureView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawPictureDoc* CDrawPictureView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawPictureDoc)));
	return (CDrawPictureDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawPictureView 消息处理程序


void CDrawPictureView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pStart = point;
	CDrawPictureDoc* pDoc = GetDocument();
	pDoc->m_aCurvePnts.RemoveAll();  //清除上一次的曲线点集数据
	m_bCurveDrawing = true;
	CView::OnLButtonDown(nFlags, point);
}


void CDrawPictureView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bCurveDrawing = false;

	if (m_nWhich == 1)	//直线
	{
	pEnd = point;
	CDC* pDC = GetDC();
	/*pDC->MoveTo(pStart);
	pDC->LineTo(pEnd);*/
	theApp.DRHLine(pDC, pStart.x, pStart.y, pEnd.x, pEnd.y, theApp.SelectColor);
	ReleaseDC(pDC);
	CView::OnLButtonUp(nFlags, point);
	}
	if (m_nWhich == 2)	//矩形
	{
		pEnd = point;
		CDC* pDC = GetDC();
		theApp.DRHLineDrawRect(pDC, pStart.x, pStart.y, pEnd.x, pEnd.y, theApp.SelectColor, false);
		ReleaseDC(pDC);
		CView::OnLButtonUp(nFlags, point);
	}

	if (m_nWhich == 3)	//圆
	{
		pEnd = point;
		CDC* pDC = GetDC();
		float l = 0.5*sqrt((pStart.x - pEnd.x)*(pStart.x - pEnd.x)+ (pStart.y - pEnd.y)*(pStart.y - pEnd.y));
		int r = (int)l;
		if (l - r>=0.5)
		{
			r++;
		}
		theApp.BRHCircle(pDC, (pStart.x + pEnd.x)/ 2, (pStart.y + pEnd.y)/ 2, r, theApp.SelectColor,false);
		ReleaseDC(pDC);
		CView::OnLButtonUp(nFlags, point);
	}

	
	

	if (m_nWhich == 5) // 填充矩形
	{
		
		pEnd = point;
		CDC* pDC = GetDC();
		theApp.DRHLineDrawRect(pDC, pStart.x, pStart.y, pEnd.x, pEnd.y, theApp.SelectColor, true);
		ReleaseDC(pDC);
		CView::OnLButtonUp(nFlags, point);
	}

	if (m_nWhich == 6) // 填充圆
	{

		pEnd = point;
		CDC* pDC = GetDC();
		float l = 0.5*sqrt((pStart.x - pEnd.x)*(pStart.x - pEnd.x) + (pStart.y - pEnd.y)*(pStart.y - pEnd.y));
		int r = (int)l;
		if (l - r >= 0.5)
		{
			r++;
		}
		theApp.BRHCircle(pDC, (pStart.x + pEnd.x) / 2, (pStart.y + pEnd.y) / 2, r, theApp.SelectColor, true);
		ReleaseDC(pDC);
		CView::OnLButtonUp(nFlags, point);
	}

	if (m_nWhich == 7)	//清空
	{
		CDC* pDC = GetDC();
		ReleaseDC(pDC);
		CView::OnLButtonUp(nFlags, point);
	}
	if (m_nWhich == 8)	//画贝塞尔曲线
	{
		if (LastClickLBTime != NULL)
		{
			if (GetCurrentTime() - LastClickLBTime < 350)
			{
				return;
			}
		}
		
		
			//如果是第一个控制点 或者没有记录位图
		LastClickLBTime = GetCurrentTime();
		CDC* pDC = GetDC();
		//如果还没有点记录 那么就是起点 那么就先保存一份当前画面 便于撤回
		if (m_LastBitMap==NULL||theApp.m_nCtrPs == 0)
		{
			if (m_LastBitMap != NULL)
			{
				delete m_LastBitMap;
			}
			m_LastBitMap = new CBitmap();
			CDC tempDC;
			CRect rect;
			GetClientRect(&rect);
			tempDC.CreateCompatibleDC(pDC);
			m_LastBitMap->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
			tempDC.SelectObject(m_LastBitMap);
			tempDC.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
			tempDC.DeleteDC();
		}
		//加点数目
		theApp.m_nCtrPs++;
		//把点加到vector里面
		theApp.PointsVec.push_back(point);
		//画虚线
		theApp.DrawDottedLine(pDC, theApp.PointsVec, RGB(255, 0, 255), m_LastBitMap,NULL,true);
		ReleaseDC(pDC);
		CView::OnLButtonUp(nFlags, point);
	}
	if (m_nWhich == 9)	//画自定义多边形
	{
		if (LastClickLBTime != NULL)
		{
			if (GetCurrentTime() - LastClickLBTime < 350)
			{
				return;
			}
		}
        //如果是第一个控制点 或者没有记录位图
		LastClickLBTime = GetCurrentTime();
		CDC* pDC = GetDC();
		//如果还没有点记录 那么就是起点 那么就先保存一份当前画面 便于撤回
		if (m_LastBitMap == NULL || theApp.PointsVec.size() == 0)
		{
			if (m_LastBitMap != NULL)
			{
				delete m_LastBitMap;
			}
			m_LastBitMap = new CBitmap();
			CDC tempDC;
			CRect rect;
			GetClientRect(&rect);
			tempDC.CreateCompatibleDC(pDC);
			m_LastBitMap->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
			tempDC.SelectObject(m_LastBitMap);
			tempDC.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
			tempDC.DeleteDC();
		}
		//把点加到vector里面
		theApp.PointsVec.push_back(point);
		//画虚线
		theApp.DrawDottedLine(pDC, theApp.PointsVec, RGB(255, 0, 255), m_LastBitMap, NULL, true);
		ReleaseDC(pDC);
		CView::OnLButtonUp(nFlags, point);
	}
	
	CView::OnLButtonUp(nFlags, point);
}
void CDrawPictureView::WhichChange()
{
	//在m_nWhich切换前调用 说明现在的m_nWhich还是上一个的状态
	if (m_nWhich== 8)
	{
		theApp.PointsVec.clear();
	}
	if (m_nWhich == 9)
	{
		theApp.PointsVec.clear();
	}
}
void CDrawPictureView::OnMouseMove(UINT nFlags, CPoint point)
{

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDrawPictureDoc* pDoc = GetDocument();
	if (m_bCurveDrawing)
	{
		pDoc->m_aCurvePnts.Add(point);   //点集数组中加入一点
		Invalidate(false);
	}
	if (m_nWhich == 8)	//画贝塞尔曲线
	{
		if (theApp.m_nCtrPs != 0)
		{
			CDC* pDC = GetDC();
			//画虚线并且连接鼠标
			theApp.DrawDottedLine(pDC, theApp.PointsVec, RGB(255, 0, 255), m_LastBitMap, &point,true);
			ReleaseDC(pDC);
		}
		
	}
	if (m_nWhich == 9)	//画自定义多边形
	{
		if (!theApp.PointsVec.empty())
		{
			CDC* pDC = GetDC();
			//画虚线并且连接鼠标
			theApp.DrawDottedLine(pDC, theApp.PointsVec, RGB(255, 0, 255), m_LastBitMap, &point, true);
			ReleaseDC(pDC);
		}

	}
}
//左键双击
void CDrawPictureView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_nWhich == 8)	//画贝塞尔曲线
	{
		CDC* pDC = GetDC();
		//保证有一定大小
		if (theApp.m_nSPs < 100)
		{
			theApp.m_nSPs = 100;
		}
		theApp.InitBezier();
		theApp.DrawDottedLine(pDC, theApp.PointsVec, RGB(255, 0, 255), m_LastBitMap, NULL, false);
		theApp.drawBezier(pDC, theApp.m_curve, theApp.m_nSPs, 1, theApp.m_nCtrPs);
		ReleaseDC(pDC);
		return;
	}
	if (m_nWhich == 9)	//画多边形
	{
		CDC* pDC = GetDC();
        theApp.DrawDottedLine(pDC, theApp.PointsVec, RGB(255, 0, 255), m_LastBitMap, NULL, false);
		theApp.DrawPolygon(pDC, theApp.PointsVec,m_LastBitMap);
        ReleaseDC(pDC);
		return;
	}
	CView::OnLButtonDblClk(nFlags, point);
}
//右键
void CDrawPictureView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_nWhich == 8)	//画贝塞尔曲线
	{
		if (!theApp.PointsVec.empty())
		{
			theApp.PointsVec.pop_back();
			theApp.m_nCtrPs--;
			CDC* pDC = GetDC();
			//保证有一定大小
			if (theApp.m_nSPs < 100)
			{
				theApp.m_nSPs = 100;
			}
			if (theApp.m_nCtrPs >= 1)
			{
				theApp.DrawDottedLine(pDC, theApp.PointsVec, RGB(255, 0, 255), m_LastBitMap, &point, true);
			}
			else
			{
				theApp.DrawDottedLine(pDC, theApp.PointsVec, RGB(255, 0, 255), m_LastBitMap, NULL, false);
			}


			ReleaseDC(pDC);
			return;
		}
	}
	if (m_nWhich == 9)	//画多边形
	{
		if (!theApp.PointsVec.empty())
		{
			theApp.PointsVec.pop_back();
			CDC* pDC = GetDC();
			//保证有一定大小
			if (theApp.PointsVec.size() >= 1)
			{
				theApp.DrawDottedLine(pDC, theApp.PointsVec, RGB(255, 0, 255), m_LastBitMap, &point, true);
			}
			else
			{
				theApp.DrawDottedLine(pDC, theApp.PointsVec, RGB(255, 0, 255), m_LastBitMap, NULL, false);
			}


			ReleaseDC(pDC);
			return;
		}
	}
	CView::OnRButtonUp(nFlags, point);
}
//菜单按键
void CDrawPictureView::On1line()
{
	WhichChange();
	m_nWhich = 1;
	Invalidate(false);
	// TODO: 在此添加命令处理程序代码
}
void CDrawPictureView::On1rect()
{
	WhichChange();
	m_nWhich = 2;	
	Invalidate(false);
	// TODO: 在此添加命令处理程序代码
}
void CDrawPictureView::On1cricle()
{
	WhichChange();
	m_nWhich = 3;
	Invalidate(false);
	// TODO: 在此添加命令处理程序代码
}
void CDrawPictureView::On1free()
{
	WhichChange();
	m_nWhich = 4;
	Invalidate(false);
	// TODO: 在此添加命令处理程序代码
}

void CDrawPictureView::On1color()
{
	WhichChange();
	m_nWhich = 5;
	Invalidate(false);
	// TODO: 在此添加命令处理程序代码
}

void CDrawPictureView::On2color()
{
	WhichChange();
	m_nWhich = 6;
	Invalidate(false);
	// TODO: 在此添加命令处理程序代码
}



void CDrawPictureView::On1delete()
{
	WhichChange();
	m_nWhich = 7;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}
//贝塞尔曲线按键
void CDrawPictureView::OnBezier()
{
	WhichChange();
	m_nWhich = 8;
	Invalidate(false);
	// TODO: 在此添加命令处理程序代码
}
//自定义多边形按键
void CDrawPictureView::OnPolygon()
{
	WhichChange();
	m_nWhich = 9;
	Invalidate(false);
	// TODO: 在此添
}

void CDrawPictureView::On1save()
{
	CClientDC dc(this);
	CRect rect;
	//GetClientRect(&rect);  //获取画布大小
	rect.left = 0;
	rect.right = boxlength;//boxlength为宏定义
	rect.top = 0;
	rect.bottom = boxwidth;
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);
	//创建位图
	HDC hdc = CreateCompatibleDC(dc);      //创建DC，以便将图像保存为不同的格式
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);
	//将位图选入DC，并保存返回值 
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);
	//将屏幕DC的图像复制到内存DC中
	CImage image;
	image.Attach(hbitmap); //将位图转化为一般图像
	CString saveFilePath;
	{
		CString  strFilter = _T("位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|GIF图像文件 |*.gif| PNG图像文件 |*.png|其他格式(*.*)| *.* ||");
		CFileDialog dlg(FALSE, _T("bmp"), _T("Picture01.bmp"), NULL, strFilter);
		if (dlg.DoModal() != IDOK)
			return;
		CString strFileName; //文件扩展名
		CString strExtension;
		strFileName = dlg.m_ofn.lpstrFile;
		if (dlg.m_ofn.nFileExtension == 0)
		{
			switch (dlg.m_ofn.nFilterIndex)
			{
			case 1:
				strExtension = "bmp"; break;
			case 2:
				strExtension = "jpg"; break;
			case 3:
				strExtension = "gif"; break;
			case 4:
				strExtension = "png"; break;
			default:
				break;
			}
			strFileName = strFileName + "." + strExtension;
		}
		saveFilePath = strFileName;
	}
	HRESULT hResult = image.Save(saveFilePath);     //保存图像
	image.Detach();
	SelectObject(hdc, hOldMap);

	// TODO: 在此添加命令处理程序代码
}



void CDrawPictureView::On1open()
{
	//四种格式的文件：bmp gif jpg tiff
	CString filter;
	filter = "所有文件(*.bmp,*.jpg,*.gif,*tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg| GIF(*.gif)|*.gif| TIFF(*.tiff)|*.tiff||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);
	//按下确定按钮 dlg.DoModal() 函数显示对话框
	if (dlg.DoModal() == IDOK)
	{
		BmpName = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp
		EntName = dlg.GetFileExt();      //获取文件扩展名
		EntName.MakeLower();             //将文件扩展名转换为一个小写字符
		Invalidate();                    //调用该函数就会调用OnDraw重绘画图
	}
	
	// TODO: 在此添加命令处理程序代码
}

void CDrawPictureView::ShowBmp(CDC* pDC, CString BmpName)
{
	//定义bitmap指针 调用函数LoadImage装载位图
	HBITMAP m_hBitmap;
	m_hBitmap = (HBITMAP)LoadImage(NULL, BmpName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);

	if (m_bitmap.m_hObject)
	{
		m_bitmap.Detach();           //切断CWnd和窗口联系
	}
	m_bitmap.Attach(m_hBitmap);      //将句柄HBITMAP m_hBitmap与CBitmap m_bitmap关联

	//边界
	CRect rect;
	GetClientRect(&rect);

	//图片显示(x,y)起始坐标
	int m_showX = 0;
	int m_showY = 0;
	int m_nWindowWidth = rect.right - rect.left;   //计算客户区宽度
	int m_nWindowHeight = rect.bottom - rect.top;  //计算客户区高度

	//定义并创建一个内存设备环境DC
	CDC dcBmp;
	if (!dcBmp.CreateCompatibleDC(pDC))   //创建兼容性的DC
		return;

	BITMAP m_bmp;                          //临时bmp图片变量
	m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中

	CBitmap* pbmpOld = NULL;
	dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境

	//图片显示调用函数stretchBlt
	pDC->StretchBlt(0, 0, m_bmp.bmWidth, m_bmp.bmHeight, &dcBmp, 0, 0, m_bmp.bmWidth, m_bmp.bmHeight, SRCCOPY);

	
	dcBmp.SelectObject(pbmpOld);           //恢复临时DC的位图
	DeleteObject(&m_bitmap);               //删除内存中的位图
	dcBmp.DeleteDC();                      //删除CreateCompatibleDC得到的图片DC
}










void CDrawPictureView::OnDestroy()
{
	CView::OnDestroy();
	if (m_LastBitMap)
	{
		delete m_LastBitMap;
	}
	
	// TODO: 在此处添加消息处理程序代码
}





