#include "Pipe.hpp"

Pipe::Pipe(float speed, int rand_value, bool hardmode)
{
	this->speed = speed;
	if (hardmode) distance_inbetween = 1.75 * pipe_pass_height;
	else distance_inbetween = pipe_pass_height;
	this->height = window_height;
	this->y_axis = pipe_axis;
	plant_attached = false;

	upper_pipe.setSize(sf::Vector2f(pipe_width, height));
	lower_pipe.setSize(sf::Vector2f(pipe_width, height));
	
	
	upper_pipe.setPosition(sf::Vector2f(900, y_axis - height + rand_value));
	lower_pipe.setPosition(sf::Vector2f(900, y_axis + distance_inbetween + rand_value));
}

Pipe::~Pipe()
{
}

bool Pipe::check()
{
	if (upper_pipe.getPosition().x + pipe_width > 0) return true;
	return false;
}

void Pipe::set_x(float x)
{
	upper_pipe.setPosition(sf::Vector2f(x, upper_pipe.getPosition().y));
	lower_pipe.setPosition(sf::Vector2f(x, lower_pipe.getPosition().y));
}

void Pipe::set_pipe_texture(sf::Texture* texture)
{
	upper_pipe.setTexture(texture);
	lower_pipe.setTexture(texture);
	sf::IntRect uv;
	uv.width = texture->getSize().x / float(2);
	uv.height = texture->getSize().y / float(1);
	upper_pipe.setTextureRect(sf::IntRect(0, 0, uv.width, uv.height));
	lower_pipe.setTextureRect(sf::IntRect(uv.width, 0, uv.width, uv.height));

}

void Pipe::update(float delta_time)
{
	sf::Vector2f movement(0.0, 0.0);
	movement.x -= speed * delta_time;

	upper_pipe.move(movement);
	lower_pipe.move(movement);
}

void Pipe::draw(sf::RenderWindow& window)
{
	window.draw(upper_pipe);
	window.draw(lower_pipe);
}
