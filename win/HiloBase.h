#if !defined(AFX_HILOBASE_H__4815F74C_370C_11D2_9291_000021F2B5E0__INCLUDED_)
#define AFX_HILOBASE_H__4815F74C_370C_11D2_9291_000021F2B5E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HiloBase.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CHiloBase thread

#define MAX_VALORES 150
#define ANCHO MAX_VALORES

class CHiloBase : public CWinThread
{
	DECLARE_DYNAMIC(CHiloBase)
protected:
	CFont m_font;
	long m_iIterac;
	CString m_sNombre;
	HDC m_hDC;
	CDC m_dc;
	CRect m_rectBorde;

	HPEN m_hPen;
	CPen m_pen;

	void Marcar(int pos);
	int m_iID;
	void Pintar(int pos);
	void Borrar(int pos);
	void Intercambiar(int a,int b);
	virtual  ~CHiloBase();
	int m_piValores[MAX_VALORES];

	CHiloBase(CWnd* pWnd, HDC hDC,int *vals,int id);

	//{{AFX_VIRTUAL(CHiloBase)
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
public:
	bool m_bTerminar;
	void PintarTodo();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HILOBASE_H__4815F74C_370C_11D2_9291_000021F2B5E0__INCLUDED_)
