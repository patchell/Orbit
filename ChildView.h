
// ChildView.h : interface of the CChildView class
//


#pragma once

// CChildView window

class CChildView : public CWnd
{
	UINT m_TimerID;
	double m_G;
	int m_Run;
public:
	CChildView();
	virtual ~CChildView();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnIntialUpdate();
	//----------------------------
	// Orbit Stuff
	//----------------------------
	void SetDefaultBodyOrbits();
	CVector DeltaX(CVector m1Pos, CVector m2Pos, double m2);
	CBody* GetOtherBodies(CBody* pNotThisOne, CBody* pLastOne);
	void DrawCircleAt(CDC* pDC, CPoint ptCenter, int Radius, COLORREF color);
	CVector CenterOfMass(CBody* pBodies);
	//----------------------------
	// Message Handlers
	//----------------------------
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileStart();
	afx_msg void OnFilePause();
protected:
	DECLARE_MESSAGE_MAP()
};

