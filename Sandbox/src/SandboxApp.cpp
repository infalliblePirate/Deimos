#include "Deimos.h"

#include "Deimos/Core/EntryPoint.h"

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Deimos::Application {
public:
    Sandbox() {
        pushLayer(new Sandbox2D());
        //pushLayer(new ExampleLayer());
    }

    ~Sandbox() {

    }
};


Deimos::Application *Deimos::createApplication() {
    return new Sandbox();
}
