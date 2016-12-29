/////////////////////////////////////////////////////////////////////
//
// Agus Kurniawan <agusasia@yahoo.com>
// Copyright 2001,
// First release : November 20, 2001
//
//////////////////////////////////////////////////////////////////////  
// File         : agsMSMQ.h: 
// Version		: 1.0
// Description  : interface for the agsMSMQ class.
//////////////////////////////////////////////////////////////////////
// File         : agsMSMQ.cpp: 
// Version		: 1.1
// Date			: January 16, 2002  
// Description  : Modified on PrepareGetMessage() and getMSMQmsg()
/////////////////////////////////////////////////////////////////////////////
// Note : Don't forget to add library file ,mqrt.lib , 
//        into your project
//////////////////////////////////////////////////////////////////////



#if !defined(AFX_AGSMSMQ_H__501BB380_8876_4799_93A7_A238191419D9__INCLUDED_)
#define AFX_AGSMSMQ_H__501BB380_8876_4799_93A7_A238191419D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mq.h>

#define NUMBER_OF_PROPERTIES	4

//##ModelId=3C0DB2FF024D
struct MQmsg{
	//##ModelId=3C0DB2FF0258
	CString label;
	//##ModelId=3C0DB2FF0261
	CString msg;
};

//##ModelId=3C0DB2FF02CF
class agsMSMQ  
{
public:
	//##ModelId=3C0DB2FF02D9
	BOOL closeMSMQ();
	//##ModelId=3C0DB2FF02DA
	MQmsg getMessageQ();
	//##ModelId=3C0DB2FF02E3
	int getTotalMessage();
	//##ModelId=3C0DB2FF02E4
	HRESULT getMSMQmsg();
	//##ModelId=3C0DB2FF02ED
	BOOL PrepareGetMessage(CString srv,CString path,int modeMSMQ);
	//##ModelId=3C0DB2FF02F8
	BOOL SendPrivateQ(CString serv, CString pathmsg,CString labelmsg,CString msg);
	//##ModelId=3C0DB2FF030B
	BOOL SendPublicQ(CString serv, CString pathmsg,CString labelmsg,CString msg);
	//##ModelId=3C0DB2FF0317
	BOOL DeletePrivateQ(CString serv, CString pathmsg);
	//##ModelId=3C0DB2FF0321
	BOOL DeletePublicQ(CString serv, CString pathmsg);
	//##ModelId=3C0DB2FF0333
	BOOL CreatePrivateQ(CString serv, CString pathmsg,CString label);
	//##ModelId=3C0DB2FF033E
	BOOL CreatePublicQ(CString serv, CString pathmsg,CString label);
	//##ModelId=3C0DB2FF0349
	CString getErrorMsg();
	//##ModelId=3C0DB2FF0351
	agsMSMQ();
	//##ModelId=3C0DB2FF0352
	virtual ~agsMSMQ();

private:
	//##ModelId=3C0DB2FF0354
	void InitialMQMSG();
	//##ModelId=3C0DB2FF035B
	void InitialPropidBody(CString label,CString msg);
	//##ModelId=3C0DB2FF0367
	void InitialPropidQ();
	//##ModelId=3C0DB2FF036F
	CString m_sError;
	//##ModelId=3C0DB2FF0379
	void InitialMQQueue();
	//##ModelId=3C0DB2FF037A
	DWORD			dwIDprop;
	//##ModelId=3C0DB2FF0383
	DWORD			dwBufferLength;
	//##ModelId=3C0DB2FF038D
	WCHAR			wszBuffer[250];
	//##ModelId=3C0DB2FF0397
	CString			m_sPathQ;
	//##ModelId=3C0DB2FF03A1
	CString			m_sMSMQserv;
	//##ModelId=3C0DB2FF03AB
	CString			m_sLabelQ;
	//##ModelId=3C0DB2FF03B5
	unsigned short	wszPath[256];
	//##ModelId=3C0DB2FF03BF
	unsigned short	wszLabel[1024];
	//##ModelId=3C0DB2FF03C9
	DWORD			dwDestFormatLength;
	//##ModelId=3C0DB2FF03DD
	WCHAR			wszDestFormat[256];
	//##ModelId=3C0DB2FF03E7
	unsigned char	pMessage[2048];
	//##ModelId=3C0DB3000009
	DWORD			dwAccessMode;
	//##ModelId=3C0DB3000013
	DWORD			dwShareMode;
	//##ModelId=3C0DB300001D
	DWORD			dwReaction; 
	//##ModelId=3C0DB3000027
	int				m_nMessage;
	//##ModelId=3C0DB4F403AC
	MQmsg			msgQ;	
	
	


	

protected:
	//##ModelId=3C0DB3000046
	MQQUEUEPROPS	QProps;
	//##ModelId=3C0DB3000050
	MQMSGPROPS		QPropMsg;
	//##ModelId=3C0DB300005A
	MQPROPVARIANT	QPropVar[NUMBER_OF_PROPERTIES];	
	//##ModelId=3C0DB3000064
	QUEUEPROPID		QPropID[NUMBER_OF_PROPERTIES];
	//##ModelId=3C0DB300006E
	MSGPROPID		QMsg[NUMBER_OF_PROPERTIES];
	//##ModelId=3C0DB3000077
	HRESULT			QStatus[NUMBER_OF_PROPERTIES];
	//##ModelId=3C0DB3000081
	HRESULT			hr;
	//##ModelId=3C0DB3000095
	HANDLE			hrTrack;
	//##ModelId=3C0DB30000AA
	HANDLE			hQue;
	//##ModelId=3C0DB30000B5
	PSECURITY_DESCRIPTOR	pSecurity;
	
	


};

#endif // !defined(AFX_AGSMSMQ_H__501BB380_8876_4799_93A7_A238191419D9__INCLUDED_)
