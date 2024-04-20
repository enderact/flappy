#include <SFML/Graphics.hpp>
#include <iostream>

#include "Bird.hpp"
#include "Pipe.hpp"
#include "Generator.hpp"
#include "Plant.hpp"
#include "Cloud.hpp"
#include "global.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

int main()
{

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Flappy Bird", sf::Style::Close);
	sf::View view(sf::Vector2f(0.0, 0.0), sf::Vector2f(window_width, window_height));
	window.setView(sf::View(sf::FloatRect(0, 0, window_width, window_height)));

	sf::RectangleShape main_window;
	main_window.setSize(sf::Vector2f(window_width, window_height));
	sf::Texture main_texture;
	main_texture.loadFromFile("main_page_texture.png");
	main_window.setTexture(&main_texture);

	Bird flappy;

	sf::Texture pipe_texture;
	pipe_texture.loadFromFile("pipe_texture.png");
	Generator gen(&pipe_texture, false);
	Generator gen_hard(&pipe_texture, true);

	sf::Texture plant_texture;
	plant_texture.loadFromFile("plant_texture.png");
	Plant plant(&plant_texture);
	

	sf::Font font;
	if (!font.loadFromFile("score_font.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		exit(0);
	}
	sf::Text text_score;
	text_score.setFont(font);
	text_score.setCharacterSize(35);
	text_score.setOutlineColor(sf::Color::Black);
	text_score.setOutlineThickness(1);
	text_score.setLetterSpacing(2);

	sf::Text text_game_over;
	text_game_over.setFont(font);
	text_game_over.setFillColor(sf::Color::Red);
	text_game_over.setCharacterSize(50);
	text_game_over.setLetterSpacing(3);
	text_game_over.setOutlineThickness(2);
	text_game_over.setString("GAME OVER");
	text_game_over.setPosition(175, 200);
	sf::Text text_restart(text_score);
	text_restart.setString("Press ENTER to restart\n\t\tESC to exit");
	text_restart.setPosition(125, 300);
	sf::RectangleShape text_restart_baground;
	text_restart_baground.setSize(sf::Vector2f(400,100));
	text_restart_baground.setFillColor(sf::Color(0, 125, 125, 150));
	text_restart_baground.setPosition(100, 290);



	sf::Texture bird_texture;
	bird_texture.loadFromFile("bird_texture.png");
	flappy.set_texture(&bird_texture);
	sf::IntRect uv_rect;
	uv_rect.width = bird_texture.getSize().x / float(3);
	uv_rect.height = bird_texture.getSize().y / float(1);
	uv_rect.top = 0;
	flappy.set_uv_rect(uv_rect);

	sf::Texture cloud_texture;
	cloud_texture.loadFromFile("cloud.png");
	Cloud cloud(&cloud_texture);
	Cloud cloud2(&cloud_texture);
	Cloud cloud3(&cloud_texture);
	Cloud cloud4(&cloud_texture);

	unsigned int highscore_normal = 0;
	unsigned int highscore_hard = 0;
	std::ifstream readfile("high_score_data.txt");
	std::string temp; unsigned int temp_int;
	while (readfile >> temp >> temp_int)
	{
		if (temp == "normal")
		{
			highscore_normal = temp_int;
		}
		else if (temp == "hard")
		{
			highscore_hard = temp_int;
		}
	}
	sf::Text high_score(text_score);
	high_score.setPosition(sf::Vector2f(350, 0));

	float delta_time = 0.0;
	sf::Clock clock;

	bool  game_over = false;
	bool main_window_bool = true;
	bool normal_mode_bool = false;
	bool hard_mode_bool = false;

	while (window.isOpen())
	{
		delta_time = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && main_window_bool)
				{
					window.close();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && normal_mode_bool)
				{
					normal_mode_bool = false;
					hard_mode_bool = false;
					main_window_bool = true;
					flappy.bird_reset();
					gen.generator_restart(&pipe_texture);
					gen_hard.generator_restart(&pipe_texture);
					plant.plant_reset();
					cloud.cloud_reset();
					cloud2.cloud_reset();
					cloud3.cloud_reset();
					cloud4.cloud_reset();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && hard_mode_bool)
				{
					hard_mode_bool = false;
					normal_mode_bool = false;
					main_window_bool = true;
					flappy.bird_reset();
					gen_hard.generator_restart(&pipe_texture);
					gen.generator_restart(&pipe_texture);
					plant.plant_reset();
					cloud.cloud_reset();
					cloud2.cloud_reset();
					cloud3.cloud_reset();
					cloud4.cloud_reset();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					flappy.bird_reset();
					gen_hard.generator_restart(&pipe_texture);
					gen.generator_restart(&pipe_texture);
					plant.plant_reset();
					cloud.cloud_reset();
					cloud2.cloud_reset();
					cloud3.cloud_reset();
					cloud4.cloud_reset();
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::getPosition(window).x > 130 && sf::Mouse::getPosition(window).x < 460
					&& sf::Mouse::getPosition(window).y > 430 && sf::Mouse::getPosition(window).y < 525
					&& sf::Mouse::isButtonPressed(sf::Mouse::Left) && main_window_bool)
				{
					normal_mode_bool = true;
					main_window_bool = false;
				}
				else if (sf::Mouse::getPosition(window).x > 130 && sf::Mouse::getPosition(window).x < 460
					&& sf::Mouse::getPosition(window).y > 630 && sf::Mouse::getPosition(window).y < 725
					&& sf::Mouse::isButtonPressed(sf::Mouse::Left) && main_window_bool)
				{
					hard_mode_bool = true;
					main_window_bool = false;
				}
				else if (sf::Mouse::getPosition(window).x > 130 && sf::Mouse::getPosition(window).x < 460
					&& sf::Mouse::getPosition(window).y > 780 && sf::Mouse::getPosition(window).y < 850
					&& sf::Mouse::isButtonPressed(sf::Mouse::Left) && main_window_bool)
				{
					window.close();
				}
				break;
			}
		}
		
		if (hard_mode_bool)
		{
			if(flappy.get_score() > highscore_hard) highscore_hard = flappy.get_score();
			high_score.setString("Highscore:  " + std::to_string(highscore_hard));
		}
		if (normal_mode_bool)
		{
			if(flappy.get_score() > highscore_normal) highscore_normal = flappy.get_score();
			high_score.setString("Highscore:  " + std::to_string(highscore_normal));
		}
		text_score.setString("Score :  " + std::to_string(flappy.get_score()));

		cloud.update(delta_time);
		cloud2.update(delta_time);
		cloud3.update(delta_time);
		cloud4.update(delta_time);
		if (flappy.get_status() && (normal_mode_bool || hard_mode_bool))
		{
			if (hard_mode_bool)
			{
				plant.update(delta_time, gen_hard, flappy);
				gen_hard.update(delta_time, &pipe_texture);
				flappy.update(delta_time, gen_hard);
			}
			else
			{
				gen.update(delta_time, &pipe_texture);
				flappy.update(delta_time, gen);
			}
		}
		
		
		window.clear(sf::Color(100, 200, 255));
		
		if (normal_mode_bool || hard_mode_bool)
		{
			cloud.draw(window);
			cloud2.draw(window);
			cloud3.draw(window);
			cloud4.draw(window);
			if (hard_mode_bool)
			{
				plant.draw(window);
				gen_hard.draw(window);
			}
			else
			{
				gen.draw(window);
			}
			
			flappy.draw(window);
			window.draw(text_score);
			window.draw(high_score);
		}
		
		if (flappy.get_status() == false)
		{
			window.draw(text_restart_baground);
			window.draw(text_game_over);
			window.draw(text_restart);
			
		}
		if (main_window_bool)
		{
			window.draw(main_window);
		}

		window.display();
	}

	std::ofstream writefile;
	writefile.open("high_score_data.txt", std::ofstream::out);
	writefile << "normal" << '\t' << highscore_normal << '\n';
	writefile << "hard" << '\t' << highscore_hard;


	return 0;
}