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

### Visual C++ 프로젝트 linking 및 실행을 위한 환경 설정
  - 이 프로젝트의 Properties -> Linker -> General -> Additional Library Directories 에 아래 내용을 추가한다.
```  
  C:\Works\VTK-9.0.1\build\lib\Debug
```
  - 이 프로젝트의 Properties -> Linker -> General -> Enable Incremental Linking 을 No 로 한다. (Linker busy 에러가 날 경우)
  - 이 프로젝트의 Properties -> Linker -> Input -> Additional Dependencies에 아래 lib 파일들을 추가한다.
```
vtkChartsCore-9.0d.lib
vtkCommonColor-9.0d.lib
vtkCommonComputationalGeometry-9.0d.lib
vtkCommonCore-9.0d.lib
vtkCommonDataModel-9.0d.lib
vtkCommonExecutionModel-9.0d.lib
vtkCommonMath-9.0d.lib
vtkCommonMisc-9.0d.lib
vtkCommonSystem-9.0d.lib
vtkCommonTransforms-9.0d.lib
vtkDICOMParser-9.0d.lib
vtkDomainsChemistry-9.0d.lib
vtkdoubleconversion-9.0d.lib
vtkexodusII-9.0d.lib
vtkexpat-9.0d.lib
vtkFiltersAMR-9.0d.lib
vtkFiltersCore-9.0d.lib
vtkFiltersExtraction-9.0d.lib
vtkFiltersFlowPaths-9.0d.lib
vtkFiltersGeneral-9.0d.lib
vtkFiltersGeneric-9.0d.lib
vtkFiltersGeometry-9.0d.lib
vtkFiltersHybrid-9.0d.lib
vtkFiltersHyperTree-9.0d.lib
vtkFiltersImaging-9.0d.lib
vtkFiltersModeling-9.0d.lib
vtkFiltersParallel-9.0d.lib
vtkFiltersParallelImaging-9.0d.lib
vtkFiltersPoints-9.0d.lib
vtkFiltersProgrammable-9.0d.lib
vtkFiltersSelection-9.0d.lib
vtkFiltersSMP-9.0d.lib
vtkFiltersSources-9.0d.lib
vtkFiltersStatistics-9.0d.lib
vtkFiltersTexture-9.0d.lib
vtkFiltersTopology-9.0d.lib
vtkFiltersVerdict-9.0d.lib
vtkfreetype-9.0d.lib
vtkGeovisCore-9.0d.lib
vtkgl2ps-9.0d.lib
vtkglew-9.0d.lib
vtkGUISupportMFC-9.0d.lib
vtkhdf5-9.0d.lib
vtkhdf5_hl-9.0d.lib
vtkImagingColor-9.0d.lib
vtkImagingCore-9.0d.lib
vtkImagingFourier-9.0d.lib
vtkImagingGeneral-9.0d.lib
vtkImagingHybrid-9.0d.lib
vtkImagingMath-9.0d.lib
vtkImagingMorphological-9.0d.lib
vtkImagingSources-9.0d.lib
vtkImagingStatistics-9.0d.lib
vtkImagingStencil-9.0d.lib
vtkInfovisCore-9.0d.lib
vtkInfovisLayout-9.0d.lib
vtkInteractionImage-9.0d.lib
vtkInteractionStyle-9.0d.lib
vtkInteractionWidgets-9.0d.lib
vtkIOAMR-9.0d.lib
vtkIOAsynchronous-9.0d.lib
vtkIOCityGML-9.0d.lib
vtkIOCore-9.0d.lib
vtkIOEnSight-9.0d.lib
vtkIOExodus-9.0d.lib
vtkIOExport-9.0d.lib
vtkIOExportGL2PS-9.0d.lib
vtkIOExportPDF-9.0d.lib
vtkIOGeometry-9.0d.lib
vtkIOImage-9.0d.lib
vtkIOImport-9.0d.lib
vtkIOInfovis-9.0d.lib
vtkIOLegacy-9.0d.lib
vtkIOLSDyna-9.0d.lib
vtkIOMINC-9.0d.lib
vtkIOMotionFX-9.0d.lib
vtkIOMovie-9.0d.lib
vtkIONetCDF-9.0d.lib
vtkIOOggTheora-9.0d.lib
vtkIOParallel-9.0d.lib
vtkIOParallelXML-9.0d.lib
vtkIOPLY-9.0d.lib
vtkIOSegY-9.0d.lib
vtkIOSQL-9.0d.lib
vtkIOTecplotTable-9.0d.lib
vtkIOVeraOut-9.0d.lib
vtkIOVideo-9.0d.lib
vtkIOXML-9.0d.lib
vtkIOXMLParser-9.0d.lib
vtkjpeg-9.0d.lib
vtkjsoncpp-9.0d.lib
vtklibharu-9.0d.lib
vtklibproj-9.0d.lib
vtklibxml2-9.0d.lib
vtkloguru-9.0d.lib
vtklz4-9.0d.lib
vtklzma-9.0d.lib
vtkmetaio-9.0d.lib
vtknetcdf-9.0d.lib
vtkogg-9.0d.lib
vtkParallelCore-9.0d.lib
vtkParallelDIY-9.0d.lib
vtkpng-9.0d.lib
vtkpugixml-9.0d.lib
vtkRenderingAnnotation-9.0d.lib
vtkRenderingContext2D-9.0d.lib
vtkRenderingCore-9.0d.lib
vtkRenderingFreeType-9.0d.lib
vtkRenderingGL2PSOpenGL2-9.0d.lib
vtkRenderingImage-9.0d.lib
vtkRenderingLabel-9.0d.lib
vtkRenderingLOD-9.0d.lib
vtkRenderingOpenGL2-9.0d.lib
vtkRenderingSceneGraph-9.0d.lib
vtkRenderingUI-9.0d.lib
vtkRenderingVolume-9.0d.lib
vtkRenderingVolumeOpenGL2-9.0d.lib
vtkRenderingVtkJS-9.0d.lib
vtksqlite-9.0d.lib
vtksys-9.0d.lib
vtkTestingRendering-9.0d.lib
vtktheora-9.0d.lib
vtktiff-9.0d.lib
vtkverdict-9.0d.lib
vtkViewsContext2D-9.0d.lib
vtkViewsCore-9.0d.lib
vtkViewsInfovis-9.0d.lib
vtkWrappingTools-9.0d.lib
vtkzlib-9.0d.lib
```
  - 실행시 DLL 로딩을 위하여 이 프로젝트의 Properties -> DebuggingEnvironment에 아래 내용을 추가한다.
```
PATH=%PATH%;C:\Users\skoo\Works\VTK-9.0.1\build\bin\Debug
```
