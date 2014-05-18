#include "Player.hpp"


Player::Player(clan::Vec2f start_pos, Level* pLevel)
{
	m_position = start_pos;
	m_pLevel = pLevel;
}