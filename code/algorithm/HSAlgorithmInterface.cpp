#include "HSAlgorithmInterface.h"
#include "algorithm.h"

std::unique_ptr<AlgorithmNamespace::HSAlgorithmInterface> AlgorithmNamespace::createAlgorithmObject()
{
    std::unique_ptr<AlgorithmNamespace::HSAlgorithmInterface> ptr = std::make_unique<Algorithm>();
    return ptr;
}
