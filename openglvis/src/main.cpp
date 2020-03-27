/*
ZJ Wood CPE 471 Lab 3 base code
*/

#include <iostream>
#include <glad/glad.h>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"

#include "WindowManager.h"
#include "Shape.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;

float PI_APPROX = 312689.0f / 99532.0f;

#define I mat4(1)

double get_last_elapsed_time()
{
	static double lasttime = glfwGetTime();
	double actualtime =glfwGetTime();
	double difference = actualtime- lasttime;
	lasttime = actualtime;
	return difference;
}

class camera
{
public:
	glm::vec3 pos, rot;
	int w, a, s, d;
	camera()
	{
		w = a = s = d = 0;
		pos = glm::vec3(0, 0, -10);
		rot = glm::vec3(0, 0, 0);
	}
	glm::mat4 process(double frametime)
	{
		double ftime = frametime;
		float speed = 0;
		if (w == 1)
		{
			speed = 10*ftime;
		}
		else if (s == 1)
		{
			speed = -10*ftime;
		}
		float yangle=0;
		if (a == 1)
			yangle = -1*ftime;
		else if(d==1)
			yangle = 1*ftime;
		rot.y += yangle;
		glm::mat4 R = glm::rotate(glm::mat4(1), rot.y, glm::vec3(0, 1, 0));
		glm::vec4 dir = glm::vec4(0, 0, speed,1);
		dir = dir*R;
		pos += glm::vec3(dir.x, dir.y, dir.z);
		glm::mat4 T = glm::translate(glm::mat4(1), pos);
		return R*T;
	}
};

camera mycam;
#define KEY_COUNT 4


class Application : public EventCallbacks
{

public:
	int kn = 0;
	bool inputkeys[KEY_COUNT] = {false};

	int releases = 5;
	WindowManager * windowManager = nullptr;
	std::vector<float> randomBank;
	FILE* f;

	// Our shader program
	std::shared_ptr<Program> prog, shapeprog;

	// Contains vertex information for OpenGL
	GLuint VertexArrayID;

	// Data necessary to give our box to OpenGL
	GLuint VertexBufferID, VertexColorIDBox, IndexBufferIDBox, CylinderArrayID, CylinderVertexBufferId;



	Shape shape;

	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			mycam.w = 1;
		}
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		{
			mycam.w = 0;
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			mycam.s = 1;
		}
		if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		{
			mycam.s = 0;
		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			mycam.a = 1;
		}
		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
			mycam.a = 0;
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			mycam.d = 1;
		}
		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		{
			mycam.d = 0;
		}
		if (key == GLFW_KEY_N && action == GLFW_PRESS) kn = 1;
		if (key == GLFW_KEY_N && action == GLFW_RELEASE)
		{
			kn = 0;
			releases--;
		}
		/*int i;
		for (i = 0; i < KEY_COUNT; i++)
		{
			if (key == (GLFW_KEY_1 + i) && action == GLFW_PRESS)
			{
				inputkeys[i] = true;
				fprintf(f,"%ld, %d, %c\n", (long)(1000.0f * glfwGetTime()), i, 'p');
			}
			else if (key == (GLFW_KEY_1 + i) && action == GLFW_RELEASE)
			{
				inputkeys[i] = false;
				releases--;
				fprintf(f,"%ld, %d, %c\n", (long)(1000.0f * glfwGetTime()), i, 'r');
			}
		}*/
	}

	// callback for the mouse when clicked move the triangle when helper functions
	// written
	void mouseCallback(GLFWwindow *window, int button, int action, int mods)
	{
		double posX, posY;
		float newPt[2];
		if (action == GLFW_PRESS)
		{
			glfwGetCursorPos(window, &posX, &posY);
			std::cout << "Pos X " << posX <<  " Pos Y " << posY << std::endl;

		}
	}

	//if the window is resized, capture the new size and reset the viewport
	void resizeCallback(GLFWwindow *window, int in_width, int in_height)
	{
		//get the window size - may be different then pixels for retina
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

	/*Note that any gl calls must always happen after a GL state is initialized */
	void initGeom()
	{
		string resourceDirectory = "../resources";
		//try t800.obj or F18.obj ...
		shape.loadMesh(resourceDirectory + "/cube.obj");
		shape.resize();
		shape.init();

		int i;
		for (i = 0; i < 1000; i++)
		{
			randomBank.push_back((rand() % 100000) / 100000.0f);
		}
	}

	//General OGL initialization - set OGL state here
	void init(const std::string& resourceDirectory)
	{
		GLSL::checkVersion();

		 f = fopen("summerair.csv" , "r");

		// Set background color.
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		// Enable z-buffer test.
		glEnable(GL_DEPTH_TEST);
		// Enable blending/transparency
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Initialize the GLSL program.
		prog = std::make_shared<Program>();
		prog->setVerbose(true);
		prog->setShaderNames(resourceDirectory + "/shader_vertex.glsl", resourceDirectory + "/shader_fragment.glsl");
		if (!prog->init())
			{
			std::cerr << "One or more shaders failed to compile... exiting!" << std::endl;
			exit(1); //make a breakpoint here and check the output window for the error message!
			}
		prog->addUniform("P");
		prog->addUniform("V");
		prog->addUniform("M");
		prog->addAttribute("vertPos");
		prog->addAttribute("vertColor");

		// Initialize the GLSL program.
		shapeprog = std::make_shared<Program>();
		shapeprog->setVerbose(true);
		shapeprog->setShaderNames(resourceDirectory + "/shape_vertex.glsl", resourceDirectory + "/shape_fragment.glsl");
		if (!shapeprog->init())
			{
			std::cerr << "One or more shaders failed to compile... exiting!" << std::endl;
			exit(1); //make a breakpoint here and check the output window for the error message!
			}
		shapeprog->addUniform("P");
		shapeprog->addUniform("V");
		shapeprog->addUniform("M");
		shapeprog->addUniform("campos");
		shapeprog->addUniform("pow_spec");
		shapeprog->addUniform("w_spec");
		shapeprog->addUniform("w_diffuse");
		shapeprog->addUniform("lp");
		shapeprog->addUniform("color_diffuse");
		shapeprog->addUniform("color_ambient");
		shapeprog->addUniform("w_ambient");
		shapeprog->addUniform("alpha");
		shapeprog->addUniform("cubepos0");
		shapeprog->addUniform("cubepos1");
		shapeprog->addUniform("cubepos2");
		shapeprog->addUniform("cubepos3");
		shapeprog->addUniform("lit_amounts");
		shapeprog->addUniform("my_index");
		shapeprog->addAttribute("vertPos");
		shapeprog->addAttribute("vertNor");
		shapeprog->addAttribute("vertTex");
	}


	/****DRAW
	This is the most important function in your program - this is where you
	will actually issue the commands to draw any geometry you have set up to
	draw
	********/
	void render()
	{
		double frametime = get_last_elapsed_time();
		int width, height;
		glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);
		float aspect = width/(float)height;
		glViewport(0, 0, width, height);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_BLEND);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
		glm::mat4 V, M, P;
		V = glm::mat4(1);
		M = glm::mat4(1);
		P = glm::perspective((float)(3.14159 / 4.), (float)((float)width/ (float)height), 0.1f, 1000.0f); //so much type casting... GLM metods are quite funny ones
		V = mycam.process(frametime);
	
		static float w = 0.0f;
		w += frametime;

		long inmillis = 0;
		int innum = 0;
		char inc = 'x';

		if (glfwGetTime() * 1000 > inmillis)
		{
			fscanf(f, "%ld,%d,%c\n", &inmillis, &innum, &inc);
			if(inc == 'p')
				inputkeys[innum] = true;
			else if (inc == 'r')
				inputkeys[innum] = false;
			printf("innum %ld\n", inmillis);
		}

		renderThings(P, V, w);
	}

	float fmap(float x, float in_min, float in_max, float out_min, float out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	void renderCube(mat4 transform, vec3 color, float w)
	{
		float scale = w ? 0.51 : 0.5;

		mat4 myscale = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
		mat4 glowscale = myscale * glm::scale(glm::mat4(1.0f), glm::vec3(1.05f, 1.05f, 1.05f));
		mat4 bglowscale = myscale * glm::scale(glm::mat4(1.0f), glm::vec3(1.3f, 1.3f, 1.3f));
		mat4 myYrot = glm::rotate(glm::mat4(1.0f), PI_APPROX / 4.0f, glm::vec3(0, 1, 0));
		mat4 myXrot = glm::rotate(glm::mat4(1.0f), PI_APPROX / 8.0f, glm::vec3(1, 0, 0));

		mat4 M = transform * myXrot * myYrot * myscale;
		glUniformMatrix4fv(shapeprog->getUniform("M"), 1, GL_FALSE, &M[0][0]);
		glUniform3f(shapeprog->getUniform("color_ambient"), color.r, color.g, color.b);
		glUniform3f(shapeprog->getUniform("color_diffuse"), color.r, color.g, color.b);
		glUniform1f(shapeprog->getUniform("w_ambient"), 0.05);
		glUniform1f(shapeprog->getUniform("w_diffuse"), fmap(w, 0, 1, 0.05, 1));
		glUniform1f(shapeprog->getUniform("alpha"), 1);
		shape.draw(shapeprog);

		if (w > 0.9)
		{
			mat4 M = transform * myXrot * myYrot * glowscale;
			glUniformMatrix4fv(shapeprog->getUniform("M"), 1, GL_FALSE, &M[0][0]);
			glUniform3f(shapeprog->getUniform("color_ambient"), color.r, color.g, color.b);
			glUniform3f(shapeprog->getUniform("color_diffuse"), color.r, color.g, color.b);
			glUniform1f(shapeprog->getUniform("w_diffuse"), 0);
			glUniform1f(shapeprog->getUniform("w_ambient"), 1);
			glUniform1f(shapeprog->getUniform("alpha"), 0.1);
			shape.draw(shapeprog);

			
		}
	}

	void renderFloor(mat4 transform, vec3 color)
	{
		mat4 myscale = glm::scale(glm::mat4(1.0f), glm::vec3(100, 0.1, 100));
		mat4 myYrot = glm::rotate(glm::mat4(1.0f), PI_APPROX / 4.0f, glm::vec3(0, 1, 0));
		mat4 myXrot = glm::rotate(glm::mat4(1.0f),(float) ((PI_APPROX / 8.0f) ), glm::vec3(1, 0, 0));

		mat4 M = transform * myXrot * myYrot * myscale;
		glUniformMatrix4fv(shapeprog->getUniform("M"), 1, GL_FALSE, &M[0][0]);
		glUniform3f(shapeprog->getUniform("color_ambient"), (3 + color.x) * 0.25f, (3 + color.y) * 0.25f, (3 + color.z) * 0.25f);
		glUniform3f(shapeprog->getUniform("color_diffuse"), color.x, color.y, color.z);
		glUniform1f(shapeprog->getUniform("w_ambient"), 0.1f);
		glUniform1f(shapeprog->getUniform("w_diffuse"), 0.05);
		glUniform1f(shapeprog->getUniform("alpha"), 1);
		shape.draw(shapeprog);
	}

	void renderWalls(vec3 color)
	{
		mat4 myscale = glm::scale(glm::mat4(1.0f), glm::vec3(100, 0.1, 100));
		mat4 myYrot = glm::rotate(glm::mat4(1.0f), PI_APPROX / 4.0f, glm::vec3(0, 1, 0));
		mat4 negmyYrot = glm::rotate(glm::mat4(1.0f), -PI_APPROX / 4.0f, glm::vec3(0, 1, 0));
		mat4 myXrot = glm::rotate(glm::mat4(1.0f), (float)((PI_APPROX / 8.0f)), glm::vec3(1, 0, 0));
		mat4 ltrans = translate(mat4(1), vec3(-50, 0, -40));
		mat4 righttrans = translate(mat4(1), vec3(50, 0, -40));
		mat4 prexrot = glm::rotate(glm::mat4(1.0f), (float)((PI_APPROX / 2.0f)), glm::vec3(1, 0, 0));

		mat4 M;
		glUniform3f(shapeprog->getUniform("color_ambient"), (3 + color.x) * 0.25f, (3 + color.y) * 0.25f, (3 + color.z) * 0.25f);
		glUniform3f(shapeprog->getUniform("color_diffuse"), color.x, color.y, color.z);
		glUniform1f(shapeprog->getUniform("w_ambient"), 0.1f);
		glUniform1f(shapeprog->getUniform("w_diffuse"), 0.05);
		glUniform1f(shapeprog->getUniform("alpha"), 1);

		M = ltrans * myXrot * myYrot * prexrot * myscale;
		glUniformMatrix4fv(shapeprog->getUniform("M"), 1, GL_FALSE, &M[0][0]);
		shape.draw(shapeprog);

		M = righttrans * myXrot * negmyYrot * prexrot * myscale;
		glUniformMatrix4fv(shapeprog->getUniform("M"), 1, GL_FALSE, &M[0][0]);
		shape.draw(shapeprog);
	}


	void renderThings(mat4 P, mat4 V, float w)
	{
		std::vector<vec3> cubeposes = std::vector<vec3>();
		
		cubeposes.push_back(vec3(-2, 1, -1));
		cubeposes.push_back(vec3(0, 2, -2));
		cubeposes.push_back(vec3(0, 0, 0));
		cubeposes.push_back(vec3(2, 1, -1));
		
		std::vector<float> flatcubeposes = std::vector<float>();
		int i;
		for (i = 0; i < cubeposes.size(); i++)
		{
			flatcubeposes.push_back(cubeposes.at(i).x);
			flatcubeposes.push_back(cubeposes.at(i).y);
			flatcubeposes.push_back(cubeposes.at(i).z);
		}

		float t = glfwGetTime();
		for (int i = 0; i < flatcubeposes.size(); i++)
		{
			flatcubeposes.data()[i] += 
				sin(t * (fmap(randomBank.at((i * 3) + 0), 0, 1, 0.5, 1.5)) + 
					fmap(randomBank.at((i * 3) + 1), 0, 1, 0, 1))
				* fmap(randomBank.at((i * 3) + 2), 0, 1, 0.01, 0.15);
		}

		cubeposes.clear();
		for (int i = 0; i < flatcubeposes.size() / 3; i++)
		{
			cubeposes.push_back(vec3(
				flatcubeposes.at((i* 3) + 0), 
				flatcubeposes.at((i * 3) + 1),
				flatcubeposes.at((i * 3) + 2)));
		}

		bindShapeProg(P, V, cubeposes);

		static float inten[4];

		std::vector<vec3> colors = std::vector<vec3>();
		colors.push_back(vec3(1, 1, 1));
		colors.push_back(vec3(1, 0, 0));
		colors.push_back(vec3(1, 0.5, 0));
		colors.push_back(vec3(1, 1, 0));
		colors.push_back(vec3(0, 1, 0));
		colors.push_back(vec3(0, 1, 1));
		colors.push_back(vec3(0, 0.3, 1));
		colors.push_back(vec3(0.6, 0, 1));
		colors.push_back(vec3(1, 0, 1));
		
		static int colorindex = 0;

		if (releases < 0)
		{
			releases += 20;
			colorindex+= 1;
			if (colorindex >= colors.size())
				colorindex = 0;
		}

		for (i = 0; i < cubeposes.size() && i < KEY_COUNT; i++)
		{
			inputkeys[i] ? inten[i] = 1 : inten[i] *= 0.9;
		}

		glUniform4fv(shapeprog->getUniform("lit_amounts"), 1, &inten[0]);

		glUniform1i(shapeprog->getUniform("my_index"), -1);
		renderWalls(colors.at(colorindex));
		renderFloor(translate(mat4(1), vec3(0, -25, -10)), colors.at(colorindex));
		for (i = 0; i < cubeposes.size() && i < KEY_COUNT; i++)
		{
			glUniform1i(shapeprog->getUniform("my_index"), i);
			renderCube(translate(mat4(1), cubeposes.at(i)), colors.at(colorindex), inten[i]);
		}

		unbindShapeProg();
	}

	void bindShapeProg(mat4 P, mat4 V, std::vector<vec3> &cubeposes)
	{
		shapeprog->bind();
		mat4 Shead = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
		mat4 Thead = glm::translate(glm::mat4(1.0f), glm::vec3(0, 2, 0));

		glUniformMatrix4fv(shapeprog->getUniform("P"), 1, GL_FALSE, &P[0][0]);
		glUniformMatrix4fv(shapeprog->getUniform("V"), 1, GL_FALSE, &V[0][0]);

		glUniform3fv(shapeprog->getUniform("campos"), 1, &mycam.pos[0]);
		glUniform3f(shapeprog->getUniform("cubepos0"), cubeposes.at(0).x, cubeposes.at(0).y, cubeposes.at(0).z);
		glUniform3f(shapeprog->getUniform("cubepos1"), cubeposes.at(1).x, cubeposes.at(1).y, cubeposes.at(1).z);
		glUniform3f(shapeprog->getUniform("cubepos2"), cubeposes.at(2).x, cubeposes.at(2).y, cubeposes.at(2).z);
		glUniform3f(shapeprog->getUniform("cubepos3"), cubeposes.at(3).x, cubeposes.at(3).y, cubeposes.at(3).z );
		glUniform1f(shapeprog->getUniform("w_ambient"), 0.05);
		glUniform3f(shapeprog->getUniform("lp"), -3, -1, -6);
		glUniform1f(shapeprog->getUniform("pow_spec"), 20);
		glUniform1f(shapeprog->getUniform("w_spec"), 1);

	}

	void unbindShapeProg()
	{
		shapeprog->unbind();
	}

	

};


//******************************************************************************************
int main(int argc, char **argv)
{
	std::string resourceDir = "../resources"; // Where the resources are loaded from
	if (argc >= 2)
	{
		resourceDir = argv[1];
	}

	Application *application = new Application();

	/* your main will always include a similar set up to establish your window
		and GL context, etc. */
	WindowManager * windowManager = new WindowManager();
	windowManager->init(1920, 1080);
	windowManager->setEventCallbacks(application);
	application->windowManager = windowManager;

	/* This is the code that will likely change program to program as you
		may need to initialize or set up different data and state */
	// Initialize scene.
	application->init(resourceDir);
	application->initGeom();

	// Loop until the user closes the window.
	while(! glfwWindowShouldClose(windowManager->getHandle()))
	{
		// Render scene.
		application->render();

		// Swap front and back buffers.
		glfwSwapBuffers(windowManager->getHandle());
		// Poll for and process events.
		glfwPollEvents();
	}

	// Quit program.
	windowManager->shutdown();
	return 0;
}
