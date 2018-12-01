//=====================================//
//               					   //
//				GAME MAP 			   //
//									   //
//=====================================//

#include "Headers/map.hpp"

void create_map_tiles(Wall ** wall, int scr_wdt, int scr_hgt, char ** map)
{
	for (int i=0 ; i<scr_hgt/20 ; i++) {
		for (int j=0 ; j<scr_wdt/20 ; j++) {
			wall[i][j].x = j*20;
			wall[i][j].y = i*20;
			wall[i][j].size_x = scr_hgt/20;
			wall[i][j].size_y = scr_wdt/20;
			wall[i][j].rectangle.setScale(scr_wdt/560, scr_hgt/720.0);
			wall[i][j].rectangle.setSize(sf::Vector2f(wall[i][j].size_x, wall[i][j].size_y));
			if (map[i][j] == '0'){
				wall[i][j].rectangle.setFillColor(sf::Color(0, 0, 255));
				wall[i][j].label = "WALL";
			}
			
			else if (map[i][j] == '+') {
				wall[i][j].rectangle.setFillColor(sf::Color(255, 0, 0));
				wall[i][j].label = "NODE";
			}
			
			else
				wall[i][j].rectangle.setFillColor(sf::Color(0, 0, 0));
			wall[i][j].rectangle.setPosition(wall[i][j].x, wall[i][j].y);
		}
	}
}

int draw_map (sf::RenderWindow * window, sf::Font * font, int scr_wdt, 
				int scr_hgt, int * menu_option, Pacman * pacman, Wall ** wall, char ** map)
{ 

	// Fazer
	for (int i=0 ; i<scr_hgt/20 ; i++) {
		for (int j=0 ; j<scr_wdt/20 ; j++) {
			window->draw(wall[i][j].rectangle);
		}
	}

	draw_pacman(pacman, scr_wdt, scr_hgt, window, map);

	return 2; // Segue o jogo;
}