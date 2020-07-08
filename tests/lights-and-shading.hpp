#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>

#include "color3d.hpp"
#include "intersection3d.hpp"
#include "intersection3d_collection.hpp"
#include "material3d.hpp"
#include "point_light3d.hpp"
#include "ray3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "util3d.hpp"
#include "vec3d.hpp"

TEST(LightsAndShading, ComputeSphereNormalsX){
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Tuple3D::Tuple3D<float> point{1,0,0};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);
    Ray_Tracer::Vec3D::Vec3D<float> answer{1, 0, 0};
    EXPECT_NEAR(n.x, answer.x, 0.001);
    EXPECT_NEAR(n.y, answer.y, 0.001);
    EXPECT_NEAR(n.z, answer.z, 0.001);
}

TEST(LightsAndShading, ComputeSphereNormalsY)
{
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Tuple3D::Tuple3D<float> point{0, 1, 0};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);
    Ray_Tracer::Vec3D::Vec3D<float> answer{0, 1, 0};
    EXPECT_NEAR(n.x, answer.x, 0.001);
    EXPECT_NEAR(n.y, answer.y, 0.001);
    EXPECT_NEAR(n.z, answer.z, 0.001);
}

TEST(LightsAndShading, ComputeSphereNormalsZ)
{
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Tuple3D::Tuple3D<float> point{0, 0, 1};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);
    Ray_Tracer::Vec3D::Vec3D<float> answer{0, 0, 1};
    EXPECT_NEAR(n.x, answer.x, 0.001);
    EXPECT_NEAR(n.y, answer.y, 0.001);
    EXPECT_NEAR(n.z, answer.z, 0.001);
}

TEST(LightsAndShading, ComputeSphereNormalsNonAxis)
{
    float non_axis = std::sqrt(3) / 3;

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Tuple3D::Tuple3D<float> point{non_axis, non_axis, non_axis};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);
    Ray_Tracer::Vec3D::Vec3D<float> answer{non_axis, non_axis, non_axis};
    EXPECT_NEAR(n.x, answer.x, 0.001);
    EXPECT_NEAR(n.y, answer.y, 0.001);
    EXPECT_NEAR(n.z, answer.z, 0.001);
}

TEST(LightsAndShading, NormalIsANormlizedVector)
{
    float non_axis = std::sqrt(3) / 3;

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Tuple3D::Tuple3D<float> point{non_axis, non_axis, non_axis};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);
    Ray_Tracer::Vec3D::Vec3D<float> nn = n.normalize();

    EXPECT_NEAR(n.x, nn.x, 0.001);
    EXPECT_NEAR(n.y, nn.y, 0.001);
    EXPECT_NEAR(n.z, nn.z, 0.001);
}

TEST(LightsAndShading, NormalTranslatedSphere)
{
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Matrix3D::Matrix3D<float> transform_matrix = sphere.get_transform();
    transform_matrix = transform_matrix.translate(0, 1, 0);
    sphere.transform(transform_matrix);
    Ray_Tracer::Tuple3D::Tuple3D<float> point{0, 1.70711, -0.70711};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);

    EXPECT_NEAR(n.x, 0, 0.001);
    EXPECT_NEAR(n.y, 0.70711, 0.001);
    EXPECT_NEAR(n.z, -0.70711, 0.001);
}

TEST(LightsAndShading, NormalScaledAndRotatedSphere)
{

    float non_axis = std::sqrt(2) / 2;

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Matrix3D::Matrix3D<float> transform_matrix = sphere.get_transform();
    transform_matrix = transform_matrix.scaling(1, 0.5, 1) * transform_matrix.rotation_z(3.14/5);
    sphere.transform(transform_matrix);
    Ray_Tracer::Tuple3D::Tuple3D<float> point{0, non_axis, -non_axis};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);

    EXPECT_NEAR(n.x, 0, 0.001);
    EXPECT_NEAR(n.y, 0.97014, 0.001);
    EXPECT_NEAR(n.z, -0.24254, 0.001);
}

TEST(LightsAndShading, Reflection45Degrees)
{
    Ray_Tracer::Vec3D::Vec3D<float> v{1, -1, 0};
    Ray_Tracer::Vec3D::Vec3D<float> n{0,1,0};
    Ray_Tracer::Vec3D::Vec3D<float> r = Ray_Tracer::Vec3D::Vec3D<float>::reflect(v, n);

    EXPECT_NEAR(r.x, 1, 0.001);
    EXPECT_NEAR(r.y, 1, 0.001);
    EXPECT_NEAR(r.z, 0, 0.001);
}

TEST(LightsAndShading, ReflectionSlantedSurface)
{
    float non_axis = std::sqrt(2) / 2;

    Ray_Tracer::Vec3D::Vec3D<float> v{0, -1, 0};
    Ray_Tracer::Vec3D::Vec3D<float> n{non_axis, non_axis, 0};
    Ray_Tracer::Vec3D::Vec3D<float> r = Ray_Tracer::Vec3D::Vec3D<float>::reflect(v, n);

    EXPECT_NEAR(r.x, 1, 0.001);
    EXPECT_NEAR(r.y, 0, 0.001);
    EXPECT_NEAR(r.z, 0, 0.001);
}

TEST(LightsAndShading, PointLight)
{
    Ray_Tracer::Color3D::Color3D<float> intensity{1,1,1};
    Ray_Tracer::Tuple3D::Tuple3D<float> position{0,0,0};
    Ray_Tracer::PointLight3D<float> light{position, intensity};

    EXPECT_NEAR(light.position.x, position.x, 0.001);
    EXPECT_NEAR(light.position.y, position.y, 0.001);
    EXPECT_NEAR(light.position.z, position.z, 0.001);
}

TEST(LightsAndShading, DefaultMaterial)
{
    Ray_Tracer::Material3D<float> material;
    EXPECT_NEAR(material.color.r, 1, 0.0001);
    EXPECT_NEAR(material.color.g, 1, 0.0001);
    EXPECT_NEAR(material.color.b, 1, 0.0001);

    EXPECT_NEAR(material.ambient, 0.1, 0.001);
    EXPECT_NEAR(material.diffuse, 0.9, 0.001);
    EXPECT_NEAR(material.specular, 0.9, 0.001);
    EXPECT_NEAR(material.shininess, 200.0, 0.001);
}

TEST(LightsAndShading, SphereDefaultMaterial)
{
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere;
    Ray_Tracer::Material3D<float> material;

    EXPECT_NEAR(sphere.material.color.r, material.color.r, 0.0001);
    EXPECT_NEAR(sphere.material.color.g, material.color.g, 0.0001);
    EXPECT_NEAR(sphere.material.color.b, material.color.b, 0.0001);

    EXPECT_NEAR(sphere.material.ambient, material.ambient, 0.001);
    EXPECT_NEAR(sphere.material.diffuse, material.diffuse, 0.001);
    EXPECT_NEAR(sphere.material.specular, material.specular, 0.001);
    EXPECT_NEAR(sphere.material.shininess, material.shininess, 0.001);
}

TEST(LightsAndShading, SphereAssignedMaterial)
{
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere;
    Ray_Tracer::Material3D<float> material;

    sphere.material = material;

    EXPECT_NEAR(sphere.material.color.r, material.color.r, 0.0001);
    EXPECT_NEAR(sphere.material.color.g, material.color.g, 0.0001);
    EXPECT_NEAR(sphere.material.color.b, material.color.b, 0.0001);

    EXPECT_NEAR(sphere.material.ambient, material.ambient, 0.001);
    EXPECT_NEAR(sphere.material.diffuse, material.diffuse, 0.001);
    EXPECT_NEAR(sphere.material.specular, material.specular, 0.001);
    EXPECT_NEAR(sphere.material.shininess, material.shininess, 0.001);
}

TEST(LightsAndShading, Lights1)
{
    Ray_Tracer::Material3D<float> m;
    Ray_Tracer::Tuple3D::Tuple3D<float> position{0, 0, 0};
    Ray_Tracer::Vec3D::Vec3D<float> eyev{0, 0, -1};
    Ray_Tracer::Vec3D::Vec3D<float> normalv{0, 0, -1};

    Ray_Tracer::Tuple3D::Tuple3D<float> light_position{0, 0, -10};
    Ray_Tracer::Color3D::Color3D<float> intensity{1, 1, 1};
    Ray_Tracer::PointLight3D<float> light{light_position, intensity};

    Ray_Tracer::Color3D::Color3D<float> lighting = Ray_Tracer::Material3D<float>::lighting(m, light, position, eyev, normalv);

    Ray_Tracer::Color3D::Color3D<float> answer{1.9, 1.9, 1.9};

    EXPECT_NEAR(answer.r, lighting.r, 0.0001);
    EXPECT_NEAR(answer.g, lighting.g, 0.0001);
    EXPECT_NEAR(answer.b, lighting.b, 0.0001);
}

TEST(LightsAndShading, Lights2)
{

    float non_axis = std::sqrt(2) / 2;

    Ray_Tracer::Material3D<float> m;
    Ray_Tracer::Tuple3D::Tuple3D<float> position{0, 0, 0};
    Ray_Tracer::Vec3D::Vec3D<float> eyev{0, non_axis, -non_axis};
    Ray_Tracer::Vec3D::Vec3D<float> normalv{0, 0, -1};

    Ray_Tracer::Tuple3D::Tuple3D<float> light_position{0, 0, -10};
    Ray_Tracer::Color3D::Color3D<float> intensity{1, 1, 1};
    Ray_Tracer::PointLight3D<float> light{light_position, intensity};

    Ray_Tracer::Color3D::Color3D<float> lighting = Ray_Tracer::Material3D<float>::lighting(m, light, position, eyev, normalv);

    Ray_Tracer::Color3D::Color3D<float> answer{1.0, 1.0, 1.0};

    EXPECT_NEAR(answer.r, lighting.r, 0.0001);
    EXPECT_NEAR(answer.g, lighting.g, 0.0001);
    EXPECT_NEAR(answer.b, lighting.b, 0.0001);
}

TEST(LightsAndShading, Lights3)
{

    float non_axis = std::sqrt(2) / 2;

    Ray_Tracer::Material3D<float> m;
    Ray_Tracer::Tuple3D::Tuple3D<float> position{0, 0, 0};
    Ray_Tracer::Vec3D::Vec3D<float> eyev{0, 0, -1};
    Ray_Tracer::Vec3D::Vec3D<float> normalv{0, 0, -1};

    Ray_Tracer::Tuple3D::Tuple3D<float> light_position{0, 10, -10};
    Ray_Tracer::Color3D::Color3D<float> intensity{1, 1, 1};
    Ray_Tracer::PointLight3D<float> light{light_position, intensity};

    Ray_Tracer::Color3D::Color3D<float> lighting = Ray_Tracer::Material3D<float>::lighting(m, light, position, eyev, normalv);

    Ray_Tracer::Color3D::Color3D<float> answer{0.7364, 0.7364, 0.7364};

    EXPECT_NEAR(answer.r, lighting.r, 0.0001);
    EXPECT_NEAR(answer.g, lighting.g, 0.0001);
    EXPECT_NEAR(answer.b, lighting.b, 0.0001);
}

TEST(LightsAndShading, Lights4)
{

    float non_axis = std::sqrt(2) / 2;

    Ray_Tracer::Material3D<float> m;
    Ray_Tracer::Tuple3D::Tuple3D<float> position{0, 0, 0};
    Ray_Tracer::Vec3D::Vec3D<float> eyev{0, -non_axis, -non_axis};
    Ray_Tracer::Vec3D::Vec3D<float> normalv{0, 0, -1};

    Ray_Tracer::Tuple3D::Tuple3D<float> light_position{0, 10, -10};
    Ray_Tracer::Color3D::Color3D<float> intensity{1, 1, 1};
    Ray_Tracer::PointLight3D<float> light{light_position, intensity};

    Ray_Tracer::Color3D::Color3D<float> lighting = Ray_Tracer::Material3D<float>::lighting(m, light, position, eyev, normalv);

    Ray_Tracer::Color3D::Color3D<float> answer{1.6364, 1.6364, 1.6364};

    EXPECT_NEAR(answer.r, lighting.r, 0.0001);
    EXPECT_NEAR(answer.g, lighting.g, 0.0001);
    EXPECT_NEAR(answer.b, lighting.b, 0.0001);
}

TEST(LightsAndShading, Lights5)
{

    float non_axis = std::sqrt(2) / 2;

    Ray_Tracer::Material3D<float> m;
    Ray_Tracer::Tuple3D::Tuple3D<float> position{0, 0, 0};
    Ray_Tracer::Vec3D::Vec3D<float> eyev{0, 0, -1};
    Ray_Tracer::Vec3D::Vec3D<float> normalv{0, 0, -1};

    Ray_Tracer::Tuple3D::Tuple3D<float> light_position{0, 0, 10};
    Ray_Tracer::Color3D::Color3D<float> intensity{1, 1, 1};
    Ray_Tracer::PointLight3D<float> light{light_position, intensity};

    Ray_Tracer::Color3D::Color3D<float> lighting = Ray_Tracer::Material3D<float>::lighting(m, light, position, eyev, normalv);

    Ray_Tracer::Color3D::Color3D<float> answer{0.1, 0.1, 0.1};

    EXPECT_NEAR(answer.r, lighting.r, 0.0001);
    EXPECT_NEAR(answer.g, lighting.g, 0.0001);
    EXPECT_NEAR(answer.b, lighting.b, 0.0001);
}