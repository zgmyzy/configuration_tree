
// MGConfigurationTree.h : main header file for the MGConfigurationTree application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMGConfigurationTreeApp:
// See MGConfigurationTree.cpp for the implementation of this class
//

class CMGConfigurationTreeApp : public CWinApp
{
public:
	CMGConfigurationTreeApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMGConfigurationTreeApp theApp;
