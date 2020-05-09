#pragma once
namespace Settings {
	namespace Window {
		inline constexpr int width = 800;
		inline constexpr int height = 600;
		inline constexpr bool windowed = true;
		inline constexpr bool isFullScreen = false;
	}
	namespace Keys {
		inline constexpr UINT exitKey = VK_ESCAPE;
	}
	namespace D3D {
		inline constexpr D3DDEVTYPE deviceType = D3DDEVTYPE_HAL;
	}
}