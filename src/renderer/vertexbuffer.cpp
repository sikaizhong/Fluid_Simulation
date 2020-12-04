#include"vertexbuffer.h"


namespace FS {


	// should be inline functions
	// This class should include
	VertexBuffer::VertexBuffer(size_t length, void*pDest) {
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ARRAY_BUFFER, length, pDest, GL_STATIC_DRAW);
	}
	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &bufferID);
	}
	void VertexBuffer::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	}
	void VertexBuffer::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


}