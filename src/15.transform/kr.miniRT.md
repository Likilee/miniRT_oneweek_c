# miniRT

##  Introduction

miniRT의 주요 목표는 수학자가 아니더라도 수학이나 물리 공식을 구현할 수 있음을 스스로 증명하는 것입니다.
가장 기본적인 레이 트레이싱 기능만 구현해볼 것이므로 평정심을 유지하면서, 깊게 심호흡을 하고, 무엇 보다 패닉에 빠지지 마세요! 이 프로젝트를 마치면 멋진 사진을 보여줄 수 있습니다.

## 🚀 content

### 🥊 Mandatory part

| Program name     | miniRT                                               |
| ---------------- | ------------------------------------------------------------ |
| Turn in files    | All your files                         |
| Makefile         | all, clean, fclean, re, bonus                             |
| Arguments        | a scene in format *.rt                         |
| External functs 1 | open, close, read, write, malloc, free, perror, strerror, exit     |
| External functs 2 | All functions of the math library (-lm man man 3 math)  |
| External functs 3 | All functions of the MinilibX |
| Libft authorized | yes                                                          |
| Description      | The goal of your program is to generate images using the Raytracing protocol. Those computer generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system. |

#### 제약 조건은 다음과 같습니다:

- miniLibX를 사용해야합니다. 첨부된 두개의 버전 모두 사용 가능합니다. 당신이 사용하는 minilibX 소스코드에 Common Instructions part에서 libft에 적용하도록 작성된 것과 동일한 규칙을 적용해야 합니다.
>
>> If your project allows you to use your libft, you must copy its sources and its associated Makefile in a libft folder with its associated Makefile. Your project’s Makefile must compile the library by using its Makefile, then compile the project.
>>
>> _Common Instructions에서 발췌
- 창(Window) 관리는 매끄럽게 유지되어야합니다 : 다른 창으로 변경, 최소화 등등.
- 최소한 5가지 단순한 기하학적 개체를 구현해야 합니다: **평면(plane)**, **구(sphere)**, **원통(cylinder)**, **정사각형(square)**, **삼각형(triangle)**
- 해당되는 경우 가능한 모든 교차점(intersection)과 개체 내부(inside of the object)를 올바르게 처리해야합니다.
- 프로그램은 개체의 고유 한 크기 속성을 조정할 수 있어야합니다(resize): 구의 반지름, 정사각형의 변의 길이, 원통의 너비와 높이.
- 프로그램은 이동 및 회전 변환을 객체(Object), 조명(Light), 카메라(Camera)에 적용 할 수 있어야합니다. (회전 불가능한 구체(Sphere), 삼각형(triangle) 및 조명은 제외)
- Light management: spot brightness, hard shadows, ambience lighting (objects are
never completely in the dark). Colored and multi-spot lights have to be handled
correctly.
- 조명 관리 : Spot brightness(광원?), Hard shadows(강한 그림자), Ambience lighting(주변광, 조도 - 객체는 절대 완전한 어둠속에 있을 수 없다). 빛에 색 적용이나, 다중 광원 적용은 정확하게 다루어져야 한다.
- In case the Deepthought has eyes one day to evaluate your project and if you want
to be able to render beautiful desktop wallpapers..
Your program must save the rendered image in bmp format when its second argument
is "–-save".
- Deepthought 이 언젠가 눈이 생겨 당신의 프로젝트를 평가할 수 있게 될 때를 대비하거나, 아름다운 랜더링 결과물을 당신의 데스크탑 배경화면으로 만들 수 있게 하기 위해, 당신의 프로그램은 두번째 인자가 --save 일 때 반드시 랜더링된 이미지를 bmp 파일로 저장할 수 있어야 합니다.
- 두 번째 인자가 제공되지 않으면 프로그램은 창에 이미지를 표시하고 다음 규칙을 따라야합니다.

>- ESC를 누르면 창을 닫고 프로그램을 깨끗하게 종료해야합니다.
>- 창의 프레임에있는 빨간색 십자가(종료 버튼)을 클릭하면 창을 닫고 프로그램을 깨끗하게 종료해야합니다.
>- 선언 된 창 크기가 디스플레이 해상도보다 크면 창 크기는 현재 디스플레이 해상도에 따라 설정됩니다.
>- 카메라가 두 개 이상인 경우 당신이 설장한 키보드 입력(key pressing)을 통해 카메라간에 전환 할 수 있어야합니다.
>- minilibX의 이미지 사용을 적극 권장합니다.(image관련 함수 사용 권장하는 듯)

- 프로그램은 `.rt` 확장자인 '장면 설명 파일'을 첫 번째 인수로 받아야합니다.

>- 파일은 창 과 렌더링 된 이미지 크기를 포함됩니다. 이 말은 당신의 miniRT가 가능한 모든 크기로 랜더링이 가능해야 한다는 뜻입니다.
>- 각 요소는 하나 이상의 줄 바꿈으로 구분되어 있습니다.
>- 요소의 각 정보는 하나 이상의 공백으로 구분되어 있습니다.
>- 파일에서 요소들은 임의의 순서로 정렬되어 있습니다.
>- 대문자로 정의 된 요소는 '장면 설명 파일'에서 한 번만 선언될 수 있습니다.
>- 각 요소의 첫 번째 정보는 유형 식별자(Specifier) (하나 또는 두 개의 문자로 구성됨)이며 반드시 다음과 같은 순서로 각 요소에 대한 특정 정보가 이어집니다 :
>> ##### * Resolution:
>>
>>> ``` c
>>> R 1920 1080
>>> ```
>>>
>>>· identifier: **R**
>>>
>>>· x render size
>>>
>>>· y render size
>>
>> ##### * Ambient lightning:
>>>
>>>``` c
>>> A 0.2 255,255,255
>>>```
>>>
>>>· identifier: **A**
>>>
>>>· ambient lighting ratio in range [0.0,1.0]: 0.2
>>>
>>>· R,G,B colors in range [0-255]: 255, 255, 255
>>>
>> ##### * Camera:
>>> ```c
>>> c -50.0,0,20 0,0,1 70
>>> ```
>>>· identifier: c
>>>
>>>· x,y,z coordinates of the view point: -50.0,0,20
>>>
>>>· 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
>>>
>>>· FOV : Horizontal field of view in degrees in range [0,180]
>>>
>> ##### * Light:
>>> ```c
>>>l -40.0,50.0,0.0 0.6 10,0,255
>>> ```
>>>· identifier: l
>>>
>>>· x,y,z coordinates of the light point: -40.0,50.0,0.0
>>>
>>>· the light brightness ratio in range [0.0,1.0]: 0.6
>>>
>>>· R,G,B colors in range [0-255]: 10, 0, 255
>>>
>> ##### * Sphere:
>>> ```c
>>> sp 0.0,0.0,20.6 12.6 10,0,255
>>> ```
>>>
>>>· identifier: sp
>>>
>>>· x,y,z coordinates of the sphere center: 0.0,0.0,20.6
>>>· the sphere diameter: 12.6
>>>
>>>· R,G,B colors in range [0-255]: 10, 0, 255
>>>
>> ##### * Plane:
>>> ```c
>>> pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
>>> ```
>>>
>>> · identifier: pl
>>>
>>> · x,y,z coordinates: 0.0,0.0,-10.0
>>>
>>> · 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
>>>
>>> · R,G,B colors in range [0-255]: 0, 0, 255
>>>
>> ##### * Square:
>>> ```c
>>> sq 0.0,0.0,20.6 1.0,0.0,0.0 12.6 255,0,255
>>> ```
>>>
>>> · identifier: sq
>>>
>>> · x,y,z coordinates of the square center: 0.0,0.0,20.6
>>>
>>> · 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 1.0,0.0,0.0
>>>
>>> · side size: 12.6
>>>
>>> · R,G,B colors in range [0-255]: 255, 0, 255
>>>
>> ##### * Cylinder:
>>> ```c
>>> cy 50.0,0.0,20.6 0.0,0.0,1.0 10,0,255 14.2 21.42
>>> ```
>>>
>>> · identifier: cy
>>>
>>> · x,y,z coordinates: 50.0,0.0,20.6
>>>
>>> · 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
>>>
>>> · the cylinder diameter: 14.2
>>>
>>> · the cylinder height: 21.42
>>>
>>> · R,G,B colors in range [0,255]: 10, 0, 255
>>>
>> ##### * Triangle:
>>> ```c
>>> tr 10.0,20.0,10.0 10.0,10.0,20.0 20.0,10.0,10.0 0,0,255
>>> ```
>>>
>>> · identifier: tr
>>>
>>> · x,y,z coordinates of the first point: 10.0,20.0,10.0
>>>
>>> · x,y,z coordinates of the second point: 10.0,10.0,20.0
>>>
>>> · x,y,z coordinates of the third point: 20.0,10.0,10.0
>>>
>>> · R,G,B colors in range [0,255]: 0, 255, 255
>>
- mandatory part의 가장 미니멀한 `.rt` '장면 설명 파일' 예시:
``` c
R 1920 1080
A 0.2										255,255,255
c -50,0,20			0,0,0 		70
l -40,0,30 						0.7			255,255,255

pl 0,0,0 			0,1.0,0 				255,0,225
sp 0,0,20 						20 			255,0,0
sq 0,100,40 		0,0,1.0 	30 			42,42,0
cy 50.0,0.0,20.6 	0,0,1.0 	14.2 		21.42 10,0,255
tr 10,20,10 		10,10,20 	20,10,10 	0,0,255
```
- 파일에서 어떤 종류의 잘못된 구성이 발견되면 프로그램이 제대로 종료되고 "Error\ n"을 반환 한 다음 사용자가 선택한 명시적 오류 메시지를 반환해야합니다.
- 방어를 위해, 생성 할 요소의 제어를 용이하게하기 위해 기능적인 것에 초점을 맞춘 전체 장면 세트를 갖는 것이 이상적 일 것입니다. (뭔소리인지 잘 모르겠음 parsing을 잘 해서 관리하라는 건가?)
>  * For the defence, it would be ideal for you to have a whole set of scenes with the
focus on what is functional, to facilitate the control of the elements to create. _ 원문

### 🥊 Bonus part

분명히 Ray Tracing 기술은 반사, 투명도, 굴절, 더 복잡한 오브젝트, 부드러운 그림자, 화선, 전역 조명, 범프 매핑, .obj 파일 렌더링 등과 같은 더 많은 것을 처리 할 수 ​​있습니다. 그러나 miniRT 프로젝트의 경우에는 첫 번째 레이트 레이서와 CGI의 첫 번째 단계는 간단합니다. 따라서 여기에 구현할 수있는 몇 가지 간단한 보너스 목록이 있습니다. 더 큰 보너스를 원할 경우이 작은 작업이 완료되고 완전히 작동 한 후 나중에 개발자 생활에서 새 광선 추적기를 다시 코딩하는 것이 좋습니다.


```c
'보너스'는 필수 부분이 'PERFECT' 인 경우에만 평가됩니다.
PERFECT 란 당연히 완전해야하고, 잘못된 사용과 같은 심한 실수가 있어도 실패 하면 안된다는 것을 의미합니다.
즉, 필수 부분이 평가 동안 모든 점수를 얻지 못하면 보너스가 완전히 무시됩니다.
```

##### Bonus list:
>- Normal disruption e.g. using sine which gives a wave effect.
>- Color disruption: checkerboard.
>- Color disruption: rainbow effect using object’s normal.
>- Parallel light following a precise direction.
>- Compound element: Cube (6 squares).
>- Compound element: Pyramid (4 triangles, 1 square).
>- Putting caps on size-limited cylinders.
>- One other 2nd degree object: Cone, Hyperboloid, Paraboloid..
>- One color filter: Sepia, R/G/B filters..
>- Anti-aliasing.
>- Simple stereoscopy (like red/green glasses).
>- Multithreaded rendering.
>- Sphere texturing: uv mapping.
>- Handle bump map textures.
>- A beautiful skybox.
>- Keyboard interactivity (translation/rotation) with camera.
>- Keyboard interactivity (translation/rotation) with objects.
>- Changing the camera rotation with the mouse.

```c
평가 중에 사용이 정당화되는 한 다른 함수들을 사용하여 보너스 부분을 완료 할 수 있습니다.
필요하다면 '장면 설명 파일' 형식을 수정할 수도 있습니다. Be smart!
```
```c
모든 보너스 포인트를 얻으려면 위 리스트에서 최소 14 가지를 인증해야합니다.
그러니 현명하게 선택하되 시간을 낭비하지 않도록 주의하십시오!
```
