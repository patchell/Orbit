// DlgEditString.cpp : implementation file
//

#include "pch.h"
#include "Orbit.h"
#include "afxdialogex.h"
#include "DlgEditString.h"


// CDlgEditString dialog

IMPLEMENT_DYNAMIC(CDlgEditString, CDialogEx)

CDlgEditString::CDlgEditString(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EDIT_STRING, pParent)
{

}

CDlgEditString::~CDlgEditString()
{
}

void CDlgEditString::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgEditString, CDialogEx)
END_MESSAGE_MAP()


// CDlgEditString message handlers
