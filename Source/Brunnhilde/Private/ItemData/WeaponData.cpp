// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData/WeaponData.h"

UWeaponData::UWeaponData( UWeaponData* WeaponData ) : UItemData( WeaponData )
{
    Damage = WeaponData->Damage;
}
