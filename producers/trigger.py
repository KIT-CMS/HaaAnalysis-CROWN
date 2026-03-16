from ..quantities import output as q
from ..quantities import nanoAOD as nanoAOD
from code_generation.producer import Producer, ExtendedVectorProducer

####################
# Set of producers used for trigger flags
####################

commonInputs = [
    	nanoAOD.TriggerObject_pt,
        nanoAOD.TriggerObject_eta,
        nanoAOD.TriggerObject_phi,
        nanoAOD.TriggerObject_id,
        nanoAOD.TriggerObject_bit,
]
GenerateSingleMuonTriggerFlags = ExtendedVectorProducer(
    name="GenerateSingleMuonTriggerFlags",
    call='trigger::SingleObjectFlag({df}, {output}, {input}, "{hlt_path}", {ptcut}, {etacut}, {trigger_particle_id}, {filterbit}, {max_deltaR_triggermatch} )',
    input={
        "mm": [q.p4_1] + commonInputs,
        "mmet": [q.p4_1] + commonInputs,
        "em": [q.p4_2] + commonInputs
    },
    output="flagname",
    scope=["mm", "em", "mmet"],
    vec_config="singlemoun_trigger",
)

GenerateSingleElectronTriggerFlags = ExtendedVectorProducer(
    name="GenerateSingleElectronTriggerFlags",
    call='trigger::SingleObjectFlag({df}, {output}, {input}, "{hlt_path}", {ptcut}, {etacut}, {trigger_particle_id}, {filterbit}, {max_deltaR_triggermatch} )',
    input=[
        q.p4_1,
        nanoAOD.TriggerObject_pt,
        nanoAOD.TriggerObject_eta,
        nanoAOD.TriggerObject_phi,
        nanoAOD.TriggerObject_id,
        nanoAOD.TriggerObject_bit,
    ],
    output="flagname",
    scope=["ee", "em", "emet"],
    vec_config="singleelectron_trigger",
)



TriggerObject_filterBits = Producer(
    name="TriggerObject_filterBits",
    call="basefunctions::rename<ROOT::RVec<Int_t>>({df}, {input}, {output})",
    input=[nanoAOD.TriggerObject_bit],
    output=[q.TriggerObject_filterBits_vector],
    scopes=["lep"],
)

TriggerObject_pt = Producer(
    name="TriggerObject_pt",
    call="basefunctions::rename<ROOT::RVec<Float_t>>({df}, {input}, {output})",
    input=[nanoAOD.TriggerObject_pt],
    output=[q.TriggerObject_pt_vector],
    scopes=["lep"],
)

TriggerObject_eta = Producer(
    name="TriggerObject_eta",
    call="basefunctions::rename<ROOT::RVec<Float_t>>({df}, {input}, {output})",
    input=[nanoAOD.TriggerObject_eta],
    output=[q.TriggerObject_eta_vector],
    scopes=["lep"],
)

TriggerObject_phi = Producer(
    name="TriggerObject_phi",
    call="basefunctions::rename<ROOT::RVec<Float_t>>({df}, {input}, {output})",
    input=[nanoAOD.TriggerObject_phi],
    output=[q.TriggerObject_phi_vector],
    scopes=["lep"],
)

TriggerObject_id = Producer(
    name="TriggerObject_id",
    call="basefunctions::rename<ROOT::RVec<Int_t>>({df}, {input}, {output})",
    input=[nanoAOD.TriggerObject_id],
    output=[q.TriggerObject_id_vector],
    scopes=["lep"],
)
