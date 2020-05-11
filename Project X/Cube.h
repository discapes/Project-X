#pragma once
#include <d3d9.h>
#include <d3dx9math.h>

namespace Cube {

	extern IDirect3DVertexBuffer9* VertexBuffer;
	extern IDirect3DIndexBuffer9* IndexBuffer;
	extern IDirect3DTexture9* Texture;
	inline constexpr int VertexCount = 36;
	inline constexpr int IndexCount = 8;
	inline constexpr int PrimitiveCount = 12;

	void init (IDirect3DDevice9* d3dDevice, D3DXVECTOR3 pos);
	void cleanUp();
}