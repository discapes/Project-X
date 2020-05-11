#pragma once
#include <d3dx9math.h>

namespace Camera {
	extern D3DXVECTOR3 pos;
	extern D3DXVECTOR3 targetAbsPos;
	extern D3DXVECTOR3 up;

	extern D3DXMATRIX view;

	extern float angleX;
	extern float angleY;

	extern D3DXVECTOR4 targetRelPos;
	extern D3DXVECTOR4 targetRelPosRight;

	extern D3DXMATRIX targetAngle;
	extern D3DXMATRIX targetRightAngle;

	extern D3DXMATRIX rightAngle;
	extern D3DXMATRIX upAngle;

	void handleControls(float timeDelta);
}