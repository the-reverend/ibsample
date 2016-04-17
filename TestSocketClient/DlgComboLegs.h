#if !defined(AFX_DLGCOMBOLEGS_H__BCE33E9E_1535_4181_8C3D_F5E0C632A979__INCLUDED_)
#define AFX_DLGCOMBOLEGS_H__BCE33E9E_1535_4181_8C3D_F5E0C632A979__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgComboLegs.h : header file
//

#include "Contract.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgComboLegs dialog
class CDlgOrder;

class CDlgComboLegs : public CDialog
{
public:

	typedef Contract::ComboLegList ComboLegList;

public:

	CDlgComboLegs( ComboLegList& comboLegs, const CString& orderExchange, CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(CDlgComboLegs)
	enum { IDD = IDD_COMBOLEGS };
	CListCtrl   m_lstComboLegs;
	int      m_conId;
	int      m_ratio;
	CString  m_side;
	CString  m_exchange;
	int      m_openClose;
	int     m_shortSaleSlot;
	CString m_designatedLocation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgComboLegs)
public:
protected:
	virtual void DoDataExchange( CDataExchange* pDX );  // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgComboLegs)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAddLeg();
	afx_msg void OnBtnRemoveLeg();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	ComboLegList& m_comboLegs;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOMBOLEGS_H__BCE33E9E_1535_4181_8C3D_F5E0C632A979__INCLUDED_)
