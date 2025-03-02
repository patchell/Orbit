#pragma once


#define NUMBER_OF_BREADCRUMBS	600

class CBody
{
	CBody* m_pNext;
	CBody* m_pPrev;
	static int IdCount;
	//-------------------------
	// Body Attributes
	//-------------------------
	bool m_bFollow;
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
	CPoint m_pntScreen;
	//--------------------------
	// Bread Crumbs
	//--------------------------
	CPoint* m_pBreadCrumbs;
	int m_BreadCrumbsSize;
	int m_FirstBreadCrumb;
	int m_LastBreadCrumb;
	int m_numberOfBreadCrumbs;
	//----------------------------
	double m_Vel_Display;
	double m_X_Display;
	double m_Y_Display;
public:
	CBody() {
		m_bFollow = false;
		m_Vel_Display = 0.0;
		m_X_Display = 0.0;
		m_Y_Display = 0.0;
		m_vPos = CVector(0.0, 0.0);
		m_vVelocity = CVector(0.0, 0.0);
		m_pNext = 0;
		m_pPrev = 0;
		m_dMass = 1.0;
		m_Color = RGB(255, 255, 0);
		m_BreadCrumbsSize = NUMBER_OF_BREADCRUMBS;
		m_pBreadCrumbs = new CPoint[m_BreadCrumbsSize];
		m_numberOfBreadCrumbs = 0;
		m_FirstBreadCrumb = 0;
		m_LastBreadCrumb = 0;
		m_Radius = 3;
		m_BodyID = ++IdCount;
		m_KineticEnergy = 0.0;
		m_PotentialEnergy = 0.0;
		m_pntScreen = CPoint(0, 0);
	}
	virtual ~CBody() {}
	void Draw(CDC* pDC, double Scale, CSize CenterOffset);
	void PrintStats(CDC* pDC, int x, int y, bool Update) ;
	void PrintStats(FILE* pLog, const char* pS) ;
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
	double GetMass()  { return m_dMass; }
	CBody* GetNext() { return m_pNext; }
	void SetNext(CBody* next) { m_pNext = next; }
	CBody* GetPrev() { return m_pPrev; }
	void SetPrev(CBody* pP) { m_pPrev = pP; }
	CBody** GetNextPointer() { return &m_pNext; }
	void SetTemps(CVector pos, CVector v) {
		m_vPos_Temp = pos;
		m_vVelocity_Temp = v;
	}
	void Update() {
		m_vPos = m_vPos_Temp;
		m_vVelocity = m_vVelocity_Temp;
	}
	void SetColor(COLORREF c) { m_Color = c; }
	COLORREF GetColor()  { return m_Color; }
	void SetRadius(int r) { m_Radius = r; }
	int GetRadius()  { return m_Radius; }
	int GetID()  { return m_BodyID; }
	double Distance(CBody* pB)   {
		return GetPosition().Distance(pB->GetPosition());
	}
	CSize GetScreenCoordinate() { return CSize(m_pntScreen); }
	void DrawCircleAt(CDC* pDC, CPoint ptCenter, int Radius, COLORREF color);
	//--------------------------------------
	// Bread Crumbs
	//--------------------------------------
	void AddBreadCrum(CPoint p);
	void ResetBreadCrumbs();
	void DrawBreadCrumbs(CDC* pDC, double Scale, CSize CenterOffset);
	bool GetFollowFlag() { return m_bFollow; }
	void SetFollowFlag(bool F) { m_bFollow = F; }
	int GetNumberOfBreadCrumbs() { return m_numberOfBreadCrumbs; }
	void SetNumberOfBreadCrumbs(int n);
	//--------------------------------------
	// Energy
	//-------------------------------------
	double KineticEnergy();
	double PotentialEnergy(CBody* AttractingBody);
	void Print(int Indent);
};

