#include <iostream>
#include "tocha/tensor.hh"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
	std::cerr << "Usage: tbin-dump <file-path>" << std::endl;
	return 1;
    }

    tocha::Tensors::load(argv[1]).dump(std::cout);
    return 0;
}
