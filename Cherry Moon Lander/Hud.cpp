#include "Hud.hpp"
#include "Game.hpp"


Hud::Hud(Player* pPlayer)
{
	m_pPlayer = pPlayer;
	m_canvas = clan::Canvas(Game::get_window());

	clan::FontDescription font_desc;
	font_desc.set_typeface_name("acI");
	font_desc.set_anti_alias(false);
	font_desc.set_height(28);
	m_font = clan::Font(m_canvas, font_desc, "ARCADE_I.TTF");
}


void Hud::draw()
{
	int offset_x = 20;
	int offset_y = 20;
	int spacing = 40;

	// Draw Health
	//
	m_canvas.draw_box(clan::Rect(offset_x, offset_y, clan::Size(100, 20)), clan::Colorf::lightgreen);
	m_canvas.fill_rect(clan::Rect(offset_x, offset_y, clan::Size(m_pPlayer->get_health(), 20)), clan::Colorf::lightgreen);
	m_font.draw_text(m_canvas, clan::Pointf(140, 40),clan::StringHelp::int_to_text(m_pPlayer->get_health()) + "/100 Health", clan::Colorf::lightgreen);


	// Draw Fuel
	//
	m_canvas.draw_box(clan::Rect(offset_x, offset_y + spacing, clan::Size(100, 20)), clan::Colorf::lightgreen);
	m_canvas.fill_rect(clan::Rect(offset_x, offset_y + spacing, clan::Size(m_pPlayer->get_fuel_current() / m_pPlayer->get_fuel_max() * 100.0f, 20)), clan::Colorf::lightgreen);
	m_font.draw_text(m_canvas, clan::Pointf(140, 80), clan::StringHelp::int_to_text(m_pPlayer->get_fuel_current()) + "/" + clan::StringHelp::int_to_text(m_pPlayer->get_fuel_max()) + " Fuel", clan::Colorf::lightgreen);

	// Draw Rotation
	//
	m_font.draw_text(m_canvas, clan::Pointf(500, 40), clan::StringHelp::int_to_text(((int)m_pPlayer->get_angle().to_degrees()) % 360), clan::Colorf::lightgreen);
}