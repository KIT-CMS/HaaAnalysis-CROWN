#ifndef GUARDLORENTZVECTOREXT_H
#define GUARDLORENTZVECTOREXT_H

#include "../../../../include/defaults.hxx"
#include "../../../../include/utility/Logger.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include <Math/Vector4D.h>

/// Namespace used for lorentzvector operations

namespace lorentzvector {

    /**
     * @brief Build a kaon four-momentum vector from a PF candidate with fixed kaon mass
     * 
     * This function constructs a Lorentz vector for a kaon by taking kinematic quantities
     * (pt, eta, phi) from a PF candidate and assigning the PDG kaon mass (0.493677 GeV).
     * PF candidates are typically assigned the pion mass by default, so this function
     * corrects the mass assumption for kaon candidates.
     * 
     * @param df Input RDataFrame node
     * @param quantities Vector of column names containing: [pair indices, pts, etas, phis, masses]
     * @param outputname Name of the output column containing the kaon four-vector
     * @param position Index within the pair vector to identify which PF candidate to use
     * 
     * @return ROOT::RDF::RNode Updated RDataFrame with the new kaon four-vector column
     * 
     * @note If the index is out of range, a dummy vector with default_float values is returned
     * @note The kaon mass is hardcoded to 0.493677 GeV (PDG value)
     */
    ROOT::RDF::RNode buildKaon(ROOT::RDF::RNode df,
                               const std::vector<std::string> &quantities,
                               const std::string &outputname,
                               const int &position) {
    auto df1 = df.Define(
        outputname,
        [position, outputname](
            const ROOT::RVec<int> &pair, const ROOT::RVec<float> &pts,
            const ROOT::RVec<float> &etas, const ROOT::RVec<float> &phis,
            const ROOT::RVec<float> &masses) {
            // the index of the particle is stored in the pair vector
            ROOT::Math::PtEtaPhiMVector p4;
            Logger::get("lorentzvectors")
                ->debug("starting to build 4vector {}!", outputname);
            try {
                const int index = pair.at(position);
                Logger::get("lorentzvectors")->debug("pair {}", pair);
                Logger::get("lorentzvectors")->debug("pts {}", pts);
                Logger::get("lorentzvectors")->debug("etas {}", etas);
                Logger::get("lorentzvectors")->debug("phis {}", phis);
                //Logger::get("lorentzvectors")->debug("masses {}", masses);
                Logger::get("lorentzvectors")->debug("Index {}", index);

                p4 = ROOT::Math::PtEtaPhiMVector(pts.at(index), etas.at(index),
                                                 phis.at(index),
                                                 0.493677);
            } catch (const std::out_of_range &e) {
                p4 = ROOT::Math::PtEtaPhiMVector(default_float, default_float,
                                                 default_float, default_float);
                Logger::get("lorentzvectors")
                    ->debug("Index not found, retuning dummy vector !");
            }
            Logger::get("lorentzvectors")
                ->debug("P4 - Particle {} : {}", position, p4);
            return p4;
        },
        quantities);
    return df1;
    }
    /**
     * @brief Wrapper function to build a four-momentum vector from a PF candidate
     * 
     * This is a convenience wrapper around buildKaon() that constructs a Lorentz vector
     * from PF candidate kinematic quantities. It provides logging of the input quantities
     * and delegates to buildKaon() for the actual four-vector construction with fixed
     * kaon mass (0.493677 GeV).
     * 
     * @param df Input RDataFrame node
     * @param obj_quantities Vector of column names containing: [pair indices, pts, etas, phis, masses]
     * @param pairindex Index within the pair vector to identify which PF candidate to use
     * @param obj_p4_name Name of the output column containing the four-vector
     * 
     * @return ROOT::RDF::RNode Updated RDataFrame with the new four-vector column
     * 
     * @note This function logs the construction process and input quantities for debugging
     * @note Internally calls buildKaon() which assigns the kaon mass to the PF candidate
     */
    ROOT::RDF::RNode buildFromPFCand(ROOT::RDF::RNode df,
                       const std::vector<std::string> &obj_quantities,
                       const int pairindex, const std::string &obj_p4_name) {
    Logger::get("lorentzvector")->debug("Building {}", obj_p4_name);
    for (auto i : obj_quantities)
        Logger::get("lorentzvector")->debug("Used object quantities {}", i);
    return lorentzvector::buildKaon(df, obj_quantities, obj_p4_name,
                                         pairindex);
    } 
}
#endif /* GUARD_CUSTOM_LORENTZVECTOR_H */