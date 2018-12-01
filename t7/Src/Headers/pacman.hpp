//=====================================//
//               					   //
//				 PACMAN 			   //
//									   //
//=====================================//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>

#include "math.hpp"

struct Pacman 
{
	Point c;

	float size_x;
	float size_y;
	float speed;

	int move_dir; //0 -> cima, 1 -> direita, 2 -> baixo, 3 -> esquerda;
	int status; //0 -> morto, 1 -> vivo // 2 -> power upado
	int actual_frame;
	int fps_counter;

	sf::Sprite sprite;
	sf::Texture texture;

	Point tile_position(char ** map, int scr_wdt, int scr_hgt)
	{	
		Point pos;
		pos.x = scr_wdt/this->c.x;
		pos.y = scr_hgt/this->c.y;

		return pos;
	};

	void move()
	{

		switch(this->move_dir)
		{	
			case 0:		
				this->fps_counter++;
				this->c.y = this->c.y - this->speed;

				if (this->actual_frame == 3)
					this->actual_frame = 0;
				break;
			case 1:		
				this->fps_counter++;
				this->c.x = this->c.x + this->speed;

				if (this->actual_frame == 7)
					this->actual_frame = 4;
				
				break;	
			case 2:		
				this->fps_counter++;
				this->c.y = this->c.y + this->speed;
				
				if (this->actual_frame == 11)
					this->actual_frame = 8;

				break;
			case 3:		
				this->fps_counter++;
				this->c.x = this->c.x - this->speed;
				
				if (this->actual_frame == 15)
					this->actual_frame = 12;

				break;
			case -1:
				this->actual_frame = 0;
				break;
		}

			if  (this->fps_counter%5 == 0)
					this->actual_frame++;


		this->sprite.setTextureRect(sf::IntRect(0, this->actual_frame*20, 20, 20));
		this->sprite.setPosition(this->c.x, this->c.y);
	}
};

// Função que inicializa o pacman.
void initialize_pacman(Pacman* pacman, int scr_wdt, int scr_hgt);
void draw_pacman (Pacman* pacman, int scr_wdt, int scr_hgt, sf::RenderWindow * window, char ** map);