#include "COAL.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define setup_world()                                                                                                                                              \
                                                                                                                                                                   \
    auto floor = std::make_shared<COAL::XZPlane>(COAL::XZPlane());                                                                                                 \
    floor->get_material().set_color(COAL::Color(1, 0.9, 0.9)).set_specular(0).set_reflectiveness(0.3);                                                             \
                                                                                                                                                                   \
    auto middle_sphere = std::make_shared<COAL::Sphere>(COAL::Sphere());                                                                                           \
    middle_sphere->get_material().set_color(COAL::Color(0, 0, 0)).set_specular(1).set_diffuse(0.1).set_reflectiveness(0.3).set_shininess(300).set_transparency(1); \
    middle_sphere->translate(-0.5, 1, 0.5);                                                                                                                        \
                                                                                                                                                                   \
    auto right_sphere = std::make_shared<COAL::Sphere>(COAL::Sphere());                                                                                            \
    right_sphere->get_material().set_color(COAL::Color(0.5, 1, 0.1)).set_specular(0.3).set_diffuse(0.7).set_reflectiveness(0.3);                                   \
    right_sphere->translate(1.5, 0.5, -0.5).scale(0.5, 0.5, 0.5);                                                                                                  \
                                                                                                                                                                   \
    auto left_sphere = std::make_shared<COAL::Sphere>(COAL::Sphere());                                                                                             \
    left_sphere->get_material().set_color(COAL::Color(1, 0.8, 0.1)).set_specular(0.3).set_diffuse(0.7).set_reflectiveness(0.3);                                    \
    left_sphere->translate(-1.5, 0.33, -0.75).scale(0.33, 0.33, 0.33);                                                                                             \
                                                                                                                                                                   \
    auto light = std::make_shared<COAL::PointLight>(COAL::PointLight());                                                                                           \
    light->set_intensity(COAL::Color(255, 255, 255)).set_position(COAL::Point(-10, 10, -10));

auto camera = COAL::Camera(800, 600, std::numbers::pi / 3);
auto world = COAL::World();
std::shared_ptr<COAL::Color[]> canvas;
std::thread render_thread;
bool first_render = true;

#ifdef _WIN32
#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Random.h"

class MainLayer : public Walnut::Layer
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

        if (ImGui::TreeNode("Details"))
        {

            {
                ImGui::BeginGroup();
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

                            auto position_vec = light->get_position();

                            float position[3] = {position_vec.x, position_vec.y, position_vec.z};

                            ImGui::InputFloat3("Position", (float *)&position);

                            light->set_position(position);
                        }

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("Material"))
                    {
                        if (selected < shapes.size())
                        {
                            auto shape = shapes[selected];

                            auto color = shape->get_material().get_color();
                            auto specular = shape->get_material().get_specular();
                            auto diffuse = shape->get_material().get_diffuse();
                            auto reflectiveness = shape->get_material().get_reflectiveness();
                            auto shininess = shape->get_material().get_shininess();

                            float color_vec[3] = {color.r, color.g, color.b};

                            ImGui::ColorEdit3("Material Color", (float *)&color_vec);

                            shape->get_material().set_color(color_vec);
                        }
                        else
                        {
                            auto light = lights[selected % lights.size()];

                            auto color = light->get_intensity() / 255;

                            float color_vec[3] = {color.r, color.g, color.b};

                            ImGui::ColorEdit3("Light Color", (float *)&color_vec);

                            light->set_SDR_intensity(color_vec);
                        }

                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();

                } // End of Detail view
            }

            ImGui::EndGroup();

            ImGui::TreePop(); // Details
        }

        ImGui::Separator();

        {
            if (ImGui::TreeNode("Render Settings"))
            {
                {
                    auto v_size = camera.get_height();
                    auto h_size = camera.get_width();

                    float size[2] = {h_size, v_size};

                    ImGui::InputFloat2("Render Resolution", (float *)&size);

                    camera.set_width(size[0]);
                    camera.set_height(size[1]);
                }

                auto render_depth = world.get_max_depth();

                ImGui::SliderInt("Render Depth", &render_depth, 0, 10);

                world.set_max_depth(render_depth);

                ImGui::TreePop(); // Render Settings
            }
        }

        ImGui::Separator();

        {
            if (ImGui::Button("Render"))
            {
                Render();
            }

            ImGui::Text("Last render: %.3fms", m_LastRenderTime);
        }

        if (!first_render)
        {
            if (ImGui::Button("Save Render"))
            {

                uint8_t *pixels = new uint8_t[camera.get_width() * camera.get_height() * 3];

                int index = 0;

                for (uint32_t i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
                {
                    COAL::Color curr = canvas.get()[i];

                    pixels[index++] = (uint8_t)curr.r;
                    pixels[index++] = (uint8_t)curr.g;
                    pixels[index++] = (uint8_t)curr.b;
                }

                // You have to use 3 comp for complete jpg file. If not, the image will be grayscale or nothing.
                stbi_write_jpg("ExampleRender.jpg", camera.get_width(), camera.get_height(), 3, pixels, 100);
                delete[] pixels;
            }

            ImGui::Text("Last render: %.3fms", m_LastRenderTime);
        }

        ImGui::End(); // World Outline

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Editor");

        m_ViewportWidth = camera.get_width();
        m_ViewportHeight = camera.get_height();

        if (m_Image)
            ImGui::Image(m_Image->GetDescriptorSet(), {(float)m_Image->GetWidth(), (float)m_Image->GetHeight()});

        ImGui::End();
        ImGui::PopStyleVar();
    }

    void Render()
    {
        COAL::Timer timer;

        first_render = false;

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
                m_ImageData[i] = canvas.get()[i].create_ABGR();
            }
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
    app->PushLayer<MainLayer>();
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
    // Instrumentor::Get().beginSession("main");

    setup_world();

    world.add_shapes({floor, middle_sphere, right_sphere, left_sphere});
    world.add_lights({light});

    camera.transform(COAL::Point(0, 1.5, -5), COAL::Point(0, 1, 0), COAL::Vector(0, 1, 0));

    canvas = camera.classic_render_multi_threaded(world, 4);

    Instrumentor::Get().endSession();

    // Get a console handle
    HWND myconsole = GetConsoleWindow();
    // Get a handle to device context
    HDC mydc = GetDC(myconsole);

    // Draw pixels
    for (int16_t i = 0; i < camera.get_width(); i++)
    {

        for (int16_t j = 0; j < camera.get_height(); j++)
        {
            COLORREF COLOR = RGB(canvas.get()[j * camera.get_width() + i].r, canvas.get()[j * camera.get_width() + i].g, canvas.get()[j * camera.get_width() + i].b);

            SetPixel(mydc, i, j, COLOR);
        }
    }

    ReleaseDC(myconsole, mydc);

    std::cin.ignore();
    return 0;
}

#endif