# ISSUE
-[x] light가 objects의 첫번째 요소일 때 제대로 동작 안하는 문제.
> 해결 : ray_color 안에 if hit 안에 objs->type == LIGHT 이 부분이 문제. 삭제
---

# Study

장면 구성

![image-20201211152237280](/Users/kihoonlee/Im_korea_best_AI_engineer/42seoul_kilee/miniRT_oneweekend_c/src/15.transform/img/image-20201211152237280.png)

- 카메라
- 조명
- 배경
- 오브젝트
- 메터리얼
- (텍스쳐)

![image-20201211152150670](/Users/kihoonlee/Im_korea_best_AI_engineer/42seoul_kilee/miniRT_oneweekend_c/src/15.transform/img/image-20201211152150670.png)

![image-20201211152309474](/Users/kihoonlee/Library/Application Support/typora-user-images/image-20201211152309474.png)



## 광원

[광원 / 퐁모델](https://zamezzz.tistory.com/154)

점광원(조명) -- 거리에 반비례해서 광량이 줄어든다.
무한대 광원(태양)  -- 거리에 비례해서 광량이 줄지 않는다. 1.0
방향 광원 -- 정해진 구체적인 광원의 위치는 없으며 방향만 존재한다.

## 표면 타입 > 퐁모델


난반사도 + 간접광 + 하이라이트도


## 표면 색상

albedo - 반사율
( 표면이 r, g, b 각각을 어떻게 반사하는지 비율);


## 몬테카를로 before after

[링크](https://www.scratchapixel.com/lessons/3d-basic-rendering/global-illumination-path-tracing/global-illumination-path-tracing-practical-implementation)


## 퐁 모델 설계

### light
1. 점광원  > 오브젝트 텍스쳐
2. 주변광(조도) (background)
3. 방향광(태양광) ?()

### 반사
1. 주변광
2. 난반사도 > 오직 난반사만 하면 램버시안 물체
3. 하이라이트


## Direct_specular / Caustics/ Monte_carlo

[이친구 레이트레이서 메인함수 참고하면 좋을듯](https://github.com/kbladin/Monte_Carlo_Ray_Tracer)


## 평면 교점 구하기

[스크래치픽셀](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection)

## 사각형

Subject에서 제시하는 사각형은, axis aligned 한 사각형으로 받아들이는게 맞는듯
cause (중점과 법선 외에 다른 정보가 없음)

## Transformin

[MIT ppt](http://groups.csail.mit.edu/graphics/classes/6.837/F03/lectures/05_transformation_hierarchy.ppt)


## 실린더 교점 구하기

[강의pdf](https://mrl.cs.nyu.edu/~dzorin/rend05/lecture2.pdf)

## 그림자 이슈! 빛이 뒤에있을 때.


## 각종 quadrics 방정식

[이거](https://mrl.cs.nyu.edu/~dzorin/cg05/lecture12.pdf)


## 변환
[mit.edu>ppt](http://groups.csail.mit.edu/graphics/classes/6.837/F03/lectures/05_transformation_hierarchy.ppt)


## object/ class /instance

[요기 설명 ](https://ko.wikipedia.org/wiki/%EC%9D%B8%EC%8A%A4%ED%84%B4%EC%8A%A4_(%EC%BB%B4%ED%93%A8%ED%84%B0_%EA%B3%BC%ED%95%99))
