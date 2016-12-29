// AppMSMQDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AppMSMQ.h"
#include "AppMSMQDlg.h"
#include "agsMSMQ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

//##ModelId=3C0DB30000C8
class CAboutDlg : public CDialog
{
public:
	//##ModelId=3C0DB30000D2
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	//##ModelId=3C0DB30000D3
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//##ModelId=3C0DB30000D2
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

//##ModelId=3C0DB30000D3
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppMSMQDlg dialog

//##ModelId=3C0DB2FF00EE
CAppMSMQDlg::CAppMSMQDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppMSMQDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppMSMQDlg)
	m_sLabel = _T("");
	m_sPath = _T("");
	m_sServer = _T("");
	m_sMessage = _T("");
	m_sMessageLabel = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//##ModelId=3C0DB2FF01B6
void CAppMSMQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppMSMQDlg)
	DDX_Control(pDX, IDC_MESSAGELIST, m_cMessage);
	DDX_Text(pDX, IDC_LABEL, m_sLabel);
	DDV_MaxChars(pDX, m_sLabel, 256);
	DDX_Text(pDX, IDC_PATH, m_sPath);
	DDV_MaxChars(pDX, m_sPath, 256);
	DDX_Text(pDX, IDC_SERVER, m_sServer);
	DDV_MaxChars(pDX, m_sServer, 256);
	DDX_Text(pDX, IDC_MSG, m_sMessage);
	DDV_MaxChars(pDX, m_sMessage, 1000);
	DDX_Text(pDX, IDC_LABEL_MSG, m_sMessageLabel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAppMSMQDlg, CDialog)
	//{{AFX_MSG_MAP(CAppMSMQDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PUBQUE_BTN, OnPubqueBtn)
	ON_BN_CLICKED(IDC_PRIVATE_BTN, OnPrivateBtn)
	ON_BN_CLICKED(IDC_DELPUBQ_BTN, OnDelpubqBtn)
	ON_BN_CLICKED(IDC_DELEPRIVATEQ_BTN, OnDeleprivateqBtn)
	ON_BN_CLICKED(IDC_SENDPUB_BTN, OnSendpubBtn)
	ON_BN_CLICKED(IDC_SENDPRV_BTN, OnSendprvBtn)
	ON_BN_CLICKED(IDC_ALLPUB_BTN, OnAllpubBtn)
	ON_BN_CLICKED(IDC_ALLPRV_BTN, OnAllprvBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppMSMQDlg message handlers

//##ModelId=3C0DB2FF01CA
BOOL CAppMSMQDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_cMessage.InsertColumn(0,"Label Message",LVCFMT_LEFT,150);
	m_cMessage.InsertColumn(1,"Message",LVCFMT_LEFT,280);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//##ModelId=3C0DB2FF01D5
void CAppMSMQDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

//##ModelId=3C0DB2FF01E1
void CAppMSMQDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//##ModelId=3C0DB2FF01EA
HCURSOR CAppMSMQDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//##ModelId=3C0DB2FF01F3
void CAppMSMQDlg::OnPubqueBtn() 
{
	agsMSMQ mque;

	UpdateData();
	CWaitCursor wait;
	
	if(!mque.CreatePublicQ(m_sServer,m_sPath,m_sLabel))
	{
		AfxMessageBox(mque.getErrorMsg());
		return;
	}

	AfxMessageBox("Create Public Queue succesfully");

}

//##ModelId=3C0DB2FF01FD
void CAppMSMQDlg::OnPrivateBtn() 
{
	agsMSMQ mque;

	UpdateData();
	CWaitCursor wait;
	
	if(!mque.CreatePrivateQ(m_sServer,m_sPath,m_sLabel))
	{
		AfxMessageBox(mque.getErrorMsg());
		return;
	}

	AfxMessageBox("Create Private Queue succesfully");
	
}

//##ModelId=3C0DB2FF0207
void CAppMSMQDlg::OnDelpubqBtn() 
{
	agsMSMQ mque;

	UpdateData();
	CWaitCursor wait;
	
	if(!mque.DeletePublicQ(m_sServer,m_sPath))
	{
		AfxMessageBox(mque.getErrorMsg());
		return;
	}

	AfxMessageBox("Delete Public Queue succesfully");
}

//##ModelId=3C0DB2FF0209
void CAppMSMQDlg::OnDeleprivateqBtn() 
{
	agsMSMQ mque;

	UpdateData();
	CWaitCursor wait;
	
	if(!mque.DeletePrivateQ(m_sServer,m_sPath))
	{
		AfxMessageBox(mque.getErrorMsg());
		return;
	}

	AfxMessageBox("Delete Private Queue succesfully");
}

//##ModelId=3C0DB2FF0212
void CAppMSMQDlg::OnSendpubBtn() 
{
	agsMSMQ mque;

	UpdateData();
	CWaitCursor wait;
	
	if(!mque.SendPublicQ(m_sServer,m_sPath,m_sMessageLabel,m_sMessage))
	{
		AfxMessageBox(mque.getErrorMsg());
		return;
	}

	AfxMessageBox("Send Public Message succesfully");	
}

//##ModelId=3C0DB2FF021C
void CAppMSMQDlg::OnSendprvBtn() 
{
	agsMSMQ mque;

	UpdateData();
	CWaitCursor wait;
	
	if(!mque.SendPrivateQ(m_sServer,m_sPath,m_sMessageLabel,m_sMessage))
	{
		AfxMessageBox(mque.getErrorMsg());
		return;
	}

	AfxMessageBox("Send Public Message succesfully");	
}

//##ModelId=3C0DB2FF0225
void CAppMSMQDlg::OnAllpubBtn() 
{
	agsMSMQ mque;	
	int current;
	MQmsg msg;
	HRESULT hr;

	UpdateData();
	CWaitCursor wait;
	m_cMessage.DeleteAllItems();
	if(!mque.PrepareGetMessage(m_sServer,m_sPath,0))
	{
		AfxMessageBox(mque.getErrorMsg());
		return;
	}

	msg		= mque.getMessageQ();
	current = m_cMessage.InsertItem(0,msg.label);
	m_cMessage.SetItemText(current,1, msg.msg);	
	do
	{
		    hr	= mque.getMSMQmsg(); 
			if(hr!=0) break;
			msg		= mque.getMessageQ();
			current = m_cMessage.InsertItem(0,msg.label);
			m_cMessage.SetItemText(current,1, msg.msg);		
			
		
	}while(hr==0);
	
	if(!mque.closeMSMQ())
	{
		AfxMessageBox(mque.getErrorMsg());
		return;
	}

	if(mque.getTotalMessage()==0)
	{
		AfxMessageBox("No message in Message Queue");
	}else
	{
		CString mseg;
		mseg.Format("Get %d message(s) from public queue successfully",mque.getTotalMessage());
		AfxMessageBox(mseg);		
	}
}

//##ModelId=3C0DB2FF022F
void CAppMSMQDlg::OnAllprvBtn() 
{
	agsMSMQ mque;	
	int current;
	MQmsg msg;
	HRESULT hr;

	UpdateData();
	CWaitCursor wait;
	m_cMessage.DeleteAllItems();
	if(!mque.PrepareGetMessage(m_sServer,m_sPath,1))
	{
		AfxMessageBox(mque.getErrorMsg());
		return;
	}

	msg		= mque.getMessageQ();
	current = m_cMessage.InsertItem(0,msg.label);
	m_cMessage.SetItemText(current,1, msg.msg);	

	do
	{
		    hr	= mque.getMSMQmsg();
			if(hr!=0) break;

			msg		= mque.getMessageQ();
			current = m_cMessage.InsertItem(0,msg.label);
			m_cMessage.SetItemText(current,1, msg.msg);		
		
	}while(hr==0);
	
	if(!mque.closeMSMQ())
	{
		AfxMessageBox(mque.getErrorMsg());
		return;
	}

	if(mque.getTotalMessage()==0)
	{
		AfxMessageBox("No message in Message Queue");
	}else
	{
		CString mseg;
		mseg.Format("Get %d message(s) from private queue successfully",mque.getTotalMessage());
		AfxMessageBox(mseg);
		
	}	
}
