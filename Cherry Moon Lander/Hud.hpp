#pragma once

#include "precomp.hpp"
#include "Player.hpp"

class Player;
class Hud
{
	private:

		// Variables
		//

		Player* m_pPlayer;
		clan::Canvas m_canvas;
		clan::Font m_font;

	public:

		// Methods
		//

		Hud(Player*);

		void draw();
};