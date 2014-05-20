#pragma once

#include <ctime>

#include "precomp.hpp"
#include "FuelItem.hpp"
#include "Player.hpp"
#include "Hud.hpp"

class Player;
class Hud;
class Level
{
	friend Level;

	private:

		// Variables
		//

		Player* m_pPlayer;
		Hud* m_pHud;

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
		int m_playerStartFuel;
		float m_playerMass;
		float m_playerThrust;
		float m_playerFuelConsumption;
		bool m_levelActive;

		std::list<FuelItem*> m_fuelItems;

		// Methods
		//

		Level(std::string);

		void setup_physics(float);
		void setup_body();



		clan::Slot slot_collision_begin;
		clan::Slot slot_collision_end;
		void on_collision_start(clan::Body);
		void on_collision_end(clan::Body);

	public:

		// Methods
		//

		~Level();

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

		clan::Vec2f get_spawn_point() { return m_levelSpawnPoint; }
		clan::Rect get_end_area() { return m_levelEndArea; }
		int get_start_fuel() { return m_playerStartFuel; }
		float get_fuel_consumption() { return m_playerFuelConsumption; }
		float get_player_mass() { return m_playerMass; }
		float get_player_thrust() { return m_playerThrust; }

};