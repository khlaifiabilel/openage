// Copyright 2015-2023 the openage authors. See copying.md for legal info.

#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "resources/mesh_data.h"
#include "uniform_input.h"


namespace openage {
namespace renderer {

class Texture2d;

class ShaderProgram : public std::enable_shared_from_this<ShaderProgram> {
	friend UniformInput;

public:
	virtual ~ShaderProgram() = default;

	/**
	 * Check whether the shader program contains a uniform variable with the given ID.
	 *
	 * @param unif ID of the uniform.
	 *
	 * @return true if the shader program contains the uniform, false otherwise.
	 */
	virtual bool has_uniform(const char *unif) = 0;

	/**
	 * Creates a new uniform input (a binding of uniform names to values) for this shader
	 * and optionally sets some uniform values. To do that, just pass two arguments -
	 * - a string literal and the value for that uniform for any uniform you want to set.
	 *
	 * For example new_uniform_input("color", { 0.5, 0.5, 0.5, 1.0 }, "num", 5) will set
	 * "color" to { 0.5, 0.5, 0.5, 0.5 } and "num" to 5. Types are important here and a type
	 * mismatch between the uniform variable and the input might result in an error.
	 */
	template <typename... Ts>
	std::shared_ptr<UniformInput> new_uniform_input(Ts &&...vals) {
		auto input = this->new_unif_in();
		input->update(vals...);
		return input;
	}

	/**
	 * Alias for the \p new_uniform_input() function to create empty shader program inputs. Makes more sense
	 * name-wise when the shader doesn't have any uniforms.
	 */
	std::shared_ptr<UniformInput> create_empty_input() {
		return this->new_uniform_input();
	}

	/**
	 * Get a list of _active_ vertex attributes in the shader program. Active attributes
	 * are those which have an effect on the shader output, meaning they are included in the
	 * output calculation and are not unused. Inactive attributes may or may not be present
	 * in the list - in particular, in the OpenGL implementation they will most likely be missing.
	 *
	 * @return Map from the attribute location to its type. Locations do not need to be consecutive.
	 */
	virtual std::map<size_t, resources::vertex_input_t> vertex_attributes() const = 0;

protected:
	virtual std::shared_ptr<UniformInput> new_unif_in() = 0;

	/**
	 * Set a uniform input variable in the actual shader program.
	 */
	virtual void set_i32(std::shared_ptr<UniformInput> const &, const char *, int32_t) = 0;
	virtual void set_u32(std::shared_ptr<UniformInput> const &, const char *, uint32_t) = 0;
	virtual void set_f32(std::shared_ptr<UniformInput> const &, const char *, float) = 0;
	virtual void set_f64(std::shared_ptr<UniformInput> const &, const char *, double) = 0;
	virtual void set_v2f32(std::shared_ptr<UniformInput> const &, const char *, Eigen::Vector2f const &) = 0;
	virtual void set_v3f32(std::shared_ptr<UniformInput> const &, const char *, Eigen::Vector3f const &) = 0;
	virtual void set_v4f32(std::shared_ptr<UniformInput> const &, const char *, Eigen::Vector4f const &) = 0;
	virtual void set_m4f32(std::shared_ptr<UniformInput> const &, const char *, Eigen::Matrix4f const &) = 0;
	virtual void set_tex(std::shared_ptr<UniformInput> const &, const char *, std::shared_ptr<Texture2d> const &) = 0;
};

} // namespace renderer
} // namespace openage
