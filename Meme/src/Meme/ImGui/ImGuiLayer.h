#pragma once

#include "Meme/Layer.h"

#include "Meme/Events/MouseEvent.h"
#include "Meme/Events/KeyEvent.h"
#include "Meme/Events/ApplicationEvent.h"

namespace Meme {

	class MEME_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImguiRender() override;

		void Begin();
		void End();

	private:
		float m_time = 0.0f;
	};

}

