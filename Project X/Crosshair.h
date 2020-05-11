#pragma once
#include "Direct3DX9.h"

namespace Crosshair {
	extern IDirect3DVertexBuffer9* VertexBuffer;
	inline constexpr int VertexCount = 12;

	void init(IDirect3DDevice9* d3dDevice);
	void move(DirectX::Vertex pos);
}