#pragma once
#include <d3d9.h>
#include <d3dx9math.h>

namespace DirectX {

	//Vertex structure
	struct Vertex {
		FLOAT x, y, z;
		D3DCOLOR color;    //add color to vertex structure
		Vertex() {
			x = 0;
			y = 0;
			z = 0;
			color = D3DCOLOR_RGBA(255, 255, 255, 255);
		};
		Vertex(float _x, float _y, float _z, D3DCOLOR _color) {
			x = _x;
			y = _y;
			z = _z;
			color = _color;
		}
		Vertex operator+(Vertex d) {
			return { x + d.x, y + d.y, z + d.z, d.color };
		}
		Vertex operator-(Vertex d) {
			return { x - d.x, y - d.y, z - d.z, d.color };
		}
		Vertex operator*(float d) {
			return { x * d, y * d, z * d, color };
		}

		Vertex& operator+=(const D3DXVECTOR3& rhs) {
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			return *this;
		}
		explicit Vertex(D3DXVECTOR3 _vector) : x{ _vector.x }, y{ _vector.y }, z{ _vector.z }, color{D3DCOLOR_RGBA(255, 255, 255, 255)} {};
	};

	//Define the Flexible vertex format
	inline const DWORD VertexFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	int setupScene();
	void cleanUp();
	int renderScene(float timeDelta);
	int initializeD3D(HWND hwnd);
	void initVertices();
}