#include "Transform.h"
#include "Matrix.h"



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


STransform STransform::GetWorldTransform() const
{
	//STransform Transform;
	//Transform.Location = ((Parent) ? Parent->GetWorldTransform().Location : SVector{ 0.0 }) + Location;
	//Transform.Rotation = ((Parent) ? Parent->GetWorldTransform().Rotation : SQuaternion{ 0.0 }) + Rotation;
	//Transform.Scale = ((Parent) ? Parent->GetWorldTransform().Scale : SVector{ 1.0 }) * Scale;
	//return Transform;

	SMatrix4 ParentMat;
	ParentMat.Identity();
	if (Parent) ParentMat = Parent->GetWorldTransform();
	
	SMatrix4 ScaleMat;
	SMatrix4 RotationMat;
	SMatrix4 LocationMat;
	
	ScaleMat.ToScale(Scale);
	RotationMat.ToRotation(Rotation);
	LocationMat.ToTranslation(Location, 1.0f);
	
	SMatrix4 Local{ ScaleMat * RotationMat * LocationMat };
	//SMatrix4 Local{ LocationMat * RotationMat * ScaleMat };
	
	
	Local = ParentMat * Local;
	//Local = Local * ParentMat;
	
	// Convert the world matrix to a transform.
	return Local.GetTransform();
}