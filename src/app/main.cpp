#include "application.h"
#include <imgui.h>

#include <iostream>
#include <math.h>
#include <deque>
#include <chrono>


class TestApp : public Application
{
#define COLOR_OUT    nvgRGBA(220,50,50,255)
#define COLOR_IN     nvgRGBA(50,50,220,255)
#define COLOR_SOLVED nvgRGBA(50,220,50,255)


public:

    TestApp(int w, int h, const char * title) : Application(title, w, h) {
        
        ImGui::StyleColorsClassic();
        
        const char* name = IMGUI_FONT_FOLDER"/Cousine-Regular.ttf";
        nvgCreateFont(vg, "sans", name);
        
    }

    void process() override {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration_cast<std::chrono::microseconds>(now-lastFrame).count() >= 10./60. * 1.e6)
        {
            if(keyDown[GLFW_KEY_ESCAPE])
                exit(0);
            lastFrame = now;
        }
    }

    void drawImGui() override {

        using namespace ImGui;

       const char* method_names[] = {"A*", "RRT*", "Dijkstra"};
    //    const char* scheme_names[] = {"Explicit Euler", "Symplectic Euler", "Explicit Midpoint"};
       Begin("Menu");
    //    Text("Hello world");
        PushItemWidth(100);
       InputFloat("x", &x_pos);
       SameLine();
       InputFloat("y", &y_pos);
       SameLine();
       InputFloat("z", &z_pos);
       Combo("Path Planning Algorithm", (int*)&currentAlgorithm, method_names, 3);
       Button("Start flight");
    //    Combo("Integration Scheme", (int*)&currentScheme, scheme_names, 3);
       End();
    }

    void drawNanoVG() override {
        
    }

protected:
    void mouseButtonPressed(int button, int mods) override {

    }

    void mouseButtonReleased(int button, int mods) override {
        
    }

private:
    int loadFonts(NVGcontext* vg)
    {
        int font;
        font = nvgCreateFont(vg, "sans", "../example/Roboto-Regular.ttf");
        if (font == -1) {
            printf("Could not add font regular.\n");
            return -1;
        }
        font = nvgCreateFont(vg, "sans-bold", "../example/Roboto-Bold.ttf");
        if (font == -1) {
            printf("Could not add font bold.\n");
            return -1;
        }
        return 0;
    }

private:

    // MethodTypes currentMethod = RANDOM;
    // IntegrationScheme currentScheme = EXPLICIT;
    int* currentAlgorithm;
    float x_pos, y_pos, z_pos;

    // Boids boids = Boids(40, currentMethod);
    std::chrono::high_resolution_clock::time_point lastFrame;
};

int main(int, char**)
{
    int width = 720;
    int height = 720;
    TestApp app(width, height, "Raptor GUI");
    app.run();

    return 0;
}
