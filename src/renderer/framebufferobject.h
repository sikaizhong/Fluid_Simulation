#ifndef FRAMEBUFFEROBJECT_
#define FRAMEBUFFEROBJECT_
#include<GL/glew.h>

namespace turbo {

	// comes from ogre 2.11
	// framebuffer is too complicated for me, write a simple one at first attempt;
	class FrameBufferObject {

	public:
		/** Bind FrameBufferObject
		*/
		void bind();

	private:
		GLuint fboID;
		
		int width;
		int height;



	};
}

#endif