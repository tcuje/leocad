// HiloBase.cpp : implementation file
//

#include "stdafx.h"
#include "HiloBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHiloBase

IMPLEMENT_DYNAMIC(CHiloBase, CWinThread)

CHiloBase::CHiloBase(CWnd* pWnd, HDC hDC,int *vals,int id)
{

	m_font.CreateStockObject( DEFAULT_GUI_FONT );
	m_iID = id;
    int pos = m_iID;
	m_bAutoDelete = FALSE;

	m_pMainWnd = pWnd;
	m_pMainWnd->GetClientRect(&m_rectBorde);
	m_hDC = hDC;
	m_bTerminar = false;

	int margen = 20;
	m_rectBorde.top += margen;
	m_rectBorde.left += margen*(pos+1) + ANCHO*pos;
	m_rectBorde.bottom = m_rectBorde.top + MAX_VALORES*2;
	m_rectBorde.right = m_rectBorde.left + ANCHO;

	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	m_hPen = (HPEN)pen.Detach();

	m_dc.Attach(m_hDC);
	m_pen.Attach(m_hPen);

	for(int i = 0 ; i < MAX_VALORES;i++)
		m_piValores[i] = vals[i];

}


BOOL CHiloBase::InitInstance(){


	return TRUE;
}

void CHiloBase::PintarTodo()
{
/*	CPoint a;
	CPoint b;

	a.x = m_rectBorde.left ;

	CPen* oldpen;
	for(int i = 0 ; i < MAX_VALORES ; i++){
		a.y = m_rectBorde.top + i*2;
		b.y = m_rectBorde.top + i*2;
		b.x = m_rectBorde.left + m_piValores[i];
		oldpen = m_dc.SelectObject(&m_pen);
		m_dc.MoveTo(a);
		m_dc.LineTo(b);
	}
	CRect tmp = m_rectBorde;
	tmp.top -= 18;
	m_dc.SelectObject(&m_font);
	m_dc.DrawText(m_sNombre,tmp,DT_CENTER);
	m_dc.SelectObject(oldpen);
*/
	AfxMessageBox("hola");

}

CHiloBase::~CHiloBase()
{
	m_dc.Detach();
}

void CHiloBase::Intercambiar(int x, int y)
{
	int tmp = m_piValores[x];
	m_piValores[x] = m_piValores[y];
	m_piValores[y] = tmp;


	Marcar(y);
	Marcar(x);

	Sleep(10);

	Borrar(x);
	Borrar(y);

	Pintar(x);
	Pintar(y);

	m_iIterac++;

	CString str;
	str.Format("Iteración %d",m_iIterac);

	CRect rct= m_rectBorde;
	rct.top = rct.bottom;
	rct.bottom = rct.top  +20;
	m_dc.DrawText(str,rct,DT_CENTER);

}

void CHiloBase::Borrar(int pos)
{
	CPoint a;
	CPoint b;

	a.x = m_rectBorde.left;
	b.x = m_rectBorde.right;

	CPen* oldpen;

	CPen pen(PS_SOLID, 1, RGB(255,255,255));

	a.y = m_rectBorde.top + pos*2;
	b.y = m_rectBorde.top + pos*2;

	oldpen = m_dc.SelectObject(&pen);
	m_dc.MoveTo(a);
	m_dc.LineTo(b);
	m_dc.SelectObject(oldpen);
}

void CHiloBase::Pintar(int pos)
{
	CPoint a;
	CPoint b;

	a.x = m_rectBorde.left ;
	b.x = m_rectBorde.left + m_piValores[pos] ;

	CPen* oldpen;

	CPen pen(PS_SOLID, 1, RGB(0,0,0));

	a.y = m_rectBorde.top + pos*2;
	b.y = m_rectBorde.top + pos*2;

	oldpen = m_dc.SelectObject(&pen);
	m_dc.MoveTo(a);
	m_dc.LineTo(b);
	m_dc.SelectObject(oldpen);
}

void CHiloBase::Marcar(int pos)
{
	CPoint a;
	CPoint b;

	a.x = m_rectBorde.left ;
	b.x = m_rectBorde.right;

	CPen* oldpen;

	CPen pen(PS_SOLID, 1, RGB(200,0,0));

	a.y = m_rectBorde.top + pos*2;
	b.y = m_rectBorde.top + pos*2;

	oldpen = m_dc.SelectObject(&pen);
	m_dc.MoveTo(a);
	m_dc.LineTo(b);
	m_dc.SelectObject(oldpen);
}
