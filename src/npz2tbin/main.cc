#include <iostream>
#include "tocha/tensor.hh"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
	std::cerr << "Usage: npz2tbin <input-file> <ouput-file>" << std::endl;
	return 1;
    }

    tocha::Tensors::load_npz(argv[1]).save_tbin(argv[2]);
    return 0;
}
