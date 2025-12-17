#ifndef GUARDCUSTOMJETS_H
#define GUARDCUSTOMJETS_H

#include "../include/custom_jets.hxx"
#include "../../../../include/defaults.hxx"
#include "../../../../include/utility/CorrectionManager.hxx"
#include "../../../../include/utility/Logger.hxx"
#include "../../../../include/utility/utility.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "TRandom3.h"
#include "correction.h"
#include <Math/Vector3D.h>
#include <Math/Vector4D.h>
#include <Math/VectorUtil.h>
#include <cmath>
#include <typeinfo>

/// Namespace for custom jet operations
namespace physicsobject {
namespace jet {

/**
 * @brief Veto jets that overlap with loose leptons within a specified ΔR cone
 * 
 * This function creates a mask to identify jets that should be vetoed due to
 * spatial overlap with loose leptons. Jets within a ΔR cone of any loose lepton
 * are flagged for removal by setting their mask value to 0. This is commonly used
 * to prevent double-counting of objects or to clean jet collections from lepton
 * contamination.
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
 * @note Once a jet is matched to any lepton, the loop breaks (no need to check other leptons)
 */
ROOT::RDF::RNode
VetoOverlappingJetsLooseLeptons(ROOT::RDF::RNode df, const std::string &output_col,
				  const std::string &jet_eta, const std::string &jet_phi,
				  const std::string &loose_lepton_mask, const std::string &lepton_eta,
				  const std::string &lepton_phi, const float &deltaRmin) {

  auto df1 = df.Define(
		       output_col,
		       [deltaRmin](const ROOT::RVec<float> &jet_eta,
				   const ROOT::RVec<float> &jet_phi,
				   const ROOT::RVec<int> &loose_lepton_mask,
				   const ROOT::RVec<float> &lepton_eta,
				   const ROOT::RVec<float> &lepton_phi) {
			 Logger::get("VetoOverlappingJetsLooseLeptons")->debug("Checking jets");
			 ROOT::RVec<int> mask(jet_eta.size(), 1);
			 const auto loose_leptons = ROOT::VecOps::Nonzero(loose_lepton_mask);
			 if (loose_leptons.size() == 0) {
			   return mask;
			 }
			 auto loose_lepton_eta = ROOT::VecOps::Take(lepton_eta, loose_leptons);
			 auto loose_lepton_phi = ROOT::VecOps::Take(lepton_phi, loose_leptons);
			 for (std::size_t idx = 0; idx < mask.size(); ++idx) {
			   ROOT::Math::RhoEtaPhiVectorF jet(0, jet_eta.at(idx), jet_phi.at(idx));
			   Logger::get("VetoOverlappingJetsLooseLeptons")
			     ->debug("Jet:  Eta: {} Phi: {} ", jet.Eta(), jet.Phi());
			   for (int i = 0; i < loose_lepton_eta.size(); i++) {
			     ROOT::Math::RhoEtaPhiVectorF loose_lepton(0, loose_lepton_eta.at(i), loose_lepton_phi.at(i));
			     Logger::get("VetoOverlappingJetsLooseLeptons")
			       ->debug("Loose letpon:  Eta: {} Phi: {}", loose_lepton.Eta(), loose_lepton.Phi());
			     auto deltaR = ROOT::Math::VectorUtil::DeltaR(jet, loose_lepton);
			     Logger::get("VetoOverlappingJetsLooseLeptons")
			       ->debug("DeltaR: {}", deltaR);
			     if (deltaR < deltaRmin) {
			       mask[idx] = 0;
			       break;
			     }
			   }
			 }
			 Logger::get("VetoOverlappingJetsLooseLeptons")
			 ->debug("vetomask due to overlap: {}", mask);
			 return mask;
		       },
		       {jet_eta, jet_phi, loose_lepton_mask, lepton_eta, lepton_phi});
  return df1;
}

}
}
#endif