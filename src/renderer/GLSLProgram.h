#ifndef GLSLPROGRAM_
#define GLSLPROGRAM_
#include"GLSLShader.h"

namespace FS {
	/**
	\This class control what kind of shader program should be created.
	\it can switch among differt shaders;
	*/

	class GLSLProgram {
		
	public:
		GLSLProgram();
		~GLSLProgram();
		GLSLProgram(const GLSLProgram&) = delete;
		GLSLProgram& operator=(const GLSLProgram&) = delete;
		bool attachShader(GLSLShader* shader, GpuProgramType type);
		bool conflictShader(GpuProgramType type);

	    GLSLShader* getVertexShader() const { return vertexShader; }
		GLSLShader* getHullShader() const { return hullShader; }
		GLSLShader* getDomainShader() const { return domainShader; }
		GLSLShader* getGeometryShader() const { return geometryShader; }
		GLSLShader* getFragmentShader() const { return fragmentShader; }
		GLSLShader* getComputeShader() const { return computeShader; }

		bool isUsingShader(GLSLShader* shader) const {
			return vertexShader == shader ||
				geometryShader == shader ||
				fragmentShader == shader ||
				hullShader == shader ||
				domainShader == shader ||
				computeShader == shader;

		}

	public:
		std::string getCombinedName();

		bool isValid()const { return validProgram; } // if glCreateProgram is not called, this is an invalid program;
		inline void useProgram() { glUseProgram(programID); }
		inline void linkProgram() { glLinkProgram(programID); }
		void deleteProgram();
	public:
		bool validProgram;
		GLuint programID;
		GLSLShader* vertexShader;
		/// Linked hull (control) shader.
		GLSLShader* hullShader;
		/// Linked domain (evaluation) shader.
		GLSLShader* domainShader;
		/// Linked geometry shader.
		GLSLShader* geometryShader;
		/// Linked fragment shader.
		GLSLShader* fragmentShader;
		/// Linked compute shader.
		GLSLShader* computeShader;

	};

}

#endif