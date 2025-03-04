// EditBody.cpp : implementation file
//

#include "pch.h"


// CEditBody dialog

IMPLEMENT_DYNAMIC(CEditBody, CDialog)

CEditBody::CEditBody(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_ADD_BODOES, pParent)
{
	m_pBody = 0;
	m_pHead = 0;
	m_2Pi = atan(1) * 8;
	pWin = 0;
}

CEditBody::~CEditBody()
{
}

void CEditBody::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MASS, m_Edit_Mass);
	DDX_Control(pDX, IDC_STATIC_BODYCOLOR, m_Static_Color);
	DDX_Control(pDX, IDC_EDIT_VELOCITY_MAG, m_Edit_VelMag);
	DDX_Control(pDX, IDC_EDIT_VELOCITY_ANGLE, m_Edit_VelAngle);
	DDX_Control(pDX, IDC_EDIT_POSITION_X, m_Edit_Pos_X);
	DDX_Control(pDX, IDC_EDIT_POSITION_Y, m_Edit_Pos_Y);
	DDX_Control(pDX, IDC_STATIC_BODY_ID, m_Static_BodyId);
	DDX_Control(pDX, IDC_EDIT_SETUP_RADIUS, m_EditRadius);
	DDX_Control(pDX, IDC_EDITBODIES_CHECK_FOLLOW, m_Check_Follow);
	DDX_Control(pDX, IDC_EDIT_BREAD_CRUMBS, m_Edit_Bread_Crumbs);
}


BEGIN_MESSAGE_MAP(CEditBody, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_NEXTBODY, &CEditBody::OnClickedButtonNextbody)
	ON_BN_CLICKED(IDOK, &CEditBody::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD_NEW__BODY, &CEditBody::OnClickedButtonAddNewBody)
	ON_STN_CLICKED(IDC_STATIC_BODYCOLOR, &CEditBody::OnClickedStaticBodycolor)
	ON_BN_CLICKED(IDC_EDITBODIES_CHECK_FOLLOW, &CEditBody::OnBnClickedEditbodiesCheckFollow)
	ON_EN_CHANGE(IDC_EDIT_VELOCITY_ANGLE, &CEditBody::OnChangeEditVelocityAngle)
END_MESSAGE_MAP()


// CEditBody message handlers


void CEditBody::OnClickedButtonNextbody()
{
	if(theApp.HasConsol()) printf("Next Body\n");
	UpdateBody();
	m_pBody = m_pBody->GetNext();
	if (m_pBody)
	{
		FillInFields();
	}
	else
	{
		m_pBody = m_pHead;
		FillInFields();
	}
}


void CEditBody::OnBnClickedOk()
{
	UpdateBody();
	CDialog::OnOK();
}


BOOL CEditBody::OnInitDialog()
{

	CDialog::OnInitDialog();

	if (m_pBody)	//edit exi8sting bodies
	{
		FillInFields();
	}
	else         //Create a new body
	{
		m_pBody = CreateDefault();
		theApp.AddBody(m_pBody);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

CBody* CEditBody::CreateDefault()
{
	CBody* pBody;
	pBody = new CBody();
	pBody->SetMass(300.0);
	pBody->SetPosition(CVector(500.0, 300.0));
	pBody->SetVelociry(CVector(0.0, 0.8));
	return pBody;
}

void CEditBody::FillInFields()
{
	CString csText;
	double x, y;
	double angle;

	//-----------------------------
	//  Body Radius
	//-----------------------------
	csText.Format(_T("%4.5lf"), m_pBody->GetInitialConditions()->GetRadius());
	m_EditRadius.SetWindowTextW(csText);
	//-----------------------------
	// update the edit fields
	//-----------------------------
	csText.Format(_T("%lf"), m_pBody->GetInitialConditions()->GetMass());
	m_Edit_Mass.SetWindowTextW(csText);
	//-------------------------------------
	// Velocity
	//-------------------------------------
	x = m_pBody->GetInitialConditions()->GetVelocity().m_x;
	y = m_pBody->GetInitialConditions()->GetVelocity().m_y;
	angle = atan2(y, x);
	angle = 360 * angle / m_2Pi;
	csText.Format(_T("%lf"), angle);
	m_Edit_VelAngle.SetWindowTextW(csText);
	csText.Format(_T("%lf"), m_pBody->GetVelocity().Mag());
	m_Edit_VelMag.SetWindowTextW(csText);
	//-----------------------------------------
	// Position
	//----------------------------------------
	csText.Format(_T("%lf"), m_pBody->GetInitialConditions()->GetPosition().m_x);
	m_Edit_Pos_X.SetWindowTextW(csText);
	csText.Format(_T("%lf"), m_pBody->GetInitialConditions()->GetPosition().m_y);
	m_Edit_Pos_Y.SetWindowTextW(csText);
	//--------------------------------------
	// Body Color
	//-------------------------------------
	m_Static_Color.SetColor(m_pBody->GetInitialConditions()->GetColer());
	//-------------------------------------
	// Body ID
	//-------------------------------------
	csText.Format(_T("Body-%d"), m_pBody->GetID());
	m_Static_BodyId.SetWindowTextW(csText);
	//----------------------------------------
	// Follow Flag
	//----------------------------------------
	if (m_pBody->GetFollowFlag())
	{
		m_Check_Follow.SetCheck(BST_CHECKED);
	}
	else
	{
		m_Check_Follow.SetCheck(BST_UNCHECKED);
	}
		
}

void CEditBody::UpdateBody()
{
	CString csText;
	double angle, mag, x, y;
	CVector V, P;
	double radius, mass;
	COLORREF color;

	//------------------------------------------
	// Radius
	//------------------------------------------
	m_EditRadius.GetWindowTextW(csText);
	radius = _wtof(csText);
	//------------------------------------------
	// Mass
	//------------------------------------------
	m_Edit_Mass.GetWindowTextW(csText);
	mass = _wtof(csText);
	//------------------------------------------
	// Position
	//------------------------------------------
	m_Edit_Pos_X.GetWindowTextW(csText);
	x = _wtof(csText);
	m_Edit_Pos_Y.GetWindowTextW(csText);
	y = _wtof(csText);
	P = CVector(x, y);
	//------------------------------------------
	//  Velocity
	//------------------------------------------
	m_Edit_VelMag.GetWindowTextW(csText);
	mag = _wtof(csText);
	m_Edit_VelAngle.GetWindowTextW(csText);
	angle = _wtof(csText);
	angle = m_2Pi * angle / 360.0;
	x = mag * cos(angle);
	y = mag * sin(angle);
	V = CVector(x,y);
	//----------------------------------------
	// Follow Body Flag
	//----------------------------------------
	if (m_Check_Follow.GetCheck() == BST_CHECKED)
		m_pBody->SetFollowFlag(1);
	else
		m_pBody->SetFollowFlag(0);
	//	m_pBody->Print(10);
	color = m_Static_Color.GetColor();
	m_pBody->GetInitialConditions()->Create(
		mass,
		V,
		P,
		color,
		radius
	);
}

void CEditBody::OnClickedButtonAddNewBody()
{
	CBody* pBody;

	pBody = CreateDefault();
	theApp.AddBody(pBody);
	m_pBody = m_pBody->GetNext();
	FillInFields();
}

void CEditBody::OnClickedStaticBodycolor()
{
	CColorDialog Dlg(m_pBody->GetColor(),CC_FULLOPEN,this);
	int ID;

	ID = Dlg.DoModal();
	if (IDOK == ID)
	{
		m_pBody->SetColor(Dlg.GetColor());
		m_Static_Color.SetColor(Dlg.GetColor());

	}
}

void CEditBody::OnBnClickedEditbodiesCheckFollow()
{
	UINT Checked = m_Check_Follow.GetCheck();
	CBody* pBody = m_pHead;
	if (Checked == BST_UNCHECKED)
	{
		m_Check_Follow.SetCheck(BST_CHECKED);
		while (pBody)
		{
			pBody->SetFollowFlag(0);
			pBody = pBody->GetNext();
		}
		m_pBody->SetFollowFlag(1);
		pWin->SetFollowBody(this->m_pBody);
	}
	else
	{
		m_Check_Follow.SetCheck(BST_UNCHECKED);
		pWin->SetFollowBody(0);;
	}

}

void CEditBody::OnChangeEditVelocityAngle()
{
	double angle;
	double mag;
	double x, y;
	CString csText;

	m_Edit_VelMag.GetWindowTextW(csText);
	mag = _wtof(csText);
	m_Edit_VelAngle.GetWindowTextW(csText);
	angle = _wtof(csText);
	angle = m_2Pi * angle / 360.0;
	x = mag * cos(angle);
	y = mag * sin(angle);
	if(theApp.HasConsol()) printf("ANGLE = %5.2lf X = %8.2lf Y = %8.2lf\n", angle, x, y);
}
