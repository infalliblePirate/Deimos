#include "iostream"
#include "Deimos.h"

class ExampleLayer : public Deimos::Layer { // why here?
public:
    ExampleLayer() : Layer("Example") {}

    void onUpdate() override {
        DM_INFO("ExampleLayer::Update");
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

