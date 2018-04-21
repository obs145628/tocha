#include <iostream>
#include "tocha/tensor.hh"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
	std::cerr << "Usage: tbin-diff <file1> <file2>" << std::endl;
	return 1;
    }

    auto l1 = tocha::Tensors::load(argv[1]);
    auto l2 = tocha::Tensors::load(argv[2]);
    std::ostream& os = std::cout;
    double delta = 1e-5;

    if (l1.arr().size() != l2.arr().size())
    {
	os << "Invalid number of tensors: "
	   << l1.arr().size() << " != " << l2.arr().size() << std::endl;
	return 1;
    }

    bool onef = false;

    for (std::size_t i = 0; i < l1.arr().size(); ++i)
    {
	const auto& t1 = l1.arr()[i];
	const auto& t2 = l2.arr()[i];
	bool valid = true;

	double diff = 0;

	if (!t1.same_type(t2))
	{
	    valid = false;
	    os << "tensor types differ" << std::endl;
	}
	else if (!t1.same_dims(t2))
	{
	    valid = false;
	    os << "tensor shapes differ" << std::endl;
	}

	else
	{
	    diff = t1.distance(t2);
	    if (diff > delta)
	    {
		os << "tensor's difference is too big: " << diff << std::endl;
		valid = false;
	    }
	}

	if (valid)
	{
	    t1.dump_type(os);
	    t1.dump_dims(os);
	    os << ": diff = " << diff << std::endl;
	}
	else
	{
	    t1.dump(os);
	    t2.dump(os);
	    onef = true;
	}
    }

    return onef;
}
