#include "Player.hpp"
#include "Game.hpp"

Player::Player(Level* pLevel)
{
	m_pLevel = pLevel;

	clan::DisplayWindow win = Game::get_window();
	m_canvas = clan::Canvas(win);
	m_keyboard = win.get_ic().get_keyboard();
	m_mouse = win.get_ic().get_mouse();

	m_acceptInput = false;

	m_thrust = m_pLevel->get_player_thrust();
	m_position = m_pLevel->get_spawn_point();
	m_mass = m_pLevel->get_player_mass();
	m_fuelCurrent = m_pLevel->get_start_fuel();
	m_fuelMax = m_fuelCurrent;
	m_fuelConsumption = m_pLevel->get_fuel_consumption();
	m_hp = 100;

	m_speed = clan::Vec2f(0, 0);
	m_physicsWorld = m_pLevel->get_physics_world();
	m_sprite = clan::Sprite::resource(m_canvas, "playerShip", Game::get_resource_manager());
	m_collisionOutline = m_sprite.create_collision_outline(m_canvas, 128, clan::OutlineAccuracy::accuracy_poor);

	setup_physics();
	m_physicsBody.set_position(m_position);
	m_physicsBody.set_angle(clan::Angle::from_degrees(0));

	slot_collision_begin = m_physicsBody.sig_begin_collision().connect(this, &Player::on_collision_start);
}


void Player::setup_physics()
{
	clan::PhysicsContext pc = m_physicsWorld.get_pc();

	clan::BodyDescription body_desc(m_physicsWorld);
	body_desc.set_type(clan::BodyType::body_dynamic);
	m_physicsBody = clan::Body(pc, body_desc);

	//clan::ChainShape outline_shape(m_physicsWorld);
	//outline_shape.create_loop(m_collisionOutline);
	
	clan::PolygonShape outline_shape(m_physicsWorld);
	outline_shape.set_as_box(m_sprite.get_width()/2.0f, m_sprite.get_height()/2.0f);

	clan::FixtureDescription fix_desc(m_physicsWorld);
	fix_desc.set_shape(outline_shape);
	fix_desc.set_restitution(0.2f);
	fix_desc.set_friction(0.01f);
	fix_desc.set_density(m_mass);

	clan::Fixture(pc, m_physicsBody, fix_desc);
}


void Player::update(float delta)
{
	m_position = m_physicsBody.get_position();
	m_sprite.set_angle(m_physicsBody.get_angle());


}


void Player::draw()
{
	
	m_sprite.draw(m_canvas, m_physicsBody.get_position().x, m_physicsBody.get_position().y);
}


void Player::on_collision_start(clan::Body body)
{

}