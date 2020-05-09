#include <d3d9.h>
#include "Direct3DX9.h"
#include "Settings.h"

namespace DirectX {
	IDirect3D9* d3d9 = NULL;
	IDirect3DDevice9* d3dDevice = NULL;

	int setupScene() {
		return 0;
	}

	void cleanUp() {
        d3dDevice->Release();
        if (d3d9) {    //If there is a Direct3D device
            d3d9->Release();    //Release Memory from the device
            d3d9 = NULL;        //Make sure there is no memory leaks
        }
		return;
	}

    int renderScene(float timeDelta)    //Renders a single frame
    {
            //Clear the window to 0x00000000 (black)
            d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000055, 1.0f, 0);

            //Start drawing our scene
            d3dDevice->BeginScene();

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


}
