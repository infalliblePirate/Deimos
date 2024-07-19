#include "Deimos.h"

#include "Deimos/Core/EntryPoint.h"

#include "Sandbox2D.h"
#include "ExampleLayer.h"
#include "RocketGame/GameLayer.h"
#include "ProceduralAnimation/MainLayer.h"

class Sandbox : public Deimos::Application {
public:
    Sandbox() {
        pushLayer(new MainLayer());
    }

    ~Sandbox() {

    }
};


Deimos::Application *Deimos::createApplication() {
    return new Sandbox();
}
