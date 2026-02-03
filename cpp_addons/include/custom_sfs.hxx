#ifndef GUARD_SCALEFACTORSEXT_H
#define GUARD_SCALEFACTORSEXT_H

#include "ROOT/RDataFrame.hxx"
#include <string>

namespace scalefactor {
    namespace electron {
        ROOT::RDF::RNode trigger(ROOT::RDF::RNode df, const std::string &nom_trigger_output, 
                         const std::string &trigger_output_up, const std::string &trigger_output_down, 
                         const std::string &pt, const std::string &eta, const std::string &nom_sf_file, 
                         const std::string &nom_triggerAlgorithm, const std::string &syst_sf_file, 
                         const std::string &syst_triggerAlgorithm);
    }
}

#endif // GUARD_SCALEFACTORSEXT_H
