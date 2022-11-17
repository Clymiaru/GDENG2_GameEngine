#include "pch.h"
#include "RenderDevice.h"

namespace Engine
{
	RenderDevice::RenderDevice(ID3D11Device* device) :
		m_Device{device},
		m_DxgiDevice{nullptr},
		m_DxgiAdapter{nullptr},
		m_DxgiFactory{nullptr}

	{
		m_Device->QueryInterface(__uuidof(IDXGIDevice),
		                       reinterpret_cast<void**>(&m_DxgiDevice));

		m_DxgiDevice->GetParent(__uuidof(IDXGIAdapter),
		                        reinterpret_cast<void**>(&m_DxgiAdapter));

		m_DxgiAdapter->GetParent(__uuidof(IDXGIFactory),
		                         reinterpret_cast<void**>(&m_DxgiFactory));
	}

	RenderDevice::~RenderDevice()
	{
		m_DxgiAdapter->Release();
		m_DxgiDevice->Release();
		m_DxgiFactory->Release();
		m_Device->Release();
	}
	
	SwapChain* RenderDevice::CreateSwapChain(Window& window) const
	{
		return new SwapChain(window, m_Device, m_DxgiFactory);
	}
}
