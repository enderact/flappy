#pragma once
#include <SFML/Graphics.hpp>
#include "global.hpp"
#include "Generator.hpp"

class Bird
{
protected:
	sf::RectangleShape body;
	float vertical_speed;
	int score;
	bool status;

	sf::IntRect uv_rect;

public:
	Bird();
	~Bird();

	bool check_pass;

	void update(float delta_time, Generator& gen);
	void draw(sf::RenderWindow& window);
	void set_status(bool stat) { this->status = stat; }
	void set_texture(sf::Texture* texture);
	void set_uv_rect(sf::IntRect rect) { this->uv_rect = rect; }

	void bird_reset();

	sf::Vector2f get_position() { return body.getPosition(); }
	bool get_status() { return status; }
	int get_score() { return score; }
};

