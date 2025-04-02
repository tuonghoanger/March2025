#include "ImguiManager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"

ImguiManager::ImguiManager()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
}

ImguiManager::~ImguiManager()
{
    ImGui_ImplDX11_Shutdown();
    ImGui::DestroyContext();
}