#pragma once
namespace Settings {
	namespace Window {
		//TODO auto check screen size if fullscreen = true
		inline constexpr int width = 1920;
		inline constexpr int height = 1080;
		inline constexpr bool isFullScreen = true;
	}
	namespace Keys {
		inline constexpr UINT exitKey = VK_ESCAPE;
	}
	namespace D3D {
		//TODO fix
		inline constexpr D3DDEVTYPE deviceType = D3DDEVTYPE_HAL;
	}
}