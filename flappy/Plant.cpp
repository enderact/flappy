#include "Plant.hpp"
#include <chrono>
#include <random>
#include <cstdlib>


Plant::Plant(sf::Texture* texture)
{
	this->texture = *texture;
	plant.setSize(sf::Vector2f(plant_width, plant_height));
	direction = false;
	attached = false;
	current_image = sf::Vector2u(0, 0);
	total_time = 0;
	vertical = 0;

	plant.setTexture(texture);
	uv.width = texture->getSize().x / float(2);
	uv.height = texture->getSize().y / float(1);
}

Plant::~Plant()
{
}

int Plant::rand_gen()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generate(seed);
	std::uniform_int_distribution<int> distribution(1, 20);
	return distribution(generate);
}

void Plant::attach_plant_pipe(Generator& gen, int rand)
{
	for (Pipe& p : gen.get_pipe_conatiner())
	{
		if (rand < 10 && !attached)
		{
			attached = true;
			vertical = 0;
			p.set_attached(attached);
			if (rand > 5)
			{
				direction = false; // top
				plant.setPosition(sf::Vector2f(p.get_position_upper().x+ 10 + plant_width/2, p.get_position_upper().y + window_height + plant_height/2 - plant_height));
			}
			else if (rand < 5)
			{
				direction = true; // bottom
				plant.setPosition(sf::Vector2f(p.get_position_lower().x + 10, p.get_position_lower().y - plant_height + plant_height));
			}
		}
	}
}

bool Plant::check_gone()
{
	if (plant.getPosition().x + plant_width < 0) return true;
	return false;
}

bool Plant::check_collision(Bird& bird)
{
	sf::Vector2f c = bird.get_position();
	sf::Vector2f p = plant.getPosition();
	if (direction && c.x + bird_width >= p.x && c.x <= p.x + plant_width
		&& c.y + bird_height >= p.y)
	{
		return true;
	}
	else if (!direction && c.x + bird_width >= p.x - plant_width/2 && c.x <= p.x + plant_width/2
		&& c.y <= p.y + plant_height/2)
	{
		return true;
	}
	return false;
}

void Plant::plant_reset()
{
	attached = false;
	plant.setPosition(sf::Vector2f(1000, 1000));
}

void Plant::update(float delta_time, Generator& gen, Bird& bird)
{

	plant.setOrigin(0, 0);
	if (check_collision(bird))
	{
		bird.set_status(false);
	}

	sf::Vector2f movement(0.0, 0.0);
	movement.x -= forward_speed * delta_time;
	if (check_gone())
	{
		attached = false;
	}
	
	if ((abs(vertical) >= plant_height && direction) || (vertical >= plant_height && !direction))
	{
		movement.y = 0;
	}
	else
	{
		if (direction)
		{
			movement.y -= forward_speed * delta_time;
			vertical -= movement.y;
		}
		else
		{
			movement.y += forward_speed * delta_time;
			vertical += movement.y;
			
		}
		
	}
	attach_plant_pipe(gen, rand_gen());
	if (direction)
	{
		plant.setRotation(0);
	}
	else
	{
		plant.setOrigin(plant_width / 2, plant_height / 2);
		plant.setRotation(180);
	}

	total_time += delta_time;

	if (total_time >= switch_time) {
		total_time -= switch_time;
		current_image.x++;

		if (current_image.x >= 2) {
			current_image.x = 0;
		}
	}

	uv.left = current_image.x * uv.width;
	uv.top = current_image.y * uv.height;
	plant.setTextureRect(uv);
	
	plant.move(movement);
}

void Plant::draw(sf::RenderWindow& window)
{
	window.draw(plant);
}
