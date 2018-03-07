#include "MainCharacter.h"
#include "Debug.h"
#include "PhysicsEngine.h"
#include "Input.h"
#include "GameStateManager.h"
#include "FloatOperations.h"
#include "GameSettings.h"

MainCharacter::MainCharacter():
	m_characterState {CHARACTER_STATE::IDLE},
	m_additionalGravityMultiplier { 0.f } {

	m_objectTag = "Main";

	// Init shape
	m_shape.setSize(sf::Vector2f{ 30.f, 50.f });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setFillColor(sf::Color::Blue);

	// Create rigid body
	Collider * collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(m_shape.getSize());
	m_colliders.push_back(collider);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(true);
	m_rigidBody->setBounceFactor(0.1f);
	collider->setTrigger(false, m_rigidBody);

	// Init transform
	setPosition(sf::Vector2f{ 10.f, 20.f });
}

MainCharacter::~MainCharacter() {
}

void MainCharacter::update(float _dt) {
	movement(_dt);
	extraGravity(_dt);
	jump(_dt);
}

void MainCharacter::draw() {
	Display::draw(m_shape);
}

void MainCharacter::onCollision(Collider * _other) {
	if (_other->getGameObject()->getObjectTag() == "Floor") {
		m_characterState = CHARACTER_STATE::IDLE;
		m_additionalGravityMultiplier = 0.f;
	}
}

void MainCharacter::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_shape.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(_pos);
	}
}

GameObject * MainCharacter::clone() {
	return nullptr;
}

void MainCharacter::movement(float _dt) {
	float dx = 0.f;

	if (Input::getKey(Input::A)) {
		dx += -m_speed;
		m_direction = -1;
	}

	if (Input::getKey(Input::D)) {
		dx += m_speed;
		m_direction = 1;
	}

	dx *= _dt;

	move(sf::Vector2f{ dx, 0.f });
}

void MainCharacter::extraGravity(float _dt) {
	// Apply extra gravity to character
	sf::Vector2f vel = m_rigidBody->getVelocity();
	vel.y += GameSettings::GRAVITY * m_additionalGravityMultiplier * _dt;
	m_rigidBody->setVelocity(vel);
}

void MainCharacter::jump(float _dt) {
	if (m_characterState == CHARACTER_STATE::IDLE) {
		if (Input::getKeyDown(Input::SPACE)) {
			m_rigidBody->setVelocity(sf::Vector2f{ 0.f, -m_jumpVelocity });
			m_characterState = CHARACTER_STATE::JUMPING;
		}
	}
	
	// Landing
	if (m_characterState == CHARACTER_STATE::JUMPING) {
		if (Input::getKeyUp(Input::SPACE) || m_rigidBody->getVelocity().y > 0) {
			m_additionalGravityMultiplier = m_landingGravityMultiplier;
		}
	}
}

void MainCharacter::shoot(int _direction) {
}
