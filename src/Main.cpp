#include "COAL.h"

int main()
{
    Instrumentor::Get().beginSession("main");

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

    auto camera = COAL::Camera(1000, 1000, std::numbers::pi / 3);

    camera.transform(COAL::Point(0, 1.5, -5), COAL::Point(0, 1, 0), COAL::Vector(0, 1, 0));

    _maybe_unused COAL::Color **canvas = camera.classic_render_multi_threaded(world, 4);

    Instrumentor::Get().endSession();

    // Get a console handle
    HWND myconsole = GetConsoleWindow();
    // Get a handle to device context
    HDC mydc = GetDC(myconsole);

    // Draw pixels
    for (int16_t i = 0; i < camera.get_hsize(); i++)
    {

        for (int16_t j = 0; j < camera.get_vsize(); j++)
        {
            COLORREF COLOR = RGB(canvas[j][i].r, canvas[j][i].g, canvas[j][i].b);

            SetPixel(mydc, i, j, COLOR);
        }
    }

    ReleaseDC(myconsole, mydc);

    for (int i = 0; i < camera.get_hsize(); i++)
    {
        delete[] canvas[i];
    }

    std::cin.ignore();
    return 0;
}
