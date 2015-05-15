#include "bandit/core/Random.h"

Random::Random()
{
    SeedRandomNumberGenerator();
}

void Random::SeedRandomNumberGenerator()
{
    srand(time(NULL));
}