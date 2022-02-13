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
}


BEGIN_MESSAGE_MAP(CEditBody, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_NEXTBODY, &CEditBody::OnClickedButtonNextbody)
	ON_BN_CLICKED(IDOK, &CEditBody::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD_NEW__BODY, &CEditBody::OnClickedButtonAddNewBody)
	ON_STN_CLICKED(IDC_STATIC_BODYCOLOR, &CEditBody::OnClickedStaticBodycolor)
END_MESSAGE_MAP()


// CEditBody message handlers


void CEditBody::OnClickedButtonNextbody()
{
	printf("Next Body\n");
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
		ADDBODY(m_pBody);
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
	// update the edit fields
	// from the body class
	//-----------------------------
	csText.Format(_T("%lf"), m_pBody->GetMass());
	m_Edit_Mass.SetWindowTextW(csText);
	//-------------------------------------
	// Velocity
	//-------------------------------------
	x = m_pBody->GetVelocity().m_x;
	y = m_pBody->GetVelocity().m_y;
	angle = atan2(y, x);
	angle = 360 * angle / m_2Pi;
	csText.Format(_T("%lf"), angle);
	m_Edit_VelAngle.SetWindowTextW(csText);
	csText.Format(_T("%lf"), m_pBody->GetVelocity().Mag());
	m_Edit_VelMag.SetWindowTextW(csText);
	//-----------------------------------------
	// Position
	//----------------------------------------
	csText.Format(_T("%lf"), m_pBody->GetPosition().m_x);
	m_Edit_Pos_X.SetWindowTextW(csText);
	csText.Format(_T("%lf"), m_pBody->GetPosition().m_y);
	m_Edit_Pos_Y.SetWindowTextW(csText);
	//--------------------------------------
	// Body Color
	//-------------------------------------
	m_Static_Color.SetColor(m_pBody->GetColor());
	//-------------------------------------
	// Body ID
	//-------------------------------------
	csText.Format(_T("Body-%d"), m_pBody->GetID());
	m_Static_BodyId.SetWindowTextW(csText);
}

void CEditBody::UpdateBody()
{
	CString csText;
	double x, y, angle, mag;

	//------------------------------------------
	// Mass
	//------------------------------------------
	m_Edit_Mass.GetWindowTextW(csText);
	m_pBody->SetMass(_wtof(csText));
	//------------------------------------------
	// Position
	//------------------------------------------
	m_Edit_Pos_X.GetWindowTextW(csText);
	x = _wtof(csText);
	m_Edit_Pos_Y.GetWindowTextW(csText);
	y = _wtof(csText);
	m_pBody->SetPosition(CVector(x, y));
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
	m_pBody->SetVelociry(CVector(x,y));
	m_pBody->Print();
}

void CEditBody::OnClickedButtonAddNewBody()
{
	CBody* pBody;

	pBody = CreateDefault();
	ADDBODY(pBody);
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
