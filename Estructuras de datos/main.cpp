#include <SFML/Graphics.hpp>
#include <iostream>

int factorial(int n)
{
	if (n == 0 || n == 1) return 1;
	else
		return n * factorial(n - 1);
}

//Multiplicación egipcia

int multiplyEgyptian(int n, int a)
{
	if (n == 1) return a;

	return multiplyEgyptian(n - 1, a) + a;
}

int Josefo(int n)
{
	if (n == 1) return 1;

	int result = ((Josefo(n - 1) + 1) % n) +1 ;

	std::cout << "Mi return: " << result << " es cuando mi n es: " << n << std::endl;
	return result;

}
int main()
{
	std::cout << Josefo(7) << std::endl;
	std::cout << multiplyEgyptian(3, 4) << std::endl;
	std::cout << factorial(6) << std::endl;
	sf::RenderWindow window(sf::VideoMode({ 200,200 }), "MyGame");
	sf::CircleShape shape(100.0f);
	shape.setFillColor(sf::Color::Green);
	while (window.isOpen())
	{
		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}