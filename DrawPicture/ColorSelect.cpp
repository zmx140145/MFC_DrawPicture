// ColorSelect.cpp: 实现文件
//

#include "pch.h"
#include "DrawPicture.h"
#include "ColorSelect.h"
#include "afxdialogex.h"
#include<math.h>

// ColorSelect 对话框

IMPLEMENT_DYNAMIC(ColorSelect, CDialogEx)

ColorSelect::ColorSelect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COLORSELECT, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

ColorSelect::~ColorSelect()
{
	
}

void ColorSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MOUSEPOS, MousePos);

	DDX_Control(pDX, IDC_SLIDERV, Slider_HSV);
	DDX_Control(pDX, IDC_RGB_R, RGB_R);
	DDX_Control(pDX, IDC_RGB_G, RGB_G);
	DDX_Control(pDX, IDC_RGB_B, RGB_B);
	DDX_Control(pDX, IDC_COLORREVIEW, ColorReview);
	DDX_Control(pDX, IDC_HSV_VEDIT, HSV_VTest);
	DDX_Control(pDX, IDC_COLORPICTURE, ColorPic);
}


BEGIN_MESSAGE_MAP(ColorSelect, CDialogEx)
	ON_WM_MOUSEMOVE()
	ON_WM_HSCROLL()

	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERV, &ColorSelect::OnReleasedcaptureSliderv)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDCLOSE, &ColorSelect::OnIdclose)
	ON_COMMAND(IDNO, &ColorSelect::OnIdno)
	ON_COMMAND(IDYES, &ColorSelect::OnIdyes)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &ColorSelect::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ColorSelect::OnBnClickedCancel)
END_MESSAGE_MAP()


// ColorSelect 消息处理程序


BOOL ColorSelect::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  在此添加额外的初始化
	CDC* pDC = GetDC();
	Slider_HSV.SetRange(0,255);//设置滑动范围为0到255
	Slider_HSV.SetTicFreq(1);//每1个单位画一刻度
	Slider_HSV.SetPos(255);//设置滑块初始位置为255
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ColorSelect::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (moveCount < 2)
	{
		if (firstMove > 5)
		{
			DrawColorSelect(Size, CX, CY, HSV_V);
			firstMove = 0;
			moveCount++;
		}
		else
		{

			firstMove++;
		}
	}
	
	/*CDC* pDC = GetDC();
	DrawHSV(pDC, 150, 150, 1 / 2.0, 240);*/
	/*-------------文本信息-------------------*/
	CString str;
	CDC* pDC = GetDC();
	CPoint pos = point;
	ClientToScreen(&pos);
	str.Format(_T("坐标：%d,%d，%d,%d"), point.x, point.y,pos.x,pos.y);
	MousePos.SetWindowTextW(str);
	/*-------------颜色预览-------------------*/
    pos = point;
	ClientToScreen(&pos);
	pos.x = pos.x - CenterX;
	pos.y = pos.y - CentetY;
	float cx, cy;
	PointToHSVPos(pos.x, pos.y, &cx, &cy);
	HSVToRGB(cx, cy, HSV_V, &R, &G, &B);
	/*------------------------------------------------*/
    pDC = ColorReview.GetDC();
	CDC background;
	CBitmap map;
	CRect rect;

	ColorReview.GetClientRect(&rect);
	map.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	background.CreateCompatibleDC(pDC);
	CBitmap *pOldBit = background.SelectObject(&map);
	if (canChangeColor)
	{
		Color=RGB(R, G, B);
	}
	background.FillSolidRect(0, 0, rect.Width(), rect.Height(),Color);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &background, 0, 0, SRCCOPY);
	/*------------------------------------------------*/
	//释放空间
	background.DeleteDC();
	map.DeleteObject();
	ReleaseDC(pDC);
	CDialogEx::OnMouseMove(nFlags, point);
}
void ColorSelect::DrawHSV(CDC* pDC,int centerX, int centerY, float size, float v)
{
	//先保证在区域内
	if (centerX - 255 * size < 0)
	{
		return;
	}
	if (centerY - 255 * size < 0)
	{
		return;
	}
	    int MinX = - 255 * size;
		int MaxX =  255 * size;
		int MinY = - 255 * size;
		int MaxY =  255 * size;
		float h, s;
		float r, g, b;
		COLORREF color;
		for (int i = MinX; i <= MaxX; i++)
		{
			for (int j = MinY; j <= MaxY; j++)
			{
				if (sqrt(i*i + j * j) > 255*size)
				{
					continue;
				}
				PointToHSVPos(i / size, j/ size, &h, &s);
				HSVToRGB(h, s, v, &r, &g, &b);
				color = RGB(r, g, b);
				pDC->SetPixel(centerX+i,centerY+j,color);
			}
		}
}
void ColorSelect::PointToHSVPos(float x, float y,float* h, float* s)
{
	float length = sqrt(x*x + y * y);
	*s = min(255,length);
	if (y >= 0) {
		if (x >= 0)
		{
			*h = asin(y / length);
		}
		if (x < 0)
		{
			*h = PI-asin(y / length);
		}
	}
	else if (y < 0) {
		if (x < 0)
		{
			*h = PI + asin(-y / length);
		}
		else
		{
			*h = 2*PI - asin(-y / length);
		}
		
	}
}
void ColorSelect::HSVToRGB(float h, float s, float v, float* R, float* G, float* B)
{
	h=h / PI * 180;
	s = s / 255.0;
	if (s == 0)
		*R = *G = *B = v;
	else
	{
		h = h / 60;
		int i = (int)h;
		float C = h - i;

		float X = v * (1 - s);
		float Y = v * (1 - s * C);
		float Z = v * (1 - s * (1 - C));
		if (X > v)
			X = v;
		if (X < 0)
			X = 0;
		if (Y > v)
			Y = v;
		if (Y < 0)
			Y = 0;
		if (Z > v)
			Z = v;
		if (Z < 0)
			Z = 0;
		switch (i)
		{
		case 0: *R = v; *G = Z; *B = X; break;
		case 1: *R = Y; *G = v; *B = X; break;
		case 2: *R = X; *G = v; *B = Z; break;
		case 3: *R = X; *G = Y; *B = v; break;
		case 4: *R = Z; *G = X; *B = v; break;
		case 5: *R = v; *G = X; *B = Y; break;
		}
	}
}
void ColorSelect::RGBToHSV(float R, float G, float B, float* h, float* s, float* v)
{
	float max = 0, min = 0;

	max = max(max(R, G),B);
	min = min(min(R, G), B);
	*v = max;
	if (max == 0)
		*s = 0;
	else
		*s = 1 - (min / max);
	if (max == min)
		*h = 0;
	else if (max == R && G >= B)
		*h = 60 / 360.0f * ((G - B) / (max - min));
	else if (max == R && G < B)
		*h = 60 / 360.0f * ((G - B) / (max - min)) + 360 / 360.0f;
	else if (max == G)
		*h = 60 / 360.0f * ((B - R) / (max - min)) + 120 / 360.0f;
	else if (max == B)
		*h = 60 / 360.0f * ((R - G) / (max - min)) + 240 / 360.0f;
}
//绘制色盘
void ColorSelect::DrawColorSelect(float size,int centerX,int centerY,int v)
{
	CX = centerX;
	CY = centerY;
	Size = size;
	HSV_V = v;
	CDC* pDC = ColorPic.GetDC();
	CDC background;
	CBitmap map;
	CRect rect;
	ColorPic.MoveWindow(centerX-255*size, centerX-255*size, 2 * 255 * size+10, 2 * 255 * size+10, true);
	ColorPic.GetClientRect(&rect);
	map.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	background.CreateCompatibleDC(pDC);
	CBitmap *pOldBit = background.SelectObject(&map);
	background.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(245, 245, 245));
	DrawHSV(&background,rect.Width()/2, rect.Height()/2, size, v);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &background, 0, 0, SRCCOPY);
	CPoint pos = rect.CenterPoint();//获得矩形的中心点
    ColorPic.ClientToScreen(&pos);//转为屏幕坐标
    CenterX =  pos.x;	//记录中心点 之后可以计算出颜色
	CentetY = pos.y;
	//释放空间
	background.DeleteDC();
	map.DeleteObject();
	ReleaseDC(pDC);
	
}
//按下拖动滑条
void ColorSelect::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(TRUE);

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDERV);
	//m_int 即为当前滑块的值。
	HSV_V = 1 * pSlidCtrl->GetPos();//取得当前位置值  
	//CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	CString str;
	str.Format(_T("%d"), HSV_V);
	HSV_VTest.SetWindowTextW(str);
    UpdateData(FALSE);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
//释放滑条
void ColorSelect::OnReleasedcaptureSliderv(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	DrawColorSelect(Size, CX, CY, HSV_V);
	*pResult = 0;
}


BOOL ColorSelect::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//if (pMsg->message == WM_LBUTTONDOWN)//拦截鼠标左键按下消息
	//{
	//	if (pMsg->hwnd == GetDlgItem(IDC_COLORPICTURE)->m_hWnd)//判断按下的位置是否为目标button,button名为IDC_BUTTON5
	//	{
	//		SetTimer(2, 50, NULL);//触发定时器，定时器ID为2  1000=1s
	//	}		
	//}
	//else if (pMsg->message == WM_LBUTTONUP)//鼠标左键抬起
	//{
	//	KillTimer(2);//关闭ID为2的定时器
	//}
	return CDialog::PreTranslateMessage(pMsg); //一定要有，其他消息系统默认处理
}


void ColorSelect::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}

//左键按下
void ColorSelect::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	if (canChangeColor)
	{
		str.Format(_T("%d"), (int)R);
		RGB_R.SetWindowTextW(str);
		str.Format(_T("%d"), (int)G);
		RGB_G.SetWindowTextW(str);
		str.Format(_T("%d"), (int)B);
		RGB_B.SetWindowTextW(str);

	}
	canChangeColor = false;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void ColorSelect::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	canChangeColor = true;
	
	CDialogEx::OnRButtonDown(nFlags, point);
}


void ColorSelect::OnIdclose()
{
	DestroyWindow();
	// TODO: 在此添加命令处理程序代码
}


void ColorSelect::OnIdno()
{
	DestroyWindow();
	// TODO: 在此添加命令处理程序代码
}
void ColorSelect::OnIdyes()
{
	DestroyWindow();
	// TODO: 在此添加命令处理程序代码
}

void ColorSelect::OnDestroy()
{
	CDialogEx::OnDestroy();
	delete this;
	// TODO: 在此处添加消息处理程序代码
}


void ColorSelect::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	App->SelectColor = Color;
	CDialogEx::OnOK();
}


void ColorSelect::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
