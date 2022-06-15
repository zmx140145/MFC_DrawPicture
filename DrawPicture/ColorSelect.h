#pragma once
#define PI acos(-1)

// ColorSelect 对话框

class ColorSelect : public CDialogEx
{
	DECLARE_DYNAMIC(ColorSelect)

public:
	
	ColorSelect(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ColorSelect();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLORSELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void DrawHSV(CDC * pDC, int centerX, int centerY, float size, float v);


	
	void PointToHSVPos(float x, float y, float * h, float * s);
	void HSVToRGB(float h, float s, float v, float * R, float * G, float * B);
	void RGBToHSV(float R, float G, float B, float * h, float * s, float * v);
	void DrawColorSelect(float size, int centerX, int centerY, int v);
	//相对屏幕的中心点
	int CenterX;
	int CentetY;
	//这个是记录相对与文档中心点
	int CX;
	int CY;
	int HSV_V;
	float R;
	float G;
	float B;
	float Size;
	bool canChangeColor=true;
	int firstMove = 0;
	int moveCount=0;
	COLORREF Color;
	CStatic MousePos;
	CSliderCtrl Slider_HSV;
	CEdit RGB_R;
	CEdit RGB_G;
	CEdit RGB_B;
	CStatic ColorReview;
	CDrawPictureApp* App;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnStnClickedColorreview();
	CEdit HSV_VTest;
	afx_msg void OnReleasedcaptureSliderv(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic ColorPic;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnIdclose();
	afx_msg void OnIdno();
	afx_msg void OnIdyes();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
