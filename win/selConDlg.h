/****************************FRAN***************************/
/*														   */
/*						  SELCONDLG.H					   */
/*														   */
/****************************FRAN***************************/

#ifndef SELCONDLG_H
#define SELCONDLG_H


#include "typedefs.h"


class SelConDlg : public CDialog
{
// Constructor
public:
	SelConDlg(void* pData, CWnd* pParent = NULL);   // Constructor estándard

// Dialog Data
	//{{AFX_DATA(SelConDlg)
	enum { IDD = IDD_FRAN_SELECT_CONECTOR };
	CListBox	listaCon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelConDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateList(void);//Solo actualizaré la lista para resaltar el seleccionado
	LC_FRAN_SEL_DATA* datos;

	// Generated message map functions
	//{{AFX_MSG(SelConDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
