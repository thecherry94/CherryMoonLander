#include "Player.hpp"
#include "Game.hpp"

Player::Player(Level* pLevel)
{
	m_pLevel = pLevel;

	clan::DisplayWindow win = Game::get_window();
	m_canvas = clan::Canvas(win);
	m_keyboard = win.get_ic().get_keyboard();
	m_mouse = win.get_ic().get_mouse();

	m_acceptInput = true;

	m_thrust = m_pLevel->get_player_thrust();
	m_position = m_pLevel->get_spawn_point();
	m_mass = m_pLevel->get_player_mass();
	m_fuelCurrent = m_pLevel->get_start_fuel();
	m_fuelMax = m_fuelCurrent;
	m_fuelConsumption = m_pLevel->get_fuel_consumption();
	m_hp = 100;
	m_isColliding = false;

	m_speed = clan::Vec2f(0, 0);
	m_physicsWorld = m_pLevel->get_physics_world();
	m_sprite = clan::Sprite::resource(m_canvas, "playerShip", Game::get_resource_manager());
	
	clan::Contour contour;
	int collision_offset = 3;
	contour.get_points().push_back(clan::Pointf(-collision_offset, -collision_offset));
	contour.get_points().push_back(clan::Pointf(-collision_offset, m_sprite.get_height() + collision_offset));
	contour.get_points().push_back(clan::Pointf(m_sprite.get_width() + collision_offset, m_sprite.get_height() + collision_offset));
	contour.get_points().push_back(clan::Pointf(m_sprite.get_width() + collision_offset, -collision_offset));

	m_collisionOutline.get_contours().push_back(contour);
	m_collisionOutline.calculate_radius();
	m_collisionOutline.calculate_sub_circles();

	m_collisionOutline.set_rotation_hotspot(clan::origin_center, m_sprite.get_width() / 2.0f, m_sprite.get_height() / 2.0f);
	//m_collisionOutline.set_alignment(clan::origin_center, m_sprite.get_width() / 2.0f, m_sprite.get_height() / 2.0f);

	setup_physics();
	m_physicsBody.set_position(m_position);
	m_physicsBody.set_angle(clan::Angle::from_degrees(0));


	/*
	cb_begin_collision.set(this, &Player::on_collision_start);
	m_physicsBody.sig_begin_collision().connect(cb_begin_collision);

	cb_end_collision.set(this, &Player::on_collision_end);
	m_physicsBody.sig_end_collision().connect(cb_end_collision);
	*/
}


void Player::setup_physics()
{
	clan::PhysicsContext pc = m_physicsWorld.get_pc();

	clan::BodyDescription body_desc(m_physicsWorld);
	body_desc.set_type(clan::BodyType::body_dynamic);
	body_desc.set_angular_damping(5.0f);
	m_physicsBody = clan::Body(pc, body_desc);

	//clan::ChainShape outline_shape(m_physicsWorld);
	//outline_shape.create_loop(m_collisionOutline);

	/*
	clan::Vec2f vertices[] = { 
		clan::Vec2f(m_sprite.get_width()/4.0f, 0),
		clan::Vec2f(m_sprite.get_width()/2.0f, m_sprite.get_height()/2.0f),
		clan::Vec2f(0, m_sprite.get_height()/2.0f)
	};
	

	clan::Vec2f vertices[] = { 
		clan::Vec2f(-0.001f, 0),
		clan::Vec2f(0.001f, 0.002f),
		clan::Vec2f(0.001f, 0),
		clan::Vec2f(0, 0)
	};
	
	outline_shape.create_loop(vertices, 4);
	*/

	clan::PolygonShape outline_shape(m_physicsWorld);
	outline_shape.set_as_box(m_sprite.get_width()/2.0f, m_sprite.get_height()/2.0f);
	
	clan::FixtureDescription fix_desc(m_physicsWorld);
	fix_desc.set_shape(outline_shape);
	fix_desc.set_restitution(0.0f);
	fix_desc.set_friction(1.0f);
	fix_desc.set_density(m_mass);

	m_physicsBodyFixture = clan::Fixture(pc, m_physicsBody, fix_desc);
}


void Player::update(float delta)
{
	m_position = m_physicsBody.get_position();
	m_speed = m_positionOld - m_position;
	m_sprite.set_angle(m_physicsBody.get_angle());

	m_collisionOutline.set_angle(m_physicsBody.get_angle());
	m_collisionOutline.set_translation(m_position.x - m_sprite.get_width() / 2.0f, m_position.y - m_sprite.get_height() / 2.0f);

 	if(m_acceptInput && m_fuelCurrent > 0 && m_hp > 0)
	{
		if(m_keyboard.get_keycode(clan::keycode_space))
		{
			m_physicsBody.apply_force_to_center(clan::Vec2f(
				cos(m_physicsBody.get_angle().from_degrees(m_physicsBody.get_angle().to_degrees() - 90).to_radians()) * m_thrust, 
				sin(m_physicsBody.get_angle().from_degrees(m_physicsBody.get_angle().to_degrees() - 90).to_radians()) * m_thrust));

			m_fuelCurrent -= m_fuelConsumption * delta;
			if(m_fuelCurrent < 0)
				m_fuelCurrent = 0;
		}



		float torque = 200.0f;

		if(m_keyboard.get_keycode(clan::keycode_right))
		{
			//m_physicsBody.set_angle(m_physicsBody.get_angle().from_degrees(m_physicsBody.get_angle().to_degrees() + 50 * delta));
			m_physicsBody.apply_torque(torque * delta);
		}
		if(m_keyboard.get_keycode(clan::keycode_left))
		{
			//m_physicsBody.set_angle(m_physicsBody.get_angle().from_degrees(m_physicsBody.get_angle().to_degrees() - 50 * delta));
			m_physicsBody.apply_torque(-torque * delta);
		}
	}

	m_positionOld = m_position;

	if (m_collisionOutline.collide(m_pLevel->get_collision_outline()))
	{
		if (!m_isColliding)
		{
			m_isColliding = true;
			on_collision_start();
		}

		while_colliding();
	}
	else
	{
		if (m_isColliding)
		{
			m_isColliding = false;
			on_collision_end();
		}
	}
}


void Player::draw()
{
	m_sprite.draw(m_canvas, m_physicsBody.get_position().x, m_physicsBody.get_position().y);
	
	#ifdef __DEBUGMODE__
		m_collisionOutline.draw(m_collisionOutline.get_translation().x / 800.0f, m_collisionOutline.get_translation().y / 600.0f, clan::Colorf::pink, m_canvas);
	#endif
}


void Player::pickup_fuel(FuelItem* pItem)
{
	m_fuelCurrent = m_fuelMax;
	pItem->set_picked_up(true);
}


void Player::on_collision_start()
{
	float dmg = m_speed.length() * 15;
	if (dmg > 10)
	{
		Game::set_clear_color(clan::Colorf::red);
		m_hp -= dmg;

		if (m_hp < 0)
			m_hp = 0;
	}
}


void Player::on_collision_end()
{
	Game::set_clear_color(clan::Colorf::blue);
}


void Player::while_colliding()
{

}