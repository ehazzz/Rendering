#include "Playground.h"

#include <sstream>


#pragma region /* Local Variables */
// rendering context
static Renderer m_Renderer = Renderer{};
static Serface* m_Serface = nullptr;

static InputManager* input = nullptr;

// meshes
static MeshArray* Sample = nullptr;
static const Char* SamplePath = "../Extern/Assets/Models/KaiLu/splits_config.txt";

// state
static RealType timestep = 0.0f;
static RealType elapsed = 0.0f; // running time(measure by seconds)

static RealType zoom = 0.0f;
static RealType degreesAlongYAxis = 0.0f, cachedDegrees = 0.0f, degreeScale = 100;

#pragma region /* Buttons */
static constexpr SizeType FillButtonCount = 3;
static constexpr SizeType CullButtonCount = 3;
static constexpr SizeType DepthTestButtonCount = 6;
static constexpr SizeType DepthWriteButtonCount = 2;
static constexpr SizeType BlendButtonCount = 2;

static Button* fillModeGroup = nullptr;
static Button* cullModeGroup = nullptr;
static Button* depthTestModeGroup = nullptr;
static Button* depthWriteModeGroup = nullptr;
static Button* blendModeGroup = nullptr;
#pragma endregion
#pragma endregion


#pragma region /* Local Function */
static Void OnReset() {
    // button group
    fillModeGroup[1].OnClicked();
    cullModeGroup[1].OnClicked();
    depthTestModeGroup[0].OnClicked();
    depthWriteModeGroup[1].OnClicked();
    blendModeGroup[0].OnClicked();

    // rotation
    {
        cachedDegrees = 0.0f;

        if (degreesAlongYAxis > 0)
            while (degreesAlongYAxis > 360) degreesAlongYAxis -= 360;
        else
            while (degreesAlongYAxis < -360) degreesAlongYAxis += 360;
    }

    // zoom
    input->GetMouseScrollWheel() = 0;
}

static void ResetButtonState(Button* button) {
    button->normal = ColorF_White;
    button->highlighted = button->normal * 0.8f;
    button->pressed = button->normal * 0.5f;
}

static void SetSelectedButtonState(Button* button) {
    button->normal = ColorF_Red;
    button->highlighted = button->normal * 0.8f;
    button->pressed = button->normal * 0.5f;
}

static void SetSelectedButtonGroupState(Button* buttons, Int32 selectedButtonIndex, Int32 buttonCount) {
    for (Int32 i = 0; i < buttonCount; i++)
        ResetButtonState(buttons + i);

    SetSelectedButtonState(buttons + selectedButtonIndex);
}
#pragma endregion


Void OnAppInit()
{
    m_Serface = &m_Renderer.GetSerface();
    input = &runtimeContext.input;
    Sample = MeshArray::Load(SamplePath);

    // apply default settings
    {
        fillModeGroup = new Button[]{
            {"Wareframe",
                []() {
                    RenderPipeline::fillMode = FillMode::Wireframe;
                    SetSelectedButtonGroupState(fillModeGroup, 0, 3);
                }
            },

            {"Solid",
                []() {
                    RenderPipeline::fillMode = FillMode::Solid;
                    SetSelectedButtonGroupState(fillModeGroup, 1, 3);
                }
            },

            {"All",
                []() {
                    RenderPipeline::fillMode = FillMode::All;
                    SetSelectedButtonGroupState(fillModeGroup, 2, 3);
                }
            }
        };

        cullModeGroup = new Button[]{
            {"Disable",
                []() {
                    RenderPipeline::cullMode = CullMode::Disable;
                    SetSelectedButtonGroupState(cullModeGroup, 0, 3);
                }
            },

            {"Back",
                []() {
                    RenderPipeline::cullMode = CullMode::Back;
                    SetSelectedButtonGroupState(cullModeGroup, 1, 3);
                }
            },

            {"Front",
                []() {
                    RenderPipeline::cullMode = CullMode::Front;
                    SetSelectedButtonGroupState(cullModeGroup, 2, 3);
                }
            }
        };

        depthTestModeGroup = new Button[]{
            {"Less",
                []() {
                    RenderPipeline::depthTestMode = DepthTestMode::Less;
                    SetSelectedButtonGroupState(depthTestModeGroup, 0, 6);
                }
            },
            {"LEqual",
                []() {
                    RenderPipeline::depthTestMode = DepthTestMode::LEqual;
                    SetSelectedButtonGroupState(depthTestModeGroup, 1, 6);
                }
            },
            {"Equal",
                []() {
                    RenderPipeline::depthTestMode = DepthTestMode::Equal;
                    SetSelectedButtonGroupState(depthTestModeGroup, 2, 6);
                }
            },
            {"Greater",
                []() {
                    RenderPipeline::depthTestMode = DepthTestMode::Greater;
                    SetSelectedButtonGroupState(depthTestModeGroup, 3, 6);
                }
            },
            {"GEqual",
                []() {
                    RenderPipeline::depthTestMode = DepthTestMode::GEqual;
                    SetSelectedButtonGroupState(depthTestModeGroup, 4, 6);
                }
            },
            {"Always",
                []() {
                    RenderPipeline::depthTestMode = DepthTestMode::Always;
                    SetSelectedButtonGroupState(depthTestModeGroup, 5, 6);
                }
            }
        };

        depthWriteModeGroup = new Button[]{
            {"Disable",
                []() {
                    RenderPipeline::depthWriteMode = DepthWriteMode::Disable;
                    SetSelectedButtonGroupState(depthWriteModeGroup, 0, 2);
                }
            },
            {"Enable",
                []() {
                    RenderPipeline::depthWriteMode = DepthWriteMode::Enable;
                    SetSelectedButtonGroupState(depthWriteModeGroup, 1, 2);
                }
            }
        };

        blendModeGroup = new Button[]{
            {"Disable",
                []() {
                    RenderPipeline::blendMode = BlendMode::Disable;
                    SetSelectedButtonGroupState(blendModeGroup, 0, 2);
                }
            },

            {"SrcAlpha_OneMinusSrcAlpha",
                []() {
                    RenderPipeline::blendMode = BlendMode::SrcAlpha_OneMinusSrcAlpha;
                    SetSelectedButtonGroupState(blendModeGroup, 1, 2);
                }
            }
        };
        /* --- */

        OnReset();
    }
}

Void OnAppResize(SizeType width, SizeType height)
{
    m_Serface->Resize(width, height);
}

Bool OnAppQuit()
{
    return true;
}

Void OnUpdate(RealType deltaTime)
{
    // state
    {
        // time
        {
            timestep = deltaTime;
            elapsed += timestep;
        }

        // scroll wheel
        {
            //limit at [-10, 10]
            auto& scrollWheel = input->GetMouseScrollWheel();
            scrollWheel = Clamp(scrollWheel, -10, 10);
            zoom = Lerp(zoom, scrollWheel * 0.1f, deltaTime);
        }

        // rotation
        degreesAlongYAxis = Lerp(degreesAlongYAxis, cachedDegrees, deltaTime * 2);
    }

    // update cbuffer(used by vertex or pixel shader)
    CBuffer::Model = RotateY(degreesAlongYAxis * DegreesToRadians<RealType>);
    CBuffer::View = LookAt(Vector3F_Forward * (2 + zoom) + Vector3F_Up * 0.85f, Vector3_Forward<RealType>, Vector3_Up<RealType>);
    CBuffer::Projection = PerspectiveProjection(Pi<RealType> / 3, m_Serface->GetAspect(), 0.1f, 100.0f);

    CBuffer::MV = CBuffer::View * CBuffer::Model;
    CBuffer::VP = CBuffer::Projection * CBuffer::View;
    CBuffer::MVP = CBuffer::Projection * CBuffer::MV;
    CBuffer::EyePosition = ToVector3(CBuffer::View.GetColumn(3));
}

Void OnRender(Void* RenderTarget)
{
    // frame start
    m_Serface->Clear(ClearFlag::ColorDepth);

    RenderPipeline::VS = DefaultVertexShader;
    RenderPipeline::PS = BlinnPhong;

    if (Sample) 
        m_Renderer.Draw(*Sample);

    DrawMaskBackground();
    DrawImmediateModeUI();
    // frame end
    if(RenderTarget) m_Serface->CopyTo(RenderTarget);
}


#pragma region 
Void DrawMaskBackground()
{
    auto width = m_Serface->GetWidth();
    auto height = m_Serface->GetHeight();
    auto colorBuffer = m_Serface->GetColorBuffer();

    auto maskWidth = 500;
    maskWidth = Minimum(maskWidth, width);

    auto maskColor = ColorF{ 0.0f, 0.0f, 0.0f, 0.25f };

    for (Int32 y = 0; y < height; y++)
        for (Int32 x = 0; x < maskWidth; x++)
            colorBuffer[width * y + x] = Blend(maskColor, m_Serface->GetPixel(x, y));
}

Void DrawImmediateModeUI()
{
    constexpr UInt32 HorizontalOffset = 10;
    constexpr UInt32 SecondaryHorizontalOffset = HorizontalOffset + 16;
    constexpr UInt32 VerticalOffset = 20;

    Int32 yOffset = m_Serface->GetHeight() - 1;

    // Grapics
    {
        // tip
        {
            yOffset -= VerticalOffset + AsciiGlyph::Height * 1;

            AsciiGlyph::Render(m_Serface, Vector2Int{ HorizontalOffset, yOffset }, "Graphics", ColorF_Black);
        }

        // fps
        {
            static std::stringstream ss;
            ss.str("");
            ss << "refresh rate: " << (UInt32)(1 / timestep);

            yOffset -= AsciiGlyph::Height;

            AsciiGlyph::Render(m_Serface, Vector2Int{ SecondaryHorizontalOffset, yOffset }, ss.str().c_str(), ColorF_White);
        }
    }

    // Tips
    {
        // tip
        {
            yOffset -= AsciiGlyph::Height * 2;

            AsciiGlyph::Render(m_Serface, Vector2Int{ HorizontalOffset, yOffset }, "Tips", ColorF_Black);
        }

        // mouse scroll
        {
            yOffset -= AsciiGlyph::Height;

            AsciiGlyph::Render(m_Serface, Vector2Int{ SecondaryHorizontalOffset, yOffset }, "mouse scroll wheel: zoom in/out", ColorF_White);
        }
    }

    // Settings
    {
        // tip
        {
            yOffset -= AsciiGlyph::Height * 3;

            AsciiGlyph::Render(m_Serface, Vector2Int{ HorizontalOffset, yOffset }, "Settings", ColorF_Black);
        }

        // reset
        {
            yOffset -= AsciiGlyph::Height * 2;

            static Button button = { "Reset",
                []() {OnReset(); }
            };

            button.position = Vector2Int{ SecondaryHorizontalOffset, yOffset };
            button.Update(timestep);
            button.Render(m_Serface);
        }

        // rotation
        {

            // tip
            {
                yOffset -= AsciiGlyph::Height * 2;

                AsciiGlyph::Render(m_Serface, Vector2Int{ SecondaryHorizontalOffset, yOffset }, "rotating model along y axis", ColorF_Yellow);
            }

            // left arrow
            {
                yOffset -= AsciiGlyph::Height * 2;
                static Button button = { "<=", nullptr,
                    []() {
                        cachedDegrees -= timestep * degreeScale;
                    }
                };

                button.position = Vector2Int{ SecondaryHorizontalOffset, yOffset };
                button.Update(timestep);
                button.Render(m_Serface);
            }

            // right arrow
            {
                static Button button = { "=>", nullptr,
                    []() {
                        cachedDegrees += timestep * degreeScale;
                    }
                };

                button.position = Vector2Int{ SecondaryHorizontalOffset + AsciiGlyph::Width * (4 + 2), yOffset };
                button.Update(timestep);
                button.Render(m_Serface);
            }
        }

        // fill mode
        {
            // tip
            {
                yOffset -= AsciiGlyph::Height * 2;

                AsciiGlyph::Render(m_Serface, Vector2Int{ SecondaryHorizontalOffset, yOffset }, "fill mode", ColorF_Yellow);
            }

            // draw buttons
            {
                yOffset -= AsciiGlyph::Height * 2;
                auto xExtraOffset = 0;
                for (auto i = 0; i < FillButtonCount; i++)
                {
                    auto& button = fillModeGroup[i];
                    button.position = Vector2Int{ SecondaryHorizontalOffset + xExtraOffset, yOffset };
                    button.Update(timestep);
                    button.Render(m_Serface);

                    xExtraOffset += (button.text.size() + 4) * AsciiGlyph::Width;
                }
            }
        }

        // cull mode
        {
            // tip
            {
                yOffset -= AsciiGlyph::Height * 2;

                AsciiGlyph::Render(m_Serface, Vector2Int{ SecondaryHorizontalOffset, yOffset }, "cull mode", ColorF_Yellow);
            }

            // draw buttons
            {
                yOffset -= AsciiGlyph::Height * 2;
                auto xExtraOffset = 0;
                for (auto i = 0; i < CullButtonCount; i++)
                {
                    auto& button = cullModeGroup[i];
                    button.position = Vector2Int{ SecondaryHorizontalOffset + xExtraOffset, yOffset };
                    button.Update(timestep);
                    button.Render(m_Serface);

                    xExtraOffset += (button.text.size() + 4) * AsciiGlyph::Width;
                }
            }
        }

        // depth test mode
        {
            // tip
            {
                yOffset -= AsciiGlyph::Height * 2;

                AsciiGlyph::Render(m_Serface, Vector2Int{ SecondaryHorizontalOffset, yOffset }, "depth test mode", ColorF_Yellow);
            }

            // draw buttons
            {
                yOffset -= AsciiGlyph::Height * 2;
                auto xExtraOffset = 0;
                for (auto i = 0; i < DepthTestButtonCount; i++)
                {
                    auto& button = depthTestModeGroup[i];
                    button.position = Vector2Int{ SecondaryHorizontalOffset + xExtraOffset, yOffset };
                    button.Update(timestep);
                    button.Render(m_Serface);

                    xExtraOffset += (button.text.size() + 4) * AsciiGlyph::Width;
                }
            }
        }

        // depth write mode
        {
            // tip
            {
                yOffset -= AsciiGlyph::Height * 2;

                AsciiGlyph::Render(m_Serface, Vector2Int{ SecondaryHorizontalOffset, yOffset }, "depth write mode", ColorF_Yellow);
            }

            // draw buttons
            {
                yOffset -= AsciiGlyph::Height * 2;
                auto xExtraOffset = 0;
                for (auto i = 0; i < DepthWriteButtonCount; i++)
                {
                    auto& button = depthWriteModeGroup[i];
                    button.position = Vector2Int{ SecondaryHorizontalOffset + xExtraOffset, yOffset };
                    button.Update(timestep);
                    button.Render(m_Serface);

                    xExtraOffset += (button.text.size() + 4) * AsciiGlyph::Width;
                }
            }
        }

        // blend mode
        {
            // tip
            {
                yOffset -= AsciiGlyph::Height * 2;

                AsciiGlyph::Render(m_Serface, Vector2Int{ SecondaryHorizontalOffset, yOffset }, "blend mode", ColorF_Yellow);
            }

            // draw buttons
            {
                yOffset -= AsciiGlyph::Height * 2;
                auto xExtraOffset = 0;
                for (auto i = 0; i < BlendButtonCount; i++)
                {
                    auto& button = blendModeGroup[i];
                    button.position = Vector2Int{ SecondaryHorizontalOffset + xExtraOffset, yOffset };
                    button.Update(timestep);
                    button.Render(m_Serface);

                    xExtraOffset += (button.text.size() + 4) * AsciiGlyph::Width;
                }
            }
        }

        // load model
        {
            // tip
            {
                yOffset -= AsciiGlyph::Height * 2;

                AsciiGlyph::Render(m_Serface, Vector2Int{ SecondaryHorizontalOffset, yOffset }, "load extern meshes", ColorF_Yellow);
            }

            {
                yOffset -= AsciiGlyph::Height * 2;

                static Button button = {
                    "Open..",
                    []() {
                        auto path = FileDialog::Open(L"(*.txt)\0*.txt\0", L"../Extern/Assets/Models", L"Open File(splits_config.txt)", runtimeContext.window.GetHandle());

                        auto loaded = MeshArray::Load(path);
                        if (loaded)
                        {
                            Allocator::Release(Sample);
                            Sample = loaded;
                        }
                    }
                };

                button.position = Vector2Int{ SecondaryHorizontalOffset, yOffset };
                button.Update(timestep);
                button.Render(m_Serface);
            }
        }
    }
}
#pragma endregion