#ifndef BITMAP_H
# define BITMAP_H

# include "scene.h"

typedef struct s_bmph_file		t_bmph_file;
typedef struct s_bmph_info		t_bmph_info;
typedef struct s_bmph			t_bmph;

# pragma pack(push, 1)                // 구조체를 1바이트 크기로 정렬

struct s_bmph_file    // BMP 비트맵 파일 헤더 구조체
{
    unsigned char	magic1; // B ascii 넣어주고
	unsigned char	magic2; // M ascii 넣어줘야함
	unsigned int	size;	// 파일 크기 바이트 54 + 4 * width * hegith (32bit 비트맵 파일기준)
	unsigned short	reserved1; // 예약 공간 = 0 넣어줘
	unsigned short	reserved2; // 예약 공간 = 0 넣어줘
	unsigned int	offset; // 비트맵 데이터의 시작 위치 54 넣어줘
};

struct s_bmph_info     // BMP 비트맵 정보 헤더 구조체(DIB 헤더)
{
    unsigned int	size; // 40 넣어줘
	int				width;
	int				height; // 음으로 넣으면 이미지 상하 반전
	unsigned short	plane; // 색상판 수 = 1넣어요
	unsigned short	bit_per_pixel; // bit_per_pixel  32 넣어요
	unsigned int	compression; // 0 넣어요 압축안해요~
	unsigned int	size_image; // 비트맵 이미지의 픽셀 데이터 크기,(바이트로) 4 * width * height;
	unsigned int	resolution_x; // 해상도 가로 (미터당 픽셀)
	unsigned int	resolution_y; // 해상도 세로 (미터당 픽셀)
	unsigned int	color_used; // 0xffffff
	unsigned int	color_important; // 비트맵을 표현하기 위해 필요한 색상 인덱스 수, 뭔지 몰라 걍 0 떄려박어.
};

struct s_bmph
{
	t_bmph_file		file_h;
	t_bmph_info		info_h;
};

# pragma pack(pop)

#endif
