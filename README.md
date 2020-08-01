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
  - ~View.h 에 아래 header 파일들을 include 한다.
`
#include "vtkMFCWindow.h"
#include "vtkRenderer.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkCapsuleSource.h"
`
