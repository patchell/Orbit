#pragma once


#define NUMBER_OF_BREADCRUMBS	600

class CBody
{
	struct SAttributes {
		double m_Mass;
		CVector m_Velocity;
		CVector m_Position;
		COLORREF m_Color;
		double m_Radius;
		SAttributes() {
			m_Mass = 1.0;
			m_Velocity = CVector(0.0, 0.0);
			m_Position = CVector(0.0, 0.0);;
			m_Color = RGB(0,0,0);
			m_Radius = 1.0;
		}
		void Create(
			double Mass,
			CVector Velocity,
			CVector Position,
			COLORREF color,
			double Radius
		)
		{
			m_Mass = Mass;
			m_Velocity = Velocity;
			m_Position = Position;;
			m_Color = color;
			m_Radius = Radius;
		}
		double GetMass() { return m_Mass; }
		CVector GetVelocity() { return m_Velocity; }
		CVector GetPosition() { return m_Position; }
		COLORREF GetColer() { return m_Color; }
		double GetRadius() { return m_Radius; }
		void Copy(SAttributes* Src)
		{
			m_Mass = Src->m_Mass;
			m_Velocity = Src->m_Velocity;
			m_Position = Src->m_Position;;
			m_Color = Src->m_Color;
			m_Radius = Src->m_Radius;
		}
	};
	CBody* m_pNext;
	CBody* m_pPrev;
	static int IdCount;
	//-------------------------
	// Body Attributes
	//-------------------------
	bool m_bFollow;
	int m_BodyID;
	SAttributes m_InitialConditions;
	SAttributes m_BodyState;
	CVector m_vPos_Temp;
	CVector m_vVelocity_Temp;
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
		m_pNext = 0;
		m_pPrev = 0;
		m_BreadCrumbsSize = NUMBER_OF_BREADCRUMBS;
		m_pBreadCrumbs = new CPoint[m_BreadCrumbsSize];
		m_numberOfBreadCrumbs = 0;
		m_FirstBreadCrumb = 0;
		m_LastBreadCrumb = 0;
		m_BodyID = ++IdCount;
		m_KineticEnergy = 0.0;
		m_PotentialEnergy = 0.0;
		m_pntScreen = CPoint(0, 0);
	}
	virtual ~CBody() {}
	void Create(
		double Mass,
		CVector Velocity,
		CVector Position,
		COLORREF color,
		double Radius
	);
	SAttributes* GetInitialConditions() {
		return &m_InitialConditions
			;
	}
	SAttributes* GetBodyState() {
		return &m_BodyState;
	}
	void Reset();
		void Draw(CDC* pDC, double Scale, CSize CenterOffset);
	void PrintStats(CDC* pDC, int x, int y, bool Update) ;
	void PrintStats(FILE* pLog, const char* pS) ;
	void SetVelociry(CVector v)
	{
		m_BodyState.m_Velocity = v;
	}
	CVector GetVelocity() { return m_BodyState.m_Velocity; }
	void SetPosition(CVector v) {
		m_BodyState.m_Position = v;
	}
	CVector GetPosition() { return m_BodyState.m_Position; }
	void SetMass(double m) { 
		m_BodyState.m_Mass = m;
	}
	double GetMass()  { return m_BodyState.m_Mass; }
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
		m_BodyState.m_Position = m_vPos_Temp;
		m_BodyState.m_Velocity = m_vVelocity_Temp;
	}
	void SetColor(COLORREF c) { m_BodyState.m_Color = c; }
	COLORREF GetColor()  { return m_BodyState.m_Color; }
	void SetRadius(int r) { m_BodyState.m_Radius = r; }
	int GetRadius()  { return m_BodyState.m_Radius; }
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
	void CopyAttributs(SAttributes* pDest, SAttributes* pSrc);
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

