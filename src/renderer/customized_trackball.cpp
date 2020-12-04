#include<renderer/customized_trackball.h>
#include<glm/gtx/norm.hpp>
#include<iostream>
namespace FS {
	//  Rewrite this fun for efficiency; 
	glm::vec3 CustomizedTrackBall::projectionToSphere(float x, float y) const {

		static const float sqrt2 = sqrtf(2.f);
		glm::vec3 res;
		float d = sqrtf(x*x + y * y);// no sqrttf?
		if (d < (radius*sqrt2 / 2.f)) { /*Inside sphere*/
			 // The factor "sqrt2/2.f" make a smooth changeover from sphere to hyperbola. If we leave
		// factor 1/sqrt(2) away, the trackball would bounce at the changeover.
			res.z = sqrtf(radius*radius - d * d);
		}
		else { /* On hyperbola*/

			float t = radius / sqrt2;
			res.z = t * t / d;

		}

		res.x = x, res.y = y;
		return glm::normalize(res);
	}

	glm::vec3 CustomizedTrackBall::mapNormalizedMousePosToTrackball(const float& mouse_x, const float & mouse_y, const float& r) {
		// set x and y to lie in interval [-r, r]
		const glm::vec2 centerOffset = glm::vec2(2.f * mouse_x - 1.f, 2.f * (1.f - mouse_y) - 1.f);

		//std::cout << "inside trackball" << centerOffset.x << " " << centerOffset.y << std::endl;
		const float norm = glm::length2(centerOffset);
		float z = 0;
		// Mapping according to Holroyds trackball
		// Piece-wise sphere + hyperbolic sheet
		if (norm <= r * r / (2.0f)) {  // Spherical Region
			z = r * r - norm;
			z = z > 0.0f ? sqrtf(z) : 0.0f;
		}
		else {  // Hyperbolic Region - for smooth z values
			z = ((r * r) / (2.0f * sqrtf(norm)));
		}
		return glm::normalize(glm::vec3(centerOffset.x, centerOffset.y, z));
	}

	//CustomizedTrackBall::CustomizedTrackBall(CustomizedTrackBall&ls) {
		//camera = new PerspectiveCamera();
		//curCamPos = CamPos = camera->getLookFrom();// store postion so we can restore 
		//panVec = ls.panVec;
		//prePanVec = ls.prePanVec
		//PanActivited = ls.pan; Quat = glm::quat(glm::mat4(1.0f));
		//fov = camera->getFovy();

	//}





	void CustomizedTrackBall::MousePress_QT(int x, int y, int height, int width, /*Button*/ int button) {
		if (button == BUTTON_LEFT) {
			leftMouseDown = true;
			//std::cout << "left button clicked" << std::endl;
			// ndc coordinates[-1,1]*[-1,1]
			prevX = 1.0f - (width - x * 1.0f) / width;
			prevY = 1.0f - (height - y * 1.0f) / height;
			oldMouseX = x;
			oldMouseY = y;
			if (PanActivited)
			{
				prePanVec = panVec;
			}
			else 
				prevQuat = Quat;

		}


	}
	void CustomizedTrackBall::MouseRelease_QT(int mouse_x, int mouse_y, int height, int width, int button) {
		if (button == BUTTON_LEFT) {
			leftMouseDown = false;
		}
	}




	void CustomizedTrackBall::MouseMove_Qt(int x, int y, int height, int width,/*Button*/ int button) {

		if (leftMouseDown) {
			float x_ = 1.0f - (width - x * 1.0f) / width;
			float y_ = 1.0f - (height - y * 1.0f) / height;
			glm::vec3 s = mapNormalizedMousePosToTrackball(prevX, prevY, 1);
			glm::vec3 e = mapNormalizedMousePosToTrackball(x_, y_, 1);
			glm::quat delta = glm::quat(e, s);
			//if (abs(mouseX - oldMouseX) >= 1 || abs(mouseY - oldMouseY) >= 1)
			//std::cout << "pre" << prevX << " " << prevY << std::endl;
			glm::vec3 PanVec_delta= glm::vec3((prevX - x_), (y_ - prevY), 0);
			//if (panVecAccu)panVec += curPan;
			//else panVec = curPan;
			if (PanActivited) {
				/// move camera position;
				panVec = PanVec_delta + prePanVec;
				camera.setLookFrom(CamPos + panVec);
				camera.setLookTo(glm::vec3(0, 0, -40.f) + panVec);

				//glm::vec3 temp = camera->getLookFrom();
				//std::cout << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
			}
			else
				Quat = prevQuat * delta;

			//mouseX = x;
			//mouseY = y;
			//std::cout << prevX << " " << prevY << std::endl;
			//std::cout << s[0]<<" "<<s[1]<<" "<<s[2] << std::endl;
			//std::cout << e[0] << " " << e[1] << " " << e[2] << std::endl;

			//std::cout << x << " " << y << std::endl;
			//glm::mat4 rot = glm::toMat4(Quat);
			//std::cout << Quat[0] << " " << Quat[1] << " " << Quat[2]<<" "<<Quat[3] << std::endl;
			//for (int i = 0; i < 4; i++) {
			//	for (int j = 0; j < 4; j++) {
			//		std::cout << rot[i][j] << " .";
			//	}
			//	std::cout << std::endl;
			//}
			//std::cout << "_______________________________" << std::endl;

		}

	}

	void CustomizedTrackBall::keyPressEvent(int key) {


		switch (key) {
		case Key_A:
			//xoffset = xoffset - 0.01f;
			//std::cout << "ho" << std::endl;
			break;
		case Key_S:
			//zoffset = zoffset - 0.02f;
			break;
		case Key_D:
			//xoffset = xoffset + 0.01f;
			break;
		case Key_W:
			//zoffset = zoffset + 0.02f;
			break;
		case Key_Control:
			PanActivited = true;
			break;
		}
	}

	void CustomizedTrackBall::resetTrackball() {
		panVec = glm::vec3(0, 0, 0);
		prePanVec = glm::vec3(0, 0, 0);
		PanActivited = false; 
		Quat = glm::quat(glm::mat4(1.0f));
		prevQuat= glm::quat(glm::mat4(1.0f));
		camera.setLookFrom(CamPos + panVec);
		camera.setLookTo(glm::vec3(0, 0, -40.f) + panVec);
		fov = 60.f;
		camera.setFovy(fov);

	}

	void CustomizedTrackBall::wheelEvent(float delta) {
		const int WHEEL_STEP = 120;
		float notch = delta / float(WHEEL_STEP);
		fov -= notch;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 180.0f)
			fov = 180.0f;
		camera.setFovy(fov);

	}

	void CustomizedTrackBall::keyReleaseEvent(int key) {
		switch (key) {
		case Key_A:
			//xoffset = xoffset - 0.01f;
			//std::cout << "ho" << std::endl;
			break;
		case Key_S:
			//zoffset = zoffset - 0.02f;
			break;
		case Key_D:
			//xoffset = xoffset + 0.01f;
			break;
		case Key_W:
			//zoffset = zoffset + 0.02f;
			break;
		case Key_Control:
			PanActivited = false;
			//std::cout << "ctrl key is released" << std::endl;
			break;
		}
	}





	glm::mat4 CustomizedTrackBall::getRot() {

		return glm::transpose(glm::mat4(Quat));
	}

	void CustomizedTrackBall::outputRot() {
		glm::mat4 rot=glm::transpose(glm::mat4(Quat));
		std::cout << rot[0][0] << " " << rot[0][1] << " " << rot[0][2] << " " << rot[0][3] << std::endl;
		std::cout << rot[1][0] << " " << rot[1][1] << " " << rot[1][2] << " " << rot[1][3] << std::endl;
		std::cout << rot[2][0] << " " << rot[2][1] << " " << rot[2][2] << " " << rot[2][3] << std::endl;
		std::cout << rot[3][0] << " " << rot[3][1] << " " << rot[3][2] << " " << rot[3][3] << std::endl;


	}


	glm::vec3 CustomizedTrackBall::getPan() {


		return glm::vec3(0, 0, 0);
	}





}