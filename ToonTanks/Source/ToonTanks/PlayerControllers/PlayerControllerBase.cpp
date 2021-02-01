// Copyright © Christophe Savard 2021

#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabled(bool bEnabled)
{
    bShowMouseCursor = bEnabled;

    if (bEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
}
