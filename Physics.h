#pragma once

#include<SFML/Graphics.hpp>

namespace physics {
	bool intersects(const sf::Vector2f point, const sf::VertexArray& polygon);

	bool intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2);
	sf::VertexArray GetTransformed(const sf::VertexArray& polygon, const sf::Transform& transform);
}