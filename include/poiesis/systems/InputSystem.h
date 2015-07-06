// Gets input from the user.

#ifndef INPUT_SYSTEM_H_
#define INPUT_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/components/ButtonComponent.h"
#include "poiesis/components/CameraComponent.h"
#include "poiesis/components/ColliderComponent.h"
#include "poiesis/components/MoveableComponent.h"
#include "poiesis/components/ParticleComponent.h"

class InputSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);
    bool ProcessButtonClick();
    bool ProcessPlayerImpulse();
    bool HasClickedOnPlayer(Vector mousePosition);
    Vector ConvertWindowToWorldPosition(Vector windowPosition);
    Vector GetCameraPosition();
    float GetCameraHeight();
    bool ProcessParticleForceInput();

  private:
    Vector impulse;
    Vector impulseBegin;
    Vector impulseEnd;
    bool processingImpulse;
};

#endif // INPUT_SYSTEM_H_