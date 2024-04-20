#pragma once

#include <SFML/Graphics.hpp>

#include "global.hpp"

class Pipe
{
private:
	sf::RectangleShape upper_pipe;
	sf::RectangleShape lower_pipe;

	float speed;
	float y_axis;
	float distance_inbetween;
	float height;
	bool plant_attached;

public:
	Pipe(float speed, int rand_value, bool hardmode);
	~Pipe();

	sf::Vector2f get_position_upper() { return upper_pipe.getPosition(); }
	sf::Vector2f get_position_lower() { return lower_pipe.getPosition(); }

	bool check();
	void set_x(float x);
	void set_distance_inbetween(float increment) { this->distance_inbetween = increment; }
	void set_pipe_texture(sf::Texture* pipe_texture);
	void set_attached(bool attached) { plant_attached = attached; }

	bool get_attached() { return plant_attached; }

	void update(float delta_time);
	void draw(sf::RenderWindow& window);
};

