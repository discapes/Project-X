#include <d3d9.h>
#include <d3dx9math.h>
#include "Direct3DX9.h"
#include "Settings.h"
namespace DirectX {
    namespace View {
        D3DXVECTOR3 pos(0.0f, 0.0f, -2.0f);
        D3DXVECTOR3 targ(0.0f, 0.0f, 0.0f);
        D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

        D3DXMATRIX View;
    }

	IDirect3D9* d3d9 = NULL;
	IDirect3DDevice9* d3dDevice = NULL;

    //
    IDirect3DVertexBuffer9* SquareVertexBuffer = 0;
    IDirect3DIndexBuffer9* SquareIndexBuffer = 0;
    constexpr int SquareVertexCount = 4;
    constexpr int SquareIndexCount = 6;
    //Vertex structure
    struct Vertex {
        FLOAT x, y, z;
        D3DCOLOR color;    //add color to vertex structure
    };

    //Define the Flexible vertex format
    const DWORD VertexFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
    //

	int setupScene() {
        d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
        //d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
        initVertices();

        D3DXMATRIX proj;
        D3DXMatrixPerspectiveFovLH(
            &proj,
            D3DX_PI * 0.5f, // fov
            (float)Settings::Window::width / (float)Settings::Window::height,
            0.0f, // start of sight
            1000.0f); // end of sight

        d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

        d3dDevice->SetStreamSource(0, SquareVertexBuffer, 0, sizeof(Vertex));
        d3dDevice->SetIndices(SquareIndexBuffer);
        d3dDevice->SetFVF(VertexFVF);

		return 0;
	}

	void cleanUp() {
        SquareIndexBuffer->Release();
        SquareVertexBuffer->Release();
        d3dDevice->Release();
        if (d3d9) {    //If there is a Direct3D device
            d3d9->Release();    //Release Memory from the device
            d3d9 = NULL;        //Make sure there is no memory leaks
        }
		return;
	}

    int renderScene(float timeDelta)    //Renders a single frame
    {
        // KEYBOARD INPUTS
        if (GetAsyncKeyState(0x57)) // W
            View::pos.z += timeDelta * 1000.f;
        if (GetAsyncKeyState(0x53)) // S
            View::pos.z -= timeDelta * 1000.f;

        if (GetAsyncKeyState(0x44)) // D
            View::pos.x += timeDelta * 1000.f;
        if (GetAsyncKeyState(0x41)) // A
            View::pos.x -= timeDelta * 1000.f;

        if (GetAsyncKeyState(VK_LSHIFT)) // Left Shift
            View::pos.y += timeDelta * 1000.f;
        if (GetAsyncKeyState(VK_LCONTROL)) // Left Control
            View::pos.y -= timeDelta * 1000.f;



        // NORMALIZE
        //if (y >= 6.28f)
        //    y = 0.0f;

        //if (x >= 6.28f)
        //    x = 0.0f;

            

        // COMPUTE
        D3DXMatrixLookAtLH(&View::View, &View::pos, &View::targ, &View::up);
        d3dDevice->SetTransform(D3DTS_VIEW, &View::View);



        //Clear the window to 0x00000000 (black)
        d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000055, 1.0f, 0);
        //Start drawing our scene
        d3dDevice->BeginScene();



        // DRAW
        d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);



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
        d3dDevice->CreateVertexBuffer(
            SquareVertexCount * sizeof(Vertex),
            D3DUSAGE_WRITEONLY,
            VertexFVF,
            D3DPOOL_MANAGED,
            &SquareVertexBuffer,
            0);

        d3dDevice->CreateIndexBuffer(
            SquareIndexCount * sizeof(WORD),
            D3DUSAGE_WRITEONLY,
            D3DFMT_INDEX16,
            D3DPOOL_MANAGED,
            &SquareIndexBuffer,
            0);

        // Vertices

        Vertex* vertices;

        //Lock vertex buffer
        SquareVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

        vertices[0].x = -0.5f;
        vertices[0].y = 0.5f;
        vertices[0].z = 0.0f;
        vertices[0].color = D3DCOLOR_XRGB(255, 0, 0);

        vertices[1].x = 0.5f;
        vertices[1].y = 0.5f;
        vertices[1].z = 0.0f;
        vertices[1].color = D3DCOLOR_XRGB(0, 255, 0);

        vertices[2].x = -0.5f;
        vertices[2].y = -0.5f;
        vertices[2].z = 0.0f;
        vertices[2].color = D3DCOLOR_XRGB(0, 0, 255);

        vertices[3].x = 0.5f;
        vertices[3].y = -0.5f;
        vertices[3].z = 0.0f;
        vertices[3].color = D3DCOLOR_XRGB(255, 0, 0);

        SquareVertexBuffer->Unlock(); //Unlock vertex buffer

        // Indices:

        WORD* indices = 0;

        SquareIndexBuffer->Lock(0, 0, (void**)&indices, 0);

        indices[0] = 0; indices[1] = 1; indices[2] = 2;
        indices[3] = 2; indices[4] = 1; indices[5] = 3;

        SquareIndexBuffer->Unlock();
    }
}
