#include "GLSLShader.h"
#include"GLSLProgram.h"
#include<fstream>
#include<iostream>
#include<sstream>
namespace FS {

	GLSLShader::GLSLShader(std::string filePath, GpuProgramType type):filePath(filePath),type(type),
		GLShaderHandle(0), GLProgramHandle(0){
		compile();
	}

	GLSLShader::~GLSLShader() {// no memory allocation
		glDeleteShader(GLShaderHandle);

	}

	std::string GLSLShader::getName() {
		// get the name form filePath;
		return filePath;
	}

	void GLSLShader::bind() {

	}


	void GLSLShader::unbind() {

	}
	bool GLSLShader::compile() {
		GLenum GLShaderType = getGLShaderType(type);
		GLShaderHandle = glCreateShader(GLShaderType);
		submitSource(); // init source to create shader;
		const char* source = shaderSource.c_str();
		glShaderSource(GLShaderHandle, 1, &source, NULL);
		glCompileShader(GLShaderHandle);
		int succ;
		char infoLog[512];
		glGetShaderiv(GLShaderHandle, GL_COMPILE_STATUS, &succ);
		if (!succ) {
			glGetShaderInfoLog(GLShaderHandle, 512, NULL, infoLog);
			// use map?
			std::string shaderType;
			switch (GLShaderType)
			{
			case GL_VERTEX_SHADER:
				shaderType = "VERTEX_SHADER";
				break;

			case GL_TESS_EVALUATION_SHADER:
				shaderType = "TESS_EVALUATION_SHADER";
				break;
			case GL_TESS_CONTROL_SHADER:
				shaderType = "TESS_CONTROL_SHADER";
				break;
			case GL_GEOMETRY_SHADER:
				shaderType = "GEOMETRY_SHADER";
				break;
			case GL_FRAGMENT_SHADER:
				shaderType = "FRAGMENT_SHADER";
				break;

			case GL_COMPUTE_SHADER:
				shaderType = "COMPUTE_SHADER";
				break;
				//TODO error handle;
			
			}
			std::cout << "ERROR::SHADER::"<< shaderType<<"::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		return false;
	}

	void  GLSLShader::setGLShaderHandle() { GLProgramHandle = program->programID; };
	GLenum GLSLShader::getGLShaderType(GpuProgramType programType)const {
		switch (programType)
		{
		case GpuProgramType::GPT_VERTEX_PROGRAM:
			return GL_VERTEX_SHADER;
		case GpuProgramType::GPT_HULL_PROGRAM:
			return GL_TESS_CONTROL_SHADER;
		case GpuProgramType::GPT_DOMAIN_PROGRAM:
			return GL_TESS_EVALUATION_SHADER;
		case GpuProgramType::GPT_FRAGMENT_PROGRAM:
			return GL_FRAGMENT_SHADER;
		case GpuProgramType::GPT_COMPUTE_PROGRAM:
			return GL_COMPUTE_SHADER;
		case GpuProgramType::GPT_GEOMETRY_PROGRAM:
			return GL_GEOMETRY_SHADER;

		}

		//TODO add warning or error
		return 0;
	}

	// potential error;

	GLuint GLSLShader::getGLProgramHandle()const {
		if (program == nullptr)
			return 0;
		else {
			GLProgramHandle = program->programID;
		}
		//if (GLProgramHandle == 0) {
		//	GLProgramHandle = glCreateProgram();
		//}

		return GLProgramHandle;
	}

	GLuint GLSLShader::getGLShaderHandle()const {
		return GLShaderHandle;
	}


	void GLSLShader::submitSource() {
		std::ifstream shaderFile;
		// ensure ifstream objects can throw exceptions:
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			
			shaderFile.open(filePath);
			std::stringstream ShaderStream;
			// read file’s buffer contents into streams
			ShaderStream << shaderFile.rdbuf();
			
			// close file handlers
			shaderFile.close();
			
			// convert stream into string
			shaderSource = ShaderStream.str();
			
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
	}

}
