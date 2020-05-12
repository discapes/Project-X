#include <d3dx9math.h>
#include "Camera.h"
#include "Settings.h"

namespace Camera {
	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 targetAbsPos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR4 up(0.0f, 1.0f, 0.0f, 0);

	D3DXVECTOR4 targetRelPos(0.0f, 0.0f, 0.f, 0);
	D3DXVECTOR4 targetRelPosRight(0.0f, 0.0f, 0.f, 0);
	D3DXVECTOR4 targetRelPosUp(0.0f, 0.0f, 0.f, 0);

	D3DXMATRIX targetAngle;
	D3DXMATRIX targetRightAngle;
	D3DXMATRIX targetUpAngle;

	D3DXMATRIX rightAngle;
	D3DXMATRIX upAngle;
	 
	D3DXVECTOR4 VECTOR4(D3DXVECTOR3 &VECTOR3) {
		return D3DXVECTOR4(VECTOR3.x, VECTOR3.y, VECTOR3.z, 0);
	}
	D3DXVECTOR3 VECTOR3(D3DXVECTOR4& VECTOR4) {
		return D3DXVECTOR3(VECTOR4.x, VECTOR4.y, VECTOR4.z);
	}

	D3DXMATRIX view;

	float angleX{ 0 };
	float angleY{ 0 };
	void handleControls(float timeDelta)
	{
		using Settings::Keys::flySpeed;
		using Settings::Keys::lookSpeed;
		// GET ANGLES
		if (GetAsyncKeyState(VK_UP)) // UP
			Camera::angleX -= timeDelta * lookSpeed;
		if (GetAsyncKeyState(VK_DOWN)) // DOWN
			Camera::angleX += timeDelta * lookSpeed;
		if (GetAsyncKeyState(VK_RIGHT)) // RIGHT
			Camera::angleY += timeDelta * lookSpeed;
		if (GetAsyncKeyState(VK_LEFT)) // LEFT
			Camera::angleY -= timeDelta * lookSpeed;

		if (GetAsyncKeyState(VK_RETURN)) { // ENTER
			Camera::pos = { 0.0f, 0.0f, 0.f };
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
		D3DXVec3Transform(&Camera::up, &D3DXVECTOR3(0.0f, 1.0f, 0.f), &Camera::targetAngle);	// get the target position from camera
		D3DXVec3Transform(&Camera::targetRelPosRight, &D3DXVECTOR3(0.0f, 0.0f, 1.f), &Camera::targetRightAngle);

		{ // MOVEMENT
			if (GetAsyncKeyState(0x57)) { // W
				Camera::pos.x += Camera::targetRelPos.x * timeDelta * flySpeed;
				Camera::pos.z += Camera::targetRelPos.z * timeDelta * flySpeed;
			}
			if (GetAsyncKeyState(0x53)) { // S
				Camera::pos.x -= Camera::targetRelPos.x * timeDelta * flySpeed;
				Camera::pos.z -= Camera::targetRelPos.z * timeDelta * flySpeed;
			}
			if (GetAsyncKeyState(0x44)) { // D
				Camera::pos.x += Camera::targetRelPosRight.x * timeDelta * flySpeed;
				Camera::pos.z += Camera::targetRelPosRight.z * timeDelta * flySpeed;
			}
			if (GetAsyncKeyState(0x41)) {// A
				Camera::pos.x -= Camera::targetRelPosRight.x * timeDelta * flySpeed;
				Camera::pos.z -= Camera::targetRelPosRight.z * timeDelta * flySpeed;
			}
			if (GetAsyncKeyState(VK_LSHIFT)) {// Left Shift
				Camera::pos.y += timeDelta * flySpeed;
			}
			if (GetAsyncKeyState(VK_LCONTROL)) {// Left Control
				Camera::pos.y -= timeDelta * flySpeed;
			}
		}

		{ // ANGLE
			Camera::targetAbsPos = Camera::pos + VECTOR3(Camera::targetRelPos);
		}

		// SET VIEW
		D3DXMatrixLookAtLH(&Camera::view, &Camera::pos, &Camera::targetAbsPos, &VECTOR3(Camera::up)); // get view
	}
}