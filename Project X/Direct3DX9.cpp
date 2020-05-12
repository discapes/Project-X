#include <d3d9.h>
#include <d3dx9math.h>
#include "Direct3DX9.h"
#include "Settings.h"
#include "Crosshair.h"
#include "Menu.h"
#include "imgui/imgui_impl_win32.h"
#include "Window.h"
#include <directxmath.h>
#include "Camera.h"
#include "Cube.h"

namespace DirectX {

	IDirect3D9* d3d9 = NULL;
	IDirect3DDevice9* d3dDevice = NULL;
	IDirect3DVertexDeclaration9* myVertexDecl;
	D3DMATERIAL9 white;    //Pointer to store material
	D3DLIGHT9 light;    //Pointer to store light

	int setupScene() {

		//Define the Flexible vertex format
		D3DVERTEXELEMENT9 simple_decl[] = { {0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0, 32, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END() };

		// d3dDevice is your LPDIRECT3DDEVICE9
		// simpleDecl is the array of D3DVERTEXELEMENT9s we defined above
		d3dDevice->CreateVertexDeclaration(simple_decl, &myVertexDecl);
		// d3dDevice is your LPDIRECT3DDEVICE9
		// myVertexDecl is the LPDIRECT3DVERTEXDECLARATION9 that we defined above
		d3dDevice->SetVertexDeclaration(myVertexDecl);
		// You are now ready to go!
		// Set all your stream sources, and DrawIndexedPrimitive()


		//Create the light
		ZeroMemory(&light, sizeof(light));
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) * 0.2f;
		light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) * 0.1f;
		light.Direction = { 0.5f, -0.5f, 1.f };

		//Create the material
		ZeroMemory(&white, sizeof(white));
		white.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		white.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		white.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		white.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		white.Power = 5.0f;




		Menu::init(d3dDevice, Window::hwnd);


		//Renormalize Normals
		d3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		d3dDevice->SetRenderState(D3DRS_LIGHTING, true);    //Enable Lighting
		d3dDevice->SetLight(0, &light);    //Set the light
		d3dDevice->LightEnable(0, true); //Enable the light
		//d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		//TODO
		d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		initVertices();

		// init camera
		D3DXMatrixRotationYawPitchRoll(&Camera::rightAngle, D3DXToRadian(90), 0, 0);
		D3DXMatrixRotationYawPitchRoll(&Camera::upAngle, 0, D3DXToRadian(-90), 0);

		D3DXMATRIX proj;
		D3DXMatrixPerspectiveFovLH(
			&proj,
			Settings::D3D::fov, // fov
			(float)Settings::Window::width / (float)Settings::Window::height,
			0.0f, // start of sight
			1000.0f); // end of sight

		d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

		return 0;
	}

	void cleanUp() {
		Cube::cleanUp();
		Crosshair::cleanUp();
		d3dDevice->Release();
		if (d3d9) {    //If there is a Direct3D device
			d3d9->Release();    //Release Memory from the device
			d3d9 = NULL;        //Make sure there is no memory leaks
		}
		return;
	}

	int renderScene(float timeDelta)    //Renders a single frame
	{
		// MENU TOGGLE
		static bool prevState = false;
		if (((bool)GetAsyncKeyState(VK_INSERT) == true) && (prevState == false))
			Menu::isOpen = !Menu::isOpen;
		prevState = GetAsyncKeyState(VK_INSERT);

		Camera::handleControls(timeDelta);
		DirectX::d3dDevice->SetTransform(D3DTS_VIEW, &Camera::view); // set D3DTS_VIEW to view

		Crosshair::move((Vertex)Camera::pos);

		//Clear the window to 0x00000000 (black) 0x00000055 (dark blue
		d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000055, 1.0f, 0);
		//Start drawing our scene
		d3dDevice->BeginScene();



		// DRAW
		//d3dDevice->SetStreamSource(0, Cube::VertexBuffer, 0, sizeof(Vertex));
		//d3dDevice->SetIndices(Cube::IndexBuffer);
		//d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 0, 0, 2);
		//d3dDevice->SetStreamSource(0, Cube::VertexBuffer, 0, sizeof(Vertex));
		//d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, Cube::PrimitiveCount);

		d3dDevice->SetTexture(0, Cube::Texture); //set texture
		d3dDevice->SetMaterial(&white);    //Set Material

		d3dDevice->SetStreamSource(0, Cube::VertexBuffer, 0, sizeof(Vertex));
		d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, Cube::PrimitiveCount);

		d3dDevice->SetStreamSource(0, Crosshair::VertexBuffer, 0, sizeof(Vertex));
		d3dDevice->DrawPrimitive(D3DPT_LINELIST, 0, Crosshair::PrimitiveCount);


		if (Menu::isOpen) {
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			Menu::render();
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		}



		//Stop drawing our scene
		d3dDevice->EndScene();
		//Display our newly created scene
		d3dDevice->Present(0, 0, 0, 0);
		return 0;
	}

	int initializeD3D(HWND hwnd)
	{
		//Start by initializing the Direct3D interface
		d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

		if (!d3d9) {    //If it was not initialized
			return 3;
		}

		D3DCAPS9 caps;    //Set the device capabilities structure to caps

		//Get the device capabilities
		d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, Settings::D3D::deviceType, &caps);

		int vertexproc = NULL;    //Set our vertex processing to NULL

		//If we can use hardware vertex processing
		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			//Set vertex processing to hardware
			vertexproc = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		else
			//Set vertex processing to software
			vertexproc = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		D3DPRESENT_PARAMETERS d3dpp;

		//The width of the back buffer in pixels
		d3dpp.BackBufferWidth = Settings::Window::width;

		//The height of the back buffer in pixels    
		d3dpp.BackBufferHeight = Settings::Window::height;

		//Back buffer pixel format
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

		//Amount of back buffers
		d3dpp.BackBufferCount = 1;

		//The type of multisampling for the buffer
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;

		//The quality of multisampling
		d3dpp.MultiSampleQuality = NULL;

		//Specifies how buffers will be swapped
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

		//Handle to our window
		d3dpp.hDeviceWindow = hwnd;

		//FullScreen or Windowed
		d3dpp.Windowed = !Settings::Window::isFullScreen;

		//true lets Direct3D do the depth/stencil buffer automatically
		d3dpp.EnableAutoDepthStencil = true;

		//Auto depth/stencil buffer format
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

		//Additional characteristics
		d3dpp.Flags = NULL;

		//Refresh rate
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

		//Presentation Interval
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		HRESULT createDeviceResult = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT, // primary adapter
			Settings::D3D::deviceType,         // device type
			hwnd,               // window associated with device
			vertexproc,         // vertex processing
			&d3dpp,             // present parameters
			&d3dDevice);         // return created device

		if (FAILED(createDeviceResult))    //If there was a problem creating the device
		{
			// try again using a 16-bit depth buffer
			d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

			createDeviceResult = d3d9->CreateDevice(
				D3DADAPTER_DEFAULT,
				Settings::D3D::deviceType,
				hwnd,
				vertexproc,
				&d3dpp,
				&d3dDevice);

			if (FAILED(createDeviceResult))    //If it still fails
			{
				d3d9->Release();
				return 4;
			}
		}

		d3d9->Release(); // done with d3d9 object
		return 0;
	}

	void initVertices() {

		Crosshair::init(d3dDevice);
		
		Cube::init(d3dDevice, { 0.f, 0.f, 2.f });

	}
}
