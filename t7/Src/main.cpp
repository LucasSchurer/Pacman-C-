//===================================//
//                LIBS               //
//===================================//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream> 

#include "Headers/UI.hpp"
#include "Headers/map.hpp"

//---------------------------------//

 static void display_message()
{
	std::cout << "\n\nPacman!\n";
	std::cout << "\n=======================\n";
}

//===================================//
//                MAIN               //
//===================================//

int main ()
{
	display_message();

	int scr_wdt = 560, scr_hgt = 720; // Tamanho da tela.
	char ** tiles; // Matriz do mapa.
	
	tiles = new char* [scr_hgt/20];
	for (int i=0 ; i<scr_hgt/20 ; i++)
		tiles[i] = new char [scr_wdt/20];


	// Abre o txt do mapa.
	std::ifstream map_input {"txt/map.txt"};
	if (!map_input.is_open()) {
		std::cout << "\nIt was not possible to open 'map.txt'. Exiting program...\n";
		exit(1);
	}

	// cria a matriz com os elementos do mapa.
	for (int i=0 ; i<scr_hgt/20 ; i++) {
		for (int j=0 ; j<scr_wdt/20 ; j++) {
			map_input >> tiles[i][j];
		}
	}

	for (int i=0 ; i<scr_hgt/20 ; i++) {
		for (int j=0 ; j<scr_wdt/20 ; j++) {
			std::cout << tiles[i][j] << " ";
		}
		std::cout << std::endl;
	}

	// Abre a lista de pontuações.
	std::ifstream score_list_input {"txt/scores.txt"};
	if (!score_list_input.is_open()) {
		std::cout << "\nIt was not possible to open 'scores.txt'. Exiting program...\n";
		exit(1);
	}

	std::vector <Score> scores;
	get_score_list(&score_list_input, &scores); // cria a lista com as pontuações.

	int game_status = 1; // Variável principal para decidir o status do jogo.
	sf::RenderWindow window(sf::VideoMode(scr_wdt, scr_hgt), "PACMAN");
	window.setKeyRepeatEnabled(false);

	// Carrega a fonte do jogo.
	sf::Font font;
	font.loadFromFile("../Font/font.ttf");
	int menu_option = 0;

	// Inicia o som da escolha de opção no menu.
	sf::SoundBuffer menu_settings_buffer;
    menu_settings_buffer.loadFromFile("../Audio/UI/button.wav");
    sf::Sound menu_settings;
    menu_settings.setBuffer(menu_settings_buffer);
    menu_settings.setVolume(50);

    // Inicia o som do enter no menu.
    sf::SoundBuffer menu_enter_buffer;
    menu_enter_buffer.loadFromFile("../Audio/UI/enter.wav");
    sf::Sound menu_enter;
    menu_enter.setBuffer(menu_enter_buffer);
    menu_enter.setVolume(50);

    // Inicia o pacman.
    Pacman pacman;
    initialize_pacman(&pacman, scr_wdt, scr_hgt);

    Wall ** wall;
    wall = new Wall* [scr_hgt/20];
	for (int i=0 ; i<scr_hgt/20 ; i++)
		wall[i] = new Wall [scr_wdt/20];

    create_map_tiles(wall, scr_wdt, scr_hgt, tiles);

    std::map <int, Node> node_map;
    
    int number = 1;
    for (int i=0 ; i<scr_hgt/20 ; i++) {
		for (int j=0 ; j<scr_wdt/20 ; j++) {
			if (wall[i][j].label == "NODE") {
				node_map[number] = Node();
				
				node_map[number].number = number;
				node_map[number].pos.x = j*20;
				node_map[number].pos.y = i*20;

				number++;
			}
		}
	}

	Node aux1, aux2;

	std::ifstream neighborhood {"txt/neighborhood.txt"};
	while (neighborhood >> aux1.number >> aux2.number >> aux1.target) {
		node_map[aux1.number].adj.push_back(aux2);
		node_map[aux2.number].adj.push_back(aux1);
	}	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Fecha a janela caso o jogador aperte no X ou clique quit.
			if (event.type == sf::Event::Closed || game_status == -1)
                window.close();
			
			if (game_status == 1) {	
		            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
					menu_settings.play();
					
					if (menu_option != 0)
						menu_option--;
					else
						menu_option = 2;
				}
				
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
					menu_settings.play();
					
					if (menu_option != 2)
						menu_option++;
					else
						menu_option = 0;
				}
			}

			if (game_status == 2) {
            	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && pacman.move_dir != 0) {
					pacman.move_dir = 0;
					pacman.actual_frame = 0;
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && pacman.move_dir != 1) {
					pacman.move_dir = 1;
					pacman.actual_frame = 4;
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && pacman.move_dir != 2) {
					pacman.move_dir = 2;
					pacman.actual_frame = 9;
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && pacman.move_dir != 3) {
					pacman.move_dir = 3;
					pacman.actual_frame = 14;
				}
			}
		}

		switch (game_status)
		{
            case 1: game_status = draw_menu(&window, &font, scr_wdt, scr_hgt, &menu_option, &menu_enter); 										break; // Manter o menu;
			case 2: game_status = draw_map(&window, &font, scr_wdt, scr_hgt, &menu_option, &pacman, wall, tiles); 		break;// Jogar;
	        case 3:	game_status = draw_scores(&window, &font, scr_wdt, scr_hgt, &menu_option, &menu_enter, &scores); 				break;// Menu scores;
        }
        
        window.display();
    	window.clear();
    	window.setFramerateLimit(60);
	}

	for (int i=0 ; i<scr_hgt/20 ; i++) {
		delete[] tiles[i];
		delete[] wall[i];
	}
	delete[] tiles;
	delete[] wall;

	return 0;
}

