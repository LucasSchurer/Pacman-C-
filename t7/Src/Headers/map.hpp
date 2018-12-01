//=====================================//
//               					   //
//				GAME MAP 			   //
//									   //
//=====================================//

#include <SFML/Graphics.hpp>

#include "pacman.hpp"

struct Node
{
	Point pos;
	int number;
	std::string target;

	std::list <Node> adj;

	Point tile_position(int scr_wdt, int scr_hgt)
	{
		Point aux;

		aux.x = scr_wdt/this->pos.x;
		aux.y = scr_hgt/this->pos.y;

		return aux;
	};
};

struct Wall
{
	float x;
	float y;
	float size_x;
	float size_y;
	sf::RectangleShape rectangle;
	std::string label;
};

struct GameCircle // Pontos do jogo ou power ups.
{
	float x;
	float y;
	float radius;
	int status;
	sf::CircleShape circle;

	sf::Sprite circle_sprite;
};

void create_map_tiles(Wall ** wall, int scr_wdt, int scr_hgt, char ** map);

// Função principal para desenhar o mapa do jogo.
int draw_map (sf::RenderWindow * window, sf::Font * font, int scr_wdt, 
				int scr_hgt, int * menu_option, Pacman * pacman, Wall ** wall, char ** map);
