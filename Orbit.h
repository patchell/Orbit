
// Orbit.h : main header file for the Orbit application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include <math.h>

struct vector {
	double m_x;
	double m_y;
	vector() {
		m_x = 0.0;
		m_y = 0.0;
	}
	vector(double x, double y) {
		m_x = x;
		m_y = y;
	}

	vector operator - () {
		vector r;
		r.m_x = -m_x;
		r.m_y = -m_y;
		return r;
	}
	vector operator - (vector& r) {
		vector v;

		r = -r;
		v = *this + r;
		return v;
	}
	vector operator + (vector& r) {
		vector v;

		v.m_x = m_x + r.m_x;
		v.m_y = m_y + r.m_y;
		return v;
	}

	vector operator * (double s)
	{
		vector r;

		r.m_x = s * m_x;
		r.m_y = s * m_y;
		return r;
	}

	vector operator = (vector& r) {
		vector x;
		m_x = x.m_x = r.m_x;
		m_y = x.m_y = r.m_y;
		return x;
	}

	double Mag() {
		double mag;
		mag = sqrt(m_x * m_x + m_y * m_y);
		return mag;
	}
	void Clear() {
		m_x = 0.0;
		m_y = 0.0;
	}
};

class CBody
{
	CBody* m_pNext;
	vector m_vPos;
	vector m_vVelocity;
	vector m_vPos_Temp;
	vector m_vVelocity_Temp;
	COLORREF m_Color;

	double m_dMass;
public:
	CBody() {
		m_vPos = vector(0.0, 0.0);
		m_vVelocity = vector(0.0, 0.0);
		m_pNext = 0;
		m_dMass = 1.0;
		m_Color = RGB(255, 255, 0);
	}
	virtual ~CBody() {}
	void SetVelociry(vector v)
	{
		m_vVelocity = v;
	}
	vector GetVelocity() { return m_vVelocity; }
	void SetPosition(vector v) {
		m_vPos = v;
	}
	vector GetPosition() { return m_vPos; }
	void SetMass(double m) { m_dMass = m; }
	double GetMass() { return m_dMass; }
	CBody* GetNext() { return m_pNext; }
	CBody** GetNextPointer() { return &m_pNext; }
	void SetNext(CBody* next) { m_pNext = next; }
	void SetTemps(vector pos, vector v) {
		m_vPos_Temp = pos;
		m_vVelocity_Temp = v;
	}
	void Update() {
		m_vPos = m_vPos_Temp;
		m_vVelocity = m_vVelocity_Temp;
	}
	void SetColor(COLORREF c) { m_Color = c; }
	COLORREF GetColor() { return m_Color; }
};


// COrbitApp:
// See Orbit.cpp for the implementation of this class
//

class CChildView;

class COrbitApp : public CWinApp
{
	CChildView* pView;
	CBody* m_pHead;
	CBody** m_ppEnd;
	FILE* pConsol;
public:
	COrbitApp() noexcept;
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	afx_msg void OnAppAbout();
	void SetView(CChildView* pV) { pView = pV; }

	void AddBody(CBody* pBod);
	CBody* GetBody() { return m_pHead; }
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetupCreatebody();
};

extern COrbitApp theApp;
#define GETBODIES			(theApp.GetBody())
#define GETNEXTBODY			(pBody)	(pBody->GetBody())
#define ADDBODY(pBody)		(theApp.AddBody(pBody))
