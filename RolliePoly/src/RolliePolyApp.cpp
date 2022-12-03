#include "Layers/EditorLayer.h"
#include "Pangolin/Core/Entry.h"

namespace Pangolin {
	class RolliePoly : public App {
	public:
		RolliePoly(): App("RolliePoly") {
			push_layer(new EditorLayer());
		}

		~RolliePoly() {}
	};

	Pangolin::App* create_app() {
		return new RolliePoly();
	}
}