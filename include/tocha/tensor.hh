#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

namespace tocha
{

    static constexpr int TENSOR_FLOAT = 0;
    static constexpr int TENSOR_INT = 1;
    

    class Tensor
    {
    public:
	Tensor() = default;
	Tensor(const Tensor&) = delete;
	Tensor(Tensor&&);
	Tensor& operator=(const Tensor&) = delete;
	Tensor& operator=(Tensor&&) = delete;
	~Tensor();

	static Tensor f64(double* data = nullptr);
	static Tensor f64(int d1, double* data = nullptr);
	static Tensor f64(int d1, int d2, double* data = nullptr);
	static Tensor f64(int d1, int d2, int d3, double* data = nullptr);
	static Tensor f64(int d1, int d2, int d3, int d4, double* data = nullptr);


	void dump(std::ostream& os) const;
	void dump_type(std::ostream& os) const;
	void dump_dims(std::ostream& os) const;
	bool same_type(const Tensor& t) const;
	bool same_dims(const Tensor& t) const;
	double distance(const Tensor& t) const;
	
	int type;
	size_t size;
	std::vector<int> dims;
	size_t total_len;
	uint8_t* data;
    };

    class Tensors
    {
    public:
	Tensors() = default;
	~Tensors() = default;
	Tensors(const Tensors&) = delete;
	Tensors(Tensors&&) = default;
	Tensors& operator=(const Tensors&) = delete;
	Tensors& operator=(Tensors&&) = delete;

	static Tensors load(const std::string& path);

	static Tensors load_npz(const std::string& path);
	static Tensors load_tbin(const std::string& path);

	void add(Tensor&& t);
	void dump(std::ostream& os) const;
	void save(const std::string& path) const;
	void save_npz(const std::string& path) const;
	void save_tbin(const std::string& path) const;

	const std::vector<Tensor>& arr() const;

    private:
	std::vector<Tensor> arr_;
    };

}

#include "tensor.hxx"

