#pragma once

#include "GamEngine/Core/Layer.h"

class ExampleLayer : public GamEngine::Layer {
public:
	ExampleLayer();

	void on_event(GamEngine::Event& event) override;
};