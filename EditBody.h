#pragma once


// CEditBody dialog

class CEditBody : public CDialog
{
	double m_2Pi;
	CBody* m_pBody;
	CBody* m_pHead;
	CStatic m_Static_BodyId;
	CEdit m_Edit_Mass;
	CStaticBitmap m_Static_Color;
	CEdit m_Edit_VelMag;
	CEdit m_Edit_VelAngle;
	CEdit m_Edit_Pos_X;
	CEdit m_Edit_Pos_Y;
	DECLARE_DYNAMIC(CEditBody)

public:
	CEditBody(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CEditBody();
	afx_msg void OnClickedButtonNextbody();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CBody* CreateDefault();
	void SetBody(CBody* pBod) {
		m_pBody = pBod;
		m_pHead = pBod;
	}
	void FillInFields();
	void UpdateBody();
	afx_msg void OnClickedButtonAddNewBody();
	afx_msg void OnClickedStaticBodycolor();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_BODOES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};
