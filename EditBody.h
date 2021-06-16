#pragma once


// CEditBody dialog

class CEditBody : public CDialog
{
	double m_2Pi;
	CBody* m_pBody;
	DECLARE_DYNAMIC(CEditBody)

public:
	CEditBody(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CEditBody();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_BODOES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit_Mass;
	CStatic m_Static_Color;
	CEdit m_Edit_VelMag;
	CEdit m_Edit_VelAngle;
	CEdit m_Edit_Pos_X;
	CEdit m_Edit_Pos_Y;
	afx_msg void OnClickedButtonNextbody();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void CreateDefault();
	void FillInFields();
	void UpdateBody();
};
