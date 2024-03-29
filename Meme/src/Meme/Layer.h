#pragma once

#include "Meme/core.h"
#include "Meme/Events/Event.h"
#include "Meme/Core/Timestep.h"

namespace Meme {

	class MEME_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImguiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_debugName; }

	protected:
		std::string m_debugName;

	};

}
