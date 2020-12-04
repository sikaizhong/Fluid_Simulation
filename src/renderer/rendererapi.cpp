#include <GL/glew.h>
#include<renderer/rendererapi.h>
#include<filesystem>
#include<fstream>
#include<renderer/sphere.h>
namespace FS {
#define magic_num 534361
#define sphere_vn 244
#define sphere_fn 484
	std::vector<float> data;

	unsigned int RendererAPI::m_VertexBuffer;
	unsigned int RendererAPI::m_VertexArray;
	unsigned int RendererAPI::m_IndexBuffer;


	GLSLShader*RendererAPI::vertexShader;
	GLSLShader*RendererAPI::fragmentShader;
	GLSLProgram*RendererAPI::program;



	//light
	Light RendererAPI::light_;





	unsigned int RendererAPI::edge_IndexBuffer;


	void RendererAPI::LoadFragmentShader(GLSLShader*&fs, std::string& filename) {
		fs = new GLSLShader(filename, GpuProgramType::GPT_FRAGMENT_PROGRAM);
	}
	void RendererAPI::LoadVertexShader(GLSLShader*&vs, std::string& filename) {
		vs = new GLSLShader(filename, GpuProgramType::GPT_VERTEX_PROGRAM);

	}

	void RendererAPI::LoadComputeShader(GLSLShader*&cs, std::string& filename) {
		cs = new GLSLShader(filename, GpuProgramType::GPT_COMPUTE_PROGRAM);

	}

	void RendererAPI::LoadGeometryShader(GLSLShader*&gs, std::string& filename) {
		gs = new GLSLShader(filename, GpuProgramType::GPT_GEOMETRY_PROGRAM);

	}


	void RendererAPI::InitProgram(GLSLProgram*&program, GLSLShader*&vs, GLSLShader*&fs) {
		program = new GLSLProgram();
		program->attachShader(vs, GpuProgramType::GPT_VERTEX_PROGRAM);
		program->attachShader(fs, GpuProgramType::GPT_FRAGMENT_PROGRAM);
		program->linkProgram();
	}


	void RendererAPI::InitProgram(GLSLProgram*&program, GLSLShader*&vs, GLSLShader*&gs, GLSLShader*&fs) {
		program = new GLSLProgram();
		program->attachShader(vs, GpuProgramType::GPT_VERTEX_PROGRAM);
		program->attachShader(gs, GpuProgramType::GPT_GEOMETRY_PROGRAM);
		program->attachShader(fs, GpuProgramType::GPT_FRAGMENT_PROGRAM);
		program->linkProgram();
	}

	void RendererAPI::linkMVP(GLSLProgram* program, glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
		program->vertexShader->setMat4("model", model);
		program->vertexShader->setMat4("view", view);
		program->vertexShader->setMat4("projection", projection);
	}

	void RendererAPI::useProgram(GLSLProgram*program) {
		program->useProgram();
	}

	void RendererAPI::removeProgram() {
		glUseProgram(0);
	}

	void RendererAPI::LoadXYZMesh(std::string& folderName) {
		float val = 0;
		std::string path = folderName;
		for (const auto & entry : std::filesystem::directory_iterator(path)) {
			std::ifstream in(entry.path());
			for (int i = 0; i < magic_num * 3; i++) {
				in >> val;
				data.push_back(val);
			}
			TB_RENDER_INFO("loading {}", entry.path());



		}

		//LoadXYZMesh_sphere_mode();


		if (glIsVertexArray(m_VertexArray))
			glDeleteVertexArrays(1, &m_VertexArray);

		glDeleteBuffers(1, &m_VertexBuffer); // no side effect;
		glDeleteBuffers(1, &m_IndexBuffer);


		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);


		glEnableVertexAttribArray(0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), data.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glBindVertexArray(0);




	}

	void RendererAPI::DrawXYZMesh(int frame) {
		
		glEnable(GL_POINT_SMOOTH);
		//glLineWidth(10);
		glBindVertexArray(m_VertexArray);
		glDrawArrays(GL_POINTS, magic_num*frame, magic_num);
		//glDrawElements(GL_TRIANGLES, magic_num*sphere_fn*3, GL_UNSIGNED_INT, 
		//	(void*)(magic_num*sphere_fn * 3*frame * sizeof(GLuint)));
		glBindVertexArray(0);
		glDisable(GL_POINT_SMOOTH);
		//glEnable(GL_DEPTH_TEST);
		//glDisable(GL_POLYGON_OFFSET_POINT);
	}


	void RendererAPI::LoadXYZMesh_sphere_mode() {

		float scale = 0.005;
		unsigned int Vsize = sphere_vn * magic_num * 3;
		float *vertex = new float[Vsize];
		for (int i = 0; i < magic_num; i++) {
			for (int j = 0; j < sphere_vn; j++) {
				vertex[i*sphere_vn * 3 + 3 * j] = data[3 * i] + sphere_v[3 * j] * scale;
				vertex[i*sphere_vn * 3 + 3 * j + 1] = data[3 * i + 1] + sphere_v[3 * j + 1] * scale;
				vertex[i*sphere_vn * 3 + 3 * j + 2] = data[3 * i + 2] + sphere_v[3 * j + 2] * scale;
			}
		}

			unsigned int FSize = sphere_fn * 3 * magic_num;
			unsigned int* face = new unsigned int[FSize];

			for (int i = 0; i < magic_num; i++) {
				for (int j = 0; j < sphere_fn; j++) {
					face[i*sphere_fn * 3 + 3 * j] = sphere_f[3 * j] + sphere_fn * i;
					face[i*sphere_fn * 3 + 3 * j + 1] = sphere_f[3 * j + 1] + sphere_fn * i;
					face[i*sphere_fn * 3 + 3 * j + 2] = sphere_f[3 * j + 2] + sphere_fn * i;
				}
			}
			TB_RENDER_INFO("DATA Prepared");

			if (glIsVertexArray(m_VertexArray))
				glDeleteVertexArrays(1, &m_VertexArray);

			glDeleteBuffers(1, &m_VertexBuffer); // no side effect;
			glDeleteBuffers(1, &m_IndexBuffer);

			glGenVertexArrays(1, &m_VertexArray);
			glBindVertexArray(m_VertexArray);

			glGenBuffers(1, &m_VertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*Vsize, vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			glEnableVertexAttribArray(0);

			glGenBuffers(1, &m_IndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*FSize, face, GL_STATIC_DRAW);
			glBindVertexArray(0);

			TB_RENDER_INFO("Buffer Prepared");

		}
	};


