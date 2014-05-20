#pragma once

#include "precomp.hpp"


class FuelItem
{
	private:

		// Variables
		//

		clan::Canvas m_canvas;
		clan::Vec2f m_pos;
		clan::Sprite m_sprite;

	public:

		// Methods
		//

		FuelItem(int x, int y);

		void update(float);
		void draw();
};