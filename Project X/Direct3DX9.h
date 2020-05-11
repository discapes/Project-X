#pragma once
#include <d3d9.h>
#include <d3dx9math.h>

namespace DirectX {

	//Vertex structure
	struct Vertex {
		FLOAT x{}, y{}, z{};
		FLOAT u{}, v{};
		D3DCOLOR color{ D3DCOLOR_RGBA(255, 255, 255, 255) };
		FLOAT nx{}, ny{}, nz{};
		Vertex(float _x, float _y, float _z, D3DCOLOR _color) {
			x = _x;
			y = _y;
			z = _z;
			color = _color;
		}
		Vertex(float _x, float _y, float _z, float _u, float _v, float _nx, float _ny, float _nz) {
			x = _x;
			y = _y;
			z = _z;
			u = _u;
			v = _v;
			nx = _nx;
			ny = _ny;
			nz = _nz;
		}
		Vertex() {

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

	extern IDirect3DVertexDeclaration9* myVertexDecl;

	int setupScene();
	void cleanUp();
	int renderScene(float timeDelta);
	int initializeD3D(HWND hwnd);
	void initVertices();
}