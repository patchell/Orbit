#pragma once


#define NUMBER_OF_BREADCRUMBS	600

class CBody
{
	CBody* m_pNext;
	static int IdCount;
	//-------------------------
	// Body Attributes
	//-------------------------
	int m_BodyID;
	CVector m_vPos;
	CVector m_vVelocity;
	CVector m_vPos_Temp;
	CVector m_vVelocity_Temp;
	COLORREF m_Color;
	int m_Radius;
	double m_dMass;
	double m_PotentialEnergy;
	double m_KineticEnergy;
	//--------------------------
	// Bread Crumbs
	//--------------------------
	CPoint m_BreadCrumbs[NUMBER_OF_BREADCRUMBS];
	int m_FirstBreadCrumb;
	int m_LastBreadCrumb;
	int m_numberOfBreadCrumbs;
	//----------------------------
public:
	CBody() {
		m_vPos = CVector(0.0, 0.0);
		m_vVelocity = CVector(0.0, 0.0);
		m_pNext = 0;
		m_dMass = 1.0;
		m_Color = RGB(255, 255, 0);
		m_numberOfBreadCrumbs = 0;
		m_FirstBreadCrumb = 0;
		m_LastBreadCrumb = 0;
		m_Radius = 5;
		m_BodyID = ++IdCount;

	}
	virtual ~CBody() {}
	void SetVelociry(CVector v)
	{
		m_vVelocity = v;
	}
	CVector GetVelocity() { return m_vVelocity; }
	void SetPosition(CVector v) {
		m_vPos = v;
	}
	CVector GetPosition() { return m_vPos; }
	void SetMass(double m) { m_dMass = m; }
	double GetMass() { return m_dMass; }
	CBody* GetNext() { return m_pNext; }
	CBody** GetNextPointer() { return &m_pNext; }
	void SetNext(CBody* next) { m_pNext = next; }
	void SetTemps(CVector pos, CVector v) {
		m_vPos_Temp = pos;
		m_vVelocity_Temp = v;
	}
	void Update() {
		m_vPos = m_vPos_Temp;
		m_vVelocity = m_vVelocity_Temp;
	}
	void SetColor(COLORREF c) { m_Color = c; }
	COLORREF GetColor() { return m_Color; }
	void SetRadius(int r) { m_Radius = r; }
	int GetRadius() { return m_Radius; }
	int GetID() { return m_BodyID; }
	//--------------------------------------
	// Bread Crumbs
	//--------------------------------------
	void AddBreadCrum(CPoint p);
	void DrawBreadCrumbs(CDC* pDC);
	//--------------------------------------
	// Energy
	//-------------------------------------
	double KineticEnergy();
	double PotentialEnergy(CBody* AttractingBody);
	void Print();
};

