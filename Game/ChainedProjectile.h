#pragma once
#include "GameObject.h"
#include "Trail.h"
#include "AnimationController.h"

class ChainedProjectile : public GameObject {
	// Visuals
	AnimationController m_controller;

	// References
	GameObject * m_playerRef;
	GameObject * m_hitEnemy;

	// Chain
	Trail * m_chain;

	int m_direction;

	// Game
	bool m_isStatic = false;

	// Parameters
	float m_destructionDelay = 15.f;
public:
	ChainedProjectile(int _direction);
	~ChainedProjectile();

	void destroyChain();
	void pullChain(sf::Vector2f _pullVector);

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

#pragma region Getters and setters
	inline void setPlayerRef(GameObject * _p) { m_playerRef = _p; };
	inline bool isStatic() { return m_isStatic; };
#pragma endregion
};
