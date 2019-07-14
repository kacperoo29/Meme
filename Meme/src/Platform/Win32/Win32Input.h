#pragma once

#include "Meme/Input.h"

namespace Meme {

	class Win32Input : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int32_t keycode) override;

		virtual bool IsMouseButtonPressedImpl(int32_t button) override;

		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;	

	};
}