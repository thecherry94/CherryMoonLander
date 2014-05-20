#include "FuelItem.hpp"
#include "Game.hpp"

FuelItem::FuelItem(int x, int y)
{
	m_pos = clan::Vec2f(x, y);
	m_canvas = clan::Canvas(Game::get_window());

	m_sprite = clan::Sprite::resource(m_canvas, "fuelTank", Game::get_resource_manager());
}


void FuelItem::update(float delta)
{
	
}


void FuelItem::draw()
{
	m_sprite.draw(m_canvas, m_pos.x, m_pos.y);
}