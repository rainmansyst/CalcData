
// CalcData.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCalcDataApp:
// �йش����ʵ�֣������ CalcData.cpp
//

class CCalcDataApp : public CWinAppEx
{
public:
	CCalcDataApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCalcDataApp theApp;