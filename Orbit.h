
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
	CBody* m_pTail;
	FILE* pConsol;
	FILE* m_pLog;
public:
	COrbitApp() noexcept;
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	afx_msg void OnAppAbout();
	void SetView(CChildView* pV) { pView = pV; }
	void AddBody(CBody* pBod);
	void DeleteBodies();
	CBody* GetHead() { return m_pHead; }
	void SetHead(CBody* pH) { m_pHead = pH; }
	CBody* GetTail() { return m_pTail; }
	void SetTail(CBody* pT) { m_pTail = pT; }
	FILE* LogFile() { return m_pLog; }
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetupCreatebody();
	void EditBodies(CBody* pBody);
};

extern COrbitApp theApp;
