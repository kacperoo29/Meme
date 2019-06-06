#pragma once

#include "Meme/core.h"
#include "Meme/Events/Event.h"

namespace Meme {

	class MEME_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_debugName; }

	protected:
		std::string m_debugName;

	};

}
