#include <d3dx9math.h>
#include "Camera.h"

namespace Camera {
	D3DXVECTOR3 pos(0.0f, 0.0f, -2.0f);
	D3DXVECTOR3 targetAbsPos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR4 targetRelPos(0.0f, 0.0f, 0.f, 0);
	D3DXVECTOR4 targetRelPosRight(0.0f, 0.0f, 0.f, 0);
	D3DXVECTOR4 targetRelPosUp(0.0f, 0.0f, 0.f, 0);

	D3DXMATRIX targetAngle;
	D3DXMATRIX targetRightAngle;
	D3DXMATRIX targetUpAngle;

	D3DXMATRIX rightAngle;
	D3DXMATRIX upAngle;



	D3DXMATRIX view;

	float angleX{ 0 };
	float angleY{ 0 };
	void handleControls(float timeDelta)
	{
		// GET ANGLES
		if (GetAsyncKeyState(VK_UP)) // UP
			Camera::angleX -= timeDelta * 1000.f;
		if (GetAsyncKeyState(VK_DOWN)) // DOWN
			Camera::angleX += timeDelta * 1000.f;
		if (GetAsyncKeyState(VK_RIGHT)) // RIGHT
			Camera::angleY += timeDelta * 1000.f;
		if (GetAsyncKeyState(VK_LEFT)) // LEFT
			Camera::angleY -= timeDelta * 1000.f;

		if (GetAsyncKeyState(VK_RETURN)) { // ENTER
			Camera::pos = { 0.0f, 0.0f, -2.0f };
			Camera::angleY = 0;
			Camera::angleX = 0;
		}

		// NORMALIZE ANGLES
		if (Camera::angleY >= 6.28f)
			Camera::angleY = 0.0f;

		if (Camera::angleX >= 6.28f)
			Camera::angleX = 0.0f;

		if (Camera::angleY <= -6.28f)
			Camera::angleY = 0.0f;

		if (Camera::angleX <= -6.28f)
			Camera::angleX = 0.0f;

		// CAMERA MOVEMENT AND ANGLE
		D3DXMatrixRotationYawPitchRoll(&Camera::targetAngle, Camera::angleY, Camera::angleX, 0);		// get the target angle from camera
		Camera::targetRightAngle = Camera::targetAngle * Camera::rightAngle;
		D3DXVec3Transform(&Camera::targetRelPos, &D3DXVECTOR3(0.0f, 0.0f, 1.f), &Camera::targetAngle);	// get the target position from camera
		D3DXVec3Transform(&Camera::targetRelPosRight, &D3DXVECTOR3(0.0f, 0.0f, 1.f), &Camera::targetRightAngle);

		{ // MOVEMENT
			if (GetAsyncKeyState(0x57)) { // W
				Camera::pos.x += Camera::targetRelPos.x * timeDelta * 1000.f;
				Camera::pos.z += Camera::targetRelPos.z * timeDelta * 1000.f;
			}
			if (GetAsyncKeyState(0x53)) { // S
				Camera::pos.x -= Camera::targetRelPos.x * timeDelta * 1000.f;
				Camera::pos.z -= Camera::targetRelPos.z * timeDelta * 1000.f;
			}
			if (GetAsyncKeyState(0x44)) { // D
				Camera::pos.x += Camera::targetRelPosRight.x * timeDelta * 1000.f;
				Camera::pos.z += Camera::targetRelPosRight.z * timeDelta * 1000.f;
			}
			if (GetAsyncKeyState(0x41)) {// A
				Camera::pos.x -= Camera::targetRelPosRight.x * timeDelta * 1000.f;
				Camera::pos.z -= Camera::targetRelPosRight.z * timeDelta * 1000.f;
			}
			if (GetAsyncKeyState(VK_LSHIFT)) {// Left Shift
				Camera::pos.y += timeDelta * 1000.f;
			}
			if (GetAsyncKeyState(VK_LCONTROL)) {// Left Control
				Camera::pos.y -= timeDelta * 1000.f;
			}
		}

		{ // ANGLE
			Camera::targetAbsPos.x = Camera::pos.x + Camera::targetRelPos.x;
			Camera::targetAbsPos.y = Camera::pos.y + Camera::targetRelPos.y;	// get the absolute position of target
			Camera::targetAbsPos.z = Camera::pos.z + Camera::targetRelPos.z;
		}

		// SET VIEW
		D3DXMatrixLookAtLH(&Camera::view, &Camera::pos, &Camera::targetAbsPos, &Camera::up); // get view
	}
}