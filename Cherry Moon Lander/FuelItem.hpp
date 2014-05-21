#pragma once

#include "precomp.hpp"
#include "Level.hpp"
#include "Player.hpp"

class Level;
class Player;
class FuelItem
{
	private:

		// Variables
		//

		Level* m_pLevel;

		clan::Canvas m_canvas;
		clan::Vec2f m_pos;
		clan::Sprite m_sprite;

		bool m_pickedUp;

	public:

		// Methods
		//

		FuelItem(Level*, int, int);

		void update(float);
		void draw();


		bool get_picked_up() { return m_pickedUp; }
		void set_picked_up(bool b) { m_pickedUp = b; }
};