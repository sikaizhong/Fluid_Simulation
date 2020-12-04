#include <GL/glew.h>
#include<glfw/glfw3.h>
#include <iostream>
#include<renderer/renderer.h>
#include<renderer/camera.h>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float m_xRot = 0;
float m_yRot = 0;
float m_zRot = 0;


FS::Renderer renderer;
int main()
{
	FS::Log::Init();
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	GLenum ret = glewInit();
	if (ret != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(ret));
	}
	
	glPointSize(10.0);
	renderer.Init();
	FS::Renderer::CreateProgram(renderer.api.program,
		renderer.api.vertexShader,
		renderer.api.fragmentShader,
		std::string("sphere.vert"),
		std::string("sphere.frag"));
	renderer.LoadXYZMesh(std::string("hybrid_liquid_sim_output"));
	
	// render loop
	// -----------
	int frame = 0;
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		//Sleep(2.0);
		frame++;
		if (frame > 100)
			frame = 0;
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		FS::Renderer::useProgram(renderer.api.program);
		glm::mat4 model = glm::translate(glm::mat4(1.0), -glm::vec3(0.5, 0.5, 0.5));
		model = glm::scale(glm::mat4(1.0f), glm::vec3(1.5,1.5,1.5))*model;

		glm::mat4 rot= glm::rotate(glm::mat4(1.0), (m_xRot / 16.0f), glm::vec3(1, 0, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
		rot = glm::rotate(rot, m_yRot / 16.0f, glm::vec3(0, 1, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
		rot = glm::rotate(rot, m_zRot / 16.0f, glm::vec3(0, 0, 1)); // where x, y, z is axis of rotation (e.g. 0 1 0)
		model = rot * model;


		//glm::mat4 view = clippingPlane.clippingPlaneTrackBall.camera.getViewMatrix();//glm::lookAt(cameraPos, (cameraPos + cameraFront), cameraUp);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		FS::Renderer::linkMVP(renderer.api.program, model, view, projection);
		FS::Renderer::DrawXYZMesh(frame);


		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		m_xRot -= 0.2;
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
	{
		m_yRot -= 0.2;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		m_zRot -= 0.2;
	}

	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	//camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}