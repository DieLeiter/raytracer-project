#define CATCH_CONFIG_RUNNER

#include <catch.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "box.hpp"
#include "sphere.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include <iostream>

TEST_CASE("Box Intersection"){
    Box box{ glm::vec3(-1, -1, -1), glm::vec3(1, 1, -2) };
    Ray ray{ {0, 0, 0}, {0, 0, -1} };

    HitPoint hitpoint = box.intersect(ray);

    std::cout << hitpoint.name << std::endl;
    REQUIRE(hitpoint.hit == true);
    REQUIRE(hitpoint.hit_point.x == 0);
    REQUIRE(hitpoint.hit_point.y == 0);
    REQUIRE(hitpoint.hit_point.z == -1);
}

int main(int argc, char *argv[])
{
    return Catch::Session().run(argc, argv);
}
