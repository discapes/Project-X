#pragma once
#include <d3d9.h>
#include <d3dx9math.h>

namespace Cube {

	extern IDirect3DVertexBuffer9* SquareVertexBuffer;
	extern IDirect3DIndexBuffer9* SquareIndexBuffer;
	inline constexpr int SquareVertexCount = 4;
	inline constexpr int SquareIndexCount = 6;

	void init (IDirect3DDevice9* d3dDevice, D3DXVECTOR3 pos);
	void cleanUp();
}