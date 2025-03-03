// Copyright 2019-2023 the openage authors. See copying.md for legal info.

#pragma once


#include <vector>
#include <deque>

#include "../../curve/curve.h"
#include "../../renderer/renderer.h"
#include "../../renderer/opengl/window.h"


namespace openage::main::tests::pong {

class PongEvent;
class PongState;
class PongPlayer;


class Gui {
public:
	Gui();

	const std::vector<PongEvent> &get_inputs(const std::shared_ptr<PongPlayer> &player);

	void draw(const std::shared_ptr<PongState> &state, const curve::time_t &now);

	const util::Vector2s &get_window_size() const;

	void log(const std::string &msg);

	void add_resize_callback(const renderer::Window::resize_cb_t&);
	void clear_resize_callbacks();

	void update();

	bool exit_requested = false;

private:
	renderer::opengl::GlWindow window;
	std::shared_ptr<renderer::Renderer> renderer;

	std::vector<PongEvent> input_cache;
	std::deque<std::string> log_msgs;

	// rendering objects
	renderer::Renderable ball;
	renderer::Renderable p1paddle;
	renderer::Renderable p2paddle;

	// render pass for the game area
	std::shared_ptr<renderer::RenderPass> render_pass;

	std::vector<renderer::Window::resize_cb_t> resize_callbacks;
};

} // openage::main::tests::pong
