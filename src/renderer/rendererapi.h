#ifndef RENDERERAPI_
#define RENDERERAPI_
#include<glm/glm.hpp>
#include<stdint.h>
#include<loglayer.h>
#include<renderer/GLSLProgram.h>
#include<renderer/GLSLShader.h>
#include<renderer/light.h>
namespace FS {

	class RendererAPI {
	public:
		static void Init()
		{
			TB_RENDER_INFO("OpenGL Info");
			TB_RENDER_INFO("Vender: {0}", glGetString(GL_VENDOR));
			TB_RENDER_INFO("Renderer: {0}", glGetString(GL_RENDERER));
			TB_RENDER_INFO("Version: {0}", glGetString(GL_VERSION));
			glEnable(GL_DEPTH_TEST);

		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			glViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		static void Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		static void LoadXYZMesh(std::string& folderName);
		static void LoadXYZMesh_sphere_mode();

		static void DrawXYZMesh(int frame);

	


		


		static void LoadFragmentShader(GLSLShader*&fs,std::string& filename);
		static void LoadVertexShader(GLSLShader*&vs,std::string& filename);
		static void LoadGeometryShader(GLSLShader*&gs, std::string& filename);
		static void LoadComputeShader(GLSLShader*&cs, std::string& filename);

		static void InitProgram(GLSLProgram*&program, GLSLShader*&vs, GLSLShader*&fs);
		static void InitProgram(GLSLProgram*&program, GLSLShader*&vs, GLSLShader*&gs, GLSLShader*&fs);
		static void InitComputeProgram(GLSLProgram*&program, GLSLShader*&cs);



		static void linkMVP(GLSLProgram* program,glm::mat4& model, glm::mat4& view, glm::mat4& projection);
		//static void linkMVP_Point(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
		//static void linkMVP_CP(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
		static void useProgram(GLSLProgram* program);


		static void removeProgram();

		static void setPointSize(float val);
		static void setEdgeWidth(float val);
		

		


	public:
		static Light light_;

		static unsigned int m_VertexBuffer, m_VertexArray,
			m_IndexBuffer, edge_IndexBuffer, m_TokenBuffer;
		static GLSLShader*vertexShader;
		static GLSLShader*fragmentShader;
		static GLSLShader* geometryShader;
		static GLSLProgram* program;


	};
};

#endif 