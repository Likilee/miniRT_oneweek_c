## miniRT_controller

## 구조체
```c
struct						s_cntl
{
	void	*mlx;
	void	*win;
} 							t_cntl;

R 1920 1080
A 02 255,255,255


```
## 함수

### 오브젝트 변형
#### 오브젝트 선택
- 좌클릭 : 마우스로 클릭하면 ray 쏴서 오브젝트 hit해서 오브젝트 가져오기.

#### 오브젝트 회전 적용.
- 선택된 오브젝트의 rotate,
```c
// kilee's object
struct						s_objects
{
	void			*element;
	t_matrix44		*rotate;
	t_matrix44		*rotate_normal;
	void			*next;
	t_objects_type	type;
};

// mijeong's object
typedef struct s_objects
{
	int type;
	void *data;
	t_rotate	rotate;
	struct s_objects *next;
} t_objects;

// hyeonkim's object
typedef struct s_objects
{
	int obj_type;
	void *object;
	void *next;
} t_objects;
```

####  오브젝트 이동
- 각 단일 오브젝트 값들 변경.
#### 오브젝트 크기 변경
- 각 단일 오브젝트 크기  속성  변경.

### 카메라 변형

#### 카메라 선택
c 3초이상~
방향키로 다른 카메라 선택
```c
// kilee's  camera
struct						s_camera
{
	t_point3	orig;
	t_point3	dir;
	double		hfov;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_point3	left_bottom;
};

rt : c  origin(x,y,z),   dir,    hfov,
// mijeog's camera
typedef struct s_camera
{
	double		ratio;
	double		viewport_h;
	double		viewport_w;
	double		focal_len;
	t_point3	origin;
	t_vec		horizontal;
	t_vec		vertical;
	t_point3	higher_left_corner;

} t_camera;
```

#### 카메라 이동 / 회전 / 화각 변경
wasd system
w : origin + 1 * dir;
s : origin -1 * dir;
a : origin -1 *(dir X  UP(y));
d : origin +1 * (dir X UP(y));

휠레프트 || 좌클릭: 왼쪽 회전
휠라이트 || 우클릭 : 우측 회전
휠업  : 위쪽 회전
휠다운 : 아래 회전
화각 증가 : q
화각 감소 : e


### 엑스표 누르면 윈도우 종료 || esc 누르면 윈도우 종료

### 디스플레이 해상도랑 .rt파일 해상도랑 다를 때 디스플레이 해상도에 맞춰서 window해상도 조절
