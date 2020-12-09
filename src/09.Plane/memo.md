
[광원 / 퐁모델](https://zamezzz.tistory.com/154)

## 광원

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


### Direct_specular / Caustics/ Monte_carlo

이친구 레이트레이서 메인함수 참고하면 좋을듯


### 평면 교점 구하기

[스크래치픽셀](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection)
