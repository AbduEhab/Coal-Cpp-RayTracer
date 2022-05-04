#include "Engine.h"

#include <windows.h>

int main2()
{
    // test matrix4.h inverse function
    COAL::Matrix4 m({{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}});
    COAL::Matrix4 m_inverse = m.inverse();
    COAL::Matrix4 res({{0.21805, 0.45113, 0.24060, -0.04511}, {-0.80827, -1.45677, -0.44361, 0.52068}, {-0.07895, -0.22368, -0.05263, 0.19737}, {-0.52256, -0.81391, -0.30075, 0.30639}});

    debug_print("matrix4.h inverse function test");
    debug_print("original matrix:\n", m);
    debug_print("inverse matrix:\n", m_inverse);

    std::cout << m << std::endl
              << std::endl;

    std::cout << m_inverse << std::endl;

    std::cout << res << std::endl;

    // test matrix4.h determinant function
    std::cout << m.determinant4() << std::endl;
    return 0;
}

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

    auto camera = COAL::Camera(200, 200, std::numbers::pi / 3);

    camera.transform(COAL::Point(0, 1.5, -5), COAL::Point(0, 1, 0), COAL::Vector(0, 1, 0));

    COAL::Color **canvas = camera.classic_render(world);

    // Get a console handle
    HWND myconsole = GetConsoleWindow();
    // Get a handle to device context
    HDC mydc = GetDC(myconsole);

    // Draw pixels
    for (int16_t i = 0; i < camera.get_hsize(); i++)
    {

        for (int16_t j = 0; j < camera.get_vsize(); j++)
        {
            // Choose any color
            COLORREF COLOR = RGB(canvas[i][j].r, canvas[i][j].g, canvas[i][j].b);

            SetPixel(mydc, i, j, COLOR);
        }
    }

    ReleaseDC(myconsole, mydc);

    std::cin.ignore();
    return 0;
}
