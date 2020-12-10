#ifndef  _MODEL_H_
#define  _MODEL_H_

#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class SVM {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        float kernels[4] = { 0 };
                        float decisions[1] = { 0 };
                        int votes[2] = { 0 };
                        kernels[0] = compute_kernel(x,   5980.0  , 18428.0  , 10828.0  , 5968.0  , 18904.0  , 11064.0  , 5844.0  , 18836.0  , 11060.0  , 5944.0  , 18440.0  , 11076.0  , 5932.0  , 18708.0  , 11000.0  , 5480.0  , 18884.0  , 10948.0  , 5600.0  , 18816.0  , 11032.0  , 5672.0  , 18804.0  , 11156.0  , 5524.0  , 18896.0  , 10992.0  , 5488.0  , 18912.0  , 10956.0 );
                        kernels[1] = compute_kernel(x,   5340.0  , 17912.0  , 12524.0  , 4928.0  , 18108.0  , 12300.0  , 4712.0  , 18408.0  , 12108.0  , 5108.0  , 18076.0  , 12652.0  , 4600.0  , 18512.0  , 12012.0  , 5348.0  , 18932.0  , 12192.0  , 4164.0  , 18436.0  , 12600.0  , 4472.0  , 18256.0  , 12356.0  , 4508.0  , 18248.0  , 12324.0  , 4768.0  , 18480.0  , 12356.0 );
                        kernels[2] = compute_kernel(x,   4944.0  , 18056.0  , 12424.0  , 4616.0  , 18340.0  , 12176.0  , 4784.0  , 18188.0  , 12128.0  , 4748.0  , 18420.0  , 12036.0  , 4652.0  , 18944.0  , 12008.0  , 4492.0  , 17888.0  , 12412.0  , 4692.0  , 17720.0  , 12476.0  , 4312.0  , 18396.0  , 12288.0  , 4384.0  , 18404.0  , 12180.0  , 4932.0  , 18948.0  , 12156.0 );
                        kernels[3] = compute_kernel(x,   4848.0  , 18200.0  , 12328.0  , 4504.0  , 18116.0  , 12484.0  , 4064.0  , 18704.0  , 12412.0  , 4512.0  , 18356.0  , 13080.0  , 6976.0  , 17944.0  , 11344.0  , 7552.0  , 17820.0  , 11172.0  , 7444.0  , 18076.0  , 11592.0  , 7244.0  , 16900.0  , 12240.0  , 5920.0  , 17588.0  , 12792.0  , 4636.0  , 17192.0  , 12872.0 );
                        float decision = -0.265314714729;
                        decision = decision - ( + kernels[0] * -7.4048e-08 );
                        decision = decision - ( + kernels[1] * 1.8618e-08  + kernels[2] * 3.5928e-08  + kernels[3] * 1.9502e-08 );

                        return decision > 0 ? 0 : 1;
                    }

                    /**
                    * Convert class idx to readable name
                    */
                    const char* predictLabel(float *x) {
                        switch (predict(x)) {
                            case 0:
                            return "drinking";
                            case 1:
                            return "eating";
                            default:
                            return "Houston we have a problem";
                        }
                    }

                protected:
                    /**
                    * Compute kernel between feature vector and support vector.
                    * Kernel type: linear
                    */
                    float compute_kernel(float *x, ...) {
                        va_list w;
                        va_start(w, 30);
                        float kernel = 0.0;

                        for (uint16_t i = 0; i < 30; i++) {
                            kernel += x[i] * va_arg(w, double);
                        }

                        return kernel;
                    }
                };
            }
        }
    }


#endif
