#include "Component.h"


CComponent::CComponent(SComponentInfo Info)
	:CObjectBase::CObjectBase{ Info.Core}
{
	Owner = Info.Object;
}


CComponent::~CComponent()
{}