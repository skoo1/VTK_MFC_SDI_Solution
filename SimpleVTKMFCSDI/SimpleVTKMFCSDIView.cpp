
// SimpleVTKMFCSDIView.cpp : implementation of the CSimpleVTKMFCSDIView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SimpleVTKMFCSDI.h"
#endif

#include "SimpleVTKMFCSDIDoc.h"
#include "SimpleVTKMFCSDIView.h"

#include <vtkAutoInit.h>  
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimpleVTKMFCSDIView

IMPLEMENT_DYNCREATE(CSimpleVTKMFCSDIView, CView)

BEGIN_MESSAGE_MAP(CSimpleVTKMFCSDIView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CSimpleVTKMFCSDIView construction/destruction

CSimpleVTKMFCSDIView::CSimpleVTKMFCSDIView() noexcept
{
	m_pvtkMFCWindow = NULL;

	m_pvtkRenderer = vtkRenderer::New();
	m_pvtkRenderWindowInteractor = vtkRenderWindowInteractor::New();
	m_pvtkInteractorStyleTrackballCamera = vtkInteractorStyleTrackballCamera::New();

	m_pvtkActor = vtkActor::New();
	m_pvtkMapper = vtkPolyDataMapper::New();
	m_pvtkCapsuleSource = vtkCapsuleSource::New();
}

CSimpleVTKMFCSDIView::~CSimpleVTKMFCSDIView()
{
	if (m_pvtkMFCWindow != NULL)
		delete m_pvtkMFCWindow;
}

BOOL CSimpleVTKMFCSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSimpleVTKMFCSDIView drawing

void CSimpleVTKMFCSDIView::OnDraw(CDC* pDC)
{
	CSimpleVTKMFCSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_pvtkMFCWindow != NULL)
	{
		// if (pDC->IsPrinting())
		m_pvtkMFCWindow->DrawDC(pDC);
	}
}

void CSimpleVTKMFCSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSimpleVTKMFCSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSimpleVTKMFCSDIView diagnostics

#ifdef _DEBUG
void CSimpleVTKMFCSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CSimpleVTKMFCSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimpleVTKMFCSDIDoc* CSimpleVTKMFCSDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpleVTKMFCSDIDoc)));
	return (CSimpleVTKMFCSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimpleVTKMFCSDIView message handlers


void CSimpleVTKMFCSDIView::OnDestroy()
{
	if (m_pvtkCapsuleSource != NULL)
		m_pvtkCapsuleSource->Delete();

	if (m_pvtkMapper != NULL)
		m_pvtkMapper->Delete();

	if (m_pvtkActor != NULL)
		m_pvtkActor->Delete();

	if (m_pvtkInteractorStyleTrackballCamera != NULL)
		m_pvtkInteractorStyleTrackballCamera->Delete();

	if (m_pvtkRenderWindowInteractor != NULL)
		m_pvtkRenderWindowInteractor->Delete();

	if (m_pvtkRenderer != NULL)
		m_pvtkRenderer->Delete();

	CView::OnDestroy();
}


BOOL CSimpleVTKMFCSDIView::OnEraseBkgnd(CDC* pDC)
{
	// return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CSimpleVTKMFCSDIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_pvtkMFCWindow != NULL)
		m_pvtkMFCWindow->MoveWindow(0, 0, cx, cy);
}


void CSimpleVTKMFCSDIView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	m_pvtkMFCWindow = new vtkMFCWindow(this);
	m_pvtkMFCWindow->GetRenderWindow()->AddRenderer(m_pvtkRenderer);
	m_pvtkRenderer->SetBackground(0.0, 0.0, 0.5);
	m_pvtkRenderWindowInteractor->SetRenderWindow(m_pvtkMFCWindow->GetRenderWindow());
	m_pvtkRenderWindowInteractor->SetInteractorStyle(m_pvtkInteractorStyleTrackballCamera);

	m_pvtkCapsuleSource->SetCylinderLength(0.4);
	m_pvtkCapsuleSource->SetRadius(0.1);
	m_pvtkMapper->SetInputConnection(m_pvtkCapsuleSource->GetOutputPort());
	m_pvtkActor->SetMapper(m_pvtkMapper);
	m_pvtkRenderer->AddActor(m_pvtkActor);
	m_pvtkRenderer->ResetCamera();
}
