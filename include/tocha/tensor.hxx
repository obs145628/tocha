#pragma GCC diagnostic ignored "-Wunused-result"

#include "tensor.hh"
#include <algorithm>
#include <stdexcept>
#include "../../ext/cnpy/cnpy.hh"

#pragma once

namespace tocha
{

    inline Tensor::Tensor(Tensor&& t)
	: type(t.type)
	, size(t.size)
	, dims(t.dims)
	, total_len(t.total_len)
	, data(t.data)
    {
	t.data = nullptr;
    }
    
    inline Tensor::~Tensor()
    {
	delete[] data;
    }

    inline Tensor Tensor::f64(double* data)
    {
	if (data == nullptr)
	    data = new double[1];

	Tensor t;
	t.type = TENSOR_FLOAT;
	t.size = 8;
	t.total_len = 1;
	t.data = reinterpret_cast<uint8_t*>(data);
	return t;
    }

    inline Tensor Tensor::f64(int d1, double* data)
    {
	size_t len = d1;
	if (data == nullptr)
	    data = new double[len];

	Tensor t;
	t.type = TENSOR_FLOAT;
	t.size = 8;
	t.dims = {d1};
	t.total_len = len;
	t.data = reinterpret_cast<uint8_t*>(data);
	return t;
    }

    inline Tensor Tensor::f64(int d1, int d2, double* data)
    {
	size_t len = d1 * d2;
	if (data == nullptr)
	    data = new double[len];

	Tensor t;
	t.type = TENSOR_FLOAT;
	t.size = 8;
	t.dims = {d1, d2};
	t.total_len = len;
	t.data = reinterpret_cast<uint8_t*>(data);
	return t;
    }

    inline Tensor Tensor::f64(int d1, int d2, int d3, double* data)
    {
	size_t len = d1 * d2 * d3;
	if (data == nullptr)
	    data = new double[len];

	Tensor t;
	t.type = TENSOR_FLOAT;
	t.size = 8;
	t.dims = {d1, d2, d3};
	t.total_len = len;
	t.data = reinterpret_cast<uint8_t*>(data);
	return t;
    }

    inline Tensor Tensor::f64(int d1, int d2, int d3, int d4, double* data)
    {
	size_t len = d1 * d2 * d3 * d4;
	if (data == nullptr)
	    data = new double[len];

	Tensor t;
	t.type = TENSOR_FLOAT;
	t.size = 8;
	t.dims = {d1, d2, d3, d4};
	t.total_len = len;
	t.data = reinterpret_cast<uint8_t*>(data);
	return t;
    }

    inline Tensor Tensor::f32(float* data)
    {
	if (data == nullptr)
	    data = new float[1];

	Tensor t;
	t.type = TENSOR_FLOAT;
	t.size = 4;
	t.total_len = 1;
	t.data = reinterpret_cast<uint8_t*>(data);
	return t;
    }

    inline Tensor Tensor::f32(int d1, float* data)
    {
	size_t len = d1;
	if (data == nullptr)
	    data = new float[len];

	Tensor t;
	t.type = TENSOR_FLOAT;
	t.size = 4;
	t.dims = {d1};
	t.total_len = len;
	t.data = reinterpret_cast<uint8_t*>(data);
	return t;
    }

    inline Tensor Tensor::f32(int d1, int d2, float* data)
    {
	size_t len = d1 * d2;
	if (data == nullptr)
	    data = new float[len];

	Tensor t;
	t.type = TENSOR_FLOAT;
	t.size = 4;
	t.dims = {d1, d2};
	t.total_len = len;
	t.data = reinterpret_cast<uint8_t*>(data);
	return t;
    }

    inline Tensor Tensor::f32(int d1, int d2, int d3, float* data)
    {
	size_t len = d1 * d2 * d3;
	if (data == nullptr)
	    data = new float[len];

	Tensor t;
	t.type = TENSOR_FLOAT;
	t.size = 4;
	t.dims = {d1, d2, d3};
	t.total_len = len;
	t.data = reinterpret_cast<uint8_t*>(data);
	return t;
    }

    inline Tensor Tensor::f32(int d1, int d2, int d3, int d4, float* data)
    {
	size_t len = d1 * d2 * d3 * d4;
	if (data == nullptr)
	    data = new float[len];

	Tensor t;
	t.type = TENSOR_FLOAT;
	t.size = 4;
	t.dims = {d1, d2, d3, d4};
	t.total_len = len;
	t.data = reinterpret_cast<uint8_t*>(data);
	return t;
    }


    template <class T>
    void print_vec(std::ostream& os, const uint8_t* begin, std::size_t len)
    {
	os << "{";
	auto it = reinterpret_cast<const T*>(begin);
	for (std::size_t i = 0; i < len; ++i)
        {
	    os << it[i];
	
	    if (i + 1 != len)
	    {
		os << ", ";
		if (i > 15 && i + 2 != len)
		{
		    os << "..., ";
		    i = len - 2;
		}
	    }
	}
	os << "}";
    }

    inline void Tensor::dump(std::ostream& os) const
    {
	dump_type(os);
	dump_dims(os);
	os << " ";

	if (type == 1 && size == 4)
	    print_vec<std::int32_t>(os, data, total_len);
	else if (type == 1 && size == 8)
	    print_vec<std::int64_t>(os, data, total_len);	
	else if (type == 0 && size == 4)
	    print_vec<float>(os, data, total_len);
	else if (type == 0 && size == 8)
	    print_vec<double>(os, data, total_len);
	else
	    os << "???";
	os << std::endl;
    }

    inline void Tensor::dump_type(std::ostream& os) const
    {
	const char* types = "fi";
	os << types[type] << int(size * 8);
    }
    
    inline void Tensor::dump_dims(std::ostream& os) const
    {
	os << "(";
	for (size_t i = 0; i < dims.size(); ++i)
	{
	    os << dims[i];
	    if (i + 1 != dims.size())
		os << "*";
	}
	os << ")";
    }

    inline bool Tensor::same_type(const Tensor& t) const
    {
	return type == t.type && size == t.size; 
    }
    
    inline bool Tensor::same_dims(const Tensor& t) const
    {
	return dims == t.dims;
    }

    template <class T>
    double vec_distance(const uint8_t* data1, const uint8_t* data2, size_t len)
    {
	auto beg1 = reinterpret_cast<const T*>(data1);
	auto end1 = beg1 + len;
	auto beg2 = reinterpret_cast<const T*>(data2);
	double res = 0;

	while (beg1 != end1)
	{
	    res += (*beg2 - *beg1) * (*beg2 - *beg1);
	    ++beg1;
	    ++beg2;
	}

	return res;
    }
    
    inline double Tensor::distance(const Tensor& t) const
    {
	if (type == 1 && size == 4)
	    return vec_distance<std::int32_t>(data, t.data, total_len);
	else if (type == 1 && size == 8)
	    return vec_distance<std::int64_t>(data, t.data, total_len);
	else if (type == 0 && size == 4)
	    return vec_distance<float>(data, t.data, total_len);
	else if (type == 0 && size == 8)
	    return vec_distance<double>(data, t.data, total_len);
	else
	    return 1234;
    }
	    

    inline std::string path_extract_ext(const std::string& path)
    {
	std::string::size_type pos = path.rfind('.');
	if (pos == std::string::npos)
	    return "";
	else
	    return path.substr(pos);
    }

    inline Tensors Tensors::load(const std::string& path)
    {
	auto ext = path_extract_ext(path);
	if (ext == ".npz")
	    return load_npz(path);
	else
	    return load_tbin(path);
    }

    inline Tensors Tensors::load_npz(const std::string& path)
    {
	Tensors res;
	cnpy::npz_t npz = cnpy::npz_load(path);

	for (const auto& it : npz)
	{
	    const auto& val = it.second;
	    Tensor t;
	    
	    t.type = TENSOR_FLOAT; //[FIXNE] how to find data type ?
	    t.size = val.word_size;

	    t.dims = std::vector<int>(val.shape.size());
	    for (std::size_t i = 0; i < val.shape.size(); ++i)
		t.dims[i] = val.shape[i];

	    t.total_len = val.num_vals;
	    t.data = new std::uint8_t[t.total_len * t.size];
	    std::copy_n(val.data<std::uint8_t>(), t.total_len * t.size, t.data);
	    
	    res.add(std::move(t));
	}
	
	return res;
    }

    inline Tensors Tensors::load_tbin(const std::string& path)
    {
	FILE* f = fopen(path.c_str(), "rb");
	if (!f)
	    throw std::runtime_error{"Cannot open file '" + path + "' for reading"};

	Tensors res;
	std::uint16_t ntensors;
	(void) fread(&ntensors, sizeof(std::uint16_t), 1, f);

	for (std::uint16_t i = 0; i < ntensors; ++i)
	{
	    Tensor t;
	    std::uint8_t type;
	    std::uint8_t size;
	    std::uint8_t ndims;	
	    (void) fread(&type, sizeof(std::uint8_t), 1, f);
	    (void) fread(&size, sizeof(std::uint8_t), 1, f);
	    (void) fread(&ndims, sizeof(std::uint8_t), 1, f);
	    t.type = type;
	    t.size = size;
	    t.dims = std::vector<int>(ndims);
	    (void) fread(&t.dims[0], sizeof(int), ndims, f);

	    t.total_len = 1;
	    for (std::uint8_t i = 0; i < ndims; ++i)
		t.total_len *= t.dims[i];

	    t.data = new std::uint8_t[t.total_len * t.size];
	    (void) fread(&t.data[0], t.size, t.total_len, f);
	    res.add(std::move(t));
	}

	fclose(f);
	return res;
    }

    inline void Tensors::add(Tensor&& t)
    {
	arr_.push_back(std::move(t));
    }

    inline void Tensors::dump(std::ostream& os) const
    {
	for (const auto& t : arr_)
	{
	    t.dump(os);
	    os << std::endl;
	}
    }

    inline void Tensors::save(const std::string& path) const
    {
	auto ext = path_extract_ext(path);
	if (ext == ".npz")
	    save_npz(path);
	else
	    save_tbin(path);
    }

    inline void Tensors::save_npz(const std::string&) const
    {
	//[TODO] Implement save_npz
	throw std::runtime_error{"Saving to npz file not implemented"};
    }
    
    inline void Tensors::save_tbin(const std::string& path) const
    {
	FILE* f = fopen(path.c_str(), "wb");
	if (!f)
	    throw std::runtime_error{"Cannot open file '" + path + "' for writing"};
	
	std::uint16_t ntensors = arr_.size();
	fwrite(&ntensors, sizeof(std::uint16_t), 1, f);

	for (const auto& t: arr_)
	{
	    std::uint8_t type = t.type;
	    std::uint8_t size = t.size;
	    std::uint8_t ndims = t.dims.size();
	    fwrite(&type, sizeof(std::uint8_t), 1, f);
	    fwrite(&size, sizeof(std::uint8_t), 1, f);
	    fwrite(&ndims, sizeof(std::uint8_t), 1, f);

	    fwrite(&t.dims[0], sizeof(int), t.dims.size(), f);
	    fwrite(&t.data[0], t.size, t.total_len, f);
	}

	fclose(f);
    }

    inline const std::vector<Tensor>& Tensors::arr() const
    {
	return arr_;
    }
}
