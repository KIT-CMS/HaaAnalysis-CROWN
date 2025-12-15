from ..quantities import output as q
from ..quantities import nanoAOD as nanoAOD
from code_generation.producer import Producer, ProducerGroup

####################
# Set of producers to get the genParticles from the ditaupair
####################
MMGenPair = Producer(
    name="MMGenPair",
    call="ditau_pairselection::buildgenpair({df}, {input}, {output})",
    input=[q.dileptonpair, nanoAOD.Muon_indexToGen, nanoAOD.Muon_indexToGen],
    output=[q.gen_dileptonpair],
    scopes=["mm"],
)
EEGenPair = Producer(
    name="EEGenPair",
    call="ditau_pairselection::buildgenpair({df}, {input}, {output})",
    input=[q.dileptonpair, nanoAOD.Electron_indexToGen, nanoAOD.Electron_indexToGen],
    output=[q.gen_dileptonpair],
    scopes=["ee"],
)
EMGenPair = Producer(
    name="EMGenPair",
    call="ditau_pairselection::buildgenpair({df}, {input}, {output})",
    input=[q.dileptonpair, nanoAOD.Electron_indexToGen, nanoAOD.Muon_indexToGen],
    output=[q.gen_dileptonpair],
    scopes=["em"],
)
MMTrueGenPair = Producer(
    name="GenPair",
    call="ditau_pairselection::buildtruegenpair({df}, {output}, {input}, {truegen_mother_pdgid}, {truegen_daughter_1_pdgid}, {truegen_daughter_2_pdgid})",
    input=[
        nanoAOD.GenParticle_statusFlags,
        nanoAOD.GenParticle_status,
        nanoAOD.GenParticle_pdgId,
        nanoAOD.GenParticle_motherid,
        nanoAOD.GenParticle_pt,
    ],
    output=[q.truegenpair],
    scopes=["mm","ee","em"],
)
####################
# Set of general producers for Gen DiTauPair Quantities
####################

LVGenParticle1 = Producer(
    name="LVGenParticle1",
    call="lorentzvector::Build({df}, {output}, {input}, 0)",
    input=[
        nanoAOD.GenParticle_pt,
        nanoAOD.GenParticle_eta,
        nanoAOD.GenParticle_phi,
        nanoAOD.GenParticle_mass,
        q.gen_dileptonpair
    ],
    output=[q.gen_p4_1],
    scopes=["mm","ee","em"],
)
LVGenParticle2 = Producer(
    name="LVGenParticle2",
    call="lorentzvector::Build({df}, {output}, {input}, 1)",
    input=[
        nanoAOD.GenParticle_pt,
        nanoAOD.GenParticle_eta,
        nanoAOD.GenParticle_phi,
        nanoAOD.GenParticle_mass,
        q.gen_dileptonpair
    ],
    output=[q.gen_p4_2],
    scopes=["mm","ee","em"],
)
LVTrueGenParticle1 = Producer(
    name="LVTrueGenParticle1",
    call="lorentzvector::Build({df}, {output}, {input}, 0)",
    input=[
        nanoAOD.GenParticle_pt,
        nanoAOD.GenParticle_eta,
        nanoAOD.GenParticle_phi,
        nanoAOD.GenParticle_mass,
        q.truegenpair,
    ],
    output=[q.gen_p4_1],
    scopes=["mm","ee","em"],
)
LVTrueGenParticle2 = Producer(
    name="LVTrueGenParticle2",
    call="lorentzvector::Build({df}, {output}, {input}, 1)",
    input=[
        nanoAOD.GenParticle_pt,
        nanoAOD.GenParticle_eta,
        nanoAOD.GenParticle_phi,
        nanoAOD.GenParticle_mass,
        q.truegenpair,
    ],
    output=[q.gen_p4_2],
    scopes=["mm","ee","em"],
)
gen_pt_1 = Producer(
    name="gen_pt_1",
    call="lorentzvector::GetPt({df}, {output}, {input})",
    input=[q.gen_p4_1],
    output=[q.gen_pt_1],
    scopes=["mm","ee","em"],
)
gen_pt_2 = Producer(
    name="gen_pt_2",
    call="lorentzvector::GetPt({df}, {output}, {input})",
    input=[q.gen_p4_2],
    output=[q.gen_pt_2],
    scopes=["mm","ee","em"],
)
gen_eta_1 = Producer(
    name="gen_eta_1",
    call="lorentzvector::GetEta({df}, {output}, {input})",
    input=[q.gen_p4_1],
    output=[q.gen_eta_1],
    scopes=["mm","ee","em"],
)
gen_eta_2 = Producer(
    name="gen_eta_2",
    call="lorentzvector::GetEta({df}, {output}, {input})",
    input=[q.gen_p4_2],
    output=[q.gen_eta_2],
    scopes=["mm","ee","em"],
)
gen_phi_1 = Producer(
    name="gen_phi_1",
    call="lorentzvector::GetPhi({df}, {output}, {input})",
    input=[q.gen_p4_1],
    output=[q.gen_phi_1],
    scopes=["mm","ee","em"],
)
gen_phi_2 = Producer(
    name="gen_phi_2",
    call="lorentzvector::GetPhi({df}, {output}, {input})",
    input=[q.gen_p4_2],
    output=[q.gen_phi_2],
    scopes=["mm","ee","em"],
)
gen_mass_1 = Producer(
    name="gen_mass_1",
    call="lorentzvector::GetMass({df}, {output}, {input})",
    input=[q.gen_p4_1],
    output=[q.gen_mass_1],
    scopes=["mm","ee","em"],
)
gen_mass_2 = Producer(
    name="gen_mass_2",
    call="lorentzvector::GetMass({df}, {output}, {input})",
    input=[q.gen_p4_2],
    output=[q.gen_mass_2],
    scopes=["mm","ee","em"],
)
gen_pdgid_1 = Producer(
    name="gen_pdgid_1",
    call="event::quantity::Get<int>({df}, {output}, {input}, 0)",
    input=[q.gen_dileptonpair, nanoAOD.GenParticle_pdgId],
    output=[q.gen_pdgid_1],
    scopes=["mm","ee","em"],
)
gen_pdgid_2 = Producer(
    name="gen_pdgid_2",
    call="event::quantity::Get<int>({df}, {output}, {input}, 1)",
    input=[q.gen_dileptonpair, nanoAOD.GenParticle_pdgId],
    output=[q.gen_pdgid_2],
    scopes=["mm","ee","em"],
)
gen_m_vis = Producer(
    name="gen_m_vis",
    call="lorentzvector::GetMass({df}, {output}, {input})",
    input=[q.gen_p4_1, q.gen_p4_2],
    output=[q.gen_m_vis],
    scopes=["mm","ee","em"],
)
gen_pt_vis = Producer(
    name="gen_pt_vis",
    call="lorentzvector::GetPt({df}, {output}, {input})",
    input=[q.gen_p4_1, q.gen_p4_2],
    output=[q.gen_pt_vis],
    scopes=["mm","ee","em"],
)
gen_eta_vis = Producer(
    name="gen_eta_vis",
    call="lorentzvector::GetEta({df}, {output}, {input})",
    input=[q.gen_p4_1, q.gen_p4_2],
    output=[q.gen_eta_vis],
    scopes=["mm","ee","em"],
)
gen_match_2 = Producer(
    name="gen_match_2",
    call="event::quantity::Get<UChar_t>({df}, {output}, {input}, 0)",
    input=[nanoAOD.Tau_genMatch, q.dileptonpair],
    output=[q.gen_match_2],
    scopes=["mm","ee","em"],
)
gen_taujet_pt_1 = Producer(
    name="gen_taujet_pt_1",
    call="quantities::GenJetMatching({df}, {output}, {input}, 0)",
    input=[
        nanoAOD.Tau_associatedJet,
        nanoAOD.Jet_associatedGenJet,
        nanoAOD.GenJet_pt,
        q.dileptonpair,
    ],
    output=[q.gen_taujet_pt_1],
    scopes=["mm","ee","em"],
)
gen_taujet_pt_2 = Producer(
    name="gen_taujet_pt_2",
    call="quantities::GenJetMatching({df}, {output}, {input}, 1)",
    input=[
        nanoAOD.Tau_associatedJet,
        nanoAOD.Jet_associatedGenJet,
        nanoAOD.GenJet_pt,
        q.dileptonpair,
    ],
    output=[q.gen_taujet_pt_2],
    scopes=["mm","ee","em"],
)
UnrollGenMuLV1 = ProducerGroup(
    name="UnrollGenMuLV1",
    call=None,
    input=None,
    output=None,
    scopes=["mm","ee","em"],
    subproducers=[gen_pt_1, gen_eta_1, gen_phi_1, gen_mass_1,] #gen_pdgid_1],
)
UnrollGenMuLV2 = ProducerGroup(
    name="UnrollGenMuLV2",
    call=None,
    input=None,
    output=None,
    scopes=["mm","ee","em"],
    subproducers=[gen_pt_2, gen_eta_2, gen_phi_2, gen_mass_2,] #gen_pdgid_2],
)


MMGenDiTauPairQuantities = ProducerGroup(
    name="MMGenDiTauPairQuantities",
    call=None,
    input=None,
    output=None,
    scopes=["mm"],
    subproducers=[
        MMGenPair,
        LVGenParticle1,
        LVGenParticle2,
        UnrollGenMuLV1,
        UnrollGenMuLV2,
        gen_m_vis,
        gen_pt_vis,
        gen_eta_vis,
    ],
)
EEGenDiTauPairQuantities = ProducerGroup(
    name="EEGenDiTauPairQuantities",
    call=None,
    input=None,
    output=None,
    scopes=["ee"],
    subproducers=[
        EEGenPair,
        LVGenParticle1,
        LVGenParticle2,
        UnrollGenMuLV1,
        UnrollGenMuLV2,
        gen_m_vis,
        gen_pt_vis,
        gen_eta_vis,
    ],
)
EMGenDiTauPairQuantities = ProducerGroup(
    name="EMGenDiTauPairQuantities",
    call=None,
    input=None,
    output=None,
    scopes=["em"],
    subproducers=[
        EMGenPair,
        LVGenParticle1,
        LVGenParticle2,
        UnrollGenMuLV1,
        UnrollGenMuLV2,
        gen_m_vis,
        gen_pt_vis,
        gen_eta_vis,
    ],
)
MMTrueGenDiTauPairQuantities = ProducerGroup(
    name="GenDiTauPairQuantities",
    call=None,
    input=None,
    output=None,
    scopes=["mm","ee","em"],
    subproducers=[
        MMTrueGenPair,
        LVTrueGenParticle1,
        LVTrueGenParticle2,
        UnrollGenMuLV1,
        UnrollGenMuLV2,
        gen_m_vis,
        gen_pt_vis,
    ],
)
