#include "pch.h"
#include "Body.h"

int CBody::IdCount = 0;

void CBody::Create(
	double Mass, 
	CVector Velocity, 
	CVector Position, 
	COLORREF color, 
	double Radius
)
{
	m_InitialConditions.Create(
		Mass,
		Velocity,
		Position,
		color,
		Radius
	);
	m_BodyState.Create(
		Mass,
		Velocity,
		Position,
		color,
		Radius
	);
}

void CBody::Reset()
{
	m_BodyState.m_Mass = m_InitialConditions.m_Mass;
	m_BodyState.m_Velocity = m_InitialConditions.m_Velocity;
	m_BodyState.m_Position = m_InitialConditions.m_Position;
	m_BodyState.m_Color = m_InitialConditions.m_Color;
	m_BodyState.m_Radius = m_InitialConditions.m_Radius;
}

void CBody::Draw(
	CDC* pDC, 
	double Scale, 
	CSize CenterOffset
)
{
	int x, y;
	x = (int)(GetPosition().m_x / Scale);
	y = (int)(GetPosition().m_y / Scale);
	m_pntScreen = CPoint(x, y);
	DrawCircleAt(
		pDC,
		m_pntScreen + CenterOffset,
//		CPoint(x + CenterOffset.cx, y + CenterOffset.cy),
		GetRadius(),
		GetColor()
	);
}

void CBody::PrintStats(CDC* pDC, int x, int y, bool UpDate) 
{
	CString csString;
	COLORREF Txt, Bck;

	if (UpDate)
	{
		m_Vel_Display = GetVelocity().Mag();
		m_X_Display = GetPosition().m_x;
		m_Y_Display = GetPosition().m_y;
	}
	Txt = pDC->SetTextColor(GetColor());
	Bck = pDC->SetBkColor(RGB(0, 0, 0));
	csString.Format(_T("VEL=%8.4lf X=%10.4lf Y=%10.4lf"),
		m_Vel_Display,
		m_X_Display,
		m_Y_Display
	);
	pDC->TextOutW(x, y, csString);
	pDC->SetTextColor(Txt);
	pDC->SetBkColor(Bck);
}

void CBody::PrintStats(FILE* pLog, const char* pS) 
{
	double Vel;

	Vel = GetVelocity().Mag();
	fprintf(pLog, "ID::%d:%s:Mass=%8.2lf VEL=%8.4lf X=%10.4lf Y=%10.4lf\n",
		GetID(),
		pS,
		GetMass(),
		Vel,
		GetPosition().m_x,
		GetPosition().m_y
	);
}

void CBody::DrawCircleAt(CDC* pDC, CPoint ptCenter, int Radius, COLORREF color)
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

void CBody::AddBreadCrum(CPoint p)
{
	if (m_numberOfBreadCrumbs < m_BreadCrumbsSize)
	{
		m_pBreadCrumbs[m_LastBreadCrumb] = p;
		if (++m_LastBreadCrumb == m_BreadCrumbsSize) m_LastBreadCrumb = 0;
		m_numberOfBreadCrumbs++;
	}
	else if (m_numberOfBreadCrumbs == m_BreadCrumbsSize)
	{
		if (m_BreadCrumbsSize == ++m_LastBreadCrumb)
		{
			m_LastBreadCrumb = 0;
		}
		if (m_BreadCrumbsSize == ++m_FirstBreadCrumb)
		{
			m_FirstBreadCrumb = 0;
		}

		m_pBreadCrumbs[m_LastBreadCrumb] = p;
	}
}

void CBody::ResetBreadCrumbs()
{
	m_numberOfBreadCrumbs = 0;
	m_FirstBreadCrumb = 0;
	m_LastBreadCrumb = 0;
}

void CBody::CopyAttributs(SAttributes* pDest, SAttributes* pSrc)
{
	pDest->Copy(pSrc);
}

void CBody::DrawBreadCrumbs(CDC* pDC, double Scale, CSize CenterOffset)
{
	int i, j;

	j = m_FirstBreadCrumb;
	//	printf("Total Breadcrumbs %d  Index %d\n", m_numberOfBreadCrumbs,j);
	for (i = 0; i < m_numberOfBreadCrumbs; ++i)
	{
		pDC->SetPixel(m_pBreadCrumbs[j++] + CenterOffset, GetColor());
		if (j == m_BreadCrumbsSize)j = 0;
	}
}

void CBody::SetNumberOfBreadCrumbs(int n)
{
	if (m_pBreadCrumbs)
		delete[] m_pBreadCrumbs;
	m_BreadCrumbsSize = n;
	m_pBreadCrumbs = new CPoint[n];
}

double CBody::KineticEnergy()
{
	//----------------------------
	// KE = 1/2  m  V^2
	//---------------------------
	double KE;
	double Speed = GetVelocity().Mag();
	KE = 0.5 * GetMass() * Speed * Speed;
	return KE;
}

double CBody::PotentialEnergy(CBody* AttractingBody)
{
	//-----------------------------
	//  PE = -G * M * m / r
	//-----------------------------
	double PE;
	CVector delta;

	delta = GetPosition() - AttractingBody->GetPosition();
	double r = delta.Mag();
	PE = AttractingBody->GetMass() * GetMass() / r;
	return PE;
}

void CBody::Print(int Indent)
{
	char* pI = new char[256];
	int i = 0;
	

	for (i = 0; i < Indent;++i)
		pI[i] = ' ';
	pI[i] = 0;

	printf("%sID:%d Pos X:%12.3lf Y:%12.3lf Speed:%12.3lf\n",
		pI,
		this->m_BodyID,
		GetPosition().m_x,
		GetPosition().m_y,
		GetVelocity().Mag()
	);
	delete[]pI;
}
