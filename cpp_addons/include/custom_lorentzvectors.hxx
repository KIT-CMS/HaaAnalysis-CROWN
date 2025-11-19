#ifndef GUARD_CUSTOM_LORENTZVECTOR_H
#define GUARD_CUSTOM_LORENTZVECTOR_H

#include "ROOT/RDFHelpers.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include <Math/Vector4D.h>

namespace lorentzvector {
    ROOT::RDF::RNode buildKaon(ROOT::RDF::RNode df,
                           const std::vector<std::string> &quantities,
                           const std::string &outputname,
                           const int &position);
    ROOT::RDF::RNode buildFromPFCand(ROOT::RDF::RNode df,
                                 const std::vector<std::string> &obj_quantities,
                                 const int pairindex,
                                 const std::string &obj_p4_name);
}

#endif /* GUARD_CUSTOM_LORENTZVECTOR_H */