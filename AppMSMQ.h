// AppMSMQ.h : main header file for the APPMSMQ application
//

#if !defined(AFX_APPMSMQ_H__B69E34E6_5A3C_42D5_96D7_0904283A6A34__INCLUDED_)
#define AFX_APPMSMQ_H__B69E34E6_5A3C_42D5_96D7_0904283A6A34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAppMSMQApp:
// See AppMSMQ.cpp for the implementation of this class
//

//##ModelId=3C0DB2FF0239
class CAppMSMQApp : public CWinApp
{
public:
	//##ModelId=3C0DB2FF0243
	CAppMSMQApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppMSMQApp)
	public:
	//##ModelId=3C0DB2FF0244
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAppMSMQApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPMSMQ_H__B69E34E6_5A3C_42D5_96D7_0904283A6A34__INCLUDED_)
