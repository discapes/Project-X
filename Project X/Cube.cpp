#include "Cube.h"
#include "Direct3DX9.h"

namespace Cube {

	IDirect3DVertexBuffer9* CubeVertexBuffer = 0;
	IDirect3DIndexBuffer9* CubeIndexBuffer = 0;

	void init(IDirect3DDevice9* d3dDevice, D3DXVECTOR3 pos) {
		d3dDevice->CreateVertexBuffer(
			CubeVertexCount * sizeof(DirectX::Vertex),
			D3DUSAGE_WRITEONLY,
			DirectX::VertexFVF,
			D3DPOOL_MANAGED,
			&CubeVertexBuffer,
			0);

		d3dDevice->CreateIndexBuffer(
			CubeIndexCount * sizeof(WORD),
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&CubeIndexBuffer,
			0);

		// Vertices

		DirectX::Vertex* vertices;

		//Lock vertex buffer
		CubeVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

		vertices[0].x = -0.5f;
		vertices[0].y = 0.5f;
		vertices[0].z = 0.0f;
		vertices[0].color = D3DCOLOR_XRGB(255, 0, 0);

		vertices[1].x = 0.5f;
		vertices[1].y = 0.5f;
		vertices[1].z = 0.0f;
		vertices[1].color = D3DCOLOR_XRGB(0, 255, 0);

		vertices[2].x = -0.5f;
		vertices[2].y = -0.5f;
		vertices[2].z = 0.0f;
		vertices[2].color = D3DCOLOR_XRGB(0, 0, 255);

		vertices[3].x = 0.5f;
		vertices[3].y = -0.5f;
		vertices[3].z = 0.0f;
		vertices[3].color = D3DCOLOR_XRGB(255, 0, 0);

		for (int i = 0; i < 4; i++) {
			vertices[i] += pos;
		}

		CubeVertexBuffer->Unlock(); //Unlock vertex buffer

		// Indices:

		WORD* indices = 0;

		CubeIndexBuffer->Lock(0, 0, (void**)&indices, 0);

		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 2; indices[4] = 1; indices[5] = 3;

		CubeIndexBuffer->Unlock();
	}

	void cleanUp() {
		CubeVertexBuffer->Release();
		CubeIndexBuffer->Release();
	}

}