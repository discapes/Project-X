#include "Cube.h"
#include "Direct3DX9.h"

namespace Cube {

	IDirect3DVertexBuffer9* VertexBuffer = 0;
	IDirect3DIndexBuffer9* IndexBuffer = 0;
	IDirect3DTexture9* Texture;

	void init(IDirect3DDevice9* d3dDevice, D3DXVECTOR3 pos) {
        void* pVoid;

        d3dDevice->CreateVertexBuffer(
            VertexCount * sizeof(DirectX::Vertex),
            D3DUSAGE_WRITEONLY,
            0,
            D3DPOOL_MANAGED,
            &VertexBuffer,
            0);

        DirectX::Vertex Vertices[] =
        {

            //front face
            { 1.0f,-1.0f,-1.0f, 1.0f, 1.0f},
            {-1.0f,-1.0f,-1.0f, 0.0f, 1.0f},
            {-1.0f, 1.0f,-1.0f, 0.0f, 0.0f},

            { 1.0f,-1.0f,-1.0f, 1.0f, 1.0f},
            {-1.0f, 1.0f,-1.0f, 0.0f, 0.0f},
            { 1.0f, 1.0f,-1.0f, 1.0f, 0.0f},

            //right side
            { 1.0f,-1.0f, 1.0f, 1.0f, 1.0f},
            { 1.0f,-1.0f,-1.0f, 0.0f, 1.0f},
            { 1.0f, 1.0f,-1.0f, 0.0f, 0.0f},

            { 1.0f,-1.0f, 1.0f, 1.0f, 1.0f},
            { 1.0f, 1.0f,-1.0f, 0.0f, 0.0f},
            { 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

            //left side
            {-1.0f,-1.0f,-1.0f, 1.0f, 1.0f},
            {-1.0f,-1.0f, 1.0f, 0.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f, 0.0f, 0.0f},

            {-1.0f,-1.0f,-1.0f, 1.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
            {-1.0f, 1.0f,-1.0f, 1.0f, 0.0f},

            //back side
            {-1.0f,-1.0f, 1.0f, 1.0f, 1.0f},
            { 1.0f,-1.0f, 1.0f, 0.0f, 1.0f},
            { 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},

            {-1.0f,-1.0f, 1.0f, 1.0f, 1.0f},
            { 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
            {-1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

            //top side
            { 1.0f, 1.0f,-1.0f, 1.0f, 1.0f},
            {-1.0f, 1.0f,-1.0f, 0.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f, 0.0f, 0.0f},

            { 1.0f, 1.0f,-1.0f, 1.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
            { 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

            //bottom side
            { 1.0f,-1.0f, 1.0f, 1.0f, 1.0f},
            {-1.0f,-1.0f, 1.0f, 0.0f, 1.0f},
            {-1.0f,-1.0f,-1.0f, 0.0f, 0.0f},

            { 1.0f,-1.0f, 1.0f, 1.0f, 1.0f},
            {-1.0f,-1.0f,-1.0f, 0.0f, 0.0f},
            { 1.0f,-1.0f,-1.0f, 1.0f, 0.0f},
        };

        VertexBuffer->Lock(0, 0, (void**)&pVoid, 0);

        for (int i = 0; i < 36; i++) {
            Vertices[i] += pos;
        }

        //copy the squarevertices[] array into the vertex buffer
        memcpy(pVoid, Vertices, sizeof(Vertices));

        VertexBuffer->Unlock();

        D3DXCreateTextureFromFile( // Create texture.
            d3dDevice,
            "C:\\Users\\Miika\\source\\repos\\Project X\\x64\\Release\\braynzar.png",
            &Texture);

		// Indices:
        //TODO
        //d3dDevice->CreateIndexBuffer(
        //    IndexCount * sizeof(WORD),
        //    D3DUSAGE_WRITEONLY,
        //    D3DFMT_INDEX16,
        //    D3DPOOL_MANAGED,
        //    &IndexBuffer,
        //    0);

		//WORD* indices = 0;

		//IndexBuffer->Lock(0, 0, (void**)&indices, 0);

		//indices[0] = 0; indices[1] = 1; indices[2] = 2;
		//indices[3] = 2; indices[4] = 1; indices[5] = 3;

		//IndexBuffer->Unlock();
	}

	void cleanUp() {
		VertexBuffer->Release();
        Texture->Release();
		//IndexBuffer->Release();
	}

}