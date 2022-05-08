#include "COAL.h"

#define setup_world()                                                                                                                                          \
                                                                                                                                                               \
    auto floor = std::make_shared<COAL::XZPlane>(COAL::XZPlane());                                                                                             \
    floor->m_material.set_color(COAL::Color(1, 0.9, 0.9)).set_specular(0).set_reflectiveness(0.3);                                                             \
                                                                                                                                                               \
    auto middle_sphere = std::make_shared<COAL::Sphere>(COAL::Sphere());                                                                                       \
    middle_sphere->m_material.set_color(COAL::Color(0, 0, 0)).set_specular(1).set_diffuse(0.1).set_reflectiveness(0.3).set_shininess(300).set_transparency(1); \
    middle_sphere->translate(-0.5, 1, 0.5);                                                                                                                    \
                                                                                                                                                               \
    auto right_sphere = std::make_shared<COAL::Sphere>(COAL::Sphere());                                                                                        \
    right_sphere->m_material.set_color(COAL::Color(0.5, 1, 0.1)).set_specular(0.3).set_diffuse(0.7).set_reflectiveness(0.3);                                   \
    right_sphere->translate(1.5, 0.5, -0.5).scale(0.5, 0.5, 0.5);                                                                                              \
                                                                                                                                                               \
    auto left_sphere = std::make_shared<COAL::Sphere>(COAL::Sphere());                                                                                         \
    left_sphere->m_material.set_color(COAL::Color(1, 0.8, 0.1)).set_specular(0.3).set_diffuse(0.7).set_reflectiveness(0.3);                                    \
    left_sphere->translate(-1.5, 0.33, -0.75).scale(0.33, 0.33, 0.33);                                                                                         \
                                                                                                                                                               \
    auto light = std::make_shared<COAL::PointLight>(COAL::PointLight());                                                                                       \
    light->set_intensity(COAL::Color(255, 255, 255)).set_position(COAL::Point(-10, 10, -10));

auto camera = COAL::Camera(1000, 1000, std::numbers::pi / 3);
auto world = COAL::World();
COAL::Color *canvas;
std::thread render_thread;

#ifdef _WIN32
#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Random.h"

class ExampleLayer : public Walnut::Layer
{
public:
    virtual void OnUIRender() override
    {

        // ImGui::ShowDemoWindow();
        ImGui::Begin("World Outline");

        static size_t selected = 0;

        auto shapes = world.get_shapes();
        auto lights = world.get_lights();

        if (ImGui::TreeNode("Objects"))
        {
            if (ImGui::TreeNode("Shapes"))
            {
                for (int i = 0; i < shapes.size(); i++)
                {
                    if (ImGui::Selectable((shapes[i]->get_name() + std::to_string(i)).c_str()))
                        selected = i;
                }

                ImGui::TreePop(); // Shapes
            }

            if (ImGui::TreeNode("Lights"))
            {
                for (size_t i = shapes.size(), j = 0; i < shapes.size() + lights.size(); i++)
                {
                    if (ImGui::Selectable((lights[j]->get_name() + std::to_string(i)).c_str()))
                        selected = i;
                }
                ImGui::TreePop(); // Lights
            }

            ImGui::TreePop(); // Objects
        }

        ImGui::Separator();

        {
            ImGui::BeginGroup();
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            ImGui::Text("Selected object: %s %d", selected < shapes.size() ? shapes[selected]->get_name() : lights[selected % lights.size()]->get_name(), selected);
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
                if (ImGui::BeginTabItem("Transform"))
                {
                    if (selected < shapes.size())
                    {
                        auto shape = shapes[selected];

                        auto translations = shape->get_translation();
                        auto rotations = shape->get_rotations();
                        auto scales = shape->get_scale();

                        float transformation[3] = {translations.x, translations.y, translations.z};
                        float rotation[3] = {rotations.x, rotations.y, rotations.z};
                        float scale[3] = {scales.x, scales.y, scales.z};

                        ImGui::InputFloat3("Position", (float *)&transformation);
                        ImGui::InputFloat3("Rotation", (float *)&rotation);
                        ImGui::InputFloat3("Scale", (float *)&scale);

                        shape->transform(transformation, rotation, scale);
                    }
                    else
                    {
                        auto light = lights[selected % lights.size()];

                        auto intensity_vec = light->get_intensity();
                        auto position_vec = light->get_position();

                        float position[3] = {position_vec.x, position_vec.y, position_vec.z};
                        float intensity[3] = {intensity_vec.r, intensity_vec.g, intensity_vec.b};

                        ImGui::InputFloat3("Position", (float *)&position);
                        ImGui::InputFloat3("Intensity", (float *)&intensity);

                        light->set_position(position);
                        light->set_intensity(intensity);
                    }

                    ImGui::EndTabItem();

                    if (ImGui::BeginTabItem("Details"))
                    {
                        ImGui::Text("ID: 0123456789");
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }

                ImGui::Separator();
                if (ImGui::Button("Render"))
                {
                    Render();
                }

                ImGui::SameLine();

                auto v_size = camera.get_vsize();
                auto h_size = camera.get_hsize();

                float size[2] = {h_size, v_size};

                ImGui::InputFloat2("Render Resolution", (float *)&size);

                camera.set_hsize(size[0]);
                camera.set_vsize(size[1]);

                ImGui::EndGroup();

                ImGui::EndChild();
            }

            ImGui::Text("Last render: %.3fms", m_LastRenderTime);
        }
        ImGui::End(); // World Outline

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Editor");

        m_ViewportWidth = camera.get_hsize();
        m_ViewportHeight = camera.get_vsize();

        if (m_Image)
            ImGui::Image(m_Image->GetDescriptorSet(), {(float)m_Image->GetWidth(), (float)m_Image->GetHeight()});

        // ImVec4 color;

        // ImGui::ColorEdit4("MyColor##3", (float *)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

        ImGui::End();
        ImGui::PopStyleVar();
    }

    void Render()
    {
        COAL::Timer timer;

        // auto a2 = std::async([&]()
        //                      { return camera.classic_render_multi_threaded(world); });

        // canvas = a2.get();

        canvas = camera.classic_render_multi_threaded(world);

        if (!m_Image || m_ViewportWidth != m_Image->GetWidth() || m_ViewportHeight != m_Image->GetHeight())
        {
            m_Image = std::make_shared<Walnut::Image>(m_ViewportWidth, m_ViewportHeight, Walnut::ImageFormat::RGBA);
            delete[] m_ImageData;
            m_ImageData = new uint32_t[m_ViewportWidth * m_ViewportHeight];
        }

        if (camera.is_finished())
        {
            for (uint32_t i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
            {
                m_ImageData[i] = canvas[i].createABGR();
            }

            delete[] canvas;
        }
        else
            for (uint32_t i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
                m_ImageData[i] = 0;

        m_Image->SetData(m_ImageData);

        m_LastRenderTime = timer.elapsed_millis();
    }

private:
    std::shared_ptr<Walnut::Image> m_Image;
    uint32_t *m_ImageData = nullptr;
    uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

    float m_LastRenderTime = 0.0f;
};

Walnut::Application *Walnut::CreateApplication(_maybe_unused int argc, _maybe_unused char **argv)
{

    Instrumentor::Get().beginSession("main");

    setup_world();

    world.add_shapes({floor, middle_sphere, right_sphere, left_sphere});
    world.add_lights({light});

    camera.transform(COAL::Point(0, 1.5, -5), COAL::Point(0, 1, 0), COAL::Vector(0, 1, 0));

    Walnut::ApplicationSpecification spec;
    spec.Name = "Ray Tracing";

    Walnut::Application *app = new Walnut::Application(spec);
    app->PushLayer<ExampleLayer>();
    app->SetMenubarCallback([app]()
                            {
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		} });

    Instrumentor::Get().endSession();

    return app;
}

#else

int main()
{
    Instrumentor::Get().beginSession("main");

    setup_world();

    world.add_shapes({floor, middle_sphere, right_sphere, left_sphere});
    world.add_lights({light});

    camera.transform(COAL::Point(0, 1.5, -5), COAL::Point(0, 1, 0), COAL::Vector(0, 1, 0));

    _maybe_unused COAL::Color *canvas = camera.classic_render_multi_threaded(world, 4);

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
            COLORREF COLOR = RGB(canvas[j * camera.get_hsize() + i].r, canvas[j * camera.get_hsize() + i].g, canvas[j * camera.get_hsize() + i].b);

            SetPixel(mydc, i, j, COLOR);
        }
    }

    ReleaseDC(myconsole, mydc);

    delete[] canvas;

    std::cin.ignore();
    return 0;
}

#endif