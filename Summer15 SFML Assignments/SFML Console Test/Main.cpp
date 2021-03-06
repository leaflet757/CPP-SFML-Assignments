#include <SFML/Graphics.hpp>
#include <cstdio>
#include <thread>
#include <iostream>
#include <mutex>
#include <string>

using namespace std;


std::mutex _lock;

bool running = true;
long int testNum = 0;
long updateNumer = 0;

// Create Dummy Shape
sf::CircleShape shape(10.f);

void renderingFunction(sf::RenderWindow* window)
{
	// activate the window's context
	window->setActive(true);
	window->setVerticalSyncEnabled(true);

	// the rendering loop
	while (running)
	{
		// set lock to finish rendering
		_lock.lock();

		// clear the buffers
		window->clear();

		// DEBUG
		cout << "render " << testNum-- << endl;

		// draw...
		window->draw(shape);

		// end the current frame (internally swaps the front and back buffers)
		window->display();

		// release lock for update thread
		_lock.unlock();
	}
}

void updateFunction(sf::RenderWindow* window)
{
	// DEBUG
	shape.setPosition(0, window->getSize().y / 2 - shape.getRadius());
	shape.setFillColor(sf::Color::Green);

	while (running)
	{
		// lock thread to finish updating
		_lock.lock();


		// Update logic...
		cout << "logic " << testNum++ << endl;
		cout << "   update number: " << updateNumer++ << endl;
		shape.setPosition(shape.getPosition().x + 1, shape.getPosition().y);


		// release lock for rendering thread
		_lock.unlock();
	}
}

int main()
{ 
	// create the window (remember: it's safer to create it in the main thread due to OS limitations)
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");

	// deactivate its OpenGL context
	window.setActive(false);

	// launch the rendering & update thread
	thread updateThread(updateFunction, &window);
	thread renderingThread(renderingFunction, &window);
	
	// Main thread to check for window closing
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				running = false;
			}
		}
	}

	// stop threads
	renderingThread.join();
	updateThread.join();

	return 0;
}
