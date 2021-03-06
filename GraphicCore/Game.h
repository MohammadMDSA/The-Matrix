//
// Game.h
//

#pragma once

#include "StepTimer.h"


namespace GraphicCore
{

	// A basic game implementation that creates a D3D11 device and
	// provides a game loop.
	public ref class Game sealed
	{
	public:

		Game();

		// Initialization and management
		void Initialize(Windows::UI::Core::CoreWindow^ window, int width, int height, int rotation, const Platform::Array<Types::ObjectBase^>^ objects);

		// Basic game loop
		void Tick(const Platform::Array<Types::ObjectBase^>^ objects);

		// Messages
		void OnActivated();
		void OnDeactivated();
		void OnSuspending();
		void OnResuming();
		void OnWindowSizeChanged(int width, int height, int rotation);
		void ValidateDevice();

		// Properties
		int GetDefaultWidth();
		int GetDefaultHeight();

	private:

		void Update(DX::StepTimer& timer, const Platform::Array<Types::ObjectBase^>^ objects);
		void Render();

		void Clear();
		void Present();

		void CreateDevice();
		void CreateResources();

		void OnDeviceLost();

		// Device resources.
		IUnknown* m_window;
		int                                             m_outputWidth;
		int                                             m_outputHeight;
		DXGI_MODE_ROTATION                              m_outputRotation;

		D3D_FEATURE_LEVEL                               m_featureLevel;
		Microsoft::WRL::ComPtr<ID3D11Device3>           m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext3>    m_d3dContext;

		Microsoft::WRL::ComPtr<IDXGISwapChain3>         m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

		// Rendering loop timer.
		DX::StepTimer                                   m_timer;
	};
}