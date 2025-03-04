
// ChildView.h : interface of the CChildView class
//


#pragma once

// CChildView window
constexpr auto NUMBER_OF_BODIES = 8;

class CChildView : public CWnd
{
	struct BodyParams {
		double m_Mass;
		double m_X;
		double m_Y;
		double m_VX;
		double m_VY;
		COLORREF m_Color;
		double m_Radius;
		BodyParams(
			double m,
			double x,
			double y,
			double vx,
			double vy,
			COLORREF color,
			double Radius
		) {
			m_Mass = m;
			m_X = x;
			m_Y = y;
			m_VX = vx;
			m_VY = vy;
			m_Color = color;
			m_Radius = Radius;

		}
	};
	inline static BodyParams ParamsLUT[8] = {
		{300.0,-150.0, 0.0, 0.0, 0.8, RGB(255, 0, 0), 3.0},
		{500.0, 150.0, 0.0, 0.0, -0.4750, RGB(0, 0, 255),4.0},
		{2.0, 0.0, 600.0, -1.25, 0.0, RGB(0, 192, 0), 2},
		{5.0, 0.0, -1200.0, -0.8, 0.0, RGB(128, 0, 192), 3},
		{0.02, 0.0, -1208, -1.8, 0.0, RGB(128, 0, 192), 2},
		{0.5, 5200.0,  200.0, 0.005, 0.1, RGB(0, 128, 192), 2},
		{ 50.5, 2000,  2000, -0.35, 0.35, RGB(200, 40, 125), 4 },
		{ 50.5, -2000,  -2000, 0.35, -0.35, RGB(200, 40, 125), 4 }
	};
	UINT m_TimerID;
	double m_G;		// gravitation constant
	int m_Run;
	double m_Scale;
	CSize m_CenterOffset;
	int m_Check;
	bool m_Shift;
	CBody* m_pFollowThisBody;
	int m_Speed;
	int m_SpeedTiker;
public:
	CChildView();
	virtual ~CChildView();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	bool IsRunning() {
		bool rV = false;
		if (m_Run) rV = true;
		return rV;
	}
	bool IsNotRunning() {
		bool rV = true;
		if (m_Run) rV = false;
		return rV;
	}
	void OnIntialUpdate();
	//----------------------------
	// Orbit Stuff
	//----------------------------
	void SetFollowBody(CBody* pB) { m_pFollowThisBody = pB; }
	CBody* GetFollowBody() {
		return m_pFollowThisBody;
	}
	void CreateDefaultBodies();
	void SetDefaultBodyOrbits();
	CVector DeltaX(CVector m1Pos, CVector m2Pos, double m2);
	CBody* GetOtherBodies(CBody* pNotThisOne, CBody* pLastOne);
	void DrawCircleAt(CDC* pDC, CPoint ptCenter, int Radius, COLORREF color);
	void DrawAxis(CDC* pDC, CPoint ptCenter, CSize szScreenDimensions);
	CVector CenterOfMass(CBody* pBodies);
	double GetScale() { return m_Scale; }
	void SetScale(double s) { m_Scale = s; }
	CSize GetCenterOffset() { return m_CenterOffset; }
	void SetCenterOffset(CSize szCenter) { m_CenterOffset = szCenter; }
	CChildView::BodyParams* GetBody(int i) {
		return &ParamsLUT[i];
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	//----------------------------
	// Message Handlers
	//----------------------------
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileStart();
	afx_msg void OnFilePause();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileReset();
	afx_msg void OnSetupCenterofmass();
	afx_msg void OnSetupZoomin();
	afx_msg void OnSetupZoomout();
	afx_msg void OnUpdateSetupCenterofmass(CCmdUI* pCmdUI);
    afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnAppExit();
};

