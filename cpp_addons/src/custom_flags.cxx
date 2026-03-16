#ifndef GUARD_FLAGSEXT_H
#define GUARD_FLAGSEXT_H

#include "../../../../include/utility/Logger.hxx"
#include "../../../../include/utility/RooFunctorThreadsafe.hxx"
#include "ROOT/RDataFrame.hxx"
#include "RooFunctor.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "correction.h"

namespace flags {
/**
 * @brief Flag events where at least one object passes a selection mask
 *
 * Creates a boolean flag column that is `true` if any element in the given
 * integer mask vector equals 1, indicating that at least one object in the
 * event satisfies the corresponding selection criteria.
 *
 * @param df Input RDataFrame node
 * @param flagname Name of the output boolean flag column to define
 * @param maskname Name of the input column containing the integer selection
 * mask (1 = object passes, 0 = object fails)
 *
 * @return ROOT::RDF::RNode Updated RDataFrame with the boolean flag column
 *
 * @note Returns `false` for events where no object passes (all mask entries
 * are 0), which can be used downstream to filter out such events
 */
    ROOT::RDF::RNode flagMask(ROOT::RDF::RNode df, const std::string &flagname,
                               const std::string &maskname){
                                using namespace ROOT::VecOps;
                                return df.Define(
                                    flagname,
                                    [](const ROOT::RVec<int> &mask) { return bool(Any(mask == 1)); },
                                    {maskname}
                                );
                               };
}
#endif /* GUARD_FLAGSEXT_H */