#include "LedEffect.hpp"

LedEffect::LedEffect(TM1638plus *module) : module(module)
{
}

LedEffect::~LedEffect()
{
    this->module = nullptr;
}