#ifndef VERTEXBUFFER_
#define VERTEXBUFFER_
#include <GL/glew.h>


namespace FS {

	// all buffer should have a common base class. I am not familiar with them now, refactoring related files in 
	// the future;
	// lock/ unlock issues
	class VertexBuffer {
	public:
		VertexBuffer(size_t length, void*pDest);
		~VertexBuffer();
		
		void readData(size_t offset, size_t length, void* pDest);
		void bind();
		void unbind();
		inline GLuint getGLBufferId()const { return bufferID; }

	private:
		GLuint bufferID;
	};

}

#endif