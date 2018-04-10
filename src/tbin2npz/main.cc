#include <iostream>
#include "tocha/tensor.hh"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
	std::cerr << "Usage: tbin2npz <input-file> <ouput-file>" << std::endl;
	return 1;
    }

    tocha::Tensors::load_tbin(argv[1]).save_npz(argv[2]);
    return 0;
}
