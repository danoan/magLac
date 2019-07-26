#ifndef MAGLAC_LAB_TEST_CORE_MULTITHREAD_CORRECTENESS_H
#define MAGLAC_LAB_TEST_CORE_MULTITHREAD_CORRECTENESS_H

#include <vector>
#include <set>

#include "magLac/core/multithread/Trigger.h"
#include "magLac/core/multithread/ThreadInput.h"
#include "magLac/core/multithread/ThreadControl.h"
#include "magLac/core/single/Combinator.hpp"

#include "magLac/lab/logger/logger.h"
#include "magLac/lab/utils/mockUtils.h"
#include "magLac/lab/utils/displayUtils.h"

namespace magLac
{
    namespace Test
    {
        namespace Multithread
        {
            typedef unsigned long int Size;
            typedef std::vector<int> IntVector;

            typedef std::vector< IntVector > CombinationsContainer;
            typedef std::vector< std::set<int> > CombinationsCheckContainer;

            struct CorrectParams{};

            struct CorrectUserVars
            {
                void restart(){};
                std::vector<IntVector> cv;
            };

            bool belongsTo(const std::set<int>& currComb,const CombinationsContainer& combs);
            bool correctenessMultithread(Logger& logger,Size numThreads, Size n, Size k, const CombinationsCheckContainer& checkV);
            bool correcteness(Logger& logger);
        }
    }
}


#endif //MAGLAC_LAB_TEST_CORE_MULTITHREAD_CORRECTENESS_H