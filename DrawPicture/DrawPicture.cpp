
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
void CDrawPictureApp::CirclePointSoildDraw(CDC* pDC, int x0, int y0, int x, int y, COLORREF color)
{
	// TODO: 在此处添加实现代码.
	DRHLine(pDC, x0 + x, y0 + y, x0 + x, y0 - y, color);
	DRHLine(pDC, x0 + y, y0 + x, x0 + y, y0 - x, color);
	DRHLine(pDC, x0 - x, y0 + y, x0 - x, y0 - y, color);
	DRHLine(pDC, x0 - y, y0 + x, x0 - y, y0 - x, color);

}

// CDrawPictureApp 消息处理程序




