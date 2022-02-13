
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
	m_Run = 0;	//not running
}

CChildView::~CChildView()
{
	KillTimer(m_TimerID);
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_START, &CChildView::OnFileStart)
	ON_COMMAND(ID_FILE_PAUSE, &CChildView::OnFilePause)
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

	CBody* pBod = GETBODIES;
	while (pBod)
	{
		int x, y;
		x = (int)pBod->GetPosition().m_x;
		y = (int)pBod->GetPosition().m_y;
		DrawCircleAt(
			&DCm,
			CPoint(x, y),
			10,
			pBod->GetColor()
		);
		pBod->DrawBreadCrumbs(&DCm);
		DrawCircleAt(
			&DCm,
			CenterOfMass(GETBODIES).ToPoint(),
			5,
			RGB(255, 0, 0)
		);
//		csPE.Format(_T("PE=%8.4lf"), );
//		DCm.TextOutW(0, 0, 
		pBod = pBod->GetNext();
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

void CChildView::SetDefaultBodyOrbits()
{
	CBody* pBody;

	pBody = new CBody();
	pBody->SetMass(300.0);
	pBody->SetPosition(CVector(500.0, 300.0));
	pBody->SetVelociry(CVector(0.0, 0.8));
	ADDBODY(pBody);
	pBody = new CBody();
	pBody->SetMass(500.0);
	pBody->SetPosition(CVector(800.0, 300.0));
	pBody->SetVelociry(CVector(0.0, -0.4750));
	pBody->SetColor(RGB(0, 0, 255));
	ADDBODY(pBody);
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
		pBodAttracted = GETBODIES;
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
			pBodAttracted->AddBreadCrum(oldPos.ToPoint());
			newPos = oldPos + dx + pBodAttracted->GetVelocity();
			pBodAttracted->SetTemps(newPos, pBodAttracted->GetVelocity() + dx);
			//		printf("New Pos:(%d,%d) dX=(%lf,%lf)\n", int(newPos.m_x),int( newPos.m_y),dx.m_x,dx.m_y);
			pBodAttracted = pBodAttracted = pBodAttracted->GetNext();
		}
		//	printf("---------------------\n");
		pBodAttracted = GETBODIES;
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
		pBod = GETBODIES;
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
	SetDefaultBodyOrbits();
	m_TimerID = SetTimer(1000, 10, 0);
	theApp.SetView(this);
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

CVector CChildView::CenterOfMass(CBody* pBodies)
{
	CVector CentOfMass;
	double My = 0.0, Mx = 0.0;
	double TotalMass = 0.0;
	CBody* pCB = pBodies;
	while (pCB)
	{
		Mx += pCB->GetMass() * pCB->GetPosition().m_y;
		My += pCB->GetMass() * pCB->GetPosition().m_x;
		TotalMass += pCB->GetMass();
		pCB = pCB->GetNext();
	}
	CentOfMass = CVector(My/TotalMass, Mx/TotalMass);
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
