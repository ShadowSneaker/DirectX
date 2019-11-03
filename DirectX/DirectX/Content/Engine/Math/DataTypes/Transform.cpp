#include "Transform.h"


STransform::STransform(const SVector InLocation, const SQuaternion InRotation, const SVector InScale)
	:Location{ InLocation }, Rotation{ InRotation }, Scale{ InScale }
{}


STransform::~STransform()
{
	for (uint i = 0; i < Children.size(); ++i)
	{
		Children[i]->SetParent(Parent);
	}

	RemoveFromParent();
}


inline void STransform::RemoveFromParent()
{
	if (Parent)
	{
		for (uint i = 0; i < Parent->GetChildren().size(); ++i)
		{
			if (Parent->GetChildren()[i] == this)
			{
				Parent->GetChildren().erase(Parent->GetChildren().begin() + i);
				return;
			}
		}

		Parent = nullptr;
	}
}


inline void STransform::SetParent(STransform* Transform)
{
	// Make sure children don't snap to the local position of their new parent
	// but instead retain the same location in worldspace, but change their local position.

	RemoveFromParent();
	Parent = Transform;

	// Add a reference to the parent of this instance.
	if (Parent)
	{
		Parent->GetChildren().push_back(this);
	}
}