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

TEST_CASE("test sphere area", "[sphere]") {
    Sphere s1{ {1, 1, 1}, 2.0f };
    float area = s1.area();
    REQUIRE(area == Approx(50.265f));

    Sphere s2{ {1, 1, 1}, 0.0f };
    area = s2.area();
    REQUIRE(area == Approx(0.0f));

    Sphere s3{ {1, 1, 1}, -2.0f };
    area = s3.area();
    REQUIRE(area == -1.0f);
}

TEST_CASE("test sphere volume", "[sphere]") {
    Sphere s1{ {1, 1, 1}, 3.0f };
    float volume = s1.volume();
    REQUIRE(volume == Approx(113.097f));

    Sphere s2{ {1, 1, 1}, 0.0f };
    volume = s2.volume();
    REQUIRE(volume == Approx(0.0f));

    Sphere s3{ {1, 1, 1}, -2.0f };
    volume = s3.volume();
    REQUIRE(volume == -1.0f);
}

TEST_CASE("test box area", "[area]") {
    Box b1{ {1, 1, 1}, {2, 2, 2 } };
    float area = b1.area();
    REQUIRE(area == 6.0f);
}

TEST_CASE("test box volume", "[area]") {
    Box b1{ {1, 1, 1}, {2, 2, 2 } };
    float area = b1.volume();
    REQUIRE(area == 1.0f);
}

TEST_CASE("intersect_ray_sphere", "[intersect]")
{
    // Ray
    glm::vec3 ray_origin{ 0.0f, 0.0f, 0.0f };
    // ray direction has to be normalized !
    // you can use :
    // v = glm :: normalize ( some_vector )
    glm::vec3 ray_direction{ 0.0f, 0.0f, 1.0f };
    // Sphere
    glm::vec3 sphere_center{ 0.0f ,0.0f, 5.0f };
    float sphere_radius{ 1.0f };
    float distance = 0.0f;
    auto result = glm::intersectRaySphere(
        ray_origin, ray_direction,
        sphere_center,
        sphere_radius * sphere_radius, // squared radius !!!
        distance);
    REQUIRE(distance == Approx(4.0f));

    Ray ray{ ray_origin, ray_direction };
    Sphere sphere{ "Sphere", {128, 128, 128}, sphere_center, sphere_radius };
    HitPoint hitpoint = sphere.intersect(ray);

    REQUIRE(hitpoint.hit == true);
    REQUIRE(hitpoint.distance == 4.0f);

    Ray ray2{ ray_origin, {0.0f, 0.0f, -1.0f} };
    Sphere sphere2{ "Sphere", {128, 128, 128}, sphere_center, sphere_radius };
    HitPoint hitpoint2 = sphere2.intersect(ray2);

    REQUIRE(hitpoint2.hit == false);

    Sphere sphere3{ "Sphere", {128, 128, 128}, {1.0f, 0.0f, 1.0f}, sphere_radius };
    HitPoint hitpoint3 = sphere3.intersect(ray);

    REQUIRE(hitpoint3.hit == true);
    REQUIRE(hitpoint3.distance == 1.0f);
}

TEST_CASE("Excercise 5.8", "[Destructor}") {
    std::cout << "Anfang Aufgabe 5.8 Testcase" << std::endl;
    
    Color red{ 255 , 0 , 0 };
    glm::vec3 position{ 0.0f, 0.0f, 0.0f };
    Sphere* s1 = new Sphere{"sphere0", red , position , 1.2f};
    Shape* s2 = new Sphere{ "sphere1", red , position , 1.2f };
    s1 -> print(std::cout);
    s2 -> print(std::cout);
    delete s1;
    delete s2;

    std::cout << "Ende Aufgabe 5.8 Testcase" << std::endl;
}

int main(int argc, char *argv[])
{
    Box b{ "Box", {128, 128, 128}, {5, 5, 5}, {10, 10, 10} };
    std::cout << b << std::endl;

    Sphere s{ "Sphere", {128, 128, 128}, {0, 0, 0}, 5.0f };
    std::cout << s << std::endl;

    return Catch::Session().run(argc, argv);
}
