#pragma once
#include <d3d9.h>

namespace DirectX {
	int setupScene();
	void cleanUp();
	int renderScene(float timeDelta);
    int initializeD3D(HWND hwnd); 
	void initVertices();
}