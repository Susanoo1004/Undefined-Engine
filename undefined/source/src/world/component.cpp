#include "world/component.h"

#include "world/object.h"

Component::~Component()
{
}

void Component::Enable()
{
	mIsEnable = true;
}

void Component::Disable()
{
	mIsEnable = false;
}

const bool Component::IsEnable() const
{
	return mIsEnable;
}

void Component::Start()
{
}

void Component::FixedUpdate()
{
}

void Component::Update()
{
}

void Component::LateUpdate()
{
}

void Component::Draw()
{
}

void Component::PostDraw()
{
}

void Component::OnEnable()
{
}

void Component::OnDisable()
{
}
