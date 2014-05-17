#pragma once

#include <ctime>

#include "precomp.hpp"
#include "FuelItem.hpp"


class Level
{
	friend Level;

	private:

		// Variables
		//

		std::string m_levelName;

		clan::Canvas m_canvas;
		clan::InputDevice m_keyboard;
		clan::InputDevice m_mouse;
		clan::Size m_levelSize;
		clan::PhysicsWorld m_physicsWorld;
		clan::Sprite m_levelSprite;
		clan::CollisionOutline m_levelCollisionOutline;
		clan::Body m_levelPhysicsBody;
		clan::Point m_levelSpawnPoint;
		clan::Rect m_levelEndArea;

		int m_levelRecord;
		int m_levelTimeStart;
		int m_levelTimeEnd;
		bool m_levelActive;

		std::list<FuelItem*> m_fuelItems;

		// Methods
		//

		Level(std::string);

		void setup_physics(float);
		void setup_body();

	public:

		// Methods
		//

		static Level* load(std::string);
		void update(float);
		void draw();


		// Getter & Setter
		//

		clan::CollisionOutline& get_collision_outline() { return m_levelCollisionOutline; }
		clan::Body& get_physics_body() { return m_levelPhysicsBody; }
		clan::PhysicsWorld& get_physics_world() { return m_physicsWorld; }
		clan::Size get_size() { return m_levelSize; }
		int get_start_time() { return m_levelTimeStart; }
		int get_end_time() { return m_levelTimeEnd; }
		int get_elapsed_time() { return m_levelTimeEnd - m_levelTimeStart; }

};