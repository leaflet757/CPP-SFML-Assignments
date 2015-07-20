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
		// stop threads
		renderingThread->join();
		updateThread->join();


		delete clock;
		delete updateThread;
		delete renderingThread;
		delete window;
	}

	Game& Game::getInstance()
	{
		static Game game;
		return game;
	}

	void Game::initActors()
	{
		actors.push_back(new Ball());
	}

	void Game::start()
	{
		clock = new sf::Clock();

		// launch the rendering thread
		updateThread = new thread(&OpenSFMLEngine::Game::updateFunction, this);
		renderingThread = new thread(&OpenSFMLEngine::Game::renderingFunction, this);

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

			for (int a = 0; a < actors.size(); a++)
			{
				Actor2D* actor = actors.at(a);

				glPushMatrix();

				const glm::vec3 scale = actor->getScale();
				const glm::vec3 position = actor->getPosition();

				glTranslatef(position.x, position.y, position.z);
				glScalef(scale.x, scale.y, scale.z);

				// draw...
				glColor3f(r, g, b);
				glBegin(GL_POLYGON);

				std::vector<glm::vec3> verts = actor->getVerts();
				for (int i = 0; i < verts.size(); i++)
				{
					const glm::vec3 vertex = verts.at(i);
					glVertex2f(vertex.x, vertex.y);
				}

				// draw end...
				glEnd();

				glPopMatrix();
			}

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

			sf::Time elapsed1 = clock->getElapsedTime();
			float deltaTime = elapsed1.asSeconds();
			clock->restart();

			for (int a = 0; a < actors.size(); a++)
			{
				Actor2D* actor = actors.at(a);

				actor->update();

				const glm::vec3 velocity = actor->getVelocity();
				const glm::vec3 position = actor->getPosition();
				
				glm::vec3 newPosition;
				newPosition.x = position.x + velocity.x * deltaTime;
				newPosition.y = position.y + velocity.y * deltaTime;
				newPosition.z = position.z + velocity.z * deltaTime;

				actor->setPosition(newPosition.x, newPosition.y, newPosition.z);
			}

			// double result = MathFuncs::MyMathFuncs::Add(0.2, 0.3); // test to see if engine works

			// release lock for rendering thread
			_lock.unlock();
		}
	}
}