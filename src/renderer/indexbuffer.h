#ifndef INDEXBUFFER_
#define INDEXBUFFER_
#include <GL/glew.h>

namespace FS {

	/// WILL vertex array obj controls index buffer too?
	class IndexBufferObject {

	public:
		IndexBufferObject(size_t length, void*pDest);
		~IndexBufferObject();

		void readData(size_t offset, size_t length, void* pDest);
		void bind();
		void unbind();
		inline GLuint getGLBufferId()const { return bufferID;}

	private:
		GLuint bufferID;

	};


}

#endif