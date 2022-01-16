#pragma once

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

class ControllerComponent : public Component
{
public:
	ControllerComponent(class DynamicActor* actor);

	void ProcessInput(const uint8_t* keyState) override;
	void Update(float delta) override;

	bool IsGrounded(); // todo implement in dynamic actor

	int GetLeft() const { return mLeft; }
	int GetRight() const { return mRight; }
	int GetJump() const { return mJump; }
	int GetShoot() const { return mShoot; }
	int GetCrouch() const { return mCrouch; }
	void SetLeft(SDL_Scancode key) { mLeft = key; }
	void SetRight(SDL_Scancode key) { mRight = key; }
	void SetJump(SDL_Scancode key) { mJump = key; }
	void SetShoot(SDL_Scancode key) { mShoot = key; }
	void SetCrouch(SDL_Scancode key) { mCrouch = key; }

private:
	ButtonState GetKeyState(SDL_Scancode key) const;
	ButtonState GetMouseButtonState(int button) const;

	float mCooldown, mTimer;
	bool mIsGrounded, mWasGrounded;
	int mNumJumps;
	class DynamicActor* mOwner;
	float mMouseX, mMouseY;
	b2Vec2 mToMouse;
	float mSpeedLim;
	SDL_Scancode mLeft, mRight, mJump, mShoot, mCrouch;
	uint8_t mCurrState[SDL_NUM_SCANCODES], mPrevState[SDL_NUM_SCANCODES];
	Uint32 mCurrMouse, mPrevMouse;
};

class RayCastCallback : public b2RayCastCallback
{
public:
	RayCastCallback() : m_fixture(nullptr) {}

	float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
	{
		m_fixture = fixture;
		m_point = point;
		m_normal = normal;
		m_fraction = fraction;
		return fraction;
	}

	b2Fixture* m_fixture;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	float m_fraction;
};