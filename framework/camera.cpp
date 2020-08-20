#define _USE_MATH_DEFINES

#include <cmath>
#include "camera.hpp"
#include <glm/glm.hpp>

Camera::Camera(std::string const& n, float angle, glm::vec3 const& position, glm::vec3 const& direction, glm::vec3 const& upvektor) :
	name_{n},
	fov_x_{angle},
	eye_{position},
	dir_{ direction },
	up_{ upvektor } 
{
	transform_ = compute_transform();
}


glm::mat4 Camera::compute_transform()
{
    /* Prepare Camera Transformation*/
  // n is normalized direction of eye
    glm::vec3 n = glm::normalize(dir_);
    //u = n x up
    glm::vec3 u = glm::normalize(glm::cross(n, up_));
    //v = u x n
    glm::vec3 v = glm::normalize(glm::cross(u, n));
    
    //transformation matrix of camera
	return glm::mat4{ glm::vec4{u.x, u.y, u.z, 0 },
                        glm::vec4{v.x, v.y, v.z, 0 },
                        glm::vec4{-n.x, -n.y, -n.z, 0 },
                        glm::vec4{eye_.x,eye_.y,eye_.z, 1} };
}

Ray Camera::compute_eye_ray(unsigned width, unsigned height, int x, int y) const
{
    //radians = degrees * pi / 180 ;
    float camera_angle_rad = fov_x_ * M_PI / 180.0f;
    float distance = (width / 2) / std::tan(camera_angle_rad / 2); // compute plane distance

    float ray_x = (int)width / 2 - ((int)width - x);
    float ray_y = (int)height / 2 - ((int)height - y);
    Ray ray{ glm::vec3(0, 0, 0), glm::normalize(glm::vec3(ray_x, ray_y, -distance)) };

    /*transform ray*/
    glm::vec4 origin_4{ ray.origin, 1.0f };
    glm::vec4 direction_4{ ray.direction, 0.0f };
    glm::vec4 transformed_origin = transform_ * origin_4;
    glm::vec4 transformed_direction = glm::normalize(transform_ * direction_4);
    ray = { {transformed_origin.x, transformed_origin.y, transformed_origin.z}, {transformed_direction.x, transformed_direction.y, transformed_direction.z} };

    return ray; // compute ray from camera through picture plane
}


