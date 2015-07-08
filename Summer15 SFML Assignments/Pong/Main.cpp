#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <cstdio>
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;


std::mutex _lock;

bool running = true;
float r = 0, g = 0.3, b = 0.6;


void renderingFunction(sf::Window* window)
{
	// activate the window's context
	window->setActive(true);
	window->setVerticalSyncEnabled(true);

	// adjust for the screen ratio
	float width = window->getSize().x;
	float height = window->getSize().y;

	// update the size of the viewport
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	float aspect = (float)width / (float)height;
	glOrtho(-aspect, aspect, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// the rendering loop
	while (running)
	{
		// set lock to finish rendering
		_lock.lock();

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...
		glBegin(GL_TRIANGLES);
		glColor3f(r, g, b);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0, 0.5);
		glEnd();

		// end the current frame (internally swaps the front and back buffers)
		window->display();

		// release lock for update thread
		_lock.unlock();
	}
}

void updateFunction(sf::Window* window)
{
	while (running)
	{
		// lock thread to finish updating
		_lock.lock();

		// Update logic...
		r += 0.01;
		g += 0.01;
		b += 0.01;
		if (r > 1) r = 0;
		if (g > 1) g = 0;
		if (b > 1) b = 0;

		// release lock for rendering thread
		_lock.unlock();
	}
}

int main()
{
	// create the window (remember: it's safer to create it in the main thread due to OS limitations)
	sf::Window window(sf::VideoMode(1280, 720), "Pong", sf::Style::None);

	// deactivate its OpenGL context
	window.setActive(false);

	// launch the rendering thread
	thread updateThread(updateFunction, &window);
	thread renderingThread(renderingFunction, &window);

	// the event/logic/whatever loop
	while (window.isOpen())
	{
		// ...
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}
	}

	// stop threads
	renderingThread.join();
	updateThread.join();

	return 0;
}