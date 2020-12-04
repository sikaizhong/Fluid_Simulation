#ifndef GLSLSHADER_
#define GLSLSHADER_

#include <GL/glew.h>
#include<glm/ext.hpp>


#include<string>
#include<iostream>
#include<unordered_map>

//////////////MATERIAL///////////////////////
namespace FS {
	class GLSLProgram;
	enum class GpuProgramType {
		GPT_VERTEX_PROGRAM = 0, // vertex shader
		GPT_FRAGMENT_PROGRAM,   // fragment shader
		GPT_GEOMETRY_PROGRAM,   // geometry shader
		GPT_DOMAIN_PROGRAM,
		GPT_HULL_PROGRAM,
		GPT_COMPUTE_PROGRAM     // compute shader;
	};
	/**
	\This a wrapper class for GLSL Shader(first attempt)
	\ It only implements fun related with shader itself, program should not include inside this class;
	*/
	class GLSLShader {
		// It should contain a enum class for different shaders
	public:

		friend GLSLProgram;
		GLSLShader(std::string filePath, GpuProgramType type); // default ctr is deleted;
		~GLSLShader();
		std::string getName();
		/// Bind the shader in OpenGL
		void bind();
		/// Unbind the shader in OpenGL
		void unbind();
		bool compile();
		void submitSource();
		GLenum getGLShaderType(GpuProgramType programType)const;
		GLuint getGLProgramHandle()const;
		GLuint getGLShaderHandle()const;
		void  setProgramHandle(GLuint handle) { GLProgramHandle = handle; }

		//Uniforms are another way to pass data from our application on the CPU to the shaders on the GPU;
		//Uniforms are global
		//uniforms will keep their values until they’re either reset or updated in CPU
		// Every shader object is responsible for the uniforms which is first appeared in itself;

		void setBool(const std::string&name, bool val) const {
			//glUniform Specify the value of a uniform variable for the current program object;
			// glGetUniformLocation — Returns the location of a uniform variable in SHADER (shader program);
			glUniform1i(getUniformLocation(name), val);
		}

		void setUInt(const std::string&name, unsigned int val) const {
			//glUniform Specify the value of a uniform variable for the current program object;
			// glGetUniformLocation — Returns the location of a uniform variable in SHADER (shader program);
			glUniform1ui(getUniformLocation(name), val);
		}

		void setFloat(const std::string&name, GLfloat val) const {
			//glUniform Specify the value of a uniform variable for the current program object;
			// glGetUniformLocation — Returns the location of a uniform variable in SHADER (shader program);
			glUniform1f(getUniformLocation(name), val);
		}

		void setMat4(const std::string&name, glm::mat4& val)const {
			glUniformMatrix4fv(getUniformLocation(name), 1/* because it is an array*/, GL_FALSE, &val[0][0]);
		}

		void setVec4(const std::string&name, const glm::vec4& val)const {
			glUniform4fv(getUniformLocation(name), 1, &val[0]);
		}

		void setVec3(const std::string&name, const glm::vec3& val)const {
			glUniform3fv(getUniformLocation(name), 1, &val[0]);
		}
		GLuint getUniformLocation(const std::string & name) const {

			if (uniformLocationCache.find(name) != uniformLocationCache.end())
				return uniformLocationCache[name];
			GLuint location = glGetUniformLocation(GLProgramHandle, name.c_str());
			// glGetUniformLocation returns -1 if name does not correspond to an active uniform variable
			if (location == -1) std::cout << "Warning: uniform " << name << " does not exist in"<<filePath << std::endl;
			else
				uniformLocationCache[name] = location;
			return location;
		}
	protected:
		void   setGLShaderHandle();

		GLuint GLShaderHandle; // handler returned by glCreateShader;
	    mutable GLuint GLProgramHandle; // GL handle for program object the shader is bound to;
		GLSLProgram* program;// the program which the shader program is attached;
		GpuProgramType type;
		std::string shaderSource;
		std::string filePath;
	private:
		// avoid repeating call getUniformLocal, which needs CPU-GPU communication;
		mutable std::unordered_map<std::string /*key*/, int  /*value*/>uniformLocationCache;
	};

};


#endif