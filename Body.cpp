#include "pch.h"

int CBody::IdCount = 0;

void CBody::AddBreadCrum(CPoint p)
{
	if (m_numberOfBreadCrumbs < NUMBER_OF_BREADCRUMBS)
	{
		m_BreadCrumbs[m_LastBreadCrumb] = p;
		if (++m_LastBreadCrumb == NUMBER_OF_BREADCRUMBS) m_LastBreadCrumb = 0;
		m_numberOfBreadCrumbs++;
	}
	else if (m_numberOfBreadCrumbs == NUMBER_OF_BREADCRUMBS)
	{
		if (NUMBER_OF_BREADCRUMBS == ++m_LastBreadCrumb)
		{
			m_LastBreadCrumb = 0;
		}
		if (NUMBER_OF_BREADCRUMBS == ++m_FirstBreadCrumb)
		{
			m_FirstBreadCrumb = 0;
		}

		m_BreadCrumbs[m_LastBreadCrumb] = p;
	}
}

void CBody::DrawBreadCrumbs(CDC* pDC)
{
	int i, j;

	j = m_FirstBreadCrumb;
	//	printf("Total Breadcrumbs %d  Index %d\n", m_numberOfBreadCrumbs,j);
	for (i = 0; i < m_numberOfBreadCrumbs; ++i)
	{
		pDC->SetPixel(m_BreadCrumbs[j++], m_Color);
		if (j == NUMBER_OF_BREADCRUMBS)j = 0;
	}
}

double CBody::KineticEnergy()
{
	//----------------------------
	// KE = 1/2 x m x V^2
	//---------------------------
	double KE;
	double Speed = m_vVelocity.Mag();
	KE = 0.5 * m_dMass * Speed * Speed;
	return KE;
}

double CBody::PotentialEnergy(CBody* AttractingBody)
{
	//-----------------------------
	//  PE = -G * M * m / r
	//-----------------------------
	double PE;
	double r = abs((GetPosition() - AttractingBody->GetPosition()).Mag());
	PE = AttractingBody->GetMass() * m_dMass / r;
	return PE;
}

void CBody::Print()
{
	m_vVelocity.Print("Velocity");
	m_vPos.Print("Position");
}
