//=====================================//
//               					   //
//			 USER INTERFACE 		   //
//									   //
//=====================================//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <fstream>
#include <list>
#include <iostream>
#include <string>

struct Score
{
	std::string name;
	int value;
};

// Função principal para desenhar o menu.
int draw_menu (sf::RenderWindow * window, sf::Font * font, int scr_wdt, 
				int scr_hgt, int * menu_option, sf::Sound *audio_enter);

// Desenha o menu das pontuações.
int draw_scores (sf::RenderWindow * window, sf::Font * font, int scr_wdt, 
				int scr_hgt, int * menu_option, sf::Sound * audio_enter, std::vector <Score> * scores);

// Cria a lista com as pontuações.
void get_score_list(std::ifstream * input, std::vector <Score> * scores);