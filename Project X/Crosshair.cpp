#include <d3d9.h>
#include <d3dx9math.h>
#include "Crosshair.h"
#include "Direct3DX9.h"

namespace Crosshair {
	IDirect3DVertexBuffer9* VertexBuffer;
	DirectX::Vertex offsets[24];
	float length{0.1f};
	float distFromPos{ 1.f };

	void init(IDirect3DDevice9* d3dDevice) {
		d3dDevice->CreateVertexBuffer(
			24 * sizeof(DirectX::Vertex),
			D3DUSAGE_WRITEONLY,
			DirectX::VertexFVF,
			D3DPOOL_MANAGED,
			&VertexBuffer,
			0);
		{ // set offsets
			int sideNum{};
			float f = distFromPos;
			for (int x = 0; x != (255 * 2); x += 255) {
				for (int i{}; i < 4; i++) {
					offsets[sideNum * 4 + i].x = f;
					offsets[sideNum * 4 + i].color = D3DCOLOR_XRGB(255, 255, x);
				}
				sideNum++;
				for (int i{}; i < 4; i++) {
					offsets[sideNum * 4 + i].y = f;
					offsets[sideNum * 4 + i].color = D3DCOLOR_XRGB(0, 255, x);
				}
				sideNum++;
				for (int i{}; i < 4; i++) {
					offsets[sideNum * 4 + i].z = f;
					offsets[sideNum * 4 + i].color = D3DCOLOR_XRGB(255, 0, x);
				}
				sideNum++;
				f *= -1;
			}
		}
		{ // set offsets
			int sideNum{};
			for (int i{}; i < 2; i++) {
					offsets[sideNum * 4 + 0].z = -length;
					offsets[sideNum * 4 + 1].z = length;
					offsets[sideNum * 4 + 2].y = -length;
					offsets[sideNum * 4 + 3].y = length;
				sideNum++;
				for (int i{}; i < 4; i++) {
					offsets[sideNum * 4 + 0].x = -length;
					offsets[sideNum * 4 + 1].x = length;
					offsets[sideNum * 4 + 2].z = -length;
					offsets[sideNum * 4 + 3].z = length;
				}
				sideNum++;
				for (int i{}; i < 4; i++) {
					offsets[sideNum * 4 + 0].y = -length;
					offsets[sideNum * 4 + 1].y = length;
					offsets[sideNum * 4 + 2].x = -length;
					offsets[sideNum * 4 + 3].x = length;
				}
				sideNum++;
			}
		}
	}

	void move(DirectX::Vertex pos) {
		static DirectX::Vertex* vertices;

		// move crosshair
		VertexBuffer->Lock(0, 0, (void**)&vertices, 0);
		for (int i = 0; i < 24; i++) {
			vertices[i] = pos + offsets[i];
		}

		VertexBuffer->Unlock();
	}
	void cleanUp() {
		VertexBuffer->Release();
		return;
	}
}