#pragma once

#pragma once
#include "Object.h"
#include "Interface.h"

#include "StopCommandable.generated.h"

/**
*
*/
UINTERFACE(BlueprintType)
class RTS_API UStopCommandable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class RTS_API IStopCommandable
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Commandable")
		void Stop();
};