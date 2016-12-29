// AppMSMQDlg.h : header file
//

#if !defined(AFX_APPMSMQDLG_H__AFC3AC85_0BEE_46E2_818A_A5DBA5086D6C__INCLUDED_)
#define AFX_APPMSMQDLG_H__AFC3AC85_0BEE_46E2_818A_A5DBA5086D6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAppMSMQDlg dialog

//##ModelId=3C0DB2FF00A1
class CAppMSMQDlg : public CDialog
{
// Construction
public:
	//##ModelId=3C0DB2FF00EE
	CAppMSMQDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAppMSMQDlg)
	enum { IDD = IDD_APPMSMQ_DIALOG };
	//##ModelId=3C0DB2FF0134
	CListCtrl	m_cMessage;
	//##ModelId=3C0DB2FF013E
	CString	m_sLabel;
	//##ModelId=3C0DB2FF0198
	CString	m_sPath;
	//##ModelId=3C0DB2FF01A2
	CString	m_sServer;
	//##ModelId=3C0DB2FF01A3
	CString	m_sMessage;
	//##ModelId=3C0DB2FF01AC
	CString	m_sMessageLabel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppMSMQDlg)
	protected:
	//##ModelId=3C0DB2FF01B6
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//##ModelId=3C0DB2FF01C1
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAppMSMQDlg)
	//##ModelId=3C0DB2FF01CA
	virtual BOOL OnInitDialog();
	//##ModelId=3C0DB2FF01D5
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//##ModelId=3C0DB2FF01E1
	afx_msg void OnPaint();
	//##ModelId=3C0DB2FF01EA
	afx_msg HCURSOR OnQueryDragIcon();
	//##ModelId=3C0DB2FF01F3
	afx_msg void OnPubqueBtn();
	//##ModelId=3C0DB2FF01FD
	afx_msg void OnPrivateBtn();
	//##ModelId=3C0DB2FF0207
	afx_msg void OnDelpubqBtn();
	//##ModelId=3C0DB2FF0209
	afx_msg void OnDeleprivateqBtn();
	//##ModelId=3C0DB2FF0212
	afx_msg void OnSendpubBtn();
	//##ModelId=3C0DB2FF021C
	afx_msg void OnSendprvBtn();
	//##ModelId=3C0DB2FF0225
	afx_msg void OnAllpubBtn();
	//##ModelId=3C0DB2FF022F
	afx_msg void OnAllprvBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPMSMQDLG_H__AFC3AC85_0BEE_46E2_818A_A5DBA5086D6C__INCLUDED_)
