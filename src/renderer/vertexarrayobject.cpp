#include"vertexarrayobject.h"

namespace FS {

	VertexArrayObject::VertexArrayObject() {
		glGenVertexArrays(1, &VAOID);
	}
	void VertexArrayObject::bind() {
		glBindVertexArray(VAOID);
	}

	void VertexArrayObject::unbind() {
		glBindVertexArray(0);
	}

	void VertexArrayObject::del() {
		glDeleteBuffers(1, &VAOID);
	}

	VertexArrayObject::~VertexArrayObject() {
		glDeleteBuffers(1, &VAOID);
	}

}
