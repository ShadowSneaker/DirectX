#include "Puppet.h"


CPuppet::CPuppet(SObjectBase Core)
	:CWorldObject::CWorldObject{ Core }
{
	//SetupInput(GetInputManager())
}


CPuppet::~CPuppet()
{
	CWorldObject::~CWorldObject();
}


void CPuppet::Update()
{
	CWorldObject::Update();
}