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
