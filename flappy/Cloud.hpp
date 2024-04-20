#pragma once
#include "SFML/Graphics.hpp"

class Cloud
{
private:
	sf::RectangleShape cloud;

public:
	Cloud(sf::Texture* texture);
	~Cloud();

	sf::Vector2f rand_gen(sf::Vector2i x, sf::Vector2i y);

	void cloud_reset();
	void check();

	void update(float delta_time);
	void draw(sf::RenderWindow& window);

};

