// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeInfo.h"

FBuzzAroundAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag,
	bool bLogNotFound) const
{
	for (const FBuzzAroundAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FBuzzAroundAttributeInfo();
}
