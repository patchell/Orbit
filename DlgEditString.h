#pragma once
#include "afxdialogex.h"


// CDlgEditString dialog

class CDlgEditString : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEditString)

public:
	CDlgEditString(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgEditString();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EDIT_STRING
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
