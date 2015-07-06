#include "poiesis/components/ComplexityComponent.h"

ComplexityComponent::ComplexityComponent(int maxComplexity) :
    complexity(0), maxComplexity(maxComplexity)
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

int ComplexityComponent::GetMaxComplexity()
{
    return maxComplexity;
}

void ComplexityComponent::SetMaxComplexity(int maxComplexity)
{
    this->maxComplexity = maxComplexity;
}