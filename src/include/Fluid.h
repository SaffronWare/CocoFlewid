#pragma once

#include "CocoFramework.h"
#include <glm/glm.hpp>
#include <vector>

constexpr unsigned int compute_group_size = 16;

// all SI units
const float ambient_pressure = 101.325f;
const float ambient_temperature = 25.0f;
const float air_gas_constant = 287.0f;
const float ambient_air_density = 1.2f;


// defined
struct Fluid
{
	float density;
	float max_x = 1.0f;
	float max_y = 1.0f;
	unsigned int num_grids_x;
	unsigned int num_grids_y;
	unsigned int data_texture;
	unsigned int density_texture;

	Shader enforcer;
	Shader advector;
	Shader updater;
	unsigned int dt_uniform;
	unsigned int grid_size_uniform;
	unsigned int a_dt_uniform;
	unsigned int a_grid_size_uniform;


	Fluid();
	void Init(int res_x, float aspect);

	void update(float dt);

	~Fluid();
};