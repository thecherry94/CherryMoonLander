#pragma once

#include "precomp.hpp"
#include "Level.hpp"


class Player
{
	private:

		// Variables
		//
		Level* m_pLevel;

		clan::Vec2f m_position;
		clan::Vec2f m_speed;
		clan::PhysicsWorld m_physicsWorld;
		clan::Canvas m_canvas;
		clan::InputDevice m_keyboard;
		clan::InputDevice m_mouse;
		clan::Sprite m_sprite;

		bool m_acceptInput;
		float m_acceleration;


		// Methods
		//


	public:

		// Methods
		//

		Player(clan::Vec2f, Level*);

};