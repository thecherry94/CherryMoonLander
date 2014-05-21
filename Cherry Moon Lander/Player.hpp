#pragma once

#include "precomp.hpp"
#include "Level.hpp"
#include "FuelItem.hpp"

class Level;
class FuelItem;
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
		int m_hp;
		float m_thrust;
		float m_mass;
		float m_fuelCurrent;
		float m_fuelMax;
		float m_fuelConsumption;

		clan::Slot slot_collision_begin;
		clan::Slot slot_collision_end;
		
		// Methods
		//

		void setup_physics();
		void on_collision_start(clan::Body);
		void on_collision_end(clan::Body);

	public:

		// Methods
		//

		Player(Level*);


		void update(float);
		void draw();

		void pickup_fuel(FuelItem*);


		// Getter & Setter
		//
		clan::Vec2f get_position() { return m_position; }
		int get_health() { return m_hp; }
		float get_thrust() { return m_thrust; }
		float get_mass() { return m_mass; }
		float get_fuel_current() { return m_fuelCurrent; }
		float get_fuel_max() { return m_fuelMax; }
		float get_fuel_consumption() { return m_fuelConsumption; }
		clan::Angle get_angle() { return m_physicsBody.get_angle(); }
};