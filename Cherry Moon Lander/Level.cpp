#include "Level.hpp"
#include "Game.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

Level::Level(std::string folderName) 
{
	clan::DisplayWindow win = Game::get_window();

	m_canvas = clan::Canvas(win);
	m_keyboard = win.get_ic().get_keyboard();
	m_mouse = win.get_ic().get_mouse();

	m_levelSprite = clan::Sprite(m_canvas, "level/" + folderName + "/level.png");
	m_levelSize = clan::Size(m_levelSprite.get_width(), m_levelSprite.get_height());
	m_levelCollisionOutline = m_levelSprite.create_collision_outline(m_canvas);


	std::string path = "level/" + folderName + "/properties.xml";
	rapidxml::file<> xml_file(path.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(xml_file.data());

	rapidxml::xml_node<>* root_node = doc.first_node("Level");

	// player specific data
	float gravity = .0f;
	float player_mass = .0f;
	float player_thrust = .0f;
	int start_fuel = 0;
	int fuel_consumption = 0;


	m_levelName = folderName;
	m_levelActive = false;
	m_fuelItems = std::list<FuelItem*>();

	// Load single values from xml
	m_levelRecord = atoi(root_node->first_node("Record")->value());
	gravity = (float)atof(root_node->first_node("Gravity")->value());
	m_playerMass = (float)atof(root_node->first_node("PlayerMass")->value());
	m_playerThrust = (float)atof(root_node->first_node("PlayerThrust")->value());
	m_levelSpawnPoint = clan::Point(
		atoi(root_node->first_node("SpawnPoint")->first_attribute("X")->value()),
		atoi(root_node->first_node("SpawnPoint")->first_attribute("Y")->value()));
	m_levelEndArea = clan::Rect(
		atoi(root_node->first_node("EndArea")->first_attribute("X")->value()),
		atoi(root_node->first_node("EndArea")->first_attribute("Y")->value()),
		clan::Size(
			atoi(root_node->first_node("EndArea")->first_attribute("W")->value()),
			atoi(root_node->first_node("EndArea")->first_attribute("H")->value())));
	m_playerStartFuel = atoi(root_node->first_node("StartFuel")->value());
	m_playerFuelConsumption = atoi(root_node->first_node("FuelConsumption")->value());


	// Load fuel items from xml	
	rapidxml::xml_node<>* fuelNode = root_node->first_node("Fuel");
	for(rapidxml::xml_node<>* fuelItemNode = fuelNode->first_node(); fuelItemNode != NULL; fuelItemNode = fuelNode->next_sibling())
	{
		m_fuelItems.push_back(new FuelItem(
			atoi(fuelItemNode->first_attribute("X")->value()),
			atoi(fuelItemNode->first_attribute("Y")->value())));

		if(fuelItemNode == fuelNode->last_node())
			break;
	}
	

	doc.clear();

	setup_physics(gravity);
	setup_body();

	m_pPlayer = new Player(this);
	m_pHud = new Hud(m_pPlayer);
}


Level::~Level()
{
	delete(m_pPlayer);
	m_pPlayer = NULL;
}


void Level::update(float delta)
{
	m_physicsWorld.step();

	m_pPlayer->update(delta);
	m_levelSprite.set_angle(m_levelPhysicsBody.get_angle());
}

void Level::draw()
{
	m_levelSprite.draw(m_canvas, m_levelPhysicsBody.get_position().x, m_levelPhysicsBody.get_position().y);

	m_pPlayer->draw();
	m_pHud->draw();

	#ifdef __DEBUGMODE__
		m_levelCollisionOutline.draw(0,0, clan::Colorf::red, m_canvas);

		clan::PhysicsDebugDraw debug_draw(m_physicsWorld);
		debug_draw.set_flags(clan::f_shape);
		debug_draw.draw(m_canvas);
	#endif
}


Level* Level::load(std::string folderName)
{
	return new Level(folderName);
}


void Level::setup_body()
{
	clan::PhysicsContext pc = m_physicsWorld.get_pc();
	clan::BodyDescription body_desc(m_physicsWorld);
	body_desc.set_position(0, 0);
	body_desc.set_type(clan::BodyType::body_static);

	m_levelPhysicsBody = clan::Body(pc, body_desc);

	clan::ChainShape body_shape(m_physicsWorld);
	body_shape.create_loop(m_levelCollisionOutline);

	clan::FixtureDescription fix_desc(m_physicsWorld);
	fix_desc.set_shape(body_shape);
	fix_desc.set_restitution(0.1f);
	fix_desc.set_friction(0.05f);
	fix_desc.set_density(1000.0f);
	
	clan::Fixture body_fixture(pc, m_levelPhysicsBody, fix_desc);
}


void Level::setup_physics(float gravity)
{
	clan::PhysicsWorldDescription desc;
	desc.set_gravity(0.0f, gravity);
	desc.set_sleep(false);
	desc.set_physic_scale(100);
	desc.set_timestep(1.0f / 60.0f);
	desc.set_velocity_iterations(8);
	desc.set_position_iterations(10);

	m_physicsWorld = clan::PhysicsWorld(desc);
}