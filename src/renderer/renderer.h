#ifndef RENDERER_
#define RENDERER_
#include<renderer/rendererapi.h>
#include<stdint.h>
#include<renderer/light.h>
#include<renderer/GLSLProgram.h>

namespace FS {

	class Renderer {
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);



		static void LoadFragmentShader(GLSLShader*&fs, std::string& filename);
		static void LoadVertexShader(GLSLShader*&vs, std::string& filename);
		static void CreateProgram(GLSLProgram* &program, GLSLShader*&vs, GLSLShader*&fs, std::string& vsf, std::string& fgs);
		static void LoadXYZMesh(std::string& folderName);
		static void DrawXYZMesh(int frame);

		static void linkMVP(GLSLProgram* program, glm::mat4& model, glm::mat4& view, glm::mat4& projection);


		static void useProgram(GLSLProgram*program);


		static void removeProgram();
		static void setPointSize(float val);
		static void setEdgeWidth(float val);
		static void configLight(GLSLProgram* program, Light&light);


		static RendererAPI api; // todo::renderAPI should be a wrapper class for opengl and directx

		static void BeginScene();
		static void EndScene();
		static Light light_;
	};


}


#endif 