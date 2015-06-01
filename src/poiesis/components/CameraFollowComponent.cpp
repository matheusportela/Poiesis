#include "poiesis/components/CameraFollowComponent.h"

CameraFollowComponent::CameraFollowComponent(bool enabled) :
    enabled(enabled)
{
}

std::string CameraFollowComponent::GetComponentClass()
{
    return "CameraFollowComponent";
}

bool CameraFollowComponent::GetEnabled()
{
    return enabled;
}

void CameraFollowComponent::SetEnabled(bool enabled)
{
    this->enabled = enabled;
}
