#ifndef GUARD_SCALEFACTORSEXT_H
#define GUARD_SCALEFACTORSEXT_H

#include "../../../../include/utility/Logger.hxx"
#include "../../../../include/utility/RooFunctorThreadsafe.hxx"
#include "ROOT/RDataFrame.hxx"
#include "RooFunctor.h"
#include "RooWorkspace.h"
#include "TFile.h"
#include "correction.h"

namespace scalefactor {
    namespace electron {
        ROOT::RDF::RNode trigger(ROOT::RDF::RNode df, const std::string &nom_trigger_output, 
                         const std::string &trigger_output_up, const std::string &trigger_output_down, 
                         const std::string &pt, const std::string &eta, const std::string &nom_sf_file, 
                         const std::string &nom_triggerAlgorithm, const std::string &syst_sf_file, 
                         const std::string &syst_triggerAlgorithm){
                            Logger::get("electronTriggerSF")
                                ->debug("Setting up functions for electron trigger sf");
                            auto evaluator_nom = correction::CorrectionSet::from_file(nom_sf_file)->at(nom_triggerAlgorithm);
                            auto evaluator_syst = correction::CorrectionSet::from_file(syst_sf_file)->at(syst_triggerAlgorithm);
                            auto df1 = df.Define(
                                nom_trigger_output,
                                [evaluator_nom](const float &pt,
                                                const float &eta){
                                                   double sf = 1;
                                                    Logger::get("electronTriggerSF")
                                                        ->debug("Electron - pt {}, eta {}", pt, eta);
                                                    if (pt >= 0.0){
                                                        sf = evaluator_nom->evaluate({eta, pt});
                                                    }
                                                    Logger::get("electronTriggerSF")->debug("Trigger - sf {}", sf);
                                                    return sf;
                                },
                                {pt, eta}       
                            );
                            auto df2 = df1.Define(
                                trigger_output_up,
                                [evaluator_nom, evaluator_syst](const float &pt,
                                                                const float &eta){
                                                                    double sf = 1;
                                                                    if (pt >= 0.0){
                                                                        sf = evaluator_nom->evaluate({eta, pt}) + 
                                                                             evaluator_syst->evaluate({eta, pt});
                                                                    }
                                                                    Logger::get("electronTriggerSF")->debug("Trigger up - sf {}", sf);
                                                                    return sf;
                                },
                                {pt, eta}
                            );
                            auto df3 = df2.Define(
                                trigger_output_down,
                                [evaluator_nom, evaluator_syst](const float &pt,
                                                                const float &eta){
                                                                    double sf = 1;
                                                                    if (pt >= 0.0){
                                                                        sf = evaluator_nom->evaluate({eta, pt}) - 
                                                                             evaluator_syst->evaluate({eta, pt});
                                                                    }
                                                                    Logger::get("electronTriggerSF")->debug("Trigger down - sf {}", sf);
                                                                    return sf;
                                },
                                {pt, eta}
                            );
                            return df3;
        }
    
    }
}
#endif // GUARD_SCALEFACTORSEXT_Hsrc