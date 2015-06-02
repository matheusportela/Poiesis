#include "bandit/core/Random.h"

Random::Random()
{
    SeedRandomNumberGenerator();
}

void Random::SeedRandomNumberGenerator()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    // using nano-seconds instead of seconds
    srand((time_t)ts.tv_nsec);
}

int Random::GenerateInt()
{
    return rand();
}

int Random::GenerateInt(int min, int max)
{
    if (max <= min)
    {
        LOG_E("[Random] Maximum value must be greater than minimum value.");
        exit(1);
    }

    return (min + rand()%(max - min));
}

float Random::GenerateFloat()
{
    return GenerateFloat(0, 1);
}

float Random::GenerateFloat(float min, float max)
{
    if (max <= min)
    {
        LOG_E("[Random] Maximum value must be greater than minimum value.");
        exit(1);
    }

    return (min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(max-min))));
}