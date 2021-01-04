## 🚀miniRT_controller

## 🌕 공용 구조체
```c
struct						s_cntl
{
	void	*mlx;
	void	*win;
	void	*scene;
	int		mode;		// 0: Default 1:Object 2:Camera 3:light
	int		light_on;	// render_preview 에 조명 on/off
} 							t_cntl;

struct						s_scene
{
	t_global	global;
	t_canvas	canv;
	t_camera	*cam_onair;	//현재 렌더링 기준 카메라
	t_objects	*cam_list;	//렌더링
	t_objects	*world;
	t_data		*img;
};
```

## ⭐ 기능명세

- [x] 종료 ESC
- [x] 종료 X 클릭
- [x] 해상도 조정기능
- [x] 오브젝트 선택
- [x] 오브젝트 이동
- [x] 오브젝트 회전
- [x] 오브젝트 크기
- [x] 카메라 전환
- [x] 카메라 이동
- [x] 카메라 회전
- [x] 카메라 화각
- [x] 저장 기능
- [x] 랜더링
- [x] 라이트 선택/전환
- [x] 라이트 이동
- [x] 라이트 밝기 조정
- [ ] ~~라이트 색상 조정~~

## 🏋‍♀ 변형 기능
> 컨트롤 모드(cntl->mode)에 따라 동작을 구분한다. 모드는 `0 : 기본`,`1 : 오브젝트`,`2 : 카메라`,`3 : 조명` 변형이 있다.

### 오브젝트 변형
#### 오브젝트 선택
- 좌클릭 : 마우스로 클릭하면 hit 함수를 통해서 오브젝트 가져오기.
#### 오브젝트 회전 적용.
- 선택된 오브젝트에 rotate 멤버에 적용.
####  오브젝트 이동
- 각 단일 오브젝트 점 값들 변경.
#### 오브젝트 크기 변경
- 각 단일 오브젝트 크기 속성 값 변경.


### 카메라 변형

#### 카메라 선택
방향키로 다른 카메라 선택

#### 카메라 이동 / 회전 / 화각
```
** 이동 **
w : origin + 1 * dir;
s : origin -1 * dir;
a : origin -1 *(dir X  UP(y));
d : origin +1 * (dir X UP(y));

** 회전 **
휠레프트 || 좌클릭: 왼쪽 회전
휠라이트 || 우클릭 : 우측 회전
휠업  : 위쪽 회전
휠다운 : 아래 회전

** 화각 **
화각 증가 : q
화각 감소 : e
```

## 🧘‍♂ 기타 기능
기타 유틸성 기능

### 윈도우 종료
ESC 키 종료, X버튼 클릭 종료

### 해상도 조정
디스플레이 해상도와 .rt파일의 해상도가 다를 때, 디스플레이 해상도에 맞춰 window 해상도를 변경

### 저장 기능
BMP파일 저장기능

### 랜더링 기능
Rendering 실행
