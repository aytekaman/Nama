#include "component.h"

Component::Component()
{
	m_isEnabled = true;
}

void Component::Enable()
{
	// behaviour subclass is more suitable for this though...
	m_isEnabled = true;
}

void Component::Disable()
{
	m_isEnabled = false;
}

void Component::SetGameObject( GameObject*& gameObject )
{
	m_gameObject = gameObject;
}