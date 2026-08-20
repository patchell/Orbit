// DlgFollow.cpp : implementation file
//

#include "pch.h"
#include "Orbit.h"
#include "afxdialogex.h"
#include "DlgFollow.h"


// CDlgFollow dialog

IMPLEMENT_DYNAMIC(CDlgFollow, CDialogEx)

CDlgFollow::CDlgFollow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FOLLOW, pParent)
{
	m_pFollowBody = 0;
}

CDlgFollow::~CDlgFollow()
{
}

void CDlgFollow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FOLLOW_PICK, m_Combo_PickFollow);
}


BEGIN_MESSAGE_MAP(CDlgFollow, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_FOLLOW_PICK, &CDlgFollow::OnSelchangeComboFollowPick)
END_MESSAGE_MAP()


// CDlgFollow message handlers

BOOL CDlgFollow::OnInitDialog()
{
    CDialogEx::OnInitDialog();
	CString csText;

	m_pFollowBodyListHead = theApp.GetHead();
	m_Combo_PickFollow.ResetContent();
	CBody* pBody = m_pFollowBodyListHead;
	csText.Format(_T("%S"), "None");
	m_Combo_PickFollow.AddString(csText);
	for (int i = 0; i < NUMBER_OF_BODIES; i++)
	{
		csText.Format(_T("%S"), (LPCSTR)pBody->GetBodyState()->GetName());
		m_Combo_PickFollow.AddString(csText);
		pBody = pBody->GetNext();
	}
	m_Combo_PickFollow.SetCurSel(0);
    return TRUE;  
}

void CDlgFollow::OnOK()
{
	int sel = m_Combo_PickFollow.GetCurSel();

	if (sel == 0)
	{
		m_pFollowBody;
	}
	else
	{
		CBody* pBody = m_pFollowBodyListHead;
		for (int i = 1; i < sel; i++)
		{
			pBody = pBody->GetNext();
		}
		m_pFollowBody = pBody;
	}
	CDialogEx::OnOK();
}

void CDlgFollow::OnSelchangeComboFollowPick()
{
	// TODO: Add your control notification handler code here
}
