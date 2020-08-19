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

    /*Test 2: ray in wrong z direction */
    Box box2{ glm::vec3(-1, -1, -1), glm::vec3(1, 1, -2) };
    Ray ray2{ {0, 0, 0}, {0, 0, 1} };

    HitPoint hitpoint2 = box2.intersect(ray2);
    std::cout << hitpoint.name << std::endl;
    REQUIRE(hitpoint2.hit == false);

    /*Test 3: z positive */
    Box box3{ glm::vec3(-1, -1, 1), glm::vec3(1, 1, 2) };
    Ray ray3{ {0, 0, 0}, {0, 0, 1} };

    HitPoint hitpoint3 = box3.intersect(ray3);
    std::cout << hitpoint.name << std::endl;
    REQUIRE(hitpoint3.hit == true);
    REQUIRE(hitpoint3.hit_point.x == 0);
    REQUIRE(hitpoint3.hit_point.y == 0);
    REQUIRE(hitpoint3.hit_point.z == 1);

    /*Test 4: bootom hit*/
    Box box4{ glm::vec3(-1, -1, 1), glm::vec3(1, -2, -1) };
    Ray ray4{ {0, 0, 0}, {0, -1, 0} };

    HitPoint hitpoint4 = box4.intersect(ray4);
    std::cout << hitpoint4.name << std::endl;
    REQUIRE(hitpoint4.hit == true);
    REQUIRE(hitpoint4.hit_point.x == 0);
    REQUIRE(hitpoint4.hit_point.y == -1);
    REQUIRE(hitpoint4.hit_point.z == 0);

    /*Test 5: bootom does not hit*/
    Box box5{ glm::vec3(-1, -1, 1), glm::vec3(1, -2, -1) };
    Ray ray5{ {0, 0, 0}, {0, 1, 0} };

    HitPoint hitpoint5 = box5.intersect(ray5);
    std::cout << hitpoint5.name << std::endl;
    REQUIRE(hitpoint5.hit == false);

    /*Test 6: front hit*/
    Box box6{ glm::vec3(-1, -1, 1), glm::vec3(1, 1, 2) };
    Ray ray6{ {0, 0, -5}, {0, 0, 10} };

    HitPoint hitpoint6 = box6.intersect(ray6);
    std::cout << hitpoint6.name << std::endl;
    REQUIRE(hitpoint6.hit == true);
    REQUIRE(hitpoint6.hit_point.x == 0);
    REQUIRE(hitpoint6.hit_point.y == 0);
    REQUIRE(hitpoint6.hit_point.z == 1);
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
    glm::vec3 normale = sphere.intersectNormale(hitpoint.hit_point);

    REQUIRE(normale.x == 0);
    REQUIRE(normale.y == 0);
    REQUIRE(normale.z == 1.0f);
}

TEST_CASE("Box Intersect Normale") {
    Box box{ {-100, -100, -100}, {100, 100, -200} };
    Ray ray{ {0, 0, 0}, {0, 0, -1} };

    HitPoint hitpoint = box.intersect(ray);
    glm::vec3 normale = box.intersectNormale(hitpoint.hit_point);

    REQUIRE(normale.x == 0);
    REQUIRE(normale.y == 0);
    REQUIRE(normale.z == 1);
}

int main(int argc, char *argv[])
{
    return Catch::Session().run(argc, argv);
}
