#pragma once

#include "Pipe.hpp"
#include "global.hpp"
#include <vector>

class Generator
{
private:
	std::vector<Pipe> pipe_container;
	bool hardmode;

public:

	Generator(sf::Texture* texture, bool hardmode);
	~Generator();

	int rand_gen();
	void add_pipe(sf::Texture* texture);
	bool check_collision(sf::RectangleShape& bird);
	void mode_distance(float distance);

	void update(float delta_time, sf::Texture* texture);
	void draw(sf::RenderWindow& window);

	void generator_restart(sf::Texture* texture);

	std::vector<Pipe> get_pipe_conatiner() { return pipe_container; }
};

