#include "FuelItem.hpp"
#include "Game.hpp"

FuelItem::FuelItem(Level* pLevel, int x, int y)
{
	m_pLevel = pLevel;

	m_pos = clan::Vec2f(x, y);
	m_canvas = clan::Canvas(Game::get_window());
	m_pickedUp = false;

	m_sprite = clan::Sprite::resource(m_canvas, "fuelTank", Game::get_resource_manager());
}


void FuelItem::update(float delta)
{
	Player* player = m_pLevel->get_player();

	if(m_pos.distance(player->get_position()) < 40)
		player->pickup_fuel(this);
}


void FuelItem::draw()
{
	m_sprite.draw(m_canvas, m_pos.x, m_pos.y);
}