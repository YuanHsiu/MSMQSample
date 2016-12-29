/////////////////////////////////////////////////////////////////////
//
// Agus Kurniawan <agusasia@yahoo.com>
// Copyright 2001,
// First release : November 20, 2001
//
//////////////////////////////////////////////////////////////////////  
// File         : agsMSMQ.cpp: 
// Version		: 1.0
// Description  : implementation of the agsMSMQ class.
//////////////////////////////////////////////////////////////////////
// File         : agsMSMQ.cpp: 
// Version		: 1.1
// Date			: January 16, 2002  
// Description  : Modified on PrepareGetMessage() and getMSMQmsg()
/////////////////////////////////////////////////////////////////////////////
// Note : Don't forget to add library file ,mqrt.lib , 
//        into your project
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "agsMSMQ.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=3C0DB2FF0351
agsMSMQ::agsMSMQ()
{
	pSecurity = NULL;
	dwIDprop = 0;
	dwBufferLength = 256;
}

//##ModelId=3C0DB2FF0352
agsMSMQ::~agsMSMQ()
{

}

//##ModelId=3C0DB2FF0379
void agsMSMQ::InitialMQQueue()
{
	QProps.cProp = dwIDprop;
	QProps.aPropID = QPropID;
	QProps.aPropVar = QPropVar;
	QProps.aStatus = QStatus;
}

//##ModelId=3C0DB2FF0354
void agsMSMQ::InitialMQMSG()
{
	QPropMsg.cProp		= dwIDprop;
	QPropMsg.aPropID	= QMsg;
	QPropMsg.aPropVar	= QPropVar;
	QPropMsg.aStatus	= QStatus;
}

//##ModelId=3C0DB2FF0349
CString agsMSMQ::getErrorMsg()
{
	return m_sError;
}


//##ModelId=3C0DB2FF0367
void agsMSMQ::InitialPropidQ()
{
	QPropID[dwIDprop]			= PROPID_Q_PATHNAME;
	QPropVar[dwIDprop].vt		= VT_LPWSTR;
	QPropVar[dwIDprop].pwszVal	= (LPWSTR)wszPath;
	dwIDprop++;

	QPropID[dwIDprop]			= PROPID_Q_LABEL;
	QPropVar[dwIDprop].vt		= VT_LPWSTR;
	QPropVar[dwIDprop].pwszVal	= (LPWSTR)wszLabel;
	dwIDprop++;
}

//##ModelId=3C0DB2FF035B
void agsMSMQ::InitialPropidBody(CString label,CString msg)
{		
	dwAccessMode = MQ_SEND_ACCESS;
	dwShareMode = MQ_DENY_NONE;
	
    strcpy((char*)pMessage,msg);

	QMsg[dwIDprop]				= PROPID_M_LABEL;                  
	QPropVar[dwIDprop].vt		= VT_LPWSTR;                   
	QPropVar[dwIDprop].pwszVal	=(LPWSTR) label.AllocSysString(); 
	dwIDprop++;
	
	QMsg[dwIDprop]					= PROPID_M_BODY;
	QPropVar[dwIDprop].vt			= VT_VECTOR | VT_UI1;	
	QPropVar[dwIDprop].caub.pElems	= pMessage;
	QPropVar[dwIDprop].caub.cElems	= strlen(msg);
	dwIDprop++;	

	QMsg[dwIDprop]			 = PROPID_M_DELIVERY;            
	QPropVar[dwIDprop].vt	 = VT_UI1;                   
	QPropVar[dwIDprop].bVal  = MQMSG_DELIVERY_RECOVERABLE;
	dwIDprop++;   
}

//##ModelId=3C0DB2FF033E
BOOL agsMSMQ::CreatePublicQ(CString serv, CString pathmsg,CString label)
{
	
	m_sPathQ.Format(_T("%s\\%s"),serv,pathmsg);
    m_sLabelQ.Format(_T("%s"),label);
	::MultiByteToWideChar(CP_ACP,0,m_sPathQ,-1,(LPWSTR)wszPath,sizeof(wszPath));
	::MultiByteToWideChar(CP_ACP,0,m_sLabelQ,-1,(LPWSTR)wszLabel,sizeof(wszLabel));

	InitialPropidQ();
	InitialMQQueue();

	hr = MQCreateQueue(pSecurity,
		               &QProps,
					   wszBuffer,
					   &dwBufferLength);
	if(FAILED(hr))
	{		
		m_sError = "Error to create public queue";
		return FALSE;
	}
	
	dwIDprop = 0;
	return TRUE;
}



//##ModelId=3C0DB2FF0333
BOOL agsMSMQ::CreatePrivateQ(CString serv, CString pathmsg, CString label)
{
	m_sPathQ.Format(_T("%s\\PRIVATE$\\%s"),serv,pathmsg);
    m_sLabelQ.Format(_T("%s"),label);
	::MultiByteToWideChar(CP_ACP,0,m_sPathQ,-1,(LPWSTR)wszPath,sizeof(wszPath));
	::MultiByteToWideChar(CP_ACP,0,m_sLabelQ,-1,(LPWSTR)wszLabel,sizeof(wszLabel));

	InitialPropidQ();
	InitialMQQueue();

	hr = MQCreateQueue(pSecurity,
		               &QProps,
					   wszBuffer,
					   &dwBufferLength);
	if(FAILED(hr))
	{
		m_sError = "Error to create private queue";
		return FALSE;
	}
	
	dwIDprop = 0;
	return TRUE;
}

//##ModelId=3C0DB2FF0321
BOOL agsMSMQ::DeletePublicQ(CString serv, CString pathmsg)
{
	m_sPathQ.Format(_T("DIRECT=%s\\%s"),serv,pathmsg);    
	::MultiByteToWideChar(CP_ACP,0,m_sPathQ,-1,(LPWSTR)wszPath,sizeof(wszPath));	

	dwDestFormatLength = 256;
	::SysFreeString(wszDestFormat);
	hr = MQPathNameToFormatName((LPWSTR)wszPath,
		                        wszDestFormat,
								&dwDestFormatLength);

	if(FAILED(hr))
	{
		m_sError = "Error to convert from path name into format name";
		return FALSE;
	}

	hr = MQDeleteQueue(wszDestFormat);  
	if(FAILED(hr))
	{		
		m_sError = "Error to delete public queue";
		return FALSE;
	}   		

	return TRUE;
}

//##ModelId=3C0DB2FF0317
BOOL agsMSMQ::DeletePrivateQ(CString serv, CString pathmsg)
{
	m_sPathQ.Format(_T("DIRECT=%s\\PRIVATE$\\%s"),serv,pathmsg);    
	::MultiByteToWideChar(CP_ACP,0,m_sPathQ,-1,(LPWSTR)wszPath,sizeof(wszPath));	

	dwDestFormatLength = 256;
	::SysFreeString(wszDestFormat);
	hr = MQPathNameToFormatName((LPWSTR)wszPath,
		                        wszDestFormat,
								&dwDestFormatLength);

	if(FAILED(hr))
	{
		m_sError = "Error to convert from path name into format name";
		return FALSE;
	}

	hr = MQDeleteQueue(wszDestFormat);  
	if(FAILED(hr))
	{
		m_sError = "Error to delete private queue";
		return FALSE;
	}   		

	return TRUE;
}

//##ModelId=3C0DB2FF030B
BOOL agsMSMQ::SendPublicQ(CString serv, CString pathmsg,CString labelmsg,CString msg)
{
	m_sPathQ.Format("%s\\%s",serv,pathmsg);    
	::MultiByteToWideChar(CP_ACP,0,m_sPathQ,-1,(LPWSTR)wszPath,sizeof(wszPath));

	
	InitialPropidBody(labelmsg,msg);
	InitialMQMSG();

	dwDestFormatLength = 256;
	::SysFreeString(wszDestFormat);
	hr = MQPathNameToFormatName((LPWSTR)wszPath,
		                        wszDestFormat,
								&dwDestFormatLength);

	if(FAILED(hr))
	{
		m_sError = "Error to convert from path name into format name";
		return FALSE;
	}

	hr = MQOpenQueue(wszDestFormat,
		             dwAccessMode,
					 dwShareMode,
					 &hQue);
	if(FAILED(hr))
	{
		m_sError = "Error to open queue";
		return FALSE;
	}
	
	hr = MQSendMessage(hQue,
		               &QPropMsg,
					   NULL);
	if(FAILED(hr))
	{
		m_sError = "Error to send public queue";
		return FALSE;
	}

	hr = MQCloseQueue(hQue);
	if(FAILED(hr))
	{
		m_sError = "Error to close queue";
		return FALSE;
	}

	return TRUE;
}





//##ModelId=3C0DB2FF02F8
BOOL agsMSMQ::SendPrivateQ(CString serv, CString pathmsg, CString labelmsg, CString msg)
{
	//m_sPathQ.Format(_T("%s\\PRIVATE$\\%s"),serv,pathmsg);    
	m_sPathQ.Format(_T("DIRECT=TCP:%s\\PRIVATE$\\%s"),serv,pathmsg);
	::MultiByteToWideChar(CP_ACP,0,m_sPathQ,-1,(LPWSTR)wszPath,sizeof(wszPath));

	
	InitialPropidBody(labelmsg,msg);
	InitialMQMSG();

	dwDestFormatLength = 256;
	//::SysFreeString(wszDestFormat);
	memset(wszDestFormat, 0, sizeof(wszDestFormat));
/*	
	hr = MQPathNameToFormatName((LPWSTR)wszPath, wszDestFormat, &dwDestFormatLength);

	if(FAILED(hr))
	{
		m_sError = "Error to convert from path name into format name";
		return FALSE;
	}
*/
	memcpy(wszDestFormat, wszPath, sizeof(wszPath));
	hr = MQOpenQueue(wszDestFormat,
		             dwAccessMode,
					 dwShareMode,
					 &hQue);
	if(FAILED(hr))
	{
		m_sError = "Error to open queue";
		return FALSE;
	}
	
	hr = MQSendMessage(hQue,
		               &QPropMsg,
					   NULL);
	if(FAILED(hr))
	{
		m_sError = "Error to send private queue";
		return FALSE;
	}

	hr = MQCloseQueue(hQue);
	if(FAILED(hr))
	{
		m_sError = "Error to close queue";
		return FALSE;
	}

	return TRUE;
}

//##ModelId=3C0DB2FF02ED
BOOL agsMSMQ::PrepareGetMessage(CString srv, CString path,int modeMSMQ)
{
	switch(modeMSMQ)
	{
	  case 0: 
			//m_sPathQ.Format(_T("%s\\%s"),srv,path);    
		  m_sPathQ.Format(_T("DIRECT=TCP:%s\\%s"),srv,path);    
			break;
	  case 1:
			//m_sPathQ.Format(_T("%s\\PRIVATE$\\%s"),srv,path);    
		  m_sPathQ.Format(_T("DIRECT=TCP:%s\\PRIVATE$\\%s"),srv,path);    

	}
	::MultiByteToWideChar(CP_ACP,0,m_sPathQ,-1,(LPWSTR)wszPath,sizeof(wszPath));

	dwIDprop = 0; 
	dwDestFormatLength = 256;
	
	/////////////////////////////////////////////////////////////
	// Specify the message body and body size properties.
	/////////////////////////////////////////////////////////////
  
	QMsg[dwIDprop] = PROPID_M_BODY_SIZE;       // Property ID
	QPropVar[dwIDprop].vt = VT_UI4;            // Type indicator
	dwIDprop++;
  
	QMsg[dwIDprop] = PROPID_M_BODY;            // Property ID
	QPropVar[dwIDprop].vt = VT_UI1|VT_VECTOR;   // Type indicator
	QPropVar[dwIDprop].caub.pElems = pMessage;   // Body message
	QPropVar[dwIDprop].caub.cElems = 2048;  // Size of message
	dwIDprop++;
  
	QMsg[dwIDprop] = PROPID_M_LABEL;           // Property ID
	QPropVar[dwIDprop].vt = VT_LPWSTR;            // Type indicator
	QPropVar[dwIDprop].pwszVal = (LPWSTR)wszLabel;    // Label MSMQ
	dwIDprop++;
  
	QMsg[dwIDprop] = PROPID_M_LABEL_LEN;       // Property ID
	QPropVar[dwIDprop].vt=VT_UI4;                 // Type indicator
	QPropVar[dwIDprop].ulVal= 1024;             // Value
	dwIDprop++;
 
	ZeroMemory(pMessage,sizeof(pMessage));
	ZeroMemory(wszLabel,sizeof(wszLabel));

	InitialMQMSG();
/*
	hr = MQPathNameToFormatName((LPCWSTR)wszPath,
		                        wszDestFormat,
								&dwDestFormatLength);

	if(FAILED(hr))
	{
		m_sError = "Error to convert from path name into format name";
		return FALSE;
	}
*/
	memcpy(wszDestFormat, wszPath, sizeof(wszPath));
	dwAccessMode = MQ_RECEIVE_ACCESS;
	dwShareMode = MQ_DENY_RECEIVE_SHARE;
	
	hr = MQOpenQueue(wszDestFormat,
		             dwAccessMode,
					 dwShareMode,
					 &hQue);
	if(FAILED(hr))
	{
		m_sError = "Error to open queue";
		return FALSE;
	}

	hr = MQCreateCursor(hQue,&hrTrack);
	if(FAILED(hr))
	{
		m_sError = "Error to create cursor handle";
		return FALSE;
	}
	
	dwReaction = MQ_ACTION_PEEK_CURRENT;
	m_nMessage = 0;	

	return TRUE;

}

//##ModelId=3C0DB2FF02E4
HRESULT agsMSMQ::getMSMQmsg()
{
	ZeroMemory(wszLabel,sizeof(wszLabel));
	ZeroMemory(pMessage,sizeof(pMessage));
	hr = MQReceiveMessage(hQue,
		                  0,
						  dwReaction,
						  &QPropMsg,
						  NULL,
						  NULL,
						  hrTrack,
						  NULL);
	
	if(FAILED(hr)) 
	{				
		return hr;
	}
	msgQ.label.Empty();
	msgQ.msg.Empty();	
	msgQ.label = ::SysAllocString((LPWSTR)wszLabel);	
	msgQ.msg.Format("%s",(char*)pMessage);	
	
	dwReaction = MQ_ACTION_PEEK_NEXT;
	QPropVar[1].ulVal = 256;
	m_nMessage++;
		
	return hr;
}

//##ModelId=3C0DB2FF02E3
int agsMSMQ::getTotalMessage()
{
	return m_nMessage;
}

//##ModelId=3C0DB2FF02DA
MQmsg agsMSMQ::getMessageQ()
{
	return msgQ;
}

//##ModelId=3C0DB2FF02D9
BOOL agsMSMQ::closeMSMQ()
{
	hr = MQCloseCursor(hrTrack);
	if(FAILED(hr))
	{
		m_sError = "Error to close cursor handle";
		return FALSE;
	}
	hr = MQCloseQueue(hQue);
	if(FAILED(hr))
	{
		m_sError = "Error to close queue";
		return FALSE;
	}
	return TRUE;
}
