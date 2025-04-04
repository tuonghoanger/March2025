#include "App.h"
#include <algorithm>
#include "HoangUtil.h"
#include "imgui/imgui.h"
#include "Testing.h"
#include "PerfLog.h"
#include "TestModelProbe.h"
#include "Camera.h"

namespace dx = DirectX;

App::App(const std::string& commandLine)
	:
	commandLine(commandLine),
	wnd(1280, 720, "Tuong Huy Hoang"),
	scriptCommander(TokenizeQuoted(commandLine)),
	light(wnd.Gfx())
{
	cameras.AddCamera(std::make_unique<Camera>("A", dx::XMFLOAT3{ -13.5f,6.0f,3.5f }, 0.0f, PI / 2.0f));
	cameras.AddCamera(std::make_unique<Camera>("B", dx::XMFLOAT3{ -13.5f,28.8f,-6.4f }, PI / 180.0f * 13.0f, PI / 180.0f * 61.0f));

	cube.SetPos({ 4.0f,0.0f,0.0f });
	cube2.SetPos({ 0.0f,4.0f,0.0f });
	nano.SetRootTransform(
		dx::XMMatrixRotationY(PI / 2.f) *
		dx::XMMatrixTranslation(27.f, -0.56f, 1.7f)
	);
	gobber.SetRootTransform(
		dx::XMMatrixRotationY(-PI / 2.f) *
		dx::XMMatrixTranslation(-8.f, 10.f, 0.f)
	);

	cube.LinkTechniques(rg);
	cube2.LinkTechniques(rg);
	light.LinkTechniques(rg);
	sponza.LinkTechniques(rg);
	gobber.LinkTechniques(rg);
	nano.LinkTechniques(rg);

}

void App::HandleInput(float dt)
{
	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}

		switch (e->GetCode())
		{
		case VK_ESCAPE:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_F1:
			showDemoWindow = true;
			break;
		}
	}

	if (!wnd.CursorEnabled())
	{
		if (wnd.kbd.KeyIsPressed('W'))
		{
			cameras.GetCamera().Translate({ 0.0f,0.0f,dt });
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			cameras.GetCamera().Translate({ -dt,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			cameras.GetCamera().Translate({ 0.0f,0.0f,-dt });
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			cameras.GetCamera().Translate({ dt,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('E'))
		{
			cameras.GetCamera().Translate({ 0.0f,dt,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('Q'))
		{
			cameras.GetCamera().Translate({ 0.0f,-dt,0.0f });
		}
	}

	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			cameras.GetCamera().Rotate((float)delta->x, (float)delta->y);
		}
	}
}

void App::MouseEvent()
{
	while (const auto e = wnd.mouse.Read())
	{
		switch (e->GetType())
		{
		case Mouse::Event::Type::RPress:
			wnd.DisableCursor();
			wnd.mouse.EnableRaw();
			break;
		case Mouse::Event::Type::RRelease:
			wnd.EnableCursor();
			wnd.mouse.DisableRaw();
			break;
		}
	}
}

void App::ShowGameInfo()
{
	if (ImGui::Begin("Simulation Speed"))
	{
		ImGui::Text("App %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Status: %s", wnd.kbd.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING (hold spacebar to pause)");
	}
	ImGui::End();
}

void App::DoFrame(float dt)
{
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	cameras.GetCamera().BindToGraphics(wnd.Gfx());
	light.Bind(wnd.Gfx(), cameras.GetCamera().GetMatrix());

	MouseEvent();
	ShowGameInfo();

	light.Submit();
	cube.Submit();
	sponza.Submit();
	cube2.Submit();
	gobber.Submit();
	nano.Submit();

	rg.Execute(wnd.Gfx());

	// imgui windows
	static MP sponzeProbe{ "Sponza" };
	static MP gobberProbe{ "Gobber" };
	static MP nanoProbe{ "Nano" };
	sponzeProbe.SpawnWindow(sponza);
	gobberProbe.SpawnWindow(gobber);
	nanoProbe.SpawnWindow(nano);

	light.SpawnControlWindow();

	cube.SpawnControlWindow(wnd.Gfx(), "Cube 1");
	cube2.SpawnControlWindow(wnd.Gfx(), "Cube 2");
	//rg.RenderWidgets(wnd.Gfx());

	//cameras.SpawnWindow();
	// 	ShowImguiDemoWindow();
	// present
	wnd.Gfx().EndFrame();
	rg.Reset();
}

void App::ShowImguiDemoWindow()
{
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}
}

App::~App()
{}

int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		// execute the game logic
		const auto dt = timer.Mark() * speed_factor;
		HandleInput(dt);
		DoFrame(dt);
	}
}