#include "Graphics.h"

namespace OpenSFMLEngine
{
	std::atomic<Graphics*> Graphics::pInstance{ nullptr };
	std::mutex Graphics::m_;

	Graphics::Graphics()
	{
		initialize();
	}


	Graphics::~Graphics()
	{
	}

	void Graphics::initialize()
	{

	}

	Graphics* Graphics::getInstance()
	{
		Graphics* tmp = pInstance.load();
		if (tmp == nullptr)
		{
			std::lock_guard<std::mutex> lock(m_);
			if (tmp == nullptr) {
				tmp = new Graphics();
				pInstance.store(tmp);
			}
		}
		return tmp;
	}

	void Graphics::update()
	{

	}
}