
// SimpleVTKMFCSDI.h : main header file for the SimpleVTKMFCSDI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSimpleVTKMFCSDIApp:
// See SimpleVTKMFCSDI.cpp for the implementation of this class
//

class CSimpleVTKMFCSDIApp : public CWinAppEx
{
public:
	CSimpleVTKMFCSDIApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSimpleVTKMFCSDIApp theApp;
