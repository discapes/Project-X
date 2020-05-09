#pragma once
namespace Settings {
	namespace Window {
		inline constexpr int width = 1920;
		inline constexpr int height = 1080;
		inline constexpr bool isFullScreen = true;
	}
	namespace Keys {
		inline constexpr UINT exitKey = VK_ESCAPE;
	}
	namespace D3D {
		inline constexpr D3DDEVTYPE deviceType = D3DDEVTYPE_HAL;
	}
}