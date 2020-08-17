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

TEST_CASE("Sphere Intersection") {
    Sphere sphere{ glm::vec3(0, 0, -100), 20 };
    Ray ray{ {0, 0, 0}, {0, 0, -1} };

    HitPoint hitpoint = sphere.intersect(ray);
    REQUIRE(hitpoint.hit == true);
    REQUIRE(hitpoint.hit_point.x == 0);
    REQUIRE(hitpoint.hit_point.y == 0);
    REQUIRE(hitpoint.hit_point.z == -80);
}

TEST_CASE("Sphere Intersect Normale") {
    Sphere sphere{ glm::vec3(0, 0, -100), 50 };
    Ray ray{ {0, 0, 0}, {0, 0, -1} };

    HitPoint hitpoint = sphere.intersect(ray);
    Ray normale = sphere.intersectNormale(hitpoint.hit_point);

    REQUIRE(normale.direction.x == 0);
    REQUIRE(normale.direction.y == 0);
    REQUIRE(normale.direction.z == 50);
}

int main(int argc, char *argv[])
{
    return Catch::Session().run(argc, argv);
}
