#include <Windows.h>
#include "Menu.h"
#include "imgui/imgui.h"
#include <d3dx9tex.h>
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "Direct3DX9.h"
#include "Camera.h"

namespace Menu {
    bool isOpen = false;
}

bool show_another_window = false;
PDIRECT3DTEXTURE9 texture;

// Simple helper function to load an image into a DX9 texture with common settings
bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height, IDirect3DDevice9* pDevice)
{
    // Load texture from disk
    HRESULT hr = D3DXCreateTextureFromFileA(pDevice, filename, &texture);
    if (hr != S_OK)
        return false;

    // Retrieve description of the texture surface so we can access its size
    D3DSURFACE_DESC my_image_desc;
    texture->GetLevelDesc(0, &my_image_desc);
    *out_texture = texture;
    *out_width = (int)my_image_desc.Width;
    *out_height = (int)my_image_desc.Height;
    return true;
}

void Menu::init(IDirect3DDevice9* device, HWND hwnd) {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontFromFileTTF("C:\\Users\\Miika\\Downloads\\roboto\\Roboto-Regular.ttf", 16.0f);
    // needed for the cursor to not flicker next to crosshair:
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(device);
    Menu::setStyle();
    int my_image_width = 0;
    int my_image_height = 0;
    PDIRECT3DTEXTURE9 my_texture = NULL;
    bool ret = LoadTextureFromFile("C:\\Users\\Miika\\Downloads\\anime.png", &my_texture, &my_image_width, &my_image_height, device);
    IM_ASSERT(ret);
    return;
}

void Menu::render()
{
    {
        using namespace Camera;
        ImGui::Begin("Camera");

        ImGui::SliderFloat("angleX", &angleX, -6.28f, 6.28f);
        ImGui::SliderFloat("angleY", &angleY, -6.28f, 6.28f);
        ImGui::Text("x = %f", pos.x);
        ImGui::Text("y = %f", pos.y);
        ImGui::Text("z = %f", pos.z);

        ImGui::Checkbox("Show texture", &show_another_window);

        ImGui::End();
    }

    if (show_another_window)
    {
        ImGui::Begin("DirectX9 Texture Test", &show_another_window);
        ImGui::Image((void*)texture, ImVec2(825, 550));
        ImGui::End();
    }
}

void Menu::setStyle() {
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.21f, 0.21f, 0.21f, 0.56f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.51f, 0.36f, 0.36f, 0.39f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.53f, 0.25f, 0.25f, 0.39f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.83f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.87f, 0.19f, 0.19f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.21f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.48f, 0.33f, 0.33f, 0.80f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.35f, 0.16f, 0.19f, 0.60f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.00f, 0.43f, 0.43f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 0.26f, 0.26f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.07f, 0.07f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.46f, 0.46f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.23f, 0.23f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.51f, 0.36f, 0.36f, 0.39f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.53f, 0.25f, 0.25f, 0.39f);
    colors[ImGuiCol_Header] = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.51f, 0.36f, 0.36f, 0.39f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.25f, 0.25f, 0.39f);
    colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.51f, 0.36f, 0.36f, 0.39f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.53f, 0.25f, 0.25f, 0.39f);
    colors[ImGuiCol_Tab] = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.51f, 0.36f, 0.36f, 0.39f);
    colors[ImGuiCol_TabActive] = ImVec4(0.53f, 0.25f, 0.25f, 0.39f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.53f, 0.53f, 0.53f, 0.82f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.57f, 0.57f, 0.57f, 0.84f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.48f, 0.50f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 0.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.37f, 0.37f, 0.80f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}