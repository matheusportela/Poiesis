// Random number generation methods.

#ifndef RANDOM_H_
#define RANDOM_H_

#include <ctime>
#include <cstdlib>

class Random
{
  public:
    Random();

  private:
    void SeedRandomNumberGenerator();
};

#endif // RANDOM_H_