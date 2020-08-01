# VTK_MFC_SDI_Solution

#### Visual C++ 2017을 설치한다.
#### CMake를 설치한다.

### VTK 설치
#### VTK 9.0.1 을 CMake로 Generate 한다.
  - C:\Works\VTK-9.0.1에 압축을 푼다.
  - CMake 에서 
    - source 위치는 C:\Works\VTK-9.0.1
    - build 위치는 C:\Works\VTK-9.0.1\build
    - compiler 종류는 Visual C++ 2017 (Version 15.9.24 as of 2020.08.01)
    - processor 종류는 x64 (intel 64 bit)
#### 위에서 generate 된 vtk의 sln 파일을 Visual C++ 2017에서 load 한다.
#### build 종류를 debug, x64 로 설정하고, all build 한다.
  - C:\Works\VTK-9.0.1\build\bin\Debug 에 lib 과 dll 이 생성된다.

### Visual C++ 프로젝트 Create 한다.
  - MFCApp, SDI(Single Document Interface)
  - Advanced 옵션은 모두 turn off 하는 것을 추천한다.
  - 이 예제에서는 ~View.h와 ~View.cpp만 수정한다.
  - ~View.h 에 아래 header 파일들을 include 한다.
``` c++
#include "vtkMFCWindow.h"
#include "vtkRenderer.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkCapsuleSource.h"
```
  - 위 header 파일들의 위치를 이 프로젝트의 Properties -> C/C++ -> General -> Additional Include Directories 에 추가한다.
```
C:\Works\VTK-9.0.1\Common\Core
C:\Works\VTK-9.0.1\Common\DataModel
C:\Works\VTK-9.0.1\Common\ExecutionModel
C:\Works\VTK-9.0.1\Common\Math
C:\Works\VTK-9.0.1\Filters\Sources
C:\Works\VTK-9.0.1\GUISupport\MFC
C:\Works\VTK-9.0.1\Interaction\Style
C:\Works\VTK-9.0.1\Rendering\Core
C:\Works\VTK-9.0.1\Rendering\OpenGL2
C:\Works\VTK-9.0.1\Utilities\KWIML
C:\Works\VTK-9.0.1\build\Common\Core
C:\Works\VTK-9.0.1\build\Common\DataModel
C:\Works\VTK-9.0.1\build\Common\ExecutionModel
C:\Works\VTK-9.0.1\build\Filters\Core
C:\Works\VTK-9.0.1\build\Filters\Sources
C:\Works\VTK-9.0.1\build\GUISupport\MFC
C:\Works\VTK-9.0.1\build\Interaction\Style
C:\Works\VTK-9.0.1\build\Rendering\UI
C:\Works\VTK-9.0.1\build\Rendering\OpenGL2
C:\Works\VTK-9.0.1\build\Rendering\Core
```
  - ~View.h 에 아래 private 변수들을 선언한다.
```
private:
vtkMFCWindow* m_pvtkMFCWindow;
vtkRenderer* m_pvtkRenderer;
vtkRenderWindowInteractor* m_pvtkRenderWindowInteractor;
vtkInteractorStyleTrackballCamera* m_pvtkInteractorStyleTrackballCamera;
vtkActor* m_pvtkActor;
vtkPolyDataMapper* m_pvtkMapper;
vtkCapsuleSource* m_pvtkCapsuleSource;
```
  - Class Wizard... 에서 ~View 클래스 선택하고, Messages에서 WM_DESTROY, WM_ERASEBKGND, WM_SIZE에 대한 handler를 추가한다.
  - Class Wizard... 에서 ~View 클래스 선택하고, Virtual Functions에서 OnInitialUpdate에 대한 function을 추가한다.
  - ~View.cpp 의 생성함수 View()에 변수 초기화 코드를 추가한다.
``` c++
m_pvtkMFCWindow = NULL;

m_pvtkRenderer = vtkRenderer::New();
m_pvtkRenderWindowInteractor = vtkRenderWindowInteractor::New();
m_pvtkInteractorStyleTrackballCamera = vtkInteractorStyleTrackballCamera::New();

m_pvtkActor = vtkActor::New();
m_pvtkMapper = vtkPolyDataMapper::New();
m_pvtkCapsuleSource = vtkCapsuleSource::New();
```
  - ~View.cpp 의 소멸함수 ~View()에 변수 메모리 삭제 코드를 추가한다.
``` c++
if (m_pvtkMFCWindow != NULL)
   delete m_pvtkMFCWindow;
```
  - ~View.cpp의 OnDraw(CDC* pDC)에서 pDC를 uncomment 하고, 아래 코드를 추가한다.
``` c++
if (m_pvtkMFCWindow != NULL)
   m_pvtkMFCWindow->DrawDC(pDC);
```
  - ~View.cpp의 OnInitialUpdate()에 아래 코드를 추가한다.
``` c++
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
```
  - ~View.cpp의 OnEraseBkgnd()를 아래와 같이 수정한다.
``` c++
// return CView::OnEraseBkgnd(pDC);
return TRUE;
```
  - ~View.cpp의 OnSize()를 아래와 같이 수정한다.
``` c++
CView::OnSize(nType, cx, cy);

if (m_pvtkMFCWindow != NULL)
	m_pvtkMFCWindow->MoveWindow(0, 0, cx, cy);
```
  - ~View.cpp의 OnDestroy()를 아래와 같이 수정한다.
``` c++
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
```
