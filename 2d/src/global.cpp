#include <iostream>
#include <fstream>
#include <string>

#include "inc/global.hpp"

const double constants::pi = 3.14159265e+00;
const double constants::c = 2.99792458e+08;
const double constants::epsilon_0 = 8.85418781e-12;
const complex constants::imag_unit = {0.0, 1.0};

fftw_plan fft::plan;
std::vector<complex> fft::data;

void fft::create_plan_1d(int dim_1, int sign) {
	data.resize(dim_1);
	plan = fftw_plan_dft_1d(data.size(), reinterpret_cast<fftw_complex*>(data.data()), reinterpret_cast<fftw_complex*>(data.data()), sign, FFTW_MEASURE);
}

std::vector<complex> fft::execute_plan(std::vector<complex> in) {
	data.assign(in.begin(), in.end());
	fftw_execute(plan);
	return data;
}

void fft::destroy_plan() {
	fftw_destroy_plan(plan);
}

void tools::multiply_array(array_2d<complex>& field, const double scalar) {
	for(size_t i = 0; i < field.num_elements(); i++) {
		field.data()[i] *= scalar;
	}
}

std::vector<complex> tools::row_to_vec(view_1d row) {
	size_t counter = 0;
	std::vector<complex> vec(row.shape()[0]);
	for(size_t i = 0; i < row.shape()[0]; i++) {
		vec[counter++] = row[i];
	}
	return vec;
}

void tools::vec_to_row(view_1d& row, std::vector<complex> vec) {
	size_t counter = 0;
	for(size_t i = 0; i < row.shape()[0]; i++) {
		row[i] = vec[counter++];
	}
}

std::vector<double> tools::get_real(array_2d<complex> field, std::array<int, 2> size) {
	std::vector<double> real_part(size[0] * size[1]);
	size_t counter = 0;
	for(auto j = 0; j < size[1]; j++) {
		for(auto i = 0; i < size[0]; i++) {
			real_part[counter++] = std::real(field[i][j]);
		}
	}
	return real_part;
}