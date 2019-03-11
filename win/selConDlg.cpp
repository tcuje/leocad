/****************************FRAN***************************/
/*														   */
/*						  SELCONDLG.CPP					   */
/*														   */
/****************************FRAN***************************/


#include "stdafx.h"
#include "leocad.h"
#include "selConDlg.h"


/***********************************************************/

SelConDlg::SelConDlg(void* pData, CWnd* pParent /*=NULL*/)
: CDialog(SelConDlg::IDD, pParent)
{
	datos=(LC_FRAN_SEL_DATA*)pData;
}

/***********************************************************/

void SelConDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelConDlg)
	DDX_Control(pDX, IDC_FRAN_CONECTOR_LIST, listaCon);
	//}}AFX_DATA_MAP
}

/***********************************************************/

BEGIN_MESSAGE_MAP(SelConDlg, CDialog)
	//{{AFX_MSG_MAP(SelConDlg)
	ON_LBN_SELCHANGE(IDC_SELDLG_LIST, OnSelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// SelConDlg message handlers

BOOL SelConDlg::OnInitDialog()
{

	CDialog::OnInitDialog();

	UpdateList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/***********************************************************/

void SelConDlg::OnOK()
{

	UpdateData(TRUE);

	/*****FRAN*****/
	//Cuando se llama a la fucnión del project o otra clase para decirle la información elegida!!!!!
	/*****FRAN*****/
	CDialog::OnOK();
}

/***********************************************************/

void SelConDlg::UpdateList(void)
{
	UpdateData(TRUE);
	int index,i;

	for(i=0;datos[i].puntero!=NULL;i++)
	{
		index=listaCon.AddString(datos[i].nombre);
		listaCon.SetItemDataPtr(index,&datos[i]);
	}

	for(index=0;index<listaCon.GetCount();index++)
	{
		listaCon.SetSel(index,((LC_FRAN_SEL_DATA*)listaCon.GetItemData(index))->seleccionado);
	}


}

/***********************************************************/

void SelConDlg::OnSelChange()
{
	int index;

	for(index=0;index<SelConDlg::listaCon.GetCount();index++)
	{
		((LC_FRAN_SEL_DATA*)listaCon.GetItemDataPtr(index))->seleccionado=(listaCon.GetSel(index)!=0);
	}
}
