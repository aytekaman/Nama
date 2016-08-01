#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class GameObject;

class Component
{
public:
	Component();
	~Component(){};

	virtual bool IsEnabled(){ return m_isEnabled; } 

	virtual GameObject* GetGameObject(){ return m_gameObject; }

	virtual void SetGameObject( GameObject*& gameObject );

	virtual void Enable();
	virtual void Disable();

private:
	bool m_isEnabled;

protected:
	GameObject* m_gameObject;
};

#endif