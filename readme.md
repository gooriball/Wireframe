# Wireframe

[English]  
Wireframe Map Viewer.

[한국어]  
와이어프레임 맵 뷰어.

## Preview

![Gameplay Preview](preview.gif)

## Controls

[English]
- W/A/S/D: Move Map
- Mouse Wheel: Zoom In/Out
- ESC: Quit

[한국어]
- W/A/S/D: 맵 이동
- 마우스 휠: 줌 인/아웃
- ESC: 종료

## Requirements

[English]
- CMake 3.14 or higher
- C++17 compatible compiler
- OpenGL 3.3 Core (GLSL 330)

[한국어]
- CMake 3.14 이상
- C++17 지원 컴파일러
- OpenGL 3.3 Core (GLSL 330)

## Build Instructions

[English]
```bash
# Clone the repository
git clone https://github.com/gooriball/Wireframe.git

cd Wireframe

# Build && Run
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release --parallel

cmake --build build --config Release --target run
```

[한국어]
```bash
# 저장소 복제
git clone https://github.com/gooriball/Wireframe.git

cd Wireframe

# 빌드 && 실행
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release --parallel

cmake --build build --config Release --target run
```

## Tech Stack

### Language
- C++17

### Rendering
- [OpenGL 3.3+](https://www.khronos.org/opengl/) GLSL(330)
- [GLAD](https://github.com/Dav1dde/glad)

### Windowing & input
- [SDL2](https://github.com/libsdl-org/SDL)

### Math
- [GLM](https://github.com/g-truc/glm)

### UI
- [ImGui](https://github.com/ocornut/imgui)

### Build Tools
- [CMake 3.14](https://cmake.org/)

## License

[English]  
This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.

[한국어]  
이 프로젝트는 MIT 라이선스 하에 배포됩니다 - 자세한 내용은 [LICENSE](LICENSE.md) 파일을 참조하세요.
