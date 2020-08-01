
// SimpleVTKMFCSDIView.h : interface of the CSimpleVTKMFCSDIView class
//

#pragma once


#include "vtkMFCWindow.h"
#include "vtkRenderer.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkCapsuleSource.h"


class CSimpleVTKMFCSDIView : public CView
{
private:
	vtkMFCWindow* m_pvtkMFCWindow;
	vtkRenderer* m_pvtkRenderer;
	vtkRenderWindowInteractor* m_pvtkRenderWindowInteractor;
	vtkInteractorStyleTrackballCamera* m_pvtkInteractorStyleTrackballCamera;

	vtkActor* m_pvtkActor;
	vtkPolyDataMapper* m_pvtkMapper;
	vtkCapsuleSource* m_pvtkCapsuleSource;

protected: // create from serialization only
	CSimpleVTKMFCSDIView() noexcept;
	DECLARE_DYNCREATE(CSimpleVTKMFCSDIView)

// Attributes
public:
	CSimpleVTKMFCSDIDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CSimpleVTKMFCSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in SimpleVTKMFCSDIView.cpp
inline CSimpleVTKMFCSDIDoc* CSimpleVTKMFCSDIView::GetDocument() const
   { return reinterpret_cast<CSimpleVTKMFCSDIDoc*>(m_pDocument); }
#endif

