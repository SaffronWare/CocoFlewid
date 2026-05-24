#include "Fluid.h"

void Fluid::Init(int res_x, float aspect)
{
	num_grids_x = res_x;
	max_x = aspect;
	num_grids_y = res_x / aspect;
	density = ambient_air_density;

	glGenTextures(1, &data_texture);
	glBindTexture(GL_TEXTURE_2D, data_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, num_grids_x, num_grids_y, 0, GL_RGBA, GL_FLOAT, nullptr);



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &density_texture);
	glBindTexture(GL_TEXTURE_2D, density_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, num_grids_x, num_grids_y, 0, GL_RGBA, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	std::string enforcer_source = read_file("shaders/fluid_enforcer.glsl");
	enforcer.CreateCompute(enforcer_source.c_str());

	std::string advector_source = read_file("shaders/fluid_advector.glsl");
	advector.CreateCompute(advector_source.c_str());

	std::string updater_source = read_file("shaders/update_velocities.glsl");
	updater.CreateCompute(updater_source.c_str());
	std::cout << "Initialized a fluid with " << num_grids_x << " x grids and " << num_grids_y << " y grids.\n";
	


	grid_size_uniform = enforcer.get_loc("grid_size");
	a_dt_uniform = advector.get_loc("dt");
	a_grid_size_uniform = advector.get_loc("grid_size");

}

Fluid::Fluid()  {}

void Fluid::update(float dt)
{

	std::cout << dt << std::endl;

	enforcer.Use();

	glUniform1f(grid_size_uniform, 2*max_x / num_grids_x);
	glBindImageTexture(0, data_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

	for (int i = 0; i < 10; i++)
	{

		glDispatchCompute(num_grids_x / compute_group_size, num_grids_y / compute_group_size, 1);


		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
	}

	advector.Use();
	glUniform1f(a_dt_uniform, 0.0f);
	glUniform1f(a_grid_size_uniform, 2 * max_x / num_grids_x);
	glBindImageTexture(0, data_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glBindImageTexture(1, density_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glDispatchCompute(num_grids_x / compute_group_size, num_grids_y / compute_group_size, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);

	updater.Use();
	glBindImageTexture(0, data_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glBindImageTexture(1, density_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glDispatchCompute(num_grids_x / compute_group_size, num_grids_y / compute_group_size, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);



}

Fluid::~Fluid()
{
	glDeleteTextures(1, &data_texture);
}