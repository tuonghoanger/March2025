#pragma once
#include "Window.h"
#include "Timer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "Mesh.h"
#include "TestPlane.h"
#include "TestCube.h"
#include "ScriptCommander.h"
#include "Stencil.h"
#include "FrameCommander.h"
// https://github.com/planetchili/hw3d/commits/master/?since=2019-12-01&until=2019-12-31&author=planetchili

class App
{
public:
	App(const std::string& commandLine = "");
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
	void ShowImguiDemoWindow();
	void MouseEvent();
	void ShowGameInfo();
private:
	bool showDemoWindow = false;
	ImguiManager imgui;
	Window wnd;
	Timer timer;
	ScriptCommander scriptCommander;
	float speed_factor = 1.0f;
	Camera cam;
	FrameCommander fc;
	PointLight light;

	//Model gobber{ wnd.Gfx(),"Models\\gobber\\GoblinX.obj",6.0f };
	//Model wall{ wnd.Gfx(),"Models\\brick_wall\\brick_wall.obj",6.0f };
	//Model nano{ wnd.Gfx(),"Models\\nano_textured\\nanosuit.obj",2.0f };
	//Model sponza{ wnd.Gfx(),"Models\\sponza\\sponza.obj",1.0f / 20.0f };
	TestCube cube{ wnd.Gfx(),4.0f };
	TestCube cube2{ wnd.Gfx(),4.0f };
	//TestPlane bluePlane{ wnd.Gfx(),6.0f,{ 0.3f,0.3f,1.0f,0.0f } };
	//Model blender{ wnd.Gfx(),"Models\\Untitled.obj" };

	std::string commandLine;
};

// pitch   X
// yaw     Y
// roll    Z