#pragma once

#include "HoangWindow.h"
#include "HoangException.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include "DxgiInfoManager.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>
#include "ConditionalNoexcept.h"

namespace Bind
{
    class Bindable;
}

namespace wrl = Microsoft::WRL;

class Graphics
{
    friend class Bind::Bindable;
public:
    class Exception : public HoangException
    {
        using HoangException::HoangException;
    };
    class HrException : public Exception
    {
    public:
        HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
        const char* what() const noexcept override;
        const char* GetType() const noexcept override;
        HRESULT GetErrorCode() const noexcept;
        std::string GetErrorString() const noexcept;
        std::string GetErrorDescription() const noexcept;
        std::string GetErrorInfo() const noexcept;
    private:
        HRESULT hr;
        std::string info;
    };
    class InfoException : public Exception
    {
    public:
        InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
        const char* what() const noexcept override;
        const char* GetType() const noexcept override;
        std::string GetErrorInfo() const noexcept;
    private:
        std::string info;
    };
    class DeviceRemovedException : public HrException
    {
        using HrException::HrException;
    public:
        const char* GetType() const noexcept override;
    private:
        std::string reason;
    };
public:
    Graphics(HWND hWnd);
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    ~Graphics() = default;
    void EndFrame();
    void BeginFrame(float red, float green, float blue) noexcept;

    void DrawIndexed(UINT count) noxnd;
    void SetProjection(DirectX::FXMMATRIX proj) noexcept;
    DirectX::XMMATRIX GetProjection() const noexcept;
    void SetCameraMat(DirectX::FXMMATRIX cam) noexcept;
    DirectX::XMMATRIX GetCameraSpaceMat() const noexcept;
    void EnableImgui() noexcept;
    void DisableImgui() noexcept;
    bool IsImguiEnabled() const noexcept;
private:
    DirectX::XMMATRIX projection;
    DirectX::XMMATRIX cameraSpaceMat;
    bool imguiEnabled = true;
#ifndef NDEBUG
    DxgiInfoManager infoManager;
#endif
    Microsoft::WRL::ComPtr<ID3D11Device> pDevice; // allocate create things
    Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext; // configure rendering  pipeline, issue render command
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};