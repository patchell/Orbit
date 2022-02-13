
// Orbit.h : main header file for the Orbit application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include <math.h>

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
