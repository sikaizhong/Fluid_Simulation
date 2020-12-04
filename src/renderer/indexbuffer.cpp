#include"indexbuffer.h"


namespace FS {


	// should be inline functions
	// This class should include
	IndexBufferObject::IndexBufferObject(size_t length, void*pDest) {
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, pDest, GL_STATIC_DRAW);
	}
	IndexBufferObject::~IndexBufferObject() {
		glDeleteBuffers(1, &bufferID);
	}
	void IndexBufferObject::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	}
	void IndexBufferObject::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


}