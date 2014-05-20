#include "Game.hpp"
#include "Level.hpp"


Game::Game()
{
	setup_window();
	setup_physics();
	m_resourceManager = clan::XMLResourceManager::create(clan::XMLResourceDocument("resources.xml"));
	m_quit = false;

	m_slotOnExit = m_window.sig_window_close().connect(this, &Game::on_window_close);
}


void Game::setup_window()
{
	clan::DisplayWindowDescription desc;
	//desc.set_position(clan::Rect(-800, 100, 0, 700), true);
	desc.set_size(clan::Size(800, 600), true);
	desc.set_allow_resize(false);
	desc.set_multisampling(4);
	desc.set_title("Cherry Moon Lander - v0.1 Beta");
	desc.set_refresh_rate(144);

	m_window = clan::DisplayWindow(desc);
}


void Game::setup_physics()
{
	clan::PhysicsWorldDescription desc;
	desc.set_gravity(0.0f, 10.0f);
	desc.set_sleep(true);
	desc.set_physic_scale(100);
	desc.set_timestep(1.0f / 60.0f);
	desc.set_velocity_iterations(8);
	desc.set_position_iterations(3);

	m_physicsWorld = clan::PhysicsWorld(desc);
}


void Game::commence_quit_application()
{
	m_quit = true;
}


void Game::start()
{
	clan::GameTime time;

	Level* pTestlevel = Level::load("testlevel");

	while(!m_quit)
	{
		time.update();

		m_window.get_gc().clear(clan::Colorf::blue);

		// -----------------------
		// Main Game execution
		// -----------------------

		pTestlevel->update(time.get_time_elapsed());
		pTestlevel->draw();

		m_window.flip(1);
		clan::KeepAlive::process();
	}

	delete(pTestlevel);
	pTestlevel = NULL;
}


void Game::on_window_close()
{
	commence_quit_application();
}



clan::DisplayWindow Game::m_window;
clan::PhysicsWorld Game::m_physicsWorld;
clan::ResourceManager Game::m_resourceManager;
bool Game::m_quit;