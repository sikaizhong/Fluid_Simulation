#ifndef CUSTOMIZEDTRACKBALL_
#define CUSTOMIZEDTRACKBALL_
#include<glm/gtc/quaternion.hpp>
#include<renderer/camera.h>

namespace FS {
	/// The componibile states of the manipulator system.
	

class CustomizedTrackBall {
	public:
		enum Button {
			BUTTON_NONE = 0x00000000, ///< No button or key pressed.
			BUTTON_LEFT = 0x00000001, ///< Left mouse button pressed.
			BUTTON_MIDDLE = 0x00000004, ///< Middle mouse button pressed.
			BUTTON_RIGHT = 0x00000002, ///< Right mouse button pressed.
			WHEEL = 0x0008, ///< Mouse wheel activated.
			KEY_SHIFT = 0x0010, ///< Shift key pressed.
			KEY_CTRL = 0x0020, ///< Ctrl key pressed.
			KEY_ALT = 0x0040, ///< Alt key pressed.
			HANDLE = 0x0080, ///< Application-defined state activated.
			MODIFIER_MASK = 0x00FF, ///< (mask to get modifiers only)
			KEY_UP = 0x0100, ///< Up directional key
			KEY_DOWN = 0x0200, ///< Down directional key
			KEY_LEFT = 0x0400, ///< Left directional key
			KEY_RIGHT = 0x0800, ///< Right directional key
			KEY_PGUP = 0x1000, ///< PageUp directional key
			KEY_PGDOWN = 0x2000, ///< PageDown directional key
		};
		enum Key {
			Key_Shift = 0x01000020,                // modifiers
			Key_Control = 0x01000021,
			Key_Alt = 0x01000023,
			Key_A = 0x41,
			Key_B = 0x42,
			Key_C = 0x43,
			Key_D = 0x44,
			Key_E = 0x45,
			Key_F = 0x46,
			Key_G = 0x47,
			Key_H = 0x48,
			Key_I = 0x49,
			Key_J = 0x4a,
			Key_K = 0x4b,
			Key_L = 0x4c,
			Key_M = 0x4d,
			Key_N = 0x4e,
			Key_O = 0x4f,
			Key_P = 0x50,
			Key_Q = 0x51,
			Key_R = 0x52,
			Key_S = 0x53,
			Key_T = 0x54,
			Key_U = 0x55,
			Key_V = 0x56,
			Key_W = 0x57,
			Key_X = 0x58,
			Key_Y = 0x59,
			Key_Z = 0x5a,
		};
		explicit CustomizedTrackBall(float radius) :radius(radius) {
			//camera = new PerspectiveCamera();
			curCamPos=CamPos = camera.getLookFrom();// store postion so we can restore 
			panVec = glm::vec3(0, 0, 0);
			prePanVec = glm::vec3(0, 0, 0);
			PanActivited = false; Quat = glm::quat(glm::mat4(1.0f));
			fov=camera.getFovy();

		};

		CustomizedTrackBall() = default;
		//CustomizedTrackBall(CustomizedTrackBall&ls);
		glm::vec3 projectionToSphere(float x, float y)const;
		glm::vec3 mapNormalizedMousePosToTrackball(const float& mouse_x, const float&mouse_y, const float& r);
		glm::mat4 getRot();
		void outputRot();
		glm::vec3 getPan();
		void resetTrackball();
		void MousePress_QT(int x, int y, int height, int width, /*Button*/ int button);
		void MouseRelease_QT(int mouse_x, int mouse_y,int height, int width,int button);
		void keyPressEvent(int key);
		void keyReleaseEvent(int key);
		void wheelEvent(float val);


		void MouseMove_Qt(int x, int y,int height, int width, /*Button*/ int button);
		

	public:
		float radius;
		float prevX, prevY;
		int mouseX, mouseY, oldMouseX, oldMouseY;
		float fov;

		glm::quat prevQuat;
		glm::quat Quat;
		glm::quat rot;
		glm::vec3 panVec;
		glm::vec3 prePanVec;
		glm::vec3 CamPos;
		glm::vec3 curCamPos;
		float scale;
		bool leftMouseDown;
		bool rightMouseDown;
		bool PanActivited;
		PerspectiveCamera camera;

		//glm::mat4 rot;
		//Point3<S> tra;
		//S sca;
	};

}


#endif