#ifndef GUARDCUSTOMJETS_HXX
#define GUARDCUSTOMJETS_HXX

#include "ROOT/RDataFrame.hxx"
#include <string>

namespace physicsobject {
namespace jet {

/**
 * @brief Veto jets that overlap with loose leptons within a specified ΔR cone
 * 
 * This function creates a mask to identify jets that should be vetoed due to
 * spatial overlap with loose leptons. Jets within a ΔR cone of any loose lepton
 * are flagged for removal by setting their mask value to 0.
 * 
 * @param df Input RDataFrame node
 * @param output_col Name of the output column containing the veto mask
 * @param jet_eta Column name for jet pseudorapidity
 * @param jet_phi Column name for jet azimuthal angle
 * @param loose_lepton_mask Column name for loose lepton selection mask
 * @param lepton_eta Column name for lepton pseudorapidity
 * @param lepton_phi Column name for lepton azimuthal angle
 * @param deltaRmin Minimum ΔR distance below which jets are vetoed
 * 
 * @return ROOT::RDF::RNode Updated RDataFrame with jet veto mask column
 * 
 * @note The output mask has value 1 for jets to keep, 0 for jets to veto
 * @note If no loose leptons are present, all jets pass (mask = 1)
 * @note Uses geometric distance in η-φ space: ΔR = sqrt(Δη² + Δφ²)
 */
ROOT::RDF::RNode VetoOverlappingJetsLooseLeptons(
    ROOT::RDF::RNode df, 
    const std::string &output_col,
    const std::string &jet_eta, 
    const std::string &jet_phi,
    const std::string &loose_lepton_mask, 
    const std::string &lepton_eta,
    const std::string &lepton_phi, 
    const float &deltaRmin
);

} // namespace jet
} // namespace physicsobject
#endif /* GUARDCUSTOMJETS_HXX */
