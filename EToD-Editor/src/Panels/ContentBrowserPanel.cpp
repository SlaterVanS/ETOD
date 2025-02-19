#include "etodpch.h"
#include "ContentBrowserPanel.h"

#include "ETOD/Project/Project.h"

#include <imgui/imgui.h>

namespace ETOD {

	namespace Utils {

		static bool IsImageFile(const std::filesystem::path& path)
		{
			if (path.extension() == ".png" || path.extension() == ".jpg")
				return true;

			return false;
		}
	}

	ContentBrowserPanel::ContentBrowserPanel()
		: m_BaseDirectory(Project::GetAssetDirectory()), m_CurrentDirectory(m_BaseDirectory)
	{
		m_DirectoryIcon = Texture2D::Create("Resources/Icons/ContentBrowser/DirectoryIcon.png");
		m_FileIcon = Texture2D::Create("Resources/Icons/ContentBrowser/FileIcon.png");

		// Loading Textures
		for (auto& directoryEntry : std::filesystem::recursive_directory_iterator(m_BaseDirectory))
		{
			const auto& path = directoryEntry.path();
			const auto& filenameString = path.string();

			if (Utils::IsImageFile(path))
				m_TextureIcons[filenameString] = Texture2D::Create(filenameString);
		}
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		if (languageCheck.language == 0)
		{
			ImGui::Begin("Content Browser");

			if (m_CurrentDirectory != std::filesystem::path(m_BaseDirectory))
			{
				if (ImGui::Button("Back"))
				{
					m_CurrentDirectory = m_CurrentDirectory.parent_path();
				}
			}
		}
		else if(languageCheck.language == 1)
		{
			ImGui::Begin(u8"资源管理器");

			if (m_CurrentDirectory != std::filesystem::path(m_BaseDirectory))
			{
				if (ImGui::Button(u8"返回"))
				{
					m_CurrentDirectory = m_CurrentDirectory.parent_path();
				}
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();
			std::string filenameString = path.filename().string();

			ImGui::PushID(filenameString.c_str());
			Ref<Texture2D> icon = nullptr;

			if (Utils::IsImageFile(path))
				icon = m_TextureIcons[path.string()];

			else
				icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

			if (ImGui::BeginDragDropSource())
			{
				std::filesystem::path relativePath(path);
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
					m_CurrentDirectory /= path.filename();

			}
			ImGui::TextWrapped(filenameString.c_str());

			ImGui::NextColumn();

			ImGui::PopID();
		}

		ImGui::Columns(1);

		//ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		//ImGui::SliderFloat("Padding", &padding, 0, 32);

		// TODO: status bar
		ImGui::End();
	}

}
