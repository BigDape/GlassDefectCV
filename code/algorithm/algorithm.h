#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "HSAlgorithmInterface.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "processtile.h"


class Algorithm: public AlgorithmNamespace::HSAlgorithmInterface
{
public:
    Algorithm(){}
    virtual ~Algorithm(){}
    virtual void init() override;
    virtual void Execu() override;
    virtual void Stop() override;
    virtual void Exit() override;

private:
    std::shared_ptr<ProcessTile> proPtr;

};

#endif // ALGORITHM_H
