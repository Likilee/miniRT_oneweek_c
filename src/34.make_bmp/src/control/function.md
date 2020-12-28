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

### /cntl_object_select()
오브젝트 선택

### /cntl_object_rotate()
오브젝트 회전

