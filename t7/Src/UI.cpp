
//=====================================//
//               					   //
//			 USER INTERFACE 		   //
//									   //
//=====================================//

#include "Headers/UI.hpp"

//-------------------------------------------------------------------------------------------------//

static void initialize_text(sf::Font * font, sf::Text * text, std::string string, 
				 int size, int scr_wdt, int scr_hgt, float x, float y, int color)
{
	text->setFont(*font);

	text->setString(string);
	text->setScale(scr_wdt/1280.0, scr_hgt/720.0);
	
	text->setCharacterSize(size);
	
	switch (color) 
	{
		case 0: 	text->setFillColor(sf::Color::White);  		break; // 0 == branco	
		case 1: 	text->setFillColor(sf::Color::Yellow); 		break; // 1 == Amarelo
		case 2: 	text->setFillColor(sf::Color::Red);    		break; // 2 == Vermelho
	}

	text->setPosition(x, y);
}

//-------------------------------------------------------------------------------------------------//

int draw_menu (sf::RenderWindow * window, sf::Font * font, int scr_wdt, 
				int scr_hgt, int * menu_option, sf::Sound *audio_enter)
{
	sf::Text title, play, scores, exit;
	
	initialize_text(font, &title, "PACMAN", 62, scr_wdt, scr_hgt, scr_wdt/2.8, scr_hgt/10, 1);
	
	if (*menu_option == 0)
		initialize_text(font, &play, "PLAY", 45, scr_wdt, scr_hgt, scr_wdt/2.4, scr_hgt/3.5, 2);
	else
		initialize_text(font, &play, "PLAY", 42, scr_wdt, scr_hgt, scr_wdt/2.4, scr_hgt/3.5, 0);
	if (*menu_option == 1)
		initialize_text(font, &scores, "SCORES", 45, scr_wdt, scr_hgt, scr_wdt/2.4, scr_hgt/2.5, 2);
	else
		initialize_text(font, &scores, "SCORES", 42, scr_wdt, scr_hgt, scr_wdt/2.4, scr_hgt/2.5, 0);
	if (*menu_option == 2)
		initialize_text(font, &exit, "EXIT", 45, scr_wdt, scr_hgt, scr_wdt/2.4, scr_hgt/1.95, 2);
	else
		initialize_text(font, &exit, "EXIT", 42, scr_wdt, scr_hgt, scr_wdt/2.4, scr_hgt/1.95, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		audio_enter->play();		

		switch (*menu_option) 
		{
			case 0:		return 2;  // Jogar;
			case 1:		return 3;  // Mostrar os pontos;
			case 2:		return -1; // Sair;
		}
	}
	
	window->draw(title);
	window->draw(play);
	window->draw(scores);
	window->draw(exit);

	return 1; // Menu segue on;
}

//-------------------------------------------------------------------------------------------------//

void get_score_list(std::ifstream * input, std::vector <Score> * scores)
{
	Score score;
	int tam = 0;
	
	while (*input >> score.value) {		
		input->ignore();
		*input >> score.name;
		
		scores->push_back(score);
		tam++;
	}

	// Bubble sort pra ordenar os scores.
	for (int i=0; i < tam-1; i++) {
		for (int j=0 ; j < tam-i-1 ; j++) {  
			if (scores->at(j).value < scores->at(j+1).value) {
				Score aux;
				
				aux.name  = scores->at(j).name; 
				aux.value = scores->at(j).value;
				
				scores->at(j).name	 = scores->at(j+1).name;
				scores->at(j).value = scores->at(j+1).value;
				
				scores->at(j+1).name  = aux.name;
				scores->at(j+1).value = aux.value;  
			}
        }
	}
}

//-------------------------------------------------------------------------------------------------//

int draw_scores (sf::RenderWindow * window, sf::Font * font, int scr_wdt, 
				int scr_hgt, int * menu_option, sf::Sound * audio_enter, std::vector <Score> * scores)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		audio_enter->play();
		return 1;
	}
	
	sf::Text back_advice, name, score;
	initialize_text(font, &back_advice, "[ esc to return ]", 20, scr_wdt, scr_hgt, scr_wdt*0.7, scr_hgt*0.95, 1);

	int j=0;
	for (auto i = begin(*scores) ; i != end(*scores) && j<17; i++) {
		initialize_text(font, &name, i->name, 32, scr_wdt, scr_hgt, scr_wdt*0.2, scr_hgt*0.05 + j*scr_hgt*0.05, 0);
		initialize_text(font, &score, std::to_string(i->value) , 32, scr_wdt, scr_hgt, scr_wdt*0.7, scr_hgt*0.05 + j*scr_hgt*0.05, 0);

		window->draw(name);
		window->draw(score);
		j++;
	}

	window->draw(back_advice);
	
	return 3;	
}