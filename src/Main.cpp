#include "Engine.h"

#include <cmath>
#include <iostream>
#include <windows.h>

using namespace std;

#define PI 3.14

int main()
{

    auto floor = std::make_shared<COAL::XZPlane>(COAL::XZPlane());
    floor->m_material.set_color(COAL::Color(1, 0.9, 0.9)).set_specular(0).set_reflectiveness(0.3);

    auto middle_sphere = std::make_shared<COAL::Sphere>(COAL::Sphere());
    middle_sphere->m_material.set_color(COAL::Color(0, 0, 0)).set_specular(1).set_diffuse(0.1).set_reflectiveness(0.3).set_shininess(300).set_transparency(1);
    middle_sphere->set_transform(COAL::IDENTITY.translate(-0.5, 1, 0.5));

    auto right_sphere = std::make_shared<COAL::Sphere>(COAL::Sphere());
    right_sphere->m_material.set_color(COAL::Color(0.5, 1, 0.1)).set_specular(0.3).set_diffuse(0.7).set_reflectiveness(0.3);
    right_sphere->set_transform(COAL::IDENTITY.translate(1.5, 0.5, -0.5).scale(0.5, 0.5, 0.5));

    auto left_sphere = std::make_shared<COAL::Sphere>(COAL::Sphere());
    left_sphere->m_material.set_color(COAL::Color(1, 0.8, 0.1)).set_specular(0.3).set_diffuse(0.7).set_reflectiveness(0.3);
    left_sphere->set_transform(COAL::IDENTITY.translate(-1.5, 0.33, -0.75).scale(0.33, 0.33, 0.33));

    auto light = std::make_shared<COAL::PointLight>(COAL::PointLight());
    light->set_intensity(COAL::Color(255, 255, 255)).set_position(COAL::Point(-10, 10, -10));

    auto world = COAL::World();
    world.add_shapes({floor, middle_sphere, right_sphere, left_sphere});
    world.add_lights({light});

    auto camera = COAL::Camera(500, 500, PI / 3);

    camera.transform(COAL::Point(0, 1.5, -5), COAL::Point(0, 1, 0), COAL::Vector(0, 1, 0));

    COAL::Color **canvas = camera.classic_render(world);

    // Get a console handle
    HWND myconsole = GetConsoleWindow();
    // Get a handle to device context
    HDC mydc = GetDC(myconsole);

    // Draw pixels
    for (size_t i = 0; i < 500; i++)
    {

        for (size_t j = 0; j < 500; j++)
        {
            // Choose any color
            COLORREF COLOR = RGB(canvas[i][j].r, canvas[i][j].g, canvas[i][j].b);

            SetPixel(mydc, i, j, COLOR);
        }
    } // canvas[i][j].x, canvas[i][j].y, canvas[i][j].z

    ReleaseDC(myconsole, mydc);
    cin.ignore();
    return 0;
}
