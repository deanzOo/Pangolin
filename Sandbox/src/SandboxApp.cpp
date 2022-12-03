#include "Pangolin.h"

#include "Pangolin/Core/Entry.h"

#include "Layers/TilemapLayer.h"
#include "Layers/TextureLayer.h"
#include "Layers/Sandbox2D.h"

class Sandbox : public Pangolin::App {
public:
	Sandbox() {
		//push_layer(new TilemapLayer());
		//push_layer(new TextureLayer());
		push_layer(new Sandbox2D());
	}

	~Sandbox() {}
};

Pangolin::App* Pangolin::create_app() {
	return new Sandbox();
}