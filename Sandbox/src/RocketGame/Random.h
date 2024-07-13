#pragma once

#include <random>

class Random {
public:
    static void init() {
        s_randomEngine.seed(std::random_device()());
    }

    static float Float() {
        return s_distribution(s_randomEngine);
    }
private:
    static std::mt19937 s_randomEngine;
    static std::uniform_real_distribution<float> s_distribution;
};