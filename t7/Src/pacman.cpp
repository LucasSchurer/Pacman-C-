//=====================================//
//               					   //
//				 PACMAN 			   //
//									   //
//=====================================//

#include "Headers/pacman.hpp"

void draw_pacman (Pacman* pacman, int scr_wdt, int scr_hgt, sf::RenderWindow * window, char ** map)
{
	pacman->move();
	window->draw(pacman->sprite);
}

void initialize_pacman(Pacman* pacman, int scr_wdt, int scr_hgt)
{
	// Pacman vai ser um quadrado por enquanto.
	pacman->c.x    =  1*scr_wdt/28;
	pacman->c.y    =  32*scr_hgt/36; 

	pacman->size_x = scr_wdt/28;
	pacman->size_y = scr_hgt/36; 
	pacman->speed  = 2; 

	pacman->status = 0;	  // Inicia como morto, quando começa o jogo muda a variável para 1.	
	pacman->move_dir = 0;
	pacman->actual_frame = 0;
	pacman->fps_counter = 0;

	pacman->texture.loadFromFile("../Texture/pacman.png");
	pacman->sprite.setTexture(pacman->texture);
	pacman->sprite.setTextureRect(sf::IntRect(0, pacman->actual_frame, 20, 20));
	pacman->sprite.setScale(scr_wdt/580.0, scr_hgt/720.0);
	pacman->sprite.setPosition(pacman->c.x, pacman->c.y);
}