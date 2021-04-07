#include <TinyEngine/TinyEngine>
#include <TinyEngine/color>
#include <TinyEngine/camera>

#define GRIDSIZE 128

#include "model.h"

int main( int argc, char* args[] ) {

	Tiny::view.vsync = false;
	Tiny::window("Heightmap Render", 1200, 800);	//Open Window

	cam::near = -100.0f;
	cam::far = 100.0f;
	cam::rot = 45.0f;
	cam::roty = 45.0f;
	cam::init(10, cam::ORTHO);

	Tiny::event.handler = cam::handler;						//Event Handler
	Tiny::view.interface = [&](){ /* ... */ };		//No Interface

	setup();																					//Prepare Model Stuff

	Model mesh(_construct);														//Construct a Mesh
	mesh.shift(glm::vec3(-GRIDSIZE/2, -15.0, -GRIDSIZE/2));				//Translate Mesh
	Shader defaultShader({"shader/default.vs", "shader/default.fs"}, {"in_Position", "in_Normal"});

	Tiny::view.pipeline = [&](){											//Setup Drawing Pipeline

		Tiny::view.target(color::black);								//Target Screen

		defaultShader.use();														//Prepare Shader
		defaultShader.uniform("model", mesh.model);			//Set Model Matrix
		defaultShader.uniform("vp", cam::vp);	//View Projection Matrix
		mesh.render(GL_LINES);													//Render Model with Lines

	};

	Tiny::loop([&](){ //Autorotate Camera
		cam::pan(0.1f);
	});

	Tiny::quit();

	return 0;
}
