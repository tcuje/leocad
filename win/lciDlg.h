/****************************FRAN***************************/
/*														   */
/*						   LCIDLG.H						   */
/*														   */
/****************************FRAN***************************/


#ifndef LCIDLG_H
#define LCIDLG_H


class LCIDlg : public CDialog
{
// Construction
public:
	LCIDlg(CWnd* pParent = NULL);   /**< Constructor estándard. */

	//Datos del diálogo
	//{{AFX_DATA(LCIDlg)
	enum { IDD = IDD_FRAN_LCI_DIRECTORY };
	CString	m_strLCI;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LCIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//static const DWORD m_nHelpIDs[];

	// Generated message map functions
	//{{AFX_MSG(LCIDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLCIbrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
