#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:
	Sprite m_Sprite;

	float m_JumpDuration;  // how long does a jump last

	bool m_IsJumping;
	bool m_IsFalling;

	bool m_LeftPressed;
	bool m_RightPressed;

	float m_TimerThisJump;  // how long has this lasted so far

	bool m_JustJumped = false;  // has the player initiated a jump

private:
	float m_Gravity;  // what is the gravity

	float m_Speed = 400;  // how fast is the character

	Vector2f m_Position;

	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	Texture m_Texture;

public:
	void spawn(Vector2f startPosition, float gravity);
	
	bool virtual handleInput() = 0;  // this is a pure virtual function

	FloatRect getPosition();  // where is the player

	// A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();
	
	Sprite getSprite();  // send a copy of the sprite to main

	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	Vector2f getCenter();  // center of the character

	void update(float elapsedTime);
};  // end of the class