#include "Game.h"

namespace OpenSFMLEngine
{
	Game::Game()
	{
		// create the window (remember: it's safer to create it in the main thread due to OS limitations)
		window = new sf::Window(sf::VideoMode(1280, 720), "Pong", sf::Style::None);

		// deactivate its OpenGL context
		window->setActive(false);
	}


	Game::~Game()
	{
		delete window;
	}

	void Game::Start()
	{
		// launch the rendering thread
		thread updateThread(&OpenSFMLEngine::Game::updateFunction, this);
		thread renderingThread(&OpenSFMLEngine::Game::renderingFunction, this);

		// the event/logic/whatever loop
		while (window->isOpen())
		{
			// ...
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window->close();
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
	}

	void Game::renderingFunction()
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
			glColor3f(r, g, b);
			glBegin(GL_POLYGON);
			glVertex2f(-1, -1);
			glVertex2f(1, -1);
			glVertex2f(0, 1);
			glEnd();

			// end the current frame (internally swaps the front and back buffers)
			window->display();

			// release lock for update thread
			_lock.unlock();
		}
	}

	void Game::updateFunction()
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

			// double result = MathFuncs::MyMathFuncs::Add(0.2, 0.3); // test to see if engine works

			// release lock for rendering thread
			_lock.unlock();
		}
	}
}