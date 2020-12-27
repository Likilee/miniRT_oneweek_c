## 함수 프로토타입 정의

SRC : control.c

### /my_mlx_control(t_cntl *cntl)
메인 컨트롤러

mode == 0 : 기본 모드
mode == 1 : 오브젝트 변형 모드 (오브젝트 선택 시 모드 진입)
mode == 2 : 카메라 변형 모드 (카메라 선택 시 모드 진입)


```c
void		my_mlx_control(t_cntl *cntl)
{
	int	mode;

	mode = 0; // 0 = 선택 전 모드
	mlx_hook(오브젝트 선택) -> mode 1
	mlx_hook(카메라 선택) -> mode 2
	// 1 = 오브젝트 변형 모드
	if (mode == 1)
	{
		mlx_hook(~~~, cntl_object_roate)
	}
	//이벤트에 따라서 실행시킬 함수들 : mlx hook 으로 해야됨
	mlx_hook(cntl->win, 17, (1L<<5), cntl_close_window, cntl);
	// 이벤트에 상관 없이 실행시킬 함수 : mlx_loop_hook 으로 해야됨.
	// my_main_loop : render_preview();
	mlx_loop_hook(cntl->mlx, my_main_loop, cntl);
	cntl_object_select(i)
	{
		i++;
	}
	// while >>
	mlx_loop(cntl->mlx);
}
```
## 윈도우 종료 () 완료
x 버튼 , ESC키

## 디스플레이 해상도 조정
### get_display_resolution() mijeong
저녁 메뉴는 오뎅탕~ 유후

## 오브젝트 변형
### /cntl_object_select() kilee
오브젝트 선택

### /cntl_object_rotate() kilee
오브젝트 회전

### /cntl_object_translate() hyeonkim
오브젝트 이동

### /cntl_object_scale() hyeonkim
오브젝토 크기 변형


## 카메라 변형
### cntl_camera_select(,ctrl
카메라 선택
### cntl_camera_rotate()
카메라 회전
### cntl_camera_translate()
카메라 이동
### cntl_camera_hfov()
카메라 화각 변경


