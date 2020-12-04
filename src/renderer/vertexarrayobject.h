#ifndef VERTEXARRAYOBJECT_
#define VERTEXARRAYOBJECT_
#include <GL/glew.h>
namespace FS {

	class VertexArrayObject {
	public:

		VertexArrayObject();
		~VertexArrayObject();
		/// Bind a VAO;
		void bind(void);
		void unbind(void);
		void del();

		void addBuffer();// add vertexbuffer;
	

	public:
		/// OpenGL id for the vertex array object
		GLuint VAOID;

	};





}


#endif