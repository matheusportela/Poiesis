#include "poiesis/components/ComplexityComponent.h"

ComplexityComponent::ComplexityComponent() :
    complexity(0)
{
}

std::string ComplexityComponent::GetComponentClass()
{
    return "ComplexityComponent";
}


int ComplexityComponent::GetComplexity()
{
    return complexity;
}

void ComplexityComponent::SetComplexity(int complexity)
{
    this->complexity = complexity;
}