/****************************FRAN***************************/
/*														   */
/*						  LCIDLG.CPP					   */
/*														   */
/****************************FRAN***************************/


#include "stdafx.h"
#include "leocad.h"
#include "lciDlg.h"
//????????????
#include "tools.h"
#include "resource.hm"
//????????????


/***********************************************************/

LCIDlg::LCIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LCIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(LCIDlg)
	m_strLCI = _T("");
	//}}AFX_DATA_INIT
}

/***********************************************************/

void LCIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LCIDlg)
	DDX_Text(pDX, IDC_FRAN_EDIT_LCI_PATH, m_strLCI); //???????????????
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(LCIDlg, CDialog)
	//{{AFX_MSG_MAP(LCIDlg)
	ON_BN_CLICKED(IDC_FRAN_LCIDLG_LCIBROWSE, OnLCIbrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/***********************************************************/

BOOL LCIDlg::OnInitDialog()
{
	m_strLCI = theApp.GetProfileString ("Settings", "LCI", ""); //????????????

	CDialog::OnInitDialog();

	return TRUE;
}

/***********************************************************/

void LCIDlg::OnOK()
{
	UpdateData (TRUE);

	if (m_strLCI.GetLength() == 0)
		return;

	theApp.WriteProfileString ("Settings", "LCI", m_strLCI);

	CDialog::OnOK();
}

/***********************************************************/

void LCIDlg::OnLCIbrowse()
{
	CString str;

	if (FolderBrowse(&str, _T("Select LCI folder"), GetSafeHwnd()))
	{
		UpdateData(TRUE);
		m_strLCI = str;
		UpdateData(FALSE);
	}
}

