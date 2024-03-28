#include <Deimos/ImGui/ImGuiLayer.h>

#include "iostream"
#include "Deimos.h"
#include "imgui/imgui.h"

class ExampleLayer : public Deimos::Layer { // why here?
public:
    ExampleLayer() : Layer("Example") {}

    void onUpdate() override {
        DM_INFO("ExampleLayer::Update");
    }

    virtual  void onImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!");
        ImGui::End();
    }

    void onEvent(Deimos::Event& event) override {
        DM_TRACE("{0}", event);
    }
};

class Sandbox : public Deimos::Application {
public:
    Sandbox() {
        pushLayer(new ExampleLayer);
    }

    ~Sandbox(){

    }
};


Deimos::Application *Deimos::createApplication() {
    return new Sandbox();
}

