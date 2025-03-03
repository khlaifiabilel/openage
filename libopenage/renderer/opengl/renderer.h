// Copyright 2017-2023 the openage authors. See copying.md for legal info.

#pragma once

#include <memory>

#include "../renderer.h"
#include "render_pass.h"
#include "render_target.h"
#include "shader_program.h"


namespace openage {
namespace renderer {
namespace opengl {

/// The OpenGL specialization of the rendering interface.
class GlRenderer final : public Renderer {
public:
	GlRenderer(const std::shared_ptr<GlContext> &);

	std::shared_ptr<Texture2d> add_texture(resources::Texture2dData const &) override;
	std::shared_ptr<Texture2d> add_texture(resources::Texture2dInfo const &) override;

	std::shared_ptr<ShaderProgram> add_shader(std::vector<resources::ShaderSource> const &) override;

	std::shared_ptr<Geometry> add_mesh_geometry(resources::MeshData const &) override;
	std::shared_ptr<Geometry> add_bufferless_quad() override;

	std::shared_ptr<RenderPass> add_render_pass(std::vector<Renderable>, const std::shared_ptr<RenderTarget> &) override;

	std::shared_ptr<RenderTarget> create_texture_target(std::vector<std::shared_ptr<Texture2d>> const &) override;

	std::shared_ptr<RenderTarget> get_display_target() override;

	resources::Texture2dData display_into_data() override;

	void check_error() override;

	void render(const std::shared_ptr<RenderPass> &) override;

private:
	/// Optimize the render pass by reordering stuff
	static void optimise(const std::shared_ptr<GlRenderPass> &);

	/// The GL context.
	std::shared_ptr<GlContext> gl_context;

	/// The main screen surface as a render target.
	std::shared_ptr<GlRenderTarget> display;
};

} // namespace opengl
} // namespace renderer
} // namespace openage
