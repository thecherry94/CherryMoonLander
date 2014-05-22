#pragma once

#include "precomp.hpp"


class Game
{
	private:

		// Variables
		//

		static clan::PhysicsWorld m_physicsWorld;
		static clan::ResourceManager m_resourceManager;
		static clan::DisplayWindow m_window;
		static bool m_quit;

		clan::Callback<void()> cb_window_close;

		// Methods
		//

		void setup_window();
		void setup_physics();

		// Events
		//
		void on_window_close();

	public:

		Game();


		// Methods
		//

		void start();
		static void commence_quit_application();


		// Getter & Setter
		//
		static clan::PhysicsWorld& get_physics_world() { return m_physicsWorld; }

		static clan::DisplayWindow& get_window() { return m_window; }

		static clan::ResourceManager& get_resource_manager() { return m_resourceManager; }
};