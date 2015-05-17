// Random number generation methods.

#ifndef RANDOM_H_
#define RANDOM_H_

#include <ctime>
#include <cstdlib>

#include "bandit/core/Log.h"

class Random
{
  public:
    Random();

    // Generates random integer from 0 to RAND_MAX (at least 32767).
    int GenerateInt();

    // Generates random integer from minimum to maximum values, not inclusive.
    int GenerateInt(int min, int max);

    // Generates random real number from 0 to 1.
    float GenerateFloat();

    // Generates random real number from minimum to maximum values, not
    // inclusive.
    float GenerateFloat(float min, float max);

  private:
    void SeedRandomNumberGenerator();
};

#endif // RANDOM_H_