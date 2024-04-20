#include "Bird.hpp"

Bird::Bird()
{
	vertical_speed = 0;
	status = true;
	score = 0;
	check_pass = false;

	body.setFillColor(sf::Color(255, 255, 0));
	body.setSize(sf::Vector2f(bird_width, bird_height));
	body.setPosition(sf::Vector2f(100, 400));
}

Bird::~Bird()
{
}

void Bird::update(float delta_time, Generator& gen)
{
	if (body.getPosition().y >= window_height - bird_height) {
		status = false;
		vertical_speed = 0;
		body.setPosition(sf::Vector2f(body.getPosition().x, window_height - bird_height));
	}
	if (gen.check_collision(body))
	{
		status = false;
	}
	if (gen.get_pipe_conatiner().at(0).get_position_upper().x + pipe_width > 100)
	{
		check_pass = false;
	}
	else if (check_pass == false)
	{
		if (gen.get_pipe_conatiner().at(0).get_position_upper().x + pipe_width <= 100)
		{
			check_pass = true;
			score++;
		}
	}

	vertical_speed += gravity;
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == 1 && vertical_speed >= 0 && body.getPosition().y > 0)
	{
		vertical_speed = up_speed;
	}

	if (status == false)
	{
		uv_rect.left = 2 * uv_rect.width;
	}
	else if (vertical_speed < 0)
	{
		uv_rect.left = uv_rect.width;
	}
	else if (vertical_speed >= 0)
	{
		uv_rect.left = 0;
	}
	movement.y += vertical_speed * delta_time;

	body.setTextureRect(uv_rect);
	body.move(movement);
}

void Bird::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Bird::set_texture(sf::Texture* texture)
{
	body.setTexture(texture);
}

void Bird::bird_reset()
{
	score = 0;
	vertical_speed = 0;
	status = true;
	check_pass = false;
	body.setPosition(sf::Vector2f(100, 400));
	uv_rect.left = 0;
}
