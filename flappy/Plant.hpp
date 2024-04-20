#pragma once
#include "SFML/Graphics.hpp"
#include "global.hpp"
#include "Generator.hpp"
#include "Bird.hpp"


class Plant
{
private:
	sf::RectangleShape plant;

	bool direction;
	bool attached;
	sf::Texture texture;
	sf::IntRect uv;
	sf::Vector2u current_image;
	float total_time;
	float vertical;

public:
	Plant(sf::Texture* texture);
	~Plant();

	int rand_gen();

	void attach_plant_pipe(Generator& gen, int rand);
	bool check_gone();

	bool check_collision(Bird& bird);

	void plant_reset();

	void update(float delta_time, Generator& gen, Bird& bird);
	void draw(sf::RenderWindow& window);
};

