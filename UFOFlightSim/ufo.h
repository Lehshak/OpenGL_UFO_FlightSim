#define GLM_ENABLE_EXPERIMENTAL 
#ifndef UFO_H
#define UFO_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/quaternion.hpp> // For glm::quat
#include <glm/gtx/quaternion.hpp> // For glm::rotate


class UFO {
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::quat orientation; // Add this member to store orientation


	UFO(glm::vec3 startPos = glm::vec3(0.0f))
		:
		position(startPos),
		front(glm::vec3(0.0f, 0.0f, -1.0f)),
		up(glm::vec3(0.0f, 1.0f, 0.0f)),
		orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) // Identity quaternion 
	{}

	void processInput(GLFWwindow* window, float deltaTime);

	glm::mat4 getModelMatrixTop() const;
	glm::mat4 getModelMatrixBottom() const;



};

#endif