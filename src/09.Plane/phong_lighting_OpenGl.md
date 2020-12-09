# Basic Lighting

현실 세계의 조명은 매우 복잡하고 너무 많은 요인에 따라 달라집니다. 제한된 처리 능력으로는 계산할 여유가 없습니다. 따라서 OpenGL의 조명은 처리하기 훨씬 쉽고 상대적으로 비슷해 보이는 단순화 된 모델을 사용하여 현실의 근사치를 기반으로합니다. 이 조명 모델은 우리가 이해하는 빛의 물리학을 기반으로합니다. 이러한 모델 중 하나는 퐁 조명 모델입니다. 퐁 조명 모델의 주요 구성 요소는 주변 조명(ambient), 확산 조명(diffuse) 및 반사(specular) 조명의 세 가지 구성 요소로 구성됩니다. 아래에서 이러한 조명 구성 요소가 자체적으로 그리고 결합 된 모습을 볼 수 있습니다.

![](https://learnopengl.com/img/lighting/basic_lighting_phong.png)

- 주변 조명(ambient): 어두울 때에도 일반적으로 어딘가에는 빛 (달, 먼 는 등)이 있으므로 물체는 거의 완전히 어두워지지 않습니다. 이것을 시뮬레이션하기 위해 우리는 항상 물체에 약간의 색을 주는 주변 조명 상수를 사용합니다.
- 확산 조명(diffuse): 조명 오브젝트가 오브젝트에 미치는 방향 영향(directional impact)을 시뮬레이션합니다. 이것은 조명 모델에서 시각적으로 가장 중요한 구성 요소입니다. 물체의 일부가 광원을 향할수록 더 밝아집니다.
- 반사광(specular): 반짝이는 물체에 나타나는 빛의 밝은 부분을 시뮬레이션합니다. 반사광 하이라이트는 물체의 색상보다 빛의 색상에 가깝습니다(more inclined to).

시각적으로 흥미로운 장면을 만들기 위해 최소한이 세 가지 조명 구성 요소를 시뮬레이션하고 싶습니다. 가장 간단한 것부터 시작하겠습니다 : 주변 조명(ambient).

---

## 1) Ambient Lighting

빛은 일반적으로 단일 광원에서 나오는 것이 아니라 우리 주변에 흩어져있는 많은 광원에서 옵니다. 빛의 특성 중 하나는 여러 방향으로 산란 및 반사되어 직접 보이지 않는 지점에 도달 할 수 있다는 것입니다. 따라서 빛은 다른 표면에 반사 되어 물체의 조명에 간접적인 영향을 미칠 수 있습니다. 이를 고려한 알고리즘은 전역 조명 알고리즘(global illumination algorithm)이라고 불리지만 계산하는 데 복잡하고 많은 비용이 듭니다.

우리는 복잡하고 값 비싼 알고리즘을 좋아하지 않기 때문에 우리는 매우 단순한 글로벌 조명 모델, 즉 주변 조명(ambient)을 사용할 것입니다. 이전 섹션에서 보셨 듯이 우리는 오브젝트 조각(objects fragment)의 최종 결과 색상에 빛의 색깔을 나타내는 상수(small constant color)를 추가하여 직접적인 광원이 없는 경우에도 항상 산란된 빛이있는 것처럼 보이게 할 것입니다.

장면에 주변 조명을 추가하는 것은 정말 쉽습니다. 우리는 빛의 색을 가져다가 작은 상수를 곱하고, 이것을 다시 개체의 색과 곱하여, 그것을 정육면체의 조각의 색으로 사용합니다.
```c
void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
}  
```

이제 프로그램을 실행하면 조명의 첫 번째 단계가 개체에 성공적으로 적용되었음을 알 수 있습니다. 오브젝트는 매우 어둡지 만 주변 조명이 적용 되었기 때문에 완전히 어둡지는 아닙니다 (조명에는 다른 셰이더를 사용하기 때문에 영향을 받지 않습니다). 다음과 같이 보일 것입니다.

![](https://learnopengl.com/img/lighting/ambient_lighting.png)

---

## 2) Diffuse Lighting

주변 조명(ambient) 자체는 가장 흥미로운 결과를 생성하지 않지만 확산 조명(diffuse)은 물체에 상당한 시각적 영향을 주기 시작합니다. 확산 조명은 조각(fragment)이 광원의 광선(light rays)에 더 가깝게 정렬 될수록 개체가 더 밝아집니다. 확산 조명에 대해 더 잘 이해하려면 다음 이미지를 살펴보십시오.

![](https://learnopengl.com/img/lighting/diffuse_light.png)

왼쪽에는 물체의 조각을 겨냥한 광선을 보낸 광원이 있습니다. 먼저 광선이 조각에 닿는 각도를 측정해야합니다. 광선이 물체의 표면에 수직이면 빛이 가장 큰 영향을 미칩니다. 광선과 조각 사이의 각도를 측정하기 위해 우리는 법선 벡터(이는 조각의 표면에 수직 인 벡터이고, 위 그림에서는 노란색 화살표로 표시 됐습니다). 법선 벡터에 대해서는 나중에 더 자세히 설명할 것입니다. 두 벡터 사이의 각도는 내적을 사용하여 쉽게 계산할 수 있습니다.

두 단위 벡터 사이의 각도가 낮을수록 내적은 값 1로 기울어집니다(혹시 내적에 대해 잘 알지 못한다면?[transformation chapter](https://learnopengl.com/Getting-started/Transformations)를 참고하세요!). 두 벡터 사이의 각도가 90도이면 내적 값은 0이 됩니다. 법선 벡터와 광선 사이의 각도(*θ*)에도 동일하게 적용됩니다. *θ*가 클수록 빛이 조각의 색상에 미치는 영향이 적습니다.
```c
두 벡터 사이의 각도의 코사인 만 구하려면 단위 벡터 (길이 벡터 1)로 작업하므로 모든 벡터가 정규화되었는지 확인해야합니다. 그렇지 않으면 내적이 코사인 이상을 반환합니다.
```

따라서 내적의 결과는 조각의 색상에 대한 빛의 영향을 계산하는 데 사용되는 스칼라 값을 반환합니다. 

확산 조명을 계산하기 위해서는 다음 두 가지가 필요합니다.

- 법선 벡터 : 정점(vertex point, 한국어로는 꼭지점..이지만 2D에서 point에 대비되는 개념이라고 합니다. 단순히 점이 아니라 위치,방향,색상 등 정보를 담고 있다고 합니다.) 표면에 수직인 벡터.
- 직접 광선 : 빛의 위치와 조각의 위치 사이의 차이인 방향 벡터. 이 광선을 계산하려면 빛의 위치 벡터와 조각의 위치 벡터가 필요합니다.

#### 2 - 1) normal vector(법선 벡터)

법선 벡터는 정점 표면에 수직인 (단위)벡터입니다. 정점 자체에는 표면이 없기 때문에 (점, point일 뿐입니다) 정점의 표면을 파악하기 위해 주변 정점을 사용하여 법선 벡터를 계산해야 합니다. 외적을 사용하여 모든 큐브의 정점에 대한 법선 벡터를 계산하기 위해 약간의 트릭을 사용할 수 있지만 3D 큐브는 복잡한 모양이 아니기 때문에 수동으로 정점 데이터에 추가 할 수 있습니다. 업데이트 된 정점 데이터 배열은 [이 곳](https://learnopengl.com/code_viewer.php?code=lighting/basic_lighting_vertex_data)에서 찾을 수 있습니다. 법선이 실제로 각 평면의 표면에 수직 인 벡터임을 시각화하십시오 (입방체는 6 개의 평면으로 곳성됨).

정점 배열에 추가 데이터를 추가 했으므로 큐브의 정점 셰이더를 업데이트해야합니다.

```cpp
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
...
```

이제 각 정점에 법선 벡터를 추가하고 정점 셰이더를 업데이트 했으므로 정점 속성 포인터도 업데이트해야 합니다. 광원인 정육면체는 정점 데이터에 대해 동일한 정점 배열을 사용하지만 램프 셰이더(lamp shader;cf. 광원의 음영을 나타내는 함수? 인 듯)는 새로 추가 된 법선 벡터를 사용하지 않습니다. 램프 셰이더 또는 속성 구성을 업데이트 할 필요는 없지만 새 정점 배열의 크기를 반영하도록 적어도 정점 속성 포인터를 수정해야 합니다.

```cpp
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

(여기부터 diffuse lighting 섹션이 끝날 때까지는 앞의 내용도 좀 봐야할 듯?)

We only want to use the first 3 floats of each vertex and ignore the last 3 floats so we only need to update the stride parameter to 6 times the size of a float and we're done.(해석 부탁..)

```c
램프 셰이더에서 완전히 사용하지 않는 정점 데이터를 사용하면 비효율적으로 보일 수 있지만 정점 데이터는 컨테이너 객체의 GPU 메모리에 이미 저장되어 있으므로 새 데이터를 GPU 메모리에 저장할 필요가 없습니다. 이것은 실제로 램프를 위해 특별히 새로운 VBO를 할당하는 것에 비해 더 효율적입니다.(It may look inefficient using vertex data that is not completely used by the lamp shader, but the vertex data is already stored in the GPU's memory from the container object so we don't have to store new data into the GPU's memory. This actually makes it more efficient compared to allocating a new VBO specifically for the lamp.)
```

모든 조명 계산은 조각 셰이더에서 수행되므로 정점 셰이더에서 조각 셰이더로 노멀 벡터를 전달해야합니다.(All the lighting calculations are done in the fragment shader so we need to forward the normal vectors from the vertex shader to the fragment shader.)
```cpp
out vec3 Normal;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = aNormal;
} 
```
남은 일은 조각 셰이더에서 해당 입력 변수를 선언하는 것입니다.
```cpp
in vec3 Normal; 
```

#### 2 - 2) calculating the diffuse color

이제 각 정점에 대한 법선 벡터가 있지만 여전히 조명의 위치 벡터와 조각의 위치 벡터가 필요합니다. 조명의 위치는 단일 정적 변수이므로 조각 셰이더에서이를 uniform으로 선언 할 수 있습니다.

```cpp
uniform vec3 lightPos;
```

그런 다음 렌더링 루프 (또는 프레임 당 변경되지 않으므로 외부)에서 유니폼을 업데이트합니다. 이전 장에서 선언 한 lightPos 벡터를 확산 광원의 위치로 사용합니다. (nd then update the uniform in the render loop (or outside since it doesn't change per frame). We use the lightPos vector declared in the previous chapter as the location of the diffuse light source:)

```cpp
lightingShader.setVec3("lightPos", lightPos);  
```

마지막으로 필요한 것은 실제 조각의 위치입니다. 우리는 월드 공간에서 모든 조명 계산을 수행 할 것이므로 먼저 월드 공간에 있는 정점 위치를 원합니다. 정점 위치 속성을 모델 매트릭스 (뷰 및 투영 매트릭스 제외)와 곱하여 월드 공간 좌표로 변환함으로써 이를 수행 할 수 있습니다. 이것은 버텍스 셰이더에서 쉽게 수행 할 수 있으므로 출력 변수를 선언하고 월드 공간 좌표를 계산해 보겠습니다.

```cpp
out vec3 FragPos;  
out vec3 Normal;
  
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
}
```

마지막으로 해당 입력 변수를 조각 셰이더에 추가합니다.

```cpp
in vec3 FragPos;
```

이 in변수는 삼각형의 3개의 세계 위치 벡터에서 [보간](https://m.blog.naver.com/PostView.nhn?blogId=ceoyangsj&logNo=100169531489&proxyReferer=https:%2F%2Fwww.google.com%2F)되어 조각 별 세계 위치(per-fragment world position)인 FragPos 벡터를 형성합니다 . 이제 필요한 모든 변수가 설정되었으므로 조명 계산을 시작할 수 있습니다.

가장 먼저 계산해야 할 것은 광원과 조각의 위치 사이의 방향 벡터입니다. 이전 섹션에서 우리는 빛의 방향 벡터가 빛의 위치 벡터와 조각의 위치 벡터 사이의 차이 벡터라는 것을 이야기했습니다 두 벡터를 단순히 빼는 것으로 이 차이를 쉽게 계산할 수 있습니다(벡터 연산이 궁금하다면.. [transformations](https://learnopengl.com/Getting-started/Transformations)참고). 또한 모든 관련 벡터가 단위 벡터로 끝나도록 하여 법선과 결과 방향 벡터를 모두 정규화합니다.

```cpp
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightPos - FragPos);  
```

```c
조명을 계산할 때 일반적으로 벡터의 크기 나 위치는 신경 쓰지 않습니다. 우리는 그들의 방향에만 관심이 있습니다. 우리는 그들의 방향에만 관심이 있기 때문에 대부분의 계산 (예 : 내적)을 단순화하기 때문에 거의 모든 계산이 단위 벡터로 수행됩니다. 따라서 조명 계산을 할 때는 항상 관련 벡터를 정규화하여 실제 단위 벡터인지 확인하십시오. 벡터를 정규화하는 것을 잊는 것은 흔한 실수입니다.
```

다음으로 norm 벡터 와 lightDir 벡터 사이의 내적을 취하여 현재 조각에 대한 빛의 확산 영향을 계산해야합니다 . 그런 다음 결과 값을 조명의 색상과 곱하여 확산 구성 요소를 얻습니다. 결과적으로 두 벡터 사이의 각도가 클수록 확산 구성 요소가 어두워집니다.

```cpp
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = diff * lightColor;
```

두 벡터 사이의 각도가 90도보다 크면 내적 결과는 음수가 됩니다. result에 곱해줄 확산 성분이 음의 값이 되는 것입니다. 이러한 이유로 우는는 두 매개 변수(내적값과 0) 중 큰 값을 반환하여 확산 값이 음수가 되지 않도록 할 것입니다. 음의 색깔(negative colors)은 실제로 정의되지 않았으므로 그 빛을 피하는 것이 좋습니다.

이제 주변광과 확산 구성 요소가 모두 있으므로 두 색상을 서로 추가 한 다음 결과에 오브젝트 색상을 곱하여 결과 조각의 출력 색상을 얻습니다.
```cpp
vec3 result = (ambient + diffuse) * objectColor;
FragColor = vec4(result, 1.0);
```
성공적으로 컴파일 된 경우 다음과 같은 내용이 표시됩니다.

![](https://learnopengl.com/img/lighting/basic_lighting_diffuse.png)

확산 조명을 사용하곳 큐브가 실제 큐브처럼 보이기 시작합니다. 머리에 있는 법선 벡터를 시각화하고(이건 무슨 말일까요..) 정육면체 주위로 카메라를 움직여 법선 벡터와 빛의 방향 벡터 사이의 각도가 클수록 조각이 어두워 지는지 확인하십시오.

문제가있는 경우 [이곳](https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.1.basic_lighting_diffuse/basic_lighting_diffuse.cpp) 에서 소스 코드와 전체 소스 코드를 자유롭게 비교해보십시오.

#### 2 - 3) one last thing

이전 섹션에서 우리는 정점 셰이더에서 조각 셰이더로 직접 노멀 벡터를 전달했습니다. 그러나 조각 셰이더의 계산은 모두 월드 공간에서 수행되므로 일반 벡터 역시 월드 공간 좌표로 변환해야 하는 것 아닐까요? 기본적으로는 그렇습니다. 하지만 단순히 모델 행렬을 곱하는 것만 큼 간단하지는 않습니다.

우선, 법선 벡터는 방향 벡터 일 뿐이며 공간의 특정 위치를 나타내지 않습니다. 둘째, 법선 벡터에는 homogeneous coordinate(the *w* component of a vertex position)가 없습니다. 이것은 변환이 법선 벡터에 영향을 미치지 않아야 함을 의미합니다. 따라서 법선 벡터를 모델 행렬과 곱하려면 모델 행선의 왼쪽 위부터 3x3 행렬을 취하여 translation 부분을 제거한 후 곱해줄 수도 있습니다(법선 벡터의 *w* component를 0으로 설정하고 4x4행렬과 곱할 수 있다는 것도 기억하십시오).

둘째, 모델 행렬이 비 균일 스케일을 수행하면 법선 벡터가 더 이상 표면에 수직이 아닌 방식으로 정점이 변경됩니다. 다음 이미지는 이러한 모델 행렬 (비 균일 스케일링 사용)이 법선 벡터에 미치는 영향을 보여줍니다.
![](https://learnopengl.com/img/lighting/basic_lighting_normal_transformation.png)

비 균일 스케일을 적용 할 때마다 (참고 : 균일 스케일은 방향이 아닌 법선의 크기 만 변경하므로이를 정규화하여 쉽게 고정 할 수 있음) 법선 벡터는 더 이상 해당 표면에 수직하지 않아 조명을 왜곡합니다.

이 동작을 수정하는 방법은 특별히 정규 벡터에 맞게 조정된 다른 모델 행렬을 사용하는 것입니다. 이 행렬에서는 일반 행렬 그리고 몇 가지 선형 대수 연산을 사용하여 정규 벡터를 잘못 스케일링 한 효과를 제거합니다. 이 행렬이 어떻게 계산되는지 알고 싶다면 [이 곳](http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/)을 참고하세요.

정규 행렬은 '모델 행렬의 왼쪽 위 3x3 부분의 역행렬의 전치(the transpos of the inverse of the upper-left 3x3 part of the matrix'로 정의됩니다. 식은 죽 먹기죠 우하하. 그것이 의미하는 바를 이해하지 못했더라도 걱정하지 마십시오. 우리는 아직 역행렬과 전치 행렬에 대해 논의하지 않았습니다. 대부분의 리소스는 모델-뷰 매트릭스에서 파생 된 일반 매트릭스를 정의하지만, 우리는 월드 공간 (뷰 공간이 아닌)에서 작업하므로 모델 매트릭스에서 파생됩니다.

정점 쉐이더에서 우리는 모든 매트릭스 유형에서 작동하는 버텍스 셰이더의 함수 inverse와 transpose를 사용하여 법선 행렬을 생성 할 수 있습니다. 행렬을 3x3 행렬로 변환하여 translation properties(w component)를 없앤 후 vec3일반 벡터와 곱할 수 있음을 기억하세요.

```cpp
Normal = mat3(transpose(inverse(model))) * aNormal;  
```

```c
역행렬은 셰이더에게 비용이 많이 드는 작업이므로 장면의 각 정점에서 수행해야하므로 가능한 역 연산을 피하십시오. 학습 목적으로는 괜찮지 만 효율적인 애플리케이션을 위해서는 CPU에서 노멀 매트릭스를 계산하고 그리기 전에 유니폼을 통해 셰이더로 보낼 수 있습니다 (모델 매트릭스와 마찬가지로).
```

이번 섹션에서는 오브젝트에 스케일링을 하지 않았기 때문에 조명이 괜찮았습니다. 그래서 실제로 노멀 매트릭스를 사용할 필요가 없었고 노멀과 모델 매트릭스를 곱할 수있었습니다. 그러나 비 균일 스케일을 수행하는 경우 법선 벡터와 법선 행렬을 곱하는 것이 필수적입니다.

---

## 3) Specular Lighting
광
조명 이야기에 아직 지치지 않았다면 specular highlights를 추가하여 Phong 조명 모델을 마무리 할 수 ​​있습니다.

확산 조명(diffuse)과 유사하게 반사광(specular)은 조명의 방향 벡터와 오브젝트의 법선 벡터를 기반으로 하지만 이번에는 플레이어가 조각을 바라 보는 방향(뷰 방향)도 고려해야 합니다. 반사광은 표면의 반사 속성을 기반으로 합니다. 물체의 표면을 거울로 생각하면 표면에 반사 된 빛을 볼 수있는 곳에서 반사광이 가장 강합니다. 다음 이미지에서 이 효과를 볼 수 있습니다.

![](https://learnopengl.com/img/lighting/basic_lighting_specular_theory.png)

법선 벡터를 중심으로 빛의 방향을 반사하여 반사 벡터를 계산합니다. 그런 다음이 반사 벡터와 뷰 방향 사이의 각도 거리를 계산합니다. 그들 사이의 각도가 작을 수록 반사광의 영향이 커집니다. 그 결과 표면을 통해 반사 된 빛을 볼 때 약간의 하이라이트가 보입니다. 

뷰 벡터(빛이 부딪힌 점에서 우리 눈을 향하는 벡터)는 반사광 조명에 필요한 하나의 추가 변수로서 뷰어(위의 그림에서 눈)의 세계 공간 위치와 조각의 위치를 ​​사용하여 계산할 수 있습니다. 그런 다음 반사광의 강도를 계산하고 여기에 빛의 색상을 곱한 다음 주의(ambient) 및 확산(diffuse) 구성 요소에 추가합니다.

```c
우리는 세계 공간에서 조명 계산을 선택했지만 대부분의 사람들은 뷰 공간에서 조명을 선호하는 경향이 있습니다. 뷰 공간의 장점은 시청자의 위치가 항상 (0,0,0)에 있으므로 시청자의 위치를 ​​확보할 수 있다는 것입니다. 그러나 학습 목적을 위해 세계 공간에서 조명을 계산하는 것이 더 직관적이라는 것을 알았습니다. 뷰 공간에서 조명을 계산하려면 뷰 매트릭스를 사용하여 모든 관련 벡터를 변환해야 합니다(노멀 매트릭스도 변경하는 것을 잊지 마십시오).
```

뷰어의 세계 공간 좌표를 얻으려면 카메라 객체 (물론 뷰어)의 위치 벡터를 가져옵니다. 이제 조각 셰이더에 다른 유니폼을 추가하고 카메라 위치 벡터를 셰이더에 전달하겠습니다.

```cpp
uniform vec3 viewPos;
```

```cpp
lightingShader.setVec3("viewPos", camera.Position); 
```

이제 필요한 모든 변수가 준비되었으므로 반사광(specular)의 강도를 계산할 수 있습니다. 먼저 강도 값을 정의하여 반사광 하이라이트에 중간 정도의 밝은 색상을 부여하여 너무 많은 영향을 주지 않도록합니다.

```cpp
float specularStrength = 0.5;
```

만약 위의 값을 1.0으로 설정하면 coral cube에 비해 너무 밝은 반사광 구성 요소를 얻게 됩니다. [다음 장](https://learnopengl.com/Lighting/Materials)에서 우리는 제대로 모든 조명 강도를 설정하고 그들이 어떻게 객체에 영향을 얘기할 것입니다. 다음으로 뷰 방향 벡터와 법선 축을 따라 해당하는 반사 벡터를 계산할 것입니다.

```cpp
vec3 viewDir = normalize(viewPos - FragPos);
vec3 reflectDir = reflect(-lightDir, norm); 
```

lightDir벡터를 음의 값으로 만든 것을 확인하십시오. reflect함수는 첫 번째 벡터가 광원에서 조각의 위치를 가리킬 것으로 예상하지만, lightDir 벡터는 현재 다른 방향(:조각에서 광원을 향한 방향(이는 우리가 광원 벡터를 계산했을 때 이전의 뺄셈 순서에 따라 달라짐)을 가리키고 있습니다. 올바른 reflect벡터를 얻기 위해 lightDir먼저 벡터를 음의 값으로 만들어 방향을 바꿉니다. 두 번째 인자로는 정규화된 norm벡터를 제공합니다 .

그러면 남은 일은 실제로 반사광 성분(specular component)을 계산하는 것입니다. 이는 다음 공식으로 수행됩니다.

```cpp
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = specularStrength * spec * lightColor;  
```

먼저 뷰 방향과 반사 방향 사이의 내적을 계산(음수가 아닌지 확인)하고 32 제곱을 해줍니다. 32라는 값은 highlight의 반짝이는 정도(shininess value)입니다. 물체의 반짝이는 정도가 높을수록 빛을 전체적으로 산란하기 보다는 적당하게 반사하므로 하이라이트가 작아집니다. 아래에서 다양한 광택 값의 시각적 효과를 보여주는 이미지를 볼 수 있습니다.

![](https://learnopengl.com/img/lighting/basic_lighting_specular_shininess.png)

반사광(specular) 구성 요소가 너무 흩어지지 않도록 지수를 32로 설정합니다. 남은 유일한 일은 주변(ambient) 및 확산(diffuse) 구성 요소에 반사광(specular) 구성 요소를 추가하고 결합된 결과를 오브젝트의 색상과 곱하는 것입니다.

```cpp
vec3 result = (ambient + diffuse + specular) * objectColor;
FragColor = vec4(result, 1.0);
```

이제 Phong 조명 모델의 모든 조명 구성 요소를 계산했습니다. 시점에 따라 다음과 같은 그림이 나올 수 있습니다.

![](https://learnopengl.com/img/lighting/basic_lighting_specular.png)

[이곳](https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/basic_lighting_specular.cpp)에서 응용 프로그램의 전체 소스 코드를 찾을 수 있습니다.