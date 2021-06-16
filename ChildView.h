
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

// Attributes
public:

// Operations
	vector DeltaX(vector m1Pos, vector m2Pos, double m2);
public:

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CBody* GetOtherBodies(CBody* pNotThisOne, CBody* pLastOne);
	void OnIntialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void DrawCircleAt(CDC* pDC, CPoint ptCenter, int Radius, COLORREF color);
	afx_msg void OnFileStart();
	afx_msg void OnFilePause();
};

