#include"GLSLProgram.h"


namespace FS {


	GLSLProgram::GLSLProgram() {
		validProgram = false; 
		vertexShader = nullptr;
		vertexShader=nullptr;
		/// Linked hull (control) shader.
		hullShader=nullptr;
		/// Linked domain (evaluation) shader.
		domainShader=nullptr;
		/// Linked geometry shader.
	    geometryShader=nullptr;
		/// Linked fragment shader.
		fragmentShader=nullptr;
		/// Linked compute shader.
		computeShader=nullptr;
	}


	/**
	\if the program is not created, call glCreateProgram at first;
	\check whether the input type conflicts with the existing one;
	*/
	bool GLSLProgram::attachShader(GLSLShader* shader, GpuProgramType type) {

		// will glDetachShader destroys the program; suppose not;
		//glDetachShader detaches the shader object specified by shader from the program object specified by program.
		//This command can be used to UNDO the effect of the command glAttachShader.
		// check whether it is a valid program
		if (!validProgram) {
			programID = glCreateProgram();
			validProgram = true;

		}
		//bool duplicate = ShaderInputAfterSameTypeOfShader(type);
		switch (type)
		{
		case FS::GpuProgramType::GPT_VERTEX_PROGRAM:
			if (vertexShader != nullptr)
				glDetachShader(programID, vertexShader->getGLShaderHandle());
			vertexShader = shader;

			break;
		case FS::GpuProgramType::GPT_FRAGMENT_PROGRAM:
			if (fragmentShader != nullptr)
				glDetachShader(programID, fragmentShader->getGLShaderHandle());
			fragmentShader = shader;

			break;
		case FS::GpuProgramType::GPT_GEOMETRY_PROGRAM:
			if (geometryShader != nullptr)
				glDetachShader(programID, geometryShader->getGLShaderHandle());
			geometryShader = shader;

			break;
		case FS::GpuProgramType::GPT_DOMAIN_PROGRAM:
			if (domainShader != nullptr)
				glDetachShader(programID, domainShader->getGLShaderHandle());
			domainShader = shader;
			break;
		case FS::GpuProgramType::GPT_HULL_PROGRAM:
			if (hullShader != nullptr)
				glDetachShader(programID, hullShader->getGLShaderHandle());
			hullShader = shader;
			break;
		case FS::GpuProgramType::GPT_COMPUTE_PROGRAM:
			if (computeShader != nullptr)
				glDetachShader(programID, computeShader->getGLShaderHandle());

			computeShader = shader;
			break;
			// TODO exception handle
		}
		glAttachShader(programID, shader->getGLShaderHandle());
		shader->setProgramHandle(programID);
		return true;
	}

	bool GLSLProgram::conflictShader(GpuProgramType type)
	{
		switch (type)
		{
		case FS::GpuProgramType::GPT_VERTEX_PROGRAM:
			if (vertexShader != nullptr) return true;
			break;
		case FS::GpuProgramType::GPT_FRAGMENT_PROGRAM:
			if (fragmentShader != nullptr) return true;
			break;
		case FS::GpuProgramType::GPT_GEOMETRY_PROGRAM:
			if (geometryShader != nullptr) return true;
			break;
		case FS::GpuProgramType::GPT_DOMAIN_PROGRAM:
			if (domainShader != nullptr) return true;
			break;
		case FS::GpuProgramType::GPT_HULL_PROGRAM:
			if (hullShader != nullptr) return true;
			break;
		case FS::GpuProgramType::GPT_COMPUTE_PROGRAM:
			if (computeShader != nullptr) return true;
			break;
		default:
			return false;
		}
	}

	

	void GLSLProgram::deleteProgram() {
		glDeleteProgram(programID);
	}

	//used to debug 
	std::string  GLSLProgram::getCombinedName() {
		std::string name;
		if (vertexShader != nullptr) {
			name += "Vertex Shader: ";
			name += vertexShader->getName();
			name += "\n";
		}
		if (hullShader != nullptr) {
			name += "Tessllation Control Shader: ";
			name += hullShader->getName();
			name += "\n";
		}

		if (domainShader != nullptr) {
			name += "Tessellation Evaluation Shader: ";
			name += domainShader->getName();
		}

		if (geometryShader != nullptr) {
			name += "Geometry Shader: ";
			name += geometryShader->getName();
			name += "\n";
		}

		if (fragmentShader)
		{
			name += "Fragment Shader: ";
			name += fragmentShader->getName();
			name += "\n";
		}
		if (computeShader)
		{
			name += "Compute Shader: ";
			name += computeShader->getName();
			name += "\n";
		}

		return name;


	}


	GLSLProgram::~GLSLProgram() {
		// destructor is not responsible for destroying the shader memory;

		//If a program object is in use as part of current rendering state,it will be flagged for deletion, 
		//but it will not be deleted until it is no longer part of current state for any rendering context.
		//If a program object to be deleted has shader objects attached to it, 
		//those shader objects will be automatically detached but not deleted 
		//unless they have already been flagged for deletion by a previous call to glDeleteShader.
		//A value of 0 for program will be silently ignored.



	}


}
