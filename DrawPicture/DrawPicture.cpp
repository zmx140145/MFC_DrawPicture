
// DrawPicture.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "DrawPicture.h"
#include "MainFrm.h"

#include "DrawPictureDoc.h"
#include "DrawPictureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawPictureApp

BEGIN_MESSAGE_MAP(CDrawPictureApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CDrawPictureApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
//	ON_COMMAND(ID_1Rect, &CDrawPictureApp::On1rect)
END_MESSAGE_MAP()


// CDrawPictureApp 构造

CDrawPictureApp::CDrawPictureApp() noexcept
{

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("DrawPicture.AppID.NoVersion"));

	// TODO:  在此处添加构造代码，

	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CDrawPictureApp 对象

CDrawPictureApp theApp;


// CDrawPictureApp 初始化

BOOL CDrawPictureApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDrawPictureDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CDrawPictureView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CDrawPictureApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CDrawPictureApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_DIALOG1)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CDrawPictureApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
//画直线DRH
void CDrawPictureApp::DRHLine(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF color)
{

	// TODO: 在此处添加实现代码.
	int x, y, dx, dy, d, d1, d2;
	int solution;
	dx = x1 - x0;
	dy = y1 - y0;
	//1是 0<k<1 
	//2是k>1 
	//3是 0>k>-1 
	//4是 k<-1
	float k = (float)dy / dx;
	if (k >= 0)
	{
		if (k > 1)
		{
			solution = 2;

		}
		else
		{
			solution = 1;

		}
		if (x1 < x0)
		{
			int tempx;
			int tempy;
			tempx = x1;
			tempy = y1;
			x1 = x0;
			y1 = y0;
			x0 = tempx;
			y0 = tempy;

		}
	}
	else
	{
		if (k < -1)
		{
			solution = 4;

		}
		else
		{
			solution = 3;
		}

		if (x1 < x0)
		{
			int tempx;
			int tempy;
			tempx = x1;
			tempy = y1;
			x1 = x0;
			y1 = y0;
			x0 = tempx;
			y0 = tempy;

		}
		y1 = 2 * y0 - y1;
	}
	dx = x1 - x0;
	dy = y1 - y0;
	switch (solution)
	{
	case 1:
	{
		d = 2 * dy - dx;
		d1 = 2 * dy;
		d2 = 2 * (dy - dx);
		x = x0;
		y = y0;
		pDC->SetPixel(x, y, color);
		while (x < x1)
		{
			x++;
			if (d < 0)
			{
				d += d1;
			}
			else
			{
				y += 1;
				d += d2;
			}
			pDC->SetPixel(x, y, color);
		}
		break;
	}
	case 2:
	{
		d = 2 * dx - dy;
		d1 = 2 * dx;
		d2 = 2 * (dx - dy);
		x = x0;
		y = y0;
		pDC->SetPixel(x, y, color);
		while (y < y1)
		{
			y++;
			if (d < 0)
			{
				d += d1;
			}
			else
			{
				x += 1;
				d += d2;
			}
			pDC->SetPixel(x, y, color);
		}
		break;
	}
	case 3:
	{
		d = 2 * dy - dx;
		d1 = 2 * dy;
		d2 = 2 * (dy - dx);
		x = x0;
		y = y0;

		pDC->SetPixel(x, 2 * y0 - y, color);
		while (x < x1)
		{
			x++;
			if (d < 0)
			{
				d += d1;
			}
			else
			{
				y += 1;
				d += d2;
			}
			pDC->SetPixel(x, 2 * y0 - y, color);
		}

		break;
	}
	case 4:
	{
		d = 2 * dx - dy;
		d1 = 2 * dx;
		d2 = 2 * (dx - dy);
		x = x0;
		y = y0;
		pDC->SetPixel(x, 2 * y0 - y, color);
		while (y < y1)
		{
			y++;
			if (d < 0)
			{
				d += d1;
			}
			else
			{
				x += 1;
				d += d2;
			}
			pDC->SetPixel(x, 2 * y0 - y, color);
		}
		break;
	}
	default:
		break;
	}

}
//画直线DDA
void CDrawPictureApp::DDALine(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF color)
{
	int dm = 0;
	if (abs(x1 - x0) >= abs(y1 - y0))
	{
		dm = abs(x1 - x0);
	}
	else
	{
		dm = abs(y1 - y0);
	}
	float dx = (float)(x1 - x0) / dm;
	float dy = (float)(y1 - y0) / dm;
	float x = x0;
	float y = y0;
	for (int i = 0; i < dm; i++)
	{
		pDC->SetPixel((int)(x + 0.5), (int)(y + 0.5), color);
		x += dx;
		y += dy;
	}
}
//画矩形
void CDrawPictureApp::DRHLineDrawRect(CDC* pDC, int x, int y, int x1, int y1, COLORREF color, bool isSoild)
{

	int *minX, *maxX, *minY, *maxY;
	if (x < x1)
	{
		minX = &x;
		maxX = &x1;
	}
	else
	{
		minX = &x1;
		maxX = &x;
	}
	if (y < y1)
	{
		minY = &y;
		maxY = &y1;
	}
	else
	{
		minY = &y1;
		maxY = &y;
	}
	if (isSoild)
	{
		CDC temp;
		CBitmap map;
		CRect rect;
		temp.CreateCompatibleDC(pDC);
		CView *pView = ((CFrameWndEx *)m_pMainWnd)->GetActiveView();
		pView->GetClientRect(&rect);
		map.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		CBitmap *pOldBit = temp.SelectObject(&map);

		for (int i = *minY; i <= *maxY; i++)
		{
			DRHLine(&temp, *minX, i, *maxX, i, color);
		}
		pDC->BitBlt(*minX, *minY, *maxX - *minX, *maxY - *minY, &temp, *minX, *minY, SRCCOPY);
		map.DeleteObject();
		temp.DeleteDC();
	}
	else
	{
		DRHLine(pDC, *minX, *minY, *minX, *maxY, color);
		DRHLine(pDC, *maxX, *minY, *maxX, *maxY, color);
		DRHLine(pDC, *minX, *minY, *maxX, *minY, color);
		DRHLine(pDC, *minX, *maxY, *maxX, *maxY, color);
	}

}
//画圆用半径和圆心
void CDrawPictureApp::BRHCircle(CDC* pDC, int x0, int y0, int r, COLORREF color,bool isSoild)
{
	// TODO: 在此处添加实现代码.
	int x, y, d;
	x = 0;
	y = (int)r;
	d = int(3 - 2 * r);
		CDC temp;
		CBitmap map;
		CRect rect;
		temp.CreateCompatibleDC(pDC);
		CView *pView = ((CFrameWndEx *)m_pMainWnd)->GetActiveView();
		pView->GetClientRect(&rect);
		map.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		CBitmap *pOldBit = temp.SelectObject(&map);
		COLORREF BackgroundColor;
		if (color != RGB(255, 0, 0))
		{
			BackgroundColor = RGB(255, 0, 0);
 	   }
		else
		{
			BackgroundColor = RGB(0, 255, 0);
		}
		temp.FillSolidRect(0, 0, rect.Width(), rect.Height(), BackgroundColor);
	while (x < y)
	{
		if (isSoild)
		{
			CirclePointSoildDraw(&temp, x0, y0, x, y, color);
		}
		else
		{
			CirclePointDraw(pDC, x0, y0, x, y, color);
		}
		if (d < 0)
		{
			d += 4 * x + 6;
		}
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
	if (x == y)
	{
		if (isSoild)
		{
			CirclePointSoildDraw(&temp, x0, y0, x, y, color);
		}
		else
		{
			CirclePointDraw(pDC, x0, y0, x, y, color);
		}
		
	}
	if (isSoild)
	{
		TransparentBlt(pDC->m_hDC, 0, 0, rect.Width() ,rect.Height() , temp.m_hDC, 0, 0, rect.Width(), rect.Height(),BackgroundColor);
		/*pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &temp, 0, 0, SRCCOPY);*/
	}
	
}
//画圆用两个最远点
void CDrawPictureApp::CirclePointDraw(CDC* pDC, int x0, int y0, int x, int y, COLORREF color)
{
	// TODO: 在此处添加实现代码.
	pDC->SetPixel(x0 + x, y0 + y, color);
	pDC->SetPixel(x0 + y, y0 + x, color);
	pDC->SetPixel(x0 - y, y0 + x, color);
	pDC->SetPixel(x0 - x, y0 + y, color);
	pDC->SetPixel(x0 - x, y0 - y, color);
	pDC->SetPixel(x0 - y, y0 - x, color);
	pDC->SetPixel(x0 + y, y0 - x, color);
	pDC->SetPixel(x0 + x, y0 - y, color);
}
//画实心的圆
void CDrawPictureApp::CirclePointSoildDraw(CDC* pDC, int x0, int y0, int x, int y, COLORREF color)
{
	// TODO: 在此处添加实现代码.
	DRHLine(pDC, x0 + x, y0 + y, x0 + x, y0 - y, color);
	DRHLine(pDC, x0 + y, y0 + x, x0 + y, y0 - x, color);
	DRHLine(pDC, x0 - x, y0 + y, x0 - x, y0 - y, color);
	DRHLine(pDC, x0 - y, y0 + x, x0 - y, y0 - x, color);

}
//根据全局变量中的控制点数和采样点数来分配空间初始化
int CDrawPictureApp::InitBezier()
{
	
	if (m_nCtrPs == 0 || m_nSPs == 0)
	{
		m_pCtrPs = NULL;
		m_curve = NULL;
		return 0;
	}
	m_pCtrPs = new CPoint[m_nCtrPs + 1]();
	m_curve = new CPoint[m_nSPs + 1]();
	for (int i = 0; i < m_nCtrPs; i++)
	{
		m_pCtrPs[i].x = PointsVec.at(i).x;
		m_pCtrPs[i].y = PointsVec.at(i).y;
	}
	return 1;
}
//贝塞尔曲线调用函数 function 1是定义法 2是画图法
void CDrawPictureApp::drawBezier(CDC * pDC, CPoint * curve, int m, int function, int ControllCount)
{
	if (function == 1)
	{
		Bezier(m_pCtrPs, ControllCount, m, curve);
	}
	else
	{
		Bezier2(m_pCtrPs, ControllCount, m, curve);
	}
	for (int i = 0; i <= m; i++)
	{
		pDC->SetPixel(curve[i], SelectColor);
	}
	delete[] curve;
	delete[] m_pCtrPs;
	PointsVec.clear();
	m_nCtrPs = 0;
}
//画图法贝塞尔曲线
void CDrawPictureApp::Bezier2(CPoint * pCtrPs, int nCtrPs, int m, CPoint * curve)
{
	//m 个采样点，结果保存在 curve 所指的数组里面
	float* x1 = new float[nCtrPs];
	float* y1 = new float[nCtrPs];
	int n;
	for (int j = 0; j <= m; j++)
	{

		for (int i = 0; i < nCtrPs; i++)
		{
			x1[i] = pCtrPs[i].x;
			y1[i] = pCtrPs[i].y;
		}
		n = m_nCtrPs;
		Bezier2_CalculateThisRound(x1, y1, &n, j / (float)m, &curve[j]);

	}
	delete[] x1;
	delete[] y1;
}
//配合画图法贝塞尔曲线的递归算法
void CDrawPictureApp::Bezier2_CalculateThisRound(float* x, float*y, int* nCtrPs, float t, CPoint* curve)
{
	for (int i = 0; i < *nCtrPs - 1; i++)
	{
		x[i] = x[i] + (x[i + 1] - x[i])*t;
		y[i] = y[i] + (y[i + 1] - y[i])*t;
	}
	(*nCtrPs)--;
	if (*nCtrPs <= 1)
	{
		curve->x = x[0];
		curve->y = y[0];
		return;
	}
	else
	{
		return Bezier2_CalculateThisRound(x, y, nCtrPs, t, curve);
	}
}
//定义法贝塞尔曲线
void CDrawPictureApp::Bezier(CPoint * pCtrPs, int nCtrPs, int m, CPoint * curve)
{
	//m 个采样点，结果保存在 curve 所指的数组里面
	int i;
	int *pC = (int *)malloc(nCtrPs * sizeof(int)); //分配系数的存储空间
	Bezier_ComputeCoefficients(nCtrPs - 1, pC);
	for (i = 0; i <= m; i++)
		Bezier_ComputePoint(i / (float)m, &curve[i], nCtrPs, pCtrPs, pC);
	free(pC);

}
//定义法计算每个t对应的基底
void CDrawPictureApp::Bezier_ComputeCoefficients(int n, int * c)
{
	//n 为控制点数目，c 为存储空间的首地址，存储内容为系数
	{
		int k, i;
		for (k = 0; k <= n; k++)
		{
			c[k] = 1;
			for (i = n; i >= k + 1; i--) /*求 c[k]=n*(n-1)…(k+1) */
				c[k] *= i;
			for (i = n - k; i >= 2; i--) /*求 c[k]/(n-k)!*/
				c[k] /= i;
		}
	}
}
//计算定义法的每一个采样点的值
void CDrawPictureApp::Bezier_ComputePoint(float t, CPoint * pt, int nCtrPs, CPoint * pCtrPs, int * c)
{
	//pt 为所求点，nCtrPs 为控制点数目，pCtrPs 为存储控制点坐标的空间首地址
	int i, n = nCtrPs - 1;
	float blend, t1 = 1 - t; //基函数的值
	pt->x = 0.0;
	pt->y = 0.0;
	for (i = 0; i <= n; i++)
	{
		blend = c[i] * powf(t, i)*powf(t1, n - i); /*求 C i
		n ti
		(1-t)n-i
		*/
		pt->x += pCtrPs[i].x*blend; /*求 x(t)*/
		pt->y += pCtrPs[i].y*blend; /*求 y(t)*/
	}

}
//画虚线
void CDrawPictureApp::DrawDottedLine(CDC* pDC, std::vector<CPoint>& points, COLORREF color, CBitmap* map,CPoint* AnotherPoint,bool DeleteInputFalse)
{
	//先填充背景
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	CDrawPictureView* pView = (CDrawPictureView*)pFrame->GetActiveView();
	CRect rect;
	CDC tempDC;
	pView->GetClientRect(&rect);
	tempDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = tempDC.SelectObject(map);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &tempDC, 0, 0, SRCCOPY);
	if (DeleteInputFalse)
	{
		////创建画笔
		CPen pen(PS_DASH, 1, RGB(255, 0, 255));
		CPen* pOldPen = pDC->SelectObject(&pen);
		if (points.size() == 1)
		{
			if (AnotherPoint != NULL)
			{
				pDC->MoveTo(points[0]);
				//画线 
				pDC->LineTo(*AnotherPoint);
			}
			
		}
		for (int i = 0; i < points.size() - 1; i++)
		{

			pDC->MoveTo(points[i]);
			//画线 
			pDC->LineTo(points[i + 1]);
			if (i == points.size() - 2)
			{
				if (AnotherPoint != NULL)
				{
					pDC->MoveTo(points[i + 1]);
					pDC->LineTo(*AnotherPoint);
				}
			}
		}
		pDC->SelectObject(pOldPen);
	}
	tempDC.DeleteDC();
}
//扫描多边形
void CDrawPictureApp::FreeET(EdgeTable & ET)
{
	pEdgeNode pCur;
	if (ET.base)
	{
		for (int i = 0; i < ET.size; i++)
		{
			while (ET.base[i])
			{
				pCur = ET.base[i];
				ET.base[i] = ET.base[i]->next;
				free(pCur);
			}
		}
	}
	delete[] ET.base;
}
//释放AE节点并保证其连续性
void CDrawPictureApp::FreeAE(pAENode top)
{
	pAENode pCur;
	while (top)
	{
		pCur = top;
		top = top->next;
		free(pCur);
	}
}
//初始化ET表
int CDrawPictureApp::initET(EdgeTable & ET)
{
	FreeET(ET);
	int cy = 1001;
	ET.base = new pEdgeNode[cy];
	ET.size = cy;
	for (int i = 0; i < ET.size; i++)
	{
		ET.base[i] = NULL;
	}
	return 1;
}
//初始化活动边表
int CDrawPictureApp::initAET(EdgeTable * ET)
{
	if (!ET)
	{
		return -1;
	}
	int i = 0;
	while (ET->base[i] == NULL && i < ET->size)
	{
		i++;
	}
	return i;
}
//填充点的集合
void CDrawPictureApp::FillPoints(CDC * pDC, PIXEL * pixels, COLORREF color)
{
	PIXEL* pCur = pixels;
	while (pCur)
	{
		pDC->SetPixel(pCur->x, pCur->y, color);
		pCur = pCur->next;
	}
}
//两点之间的填充
void CDrawPictureApp::FillBetweenTwoAet(pAENode top, PIXEL * pixels, int y, CDC* pDC)
{

	bool second = false;
	int x;
	pAENode pCur = top;
	while (pCur)
	{
		if (second)
		{
			for (; x < (int)(pCur->xi + 0.5); x++)
			{
				PIXEL* pX = pixels;
				pixels = new PIXEL{ x,y,pX };
			}
			second = false;
		}
		else
		{
			x = (int)(pCur->xi + 0.5);
			second = true;
		}
		pCur = pCur->next;
	}
	FillPoints(pDC, pixels, SelectColor);
	PIXEL* pP;
	while (pixels)
	{
		pP = pixels;
		pixels = pixels->next;
		free(pP);

	}
}
//多边形填充
void CDrawPictureApp::polygonFill(EdgeTable* ET, pAENode top, PIXEL* pixels, CDC* pDC)
{
	int y = initAET(ET);
	while (y < ET->size)
	{
		//先让不是新的节点全部更新 就是自己的x坐标要相应改变
		UpdateAeNode(top);
		pEdgeNode pCur = ET->base[y];
		pAENode pPre = top;
		//把新的边加到aen中
		while (pCur)
		{
			top = new AENode{ pCur->ytop,(double)pCur->xbot,pCur->fm,pPre };
			pPre = top;
			pCur = pCur->next;

		}
		//把已经超出界限的删除
		DeletAeNode(&top, y);
		//按xi的大小排序
		SortAENode(&top);
		//记录当前行的点
		FillBetweenTwoAet(top, pixels, y, pDC);
		//把当前y坐标上的记录的排序好的相邻的两个x之间的点全部绘制颜色
		y++;
	}
	//绘制完成就释放

	FreeAE(Top);

}
//更新活动边表
void CDrawPictureApp::UpdateAeNode(pAENode top)
{
	pAENode pCur = top;
	while (pCur)
	{

		pCur->xi += pCur->fm;

		pCur = pCur->next;
	}
}
//删除活动边表过期节点
void CDrawPictureApp::DeletAeNode(pAENode* top, int y)
{
	pAENode a = new aeNode();
	pAENode pPre = a;
	pPre->next = *top;
	pAENode pCur = *top;
	pAENode NeedFree;
	while (pCur)
	{
		if (pCur->ytop <= y)
		{

			pPre->next = pCur->next;
			NeedFree = pCur;
			pCur = pCur->next;
			free(NeedFree);
		}
		else {
			pPre = pCur;
			pCur = pCur->next;
		}


	}
	*top = a->next;
	free(a);
}
//给活动边表的边根据x大小排序
void CDrawPictureApp::SortAENode(pAENode* top)
{
	pAENode pCur = *top;
	pAENode a = new aeNode();
	pAENode pPre = a;
	pPre->next = pCur;
	int Count = 0;
	while (pCur)
	{
		Count++;
		pCur = pCur->next;
	}

	for (int i = 0; i < Count; i++)
	{
		pPre = a;
		pCur = a->next;
		int j = 0;
		for (; j < Count - i - 1; j++)
		{
			if (pCur->next)
			{
				if (pCur->xi > pCur->next->xi)
				{
					pPre->next = pCur->next;
					pPre = pPre->next;
					pCur->next = pPre->next;
					pPre->next = pCur;
				}
				else
				{
					pPre = pCur;
					pCur = pCur->next;
				}
			}
		}
	}
	*top = a->next;
	delete(a);
}
//创建ET边表
int CDrawPictureApp::createET(std::vector<CPoint>& points, EdgeTable* ET)
{
	if (points.size()<=1 || !ET )
	{
		return 0;
	}

	int i = 0;
	while (i + 1 < points.size())
	{

		if (points[i].y <= points[i + 1].y)
		{
			//i点在i+1点的下方
			pEdgeNode edge = new EdgeNode{ points[i].x,points[i + 1].y,(double)(points[i].x - points[i + 1].x) / (points[i].y - points[i + 1].y),NULL };
			if (ET->base[points[i].y] == NULL)
			{
				ET->base[points[i].y] = edge;
			}
			else
			{
				edge->next = ET->base[points[i].y];
				ET->base[points[i].y] = edge;

			}
		}
		else
		{
			//i点在i+1点的上方
			pEdgeNode edge = new EdgeNode{ points[i + 1].x,points[i].y,(double)(points[i].x - points[i + 1].x) / (points[i].y - points[i + 1].y),NULL };
			if (ET->base[points[i + 1].y] == NULL)
			{
				ET->base[points[i + 1].y] = edge;
			}
			else
			{

				edge->next = ET->base[points[i + 1].y];
				ET->base[points[i + 1].y] = edge;
			}
		}
		i++;
	}
	int nPnts = points.size() - 1;
	//如果初始点的高度比最后那点的高度低时
	if (points[0].y <= points[nPnts].y)
	{
		pEdgeNode edge = new EdgeNode{ points[0].x,points[nPnts].y,(double)(points[0].x - points[nPnts].x) / (points[0].y - points[nPnts].y),NULL };
		if (ET->base[points[0].y] == NULL)
		{
			ET->base[points[0].y] = edge;
		}
		else
		{
			edge->next = ET->base[points[0].y];
			ET->base[points[0].y] = edge;
		}
	}
	else
	{
		pEdgeNode edge = new EdgeNode{ points[nPnts].x,points[0].y,(double)(points[0].x - points[nPnts].x) / (points[0].y - points[nPnts].y),NULL };
		if (ET->base[points[nPnts].y] == NULL)
		{
			ET->base[points[nPnts].y] = edge;
		}
		else
		{
			edge->next = ET->base[points[nPnts].y];
			ET->base[points[nPnts].y] = edge;
		}
	}
	return 1;
}
void CDrawPictureApp::DrawPolygon(CDC* pDC,std::vector<CPoint>& points,CBitmap* map)
{
	ET = new EdgeTable();
	initET(*ET);
	createET(points, ET);
	px = NULL;
	Top = NULL;
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	CDrawPictureView* pView = (CDrawPictureView*)pFrame->GetActiveView();
	CRect rect;
	CDC tempDC;
	pView->GetClientRect(&rect);
	tempDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = tempDC.SelectObject(map);
	polygonFill(ET, Top, px, &tempDC);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &tempDC, 0, 0, SRCCOPY);
	PointsVec.clear();
	FreeET(*ET);
	free(ET);
}
// points 存储顶点序列，
// CDrawPictureApp 消息处理程序




