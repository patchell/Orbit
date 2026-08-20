#pragma once
#include "afxdialogex.h"


// CDlgFollow dialog

class CDlgFollow : public CDialogEx
{
	CComboBox m_Combo_PickFollow;
	CBody* m_pFollowBodyListHead;
	DECLARE_DYNAMIC(CDlgFollow)
public:
	CBody* m_pFollowBody;
public:
	CDlgFollow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgFollow();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FOLLOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
    afx_msg void OnSelchangeComboFollowPick();
};
