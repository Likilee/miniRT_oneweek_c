## 함수 프로토타입 정의

SRC : control.c

### /my_mlx_control(t_cntl *cntl)
메인 컨트롤러

mode == 0(DEFM) : 기본 모드
mode == 1(OBJM) : 오브젝트 변형 모드 (오브젝트 선택 시 모드 진입)
mode == 2(CAMM) : 카메라 변형 모드 (카메라 선택 시 모드 진입)
mode == 3(LIGM) : light 변형 모드 (l클릭 시 모드 진입)
LIGHT_ON 0		: light 렌더링모드 진입시
LIGHT_OFF 1		: light 렌더링모드에서 나올시


## 오브젝트 변형
### cntl_object
- 오브젝트 변형에 영향을 주는 모든 함수를 모아둔 함수
### cntl_object_select
- 마우스로 클릭한 오브젝트를 선택하는 함수
### cntl_object_deselect
- 오브젝트 선택 해제
### cntl_object_scale
- 오브젝트 크기 조절
### cntl_object_translate_x_pos
- 오브젝트 x축 이동
### cntl_object_translate_y_pos
- 오브젝트 y축 이동
### cntl_object_rotate
- 오브젝트 회전

## 카메라 조작
### cntl_camera
- 카메라에 관련된 모든 함수를 모아둔 함수
### cntl_camera_on
- 카메라 모드로 진입
### cntl_camera_off
- 카메라 모드에서 나오기
### cntl_select_camera
- 카메라 선택
### cntl_cam_rotate
- 카메라 회전
### cntl_camera_translate
- 카메라 이동
### cntl_camera_hfov
- 카메라 광각 설정

## 광원 조작
### cntl_light
- light 관련된 모든 함수를 모아둔 함수
### cntl_light_on
- light 모드로 진입
### cntl_light_on_and_off
- light 렌더링 모드로 진입
### cntl_light_deselect
- light 모드에서 나오기
### cntl_light_translate_x_pos
- light x축으로 이동
### cntl_light_translate_y_pos
- light y축으로 이동
### cntl_light_bright_up
- light 밝기 증가
### cntl_light_bright_down
- light 밝기 감소
### cntl_light_select
- light 선택
