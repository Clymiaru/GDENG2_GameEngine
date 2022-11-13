#include "CreditsScreen.h"

#include <Engine/Core/Debug.h>
#include <d3d11.h>

#include <Engine/Graphics/Renderer.h>

#include "../../../Engine/Dependencies/ImGui/imgui.h"

#include "../../../Engine/Dependencies/stb/stb_image.h"

namespace Editor
{
	// Simple helper function to load an image into a DX11 texture with common settings
	bool LoadTextureFromFile(const char* filename,
	                         ID3D11ShaderResourceView** out_srv,
	                         int* out_width,
	                         int* out_height)
	{
		// Load from disk into a raw RGBA buffer
		int image_width           = 0;
		int image_height          = 0;
		unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		// Create texture
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width            = image_width;
		desc.Height           = image_height;
		desc.MipLevels        = 1;
		desc.ArraySize        = 1;
		desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage            = D3D11_USAGE_DEFAULT;
		desc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags   = 0;

		ID3D11Texture2D* pTexture = NULL;
		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem          = image_data;
		subResource.SysMemPitch      = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;
		Engine::Renderer::GetDevice().CreateTexture2D(&desc, &subResource, &pTexture);

		// Create texture view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels       = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		Engine::Renderer::GetDevice().CreateShaderResourceView(pTexture, &srvDesc, out_srv);
		pTexture->Release();

		*out_width  = image_width;
		*out_height = image_height;
		stbi_image_free(image_data);

		return true;
	}

	CreditsScreen::CreditsScreen() :
		AUIScreen{"Credits"},
		m_IsOpen{false}
	{
		LoadTextureFromFile("Assets/DLSU_Logo.png", &m_TextureView, &m_ImageWidth, &m_ImageHeight);
	}

	CreditsScreen::~CreditsScreen() = default;

	void CreditsScreen::Open()
	{
		m_IsOpen = true;
	}

	void CreditsScreen::Close()
	{
		m_IsOpen = false;
	}

	void CreditsScreen::DrawImpl()
	{
		Engine::String uiTag = m_Name;
		uiTag += "##MainMenuBar2";
		ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;

		if (m_IsOpen == false)
			return;

		if (!ImGui::Begin(uiTag.c_str(), &m_IsOpen))
		{
			ImGui::End();
		}
		else
		{
			float imageRatio = (float)m_ImageWidth / (float)m_ImageHeight;
			ImGui::Image(m_TextureView, ImVec2(256 * imageRatio, 256 * imageRatio));
			ImGui::Spacing();

			ImGui::Text("Scene Editor Version: 0.01");
			ImGui::Text("Developer: Lanz Joseph I. Santiago");
			ImGui::Separator();

			ImGui::Text("Special Thanks");
			ImGui::Text("Sir Neil's GDENG-2 Course");
			ImGui::Text("Pardcode (https://www.youtube.com/c/PardCode)");
			ImGui::Text("Cherno (https://www.youtube.com/c/TheChernoProject)");
			ImGui::Text("ChiliTomatoNoodle (https://www.youtube.com/c/ChiliTomatoNoodle)");
			ImGui::Text("Stack Overflow ;)");
			ImGui::End();
		}
	}
}
