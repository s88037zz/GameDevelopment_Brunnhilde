// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Actions/LockEnemyAbility.h"
#include "BrunnhildeCharacter.h"
void ULockEnemyAbility::Lock()
{
    if( GetControlCharacter() )
    {
        bool IsLockedEnemy = GetControlCharacter()->IsLockedEnemy();
        GetControlCharacter()->SetLockedEnemy( !IsLockedEnemy );
    }
}
