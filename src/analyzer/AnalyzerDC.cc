/**
 * @file DC analysis
 */

/*
 *  FastCSIM Copyright (C) 2021 cassuto                                    
 *  This project is free edition; you can redistribute it and/or           
 *  modify it under the terms of the GNU Lesser General Public             
 *  License(GPL) as published by the Free Software Foundation; either      
 *  version 2.1 of the License, or (at your option) any later version.     
 *                                                                         
 *  This project is distributed in the hope that it will be useful,        
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      
 *  Lesser General Public License for more details.                        
 */

#include "csim/model/ModelBase.h"
#include "csim/utils/errors.h"
#include "csim/internal/Netlist.h"
#include "csim/internal/Circuit.h"
#include "csim/internal/Dataset.h"
#include "csim/internal/AnalyzerDC.h"

namespace csim
{

    AnalyzerDC::AnalyzerDC(Circuit *circuit)
        : AnalyzerBase(circuit)
    {
    }
    AnalyzerDC::~AnalyzerDC()
    {
    }

    int AnalyzerDC::analyze(Dataset *dataset)
    {
        /*
         * Format data set
         */
        dataset->clear();
        dataset->setName("DC analysis");
        unsigned int N = getNumInterestNodes(), M = getNumInterestBranches();
        std::vector<Variable *> dvolt(N), dcurrent(M);
        for (unsigned int i = 0; i < N; ++i)
        {
            std::string varName = makeVarName("V", getInterestNode(i));
            dvolt[i] = &dataset->addDependentVar("voltage", varName);
        }
        for (unsigned int i = 0; i < M; ++i)
        {
            std::string varName = makeVarName("I", getInterestBranch(i));
            dcurrent[i] = &dataset->addDependentVar("current", varName);
        }

        UPDATE_RC(circuit()->initMNA(this));
        UPDATE_RC(circuit()->solveMNA(this));

        /* Save the result */
        for (unsigned int i = 0; i < N; ++i)
        {
            dvolt[i]->addValue(circuit()->getNodeVolt(getInterestNode(i)));
        }
        for (unsigned int i = 0; i < M; ++i)
        {
            dcurrent[i]->addValue(circuit()->getBranchCurrent(getInterestBranch(i)));
        }

        return 0;
    }

    int AnalyzerDC::prepareMNA()
    {
        for (auto &mif : circuit()->netlist()->models())
        {
            UPDATE_RC(mif.model->prepareDC());
        }
        return 0;
    }

    int AnalyzerDC::iterateMNA()
    {
        for (auto &mif : circuit()->netlist()->models())
        {
            UPDATE_RC(mif.model->iterateDC());
        }
        return 0;
    }

}
