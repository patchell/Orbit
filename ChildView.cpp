
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
	m_G = 1.0;
	m_TimerID = 0;
	m_Scale = 1.0;
	m_Run = 0;	//not running
	m_Check = 0;
	m_Shift = false;
	m_pFollowThisBody = 0;
	m_Speed = 10;
}

CChildView::~CChildView()
{
	KillTimer(m_TimerID);
	// Delete Bodies
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_START, &CChildView::OnFileStart)
	ON_COMMAND(ID_FILE_PAUSE, &CChildView::OnFilePause)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_RESET, &CChildView::OnFileReset)
	ON_COMMAND(ID_SETUP_CENTEROFMASS, &CChildView::OnSetupCenterofmass)
	ON_COMMAND(ID_SETUP_ZOOMIN, &CChildView::OnSetupZoomin)
	ON_COMMAND(ID_SETUP_ZOOMOUT, &CChildView::OnSetupZoomout)
	ON_UPDATE_COMMAND_UI(ID_SETUP_CENTEROFMASS, &CChildView::OnUpdateSetupCenterofmass)
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_CONTEXTMENU()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CDC DCm;
	CBitmap bm;
	CRect rectClient;
	CBrush brBlack;
	CBrush brGreen;
	CBrush brBlue;
	CPen penBlack, *oldPen;
	CString csPE;
	CVector TheCenterOfGravity;
	CSize Center;
	int i = 0;
	static int Count = 0;

	brGreen.CreateSolidBrush(RGB(0, 255, 0));
	brBlue.CreateSolidBrush(RGB(0, 0, 255));
	penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPaintDC dc(this); // device context for painting
	GetClientRect(&rectClient);
	DCm.CreateCompatibleDC(&dc);
	bm.CreateCompatibleBitmap(&dc, rectClient.Width(), rectClient.Height());
	DCm.SelectObject(bm);

	brBlack.CreateSolidBrush(RGB(0, 0, 0));
	oldPen = DCm.SelectObject(&penBlack);
	DCm.FillRect(&rectClient, &brBlack);

	CBody* pBod = theApp.GetHead();
	if(m_pFollowThisBody)
		Center = m_CenterOffset - m_pFollowThisBody->GetScreenCoordinate();
	else
	{
		Center = m_CenterOffset;
		DrawAxis(&DCm, Center, rectClient.Size());
	}
	while (pBod)
	{
		pBod->Draw(&DCm, GetScale(), Center);
		pBod->PrintStats(&DCm, 10, 10 + 20 * i++, !Count);
		pBod->DrawBreadCrumbs(&DCm, GetScale(), Center);
		pBod = pBod->GetNext();
	}
	++Count;
	if (Count == 30)
		Count = 0;
	TheCenterOfGravity = CenterOfMass(theApp.GetHead());
	DrawCircleAt(
		&DCm,
		TheCenterOfGravity.ToPoint(GetScale()) + m_CenterOffset,
		5,
		RGB(255, 0, 0)
	);
	if (m_Check)
	{
//		m_CenterOffset = m_CenterOffset + TheCenterOfGravity.ToPoint(GetScale());
		m_CenterOffset.cx = (rectClient.Width() / 2) - TheCenterOfGravity.ToPoint(GetScale()).x;
		m_CenterOffset.cy = (rectClient.Height() / 2) - TheCenterOfGravity.ToPoint(GetScale()).y;
	}
	else
	{
		m_CenterOffset.cx = rectClient.Width() / 2;
		m_CenterOffset.cy = rectClient.Height() / 2;

	}
	dc.BitBlt(
		rectClient.left, 
		rectClient.top,
		rectClient.Width(),
		rectClient.Height(),
		&DCm,
		0,
		0,
		SRCCOPY
	);
}

void CChildView::CreateDefaultBodies()
{
	CBody* pBody = 0;
	int i = 0;

	for (i = 0; i < 6; ++i)
	{
		pBody = new CBody;
		theApp.AddBody(pBody);
	}
}

void CChildView::SetDefaultBodyOrbits()
{
	CBody* pBody = 0;
	int i = 0;

	pBody = theApp.GetHead();
	for (i = 0; i < 6; ++i)
	{
		pBody->SetMass(GetBody( i)->m_Mass);
		pBody->SetPosition(CVector(GetBody(i)->m_X, GetBody(i)->m_Y));
		pBody->SetVelociry(CVector(GetBody(i)->m_VX, GetBody(i)->m_VY));
		pBody->SetColor(GetBody(i)->m_Color);
		pBody = pBody->GetNext();
	}
}

CVector CChildView::DeltaX(
	CVector AtrctedPos,	//Attracted body 
	CVector AtrctingPos,	//Attractomg body
	double mass		//Attracting max
)
{
	//-------------------------------------
	// DeltaX
	// Calculates the delta x for a given boddy
	// Parameters
	//	mAtrctedPos...Position of attracted body
	//	mAtrctingPos..Position of attracting body
	//	mass....mass of attracting body
	//
	// returns the change in position/velocity
	//		of the Observed body
	//---------------------------------------
	CVector deltaX = CVector(0.0, 0.0);
	//------------------------------
	// Calculate distance CVector
	//------------------------------
	CVector r21;
	r21 = AtrctingPos - AtrctedPos;
	//-----------------------------
	// Cube magnitude of r12
	//-----------------------------
	double MagDist;
	MagDist = r21.Mag();
	double MagDistCubed;
	MagDistCubed = MagDist * MagDist * MagDist;
	//---------------------------
	// Combine all this crap
	//---------------------------
	deltaX = (r21 * (m_G * mass / MagDistCubed));
	return deltaX;
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	static unsigned int TimeCount = 0;
	CBody* pBodAttracted = 0;
	CBody* pBodAttracting = 0;

	CVector dx;
	if (m_Run)
	{
		pBodAttracted = theApp.GetHead();
//		printf("tick %d\n", ++TimeCount);
		while (pBodAttracted)
		{
			dx.Clear();
			pBodAttracting = GetOtherBodies(pBodAttracted, 0);
			while (pBodAttracting)
			{
				dx = DeltaX(
					pBodAttracted->GetPosition(),
					pBodAttracting->GetPosition(),
					pBodAttracting->GetMass()
				) + dx;
				pBodAttracting = GetOtherBodies(pBodAttracted, pBodAttracting);
			}
			CVector newPos;
			CVector oldPos = pBodAttracted->GetPosition();
			pBodAttracted->AddBreadCrum(oldPos.ToPoint(GetScale()));
			newPos = oldPos + dx + pBodAttracted->GetVelocity();
			pBodAttracted->SetTemps(newPos, pBodAttracted->GetVelocity() + dx);
			//		printf("New Pos:(%d,%d) dX=(%lf,%lf)\n", int(newPos.m_x),int( newPos.m_y),dx.m_x,dx.m_y);
			pBodAttracted = pBodAttracted = pBodAttracted->GetNext();
		}
		//	printf("---------------------\n");
		pBodAttracted = theApp.GetHead();
		while (pBodAttracted)
		{
			pBodAttracted->Update();
			pBodAttracted = pBodAttracted->GetNext();
		}
		Invalidate();
	}
	CWnd::OnTimer(nIDEvent);
}

CBody* CChildView::GetOtherBodies(CBody* pNotThisOne, CBody* pLastOne)
{
	CBody* pBod;
	int loop = 1;
	if (pLastOne == NULL)
		pBod = theApp.GetHead();
	else
		pBod = pLastOne->GetNext();
	while (pBod && loop)
	{
		if (pBod != pNotThisOne)
			loop = 0;
		else
			pBod = pBod->GetNext();
	}
	return pBod;
}

void CChildView::OnIntialUpdate()
{
	//--------------------------------
	// This function does all of the
	// initial setup
	//--------------------------------
	CRect ClientArea;

	GetClientRect(&ClientArea);
	m_CenterOffset.cx = ClientArea.Width() / 2;
	m_CenterOffset.cy = ClientArea.Height() / 2;
	CreateDefaultBodies();
	SetDefaultBodyOrbits();
	m_TimerID = SetTimer(1000, 10, 0);
	theApp.SetView(this);
	SetScale(3.0);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CChildView::DrawCircleAt(CDC *pDC,CPoint ptCenter, int Radius, COLORREF color)
{
	CRect rect;
	CBrush* pOldBrush, brush;
	CPen* oldPen, pen;

	pen.CreatePen(PS_SOLID, 1, color);
	brush.CreateSolidBrush(color);
	oldPen = pDC->SelectObject(&pen);
	pOldBrush = pDC->SelectObject(&brush);
	rect = CRect(CPoint(ptCenter - CSize(Radius, Radius)), CSize(2 * Radius, 2 * Radius));
	pDC->Ellipse(&rect);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(pOldBrush);
}

void CChildView::DrawAxis(CDC* pDC, CPoint ptCenter, CSize szScreenDimensions)
{
	CPen Pen, * oldPen;

	Pen.CreatePen(PS_SOLID, 1, RGB(255, 128, 255));
	oldPen = pDC->SelectObject(&Pen);
	pDC->MoveTo(0, ptCenter.y);;
	pDC->LineTo(szScreenDimensions.cx, ptCenter.y);
	pDC->MoveTo(ptCenter.x,0);;
	pDC->LineTo(ptCenter.x, szScreenDimensions.cy);
	pDC->SelectObject(oldPen);
}

CVector CChildView::CenterOfMass(CBody* pBodies)
{
	//-----------------------------------------
	// This is a bit tricky.  Masses closer to
	// the center will contribute more to the
	// center of mass than those far away
	// by the square of the distance
	//-----------------------------------------
	CVector CentOfMass;
	double My = 0.0, Mx = 0.0, Mz = 0;	//center of mass
	double TotalMass = 0.0;
	double EffectiveMass = 0;
	CBody* pCB = pBodies;
	CBody* pCBdist = 0;
	double Distance = 0.0;
	static int Count = 0;
	char* pS = new char[256];

	while (pCB)
	{
		pCBdist = pBodies;
		//--------------------------------
		// Calculate Effective Mass
		//--------------------------------
		EffectiveMass = 0;
		while (pCBdist)
		{
			if (pCB != pCBdist && (pCB->GetMass() < (10.0 * pCBdist->GetMass())))
			{
				Distance = pCB->GetPosition().DistanceSQ(pCBdist->GetPosition());
				TotalMass += pCB->GetMass() / Distance;
				EffectiveMass += pCB->GetMass() / Distance;
				if (pCB->GetID() == 4)
				{
					sprintf_s(pS, 256, "Effective Mass=%10.8lf To ID:%d of Mass:%8.4lf", 
						pCB->GetMass() / Distance,
						pCBdist->GetID(),
						pCBdist->GetMass()
					);
					pCB->PrintStats(theApp.LogFile(), pS);
				}
			}
			pCBdist = pCBdist->GetNext();
		}
		Mx += EffectiveMass * pCB->GetPosition().m_x;
		My += EffectiveMass * pCB->GetPosition().m_y;
		Mz += EffectiveMass * pCB->GetPosition().m_z;
		if (pCB->GetID() == 4)
		{
			sprintf_s(pS, 256, "Effective Mass=%12.10lf  My=%12.10lf", pCB->GetMass() / Distance,
				EffectiveMass * pCB->GetPosition().m_y
				);
			pCB->PrintStats(theApp.LogFile(), pS);
		}
		pCB = pCB->GetNext();
	}
	Mx /= TotalMass;
	My /= TotalMass;
	fprintf(theApp.LogFile(), "Center Of Gravityh: x=%8.2lf  y=%8.2lf  TotalMass = %12.6lf\n\n", Mx, My, TotalMass);
	CentOfMass = CVector(Mx, My);
	delete[] pS;
	return CentOfMass;
}

void CChildView::OnFileStart()
{
	m_Run = 1;
}


void CChildView::OnFilePause()
{
	m_Run = 0;
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	switch (nType)
	{
	case SIZE_MAXIMIZED:
		m_CenterOffset = CSize(cx / 2, cy / 2);
		break;
	case SIZE_MINIMIZED:
		m_CenterOffset = CSize(cx / 2, cy / 2);
		break;
	case SIZE_RESTORED:
		m_CenterOffset = CSize(cx / 2, cy / 2);
		break;
	}
}


void CChildView::OnFileReset()
{
	CBody* pBody = 0;

	SetDefaultBodyOrbits();
	Invalidate();
	pBody = theApp.GetHead();
	while (pBody)
	{
		pBody->ResetBreadCrumbs();
		pBody = pBody->GetNext();
	}
}


void CChildView::OnSetupCenterofmass()
{
	UINT state;
	m_Check ^= 1;
	if (m_Check)
		state = MF_CHECKED | MF_BYCOMMAND;
	else
		state = MF_UNCHECKED | MF_BYCOMMAND;
	AfxGetMainWnd()->GetMenu()->GetSubMenu(1)->CheckMenuItem(ID_SETUP_CENTEROFMASS, state);
}


void CChildView::OnSetupZoomin()
{
	m_Scale /= 1.5;
}


void CChildView::OnSetupZoomout()
{
	m_Scale *= 1.5;
}


void CChildView::OnUpdateSetupCenterofmass(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CChildView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CWnd::OnMouseHWheel(nFlags, zDelta, pt);
}


BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CBody* pBody = theApp.GetHead();
	if (m_Shift)
	{
		m_Speed -= zDelta/50;
		if (m_Speed < 10)
			m_Speed = 10;
		else if (m_Speed > 600)
			m_Speed = 600;
		m_TimerID = SetTimer(1000, m_Speed, 0);

	}
	else
	{
		while (pBody)
		{
			pBody->ResetBreadCrumbs();
			pBody = pBody->GetNext();
		}
		SetScale(GetScale() * (1.0 - double(zDelta) * 0.002));
		Invalidate();
	}
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

constexpr auto ID_CM_FOLLOW = 0x2000;
constexpr auto ID_CM_BREADCRUMS = 0x2001;
constexpr auto ID_CM_SPEED = 0x2002;

void CChildView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CBody* pBody = theApp.GetHead();
	CMenu ConTexMenu;
	int id;
	//-------------------------------------------
	// Create Menu
	//--------------------------------------------
	ConTexMenu.CreatePopupMenu();
	ConTexMenu.AppendMenuW(
		MF_STRING | MF_MENUBREAK | MF_POPUP, 
		ID_CM_FOLLOW,
		_T("Follow")
	);
	ConTexMenu.AppendMenuW(
		MF_STRING,
		ID_CM_BREADCRUMS,
		_T("Bread Crumbs")
	);
	ConTexMenu.AppendMenuW(
		MF_STRING,
		ID_CM_SPEED,
		_T("Speed")
	);


	id = ConTexMenu.TrackPopupMenu(
		TPM_RETURNCMD | TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
		point.x,
	point.y,
		this
	);
	ConTexMenu.DestroyMenu();
	switch (id)
	{
	case ID_CM_FOLLOW:
		break;
	case ID_CM_BREADCRUMS:
		break;
	case ID_CM_SPEED:		//change update rate
//		Invalidate();
		break;
	}
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_SHIFT:
		m_Shift = true;
		break;
	case 'P':
	case 'p':
		m_Run = 0;
		break;
	case 'S':
	case 's':
		break;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_SHIFT:
		m_Shift = false;
		break;
	case 'P':
	case 'p':
		break;
	case 'S':
	case 's':
		m_Run = 1;
		break;
	}

	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}
