#include "iostream"
#include "Deimos.h"

class Sandbox : public Deimos::Application {
public:
    Sandbox() {

    }

    ~Sandbox(){

    }
};

Deimos::Application *Deimos::createApplication() {
    return new Sandbox();
}

