#pragma once
#include <d3d9.h>
#include <d3dx9math.h>

namespace DirectX {

	namespace View {
		extern D3DXVECTOR3 pos;
		extern D3DXVECTOR3 targ;
		extern D3DXVECTOR3 up;

		extern D3DXMATRIX View;

		extern float angleX;
		extern float angleY;
		extern D3DXMATRIX cameraAngleX, cameraAngleY, cameraAngle;
	}

    //Vertex structure
    struct Vertex {
        FLOAT x, y, z;
        D3DCOLOR color;    //add color to vertex structure
    };

    //Define the Flexible vertex format
    inline const DWORD VertexFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	int setupScene();
	void cleanUp();
	int renderScene(float timeDelta);
    int initializeD3D(HWND hwnd); 
	void initVertices();
}