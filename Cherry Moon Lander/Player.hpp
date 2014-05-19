#pragma once

#include "precomp.hpp"
#include "Level.hpp"

class Level;
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
		clan::CollisionOutline m_collisionOutline;
		clan::Body m_physicsBody;

		bool m_acceptInput;
		float m_thrust;
		float m_mass;

		clan::Slot slot_collision_begin;

		// Methods
		//

		void setup_physics();
		void on_collision_start(clan::Body);

	public:

		// Methods
		//

		Player(Level*);


		void update(float);
		void draw();

};