#ifndef LIGHT_
#define LIGHT_
#include<glm/glm.hpp>
//#include<renderer/customized_trackball.h>
namespace FS {
	class Light {
	public:
		Light() :pos(glm::normalize(glm::vec3(1.0, 1.0, 1.0))),
			color(glm::vec3(1.0f, 1.0f, 1.0f)){
			pos[0] = pos[1] = pos[2] = pos[0] * 2;
			turn_on = true;
			//lightTrackBall = new CustomizedTrackBall(1.0f);
		}///glm::normalize(glm::vec3(1.0, 1.0, 1.0))
		void updateLight();
	public:
		bool turn_on;
		glm::vec3 pos;
		glm::vec3 color;
		//CustomizedTrackBall* lightTrackBall;

	};



}


#endif