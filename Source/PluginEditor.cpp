#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WASPAlphaAudioProcessorEditor::WASPAlphaAudioProcessorEditor(WASPAlphaAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    using namespace WaspParams;

    setSize(kWindowW, kWindowH);
    setResizable(false, false);

    // ===== OSC 1 =====
    setupCombo(osc1Shape, { "SAW", "SQR", "TRI", "SIN", "303" });
    addAndMakeVisible(secOsc);
    addAndMakeVisible(osc1Shape);
    addAndMakeVisible(osc1Coarse);
    addAndMakeVisible(osc1Fine);
    addAndMakeVisible(osc2Shape);
    addAndMakeVisible(osc2Coarse);
    addAndMakeVisible(osc2Fine);
    addAndMakeVisible(osc3Shape);
    addAndMakeVisible(osc3Amount);

    setupCombo(osc2Shape, { "SAW", "SQR", "TRI", "SIN", "303" });
    setupCombo(osc3Shape, { "SUB", "SUB2", "NOISE" });

    // ===== MIX / MOD =====
    addAndMakeVisible(secMix);
    addAndMakeVisible(mixKnob);
    addAndMakeVisible(pwKnob);
    addAndMakeVisible(fmKnob);
    addAndMakeVisible(rmKnob);

    // ===== FILTER =====
    setupCombo(fltType, { "LP12", "LP24", "HP12", "BP12" });
    setupCombo(fltModel, { "LADDER", "CHAMBERLIN" });
    addAndMakeVisible(secFilter);
    addAndMakeVisible(fltType);
    addAndMakeVisible(fltModel);
    addAndMakeVisible(cutoff);
    addAndMakeVisible(resonance);
    addAndMakeVisible(fltEnvAmt);
    addAndMakeVisible(fltKT);

    // ===== ENVELOPES =====
    addAndMakeVisible(secAmpEnv);
    addAndMakeVisible(ampA);
    addAndMakeVisible(ampD);
    addAndMakeVisible(ampS);
    addAndMakeVisible(ampR);

    addAndMakeVisible(secFltEnv);
    addAndMakeVisible(fltA);
    addAndMakeVisible(fltD);
    addAndMakeVisible(fltS);
    addAndMakeVisible(fltR);

    // ===== LFO 1 =====
    setupCombo(lfo1Shape, { "SIN", "TRI", "SAW", "RSAW", "SQR", "S+H" });
    setupCombo(lfo1Target, { "PITCH", "OSC1", "OSC2", "PW", "FILTER", "AMP", "RESO" });
    lfo1Sync.setLookAndFeel(&laf);
    lfo1Reset.setLookAndFeel(&laf);
    addAndMakeVisible(secLfo1);
    addAndMakeVisible(lfo1Shape);
    addAndMakeVisible(lfo1Target);
    addAndMakeVisible(lfo1Freq);
    addAndMakeVisible(lfo1Amount);
    addAndMakeVisible(lfo1Delay);
    addAndMakeVisible(lfo1Sync);
    addAndMakeVisible(lfo1Reset);

    // ===== LFO 2 =====
    setupCombo(lfo2Shape, { "SIN", "TRI", "SAW", "RSAW", "SQR", "S+H" });
    setupCombo(lfo2Target, { "PITCH", "OSC1", "OSC2", "PW", "FILTER", "AMP", "RESO" });
    lfo2Sync.setLookAndFeel(&laf);
    lfo2Reset.setLookAndFeel(&laf);
    addAndMakeVisible(secLfo2);
    addAndMakeVisible(lfo2Shape);
    addAndMakeVisible(lfo2Target);
    addAndMakeVisible(lfo2Freq);
    addAndMakeVisible(lfo2Amount);
    addAndMakeVisible(lfo2Delay);
    addAndMakeVisible(lfo2Sync);
    addAndMakeVisible(lfo2Reset);

    // ===== DISTORTION =====
    distOn.setLookAndFeel(&laf);
    setupCombo(distType, { "SOFT", "HARD" });
    addAndMakeVisible(secFx);
    addAndMakeVisible(distOn);
    addAndMakeVisible(distDrive);
    addAndMakeVisible(distTone);
    addAndMakeVisible(distType);

    // ===== CHARACTER =====
    cmosFilter.setLookAndFeel(&laf);
    addAndMakeVisible(secChar);
    addAndMakeVisible(dualVoice);
    addAndMakeVisible(waspChar);
    addAndMakeVisible(vcoBinary);
    addAndMakeVisible(cmosFilter);

    // ===== CV =====
    setupCombo(cvTarget, { "FILTER", "OSC2 PITCH", "PW", "AMP" });
    addAndMakeVisible(secCV);
    addAndMakeVisible(cvAmount);
    addAndMakeVisible(cvTarget);

    // ===== MOD ENV =====
    setupCombo(modEnvDest, { "PW", "LFO1 AMT", "OSC1 LVL", "OSC2 PITCH" });
    addAndMakeVisible(secModEnv);
    addAndMakeVisible(modEnvAtk);
    addAndMakeVisible(modEnvDec);
    addAndMakeVisible(modEnvAmt);
    addAndMakeVisible(modEnvDest);

    // ===== VELOCITY =====
    addAndMakeVisible(secVelocity);
    addAndMakeVisible(velToAmp);
    addAndMakeVisible(velToFlt);

    // ===== UNISON =====
    addAndMakeVisible(secUnison);
    addAndMakeVisible(dualDetune);

    // ===== FILTER 2 =====
    setupCombo(flt2Type, { "LP12", "LP24", "HP12", "BP12" });
    setupCombo(flt2Model, { "LADDER", "CHAMBERLIN" });
    addAndMakeVisible(secFilter2);
    addAndMakeVisible(flt2Type);
    addAndMakeVisible(flt2Model);
    addAndMakeVisible(cutoff2);
    addAndMakeVisible(resonance2);
    addAndMakeVisible(flt2EnvAmt);
    addAndMakeVisible(flt2KT);

    // ===== FILTER ROUTING =====
    setupCombo(fltRouting, { "FILTER 1 ONLY", "FILTER 2 ONLY", "SERIES 1->2", "PARALLEL" });
    addAndMakeVisible(secRouting);
    addAndMakeVisible(fltRouting);
    addAndMakeVisible(fltParallelMix);

    // ===== DELAY =====
    addAndMakeVisible(secDelay);
    addAndMakeVisible(delayTime);
    addAndMakeVisible(delayFeedback);
    addAndMakeVisible(delayMix);

    // ===== OUTPUT =====
    addAndMakeVisible(secOutput);
    addAndMakeVisible(masterVolume);

    // ========================================================================
    // DX FM module UI wiring
    // ========================================================================
    dxfmEnable.setLookAndFeel(&laf);
    addAndMakeVisible(secDx);
    addAndMakeVisible(dxfmEnable);
    addAndMakeVisible(dxfmBlend);

    addAndMakeVisible(dxCarA);
    addAndMakeVisible(dxCarD);
    addAndMakeVisible(dxCarR);
    addAndMakeVisible(dxWave);

    addAndMakeVisible(dxModI);
    addAndMakeVisible(dxModD);
    addAndMakeVisible(dxModS);
    addAndMakeVisible(dxModR);
    addAndMakeVisible(dxModV);
    addAndMakeVisible(dxCoarse);
    addAndMakeVisible(dxFine);

    addAndMakeVisible(dxThru);
    addAndMakeVisible(dxOctave);
    addAndMakeVisible(dxTune);

    // ========================================================================
    // CPU Saver UI wiring
    // ========================================================================
    bpFilter2Btn.setLookAndFeel(&laf);
    bpDelayBtn.setLookAndFeel(&laf);
    bpDistBtn.setLookAndFeel(&laf);
    bpLfo2Btn.setLookAndFeel(&laf);
    bpModEnvBtn.setLookAndFeel(&laf);
    bpCvBtn.setLookAndFeel(&laf);
    bpDualVBtn.setLookAndFeel(&laf);
    bpWaspCharBtn.setLookAndFeel(&laf);
    bpVcoBinBtn.setLookAndFeel(&laf);

    addAndMakeVisible(secCpu);
    addAndMakeVisible(bpFilter2Btn);
    addAndMakeVisible(bpDelayBtn);
    addAndMakeVisible(bpDistBtn);
    addAndMakeVisible(bpLfo2Btn);
    addAndMakeVisible(bpModEnvBtn);
    addAndMakeVisible(bpCvBtn);
    addAndMakeVisible(bpDualVBtn);
    addAndMakeVisible(bpWaspCharBtn);
    addAndMakeVisible(bpVcoBinBtn);

    // ========================================================================
    // ==== NEW: Preset UI wiring ====
    // ========================================================================
    // The preset ComboBox lists every available preset — factory first, then
    // user presets scanned from disk. The four buttons next to it let the
    // user save/delete/export the current state and reveal the preset folder.
    presetSelector.setLookAndFeel(&laf);
    presetSelector.setTextWhenNothingSelected("SELECT PRESET");

    savePresetButton.setLookAndFeel(&laf);
    deletePresetButton.setLookAndFeel(&laf);
    exportPresetButton.setLookAndFeel(&laf);
    openFolderButton.setLookAndFeel(&laf);

    addAndMakeVisible(presetSelector);
    addAndMakeVisible(savePresetButton);
    addAndMakeVisible(deletePresetButton);
    addAndMakeVisible(exportPresetButton);
    addAndMakeVisible(openFolderButton);

    // Populate the ComboBox from the manager. Safe to call here — the
    // manager was constructed in the processor's own constructor, which
    // completed before this editor was ever created.
    refreshPresetList();

    // Selection handler. Guarded by updatingPresetSelector so the
    // programmatic change made by refreshPresetList() doesn't trigger a
    // spurious load.
    presetSelector.onChange = [this] {
        if (updatingPresetSelector) return;
        onPresetSelected(presetSelector.getSelectedId());
        };

    savePresetButton.onClick = [this] { onSavePresetClicked();    };
    deletePresetButton.onClick = [this] { onDeletePresetClicked();  };
    exportPresetButton.onClick = [this] { onExportPresetClicked();  };
    openFolderButton.onClick = [this] { onOpenFolderClicked();    };

    // ========================================================================
    // ===== APVTS ATTACHMENTS =====
    // ========================================================================

    attOsc1Shape = std::make_unique<ComboAtt>(audioProcessor.apvts, OSC1_SHAPE, osc1Shape);
    attOsc1Coarse = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC1_COARSE, osc1Coarse.slider);
    attOsc1Fine = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC1_FINE, osc1Fine.slider);
    attOsc2Shape = std::make_unique<ComboAtt>(audioProcessor.apvts, OSC2_SHAPE, osc2Shape);
    attOsc2Coarse = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC2_COARSE, osc2Coarse.slider);
    attOsc2Fine = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC2_FINE, osc2Fine.slider);
    attOsc3Shape = std::make_unique<ComboAtt>(audioProcessor.apvts, OSC3_SHAPE, osc3Shape);
    attOsc3Amount = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC3_AMOUNT, osc3Amount.slider);

    attMix = std::make_unique<SliderAtt>(audioProcessor.apvts, OSC_MIX, mixKnob.slider);
    attPW = std::make_unique<SliderAtt>(audioProcessor.apvts, PULSE_WIDTH, pwKnob.slider);
    attFM = std::make_unique<SliderAtt>(audioProcessor.apvts, FM_AMOUNT, fmKnob.slider);
    attRM = std::make_unique<SliderAtt>(audioProcessor.apvts, RM_AMOUNT, rmKnob.slider);

    attFltType = std::make_unique<ComboAtt>(audioProcessor.apvts, FLT_TYPE, fltType);
    attFltModel = std::make_unique<ComboAtt>(audioProcessor.apvts, FLT_MODEL, fltModel);
    attCutoff = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_CUTOFF, cutoff.slider);
    attReso = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_RESO, resonance.slider);
    attFltEnvAmt = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_ENV_AMT, fltEnvAmt.slider);
    attFltKT = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_KEYTRACK, fltKT.slider);

    attAmpA = std::make_unique<SliderAtt>(audioProcessor.apvts, AMP_ATTACK, ampA.slider);
    attAmpD = std::make_unique<SliderAtt>(audioProcessor.apvts, AMP_DECAY, ampD.slider);
    attAmpS = std::make_unique<SliderAtt>(audioProcessor.apvts, AMP_SUSTAIN, ampS.slider);
    attAmpR = std::make_unique<SliderAtt>(audioProcessor.apvts, AMP_RELEASE, ampR.slider);

    attFltA = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_ATTACK, fltA.slider);
    attFltD = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_DECAY, fltD.slider);
    attFltS = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_SUSTAIN, fltS.slider);
    attFltR = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_RELEASE, fltR.slider);

    attLfo1Shape = std::make_unique<ComboAtt>(audioProcessor.apvts, LFO1_SHAPE, lfo1Shape);
    attLfo1Target = std::make_unique<ComboAtt>(audioProcessor.apvts, LFO1_TARGET, lfo1Target);
    attLfo1Freq = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO1_FREQ, lfo1Freq.slider);
    attLfo1Amt = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO1_AMOUNT, lfo1Amount.slider);
    attLfo1Delay = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO1_DELAY, lfo1Delay.slider);
    attLfo1Sync = std::make_unique<ButtonAtt>(audioProcessor.apvts, LFO1_SYNC, lfo1Sync);
    attLfo1Reset = std::make_unique<ButtonAtt>(audioProcessor.apvts, LFO1_RESET, lfo1Reset);

    attLfo2Shape = std::make_unique<ComboAtt>(audioProcessor.apvts, LFO2_SHAPE, lfo2Shape);
    attLfo2Target = std::make_unique<ComboAtt>(audioProcessor.apvts, LFO2_TARGET, lfo2Target);
    attLfo2Freq = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO2_FREQ, lfo2Freq.slider);
    attLfo2Amt = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO2_AMOUNT, lfo2Amount.slider);
    attLfo2Delay = std::make_unique<SliderAtt>(audioProcessor.apvts, LFO2_DELAY, lfo2Delay.slider);
    attLfo2Sync = std::make_unique<ButtonAtt>(audioProcessor.apvts, LFO2_SYNC, lfo2Sync);
    attLfo2Reset = std::make_unique<ButtonAtt>(audioProcessor.apvts, LFO2_RESET, lfo2Reset);

    attDistOn = std::make_unique<ButtonAtt>(audioProcessor.apvts, DIST_ON, distOn);
    attDistDrive = std::make_unique<SliderAtt>(audioProcessor.apvts, DIST_DRIVE, distDrive.slider);
    attDistTone = std::make_unique<SliderAtt>(audioProcessor.apvts, DIST_TONE, distTone.slider);
    attDistType = std::make_unique<ComboAtt>(audioProcessor.apvts, DIST_TYPE, distType);

    attDualVoice = std::make_unique<SliderAtt>(audioProcessor.apvts, DUAL_VOICE, dualVoice.slider);
    attDualDetune = std::make_unique<SliderAtt>(audioProcessor.apvts, DUAL_DETUNE, dualDetune.slider);
    attWaspChar = std::make_unique<SliderAtt>(audioProcessor.apvts, WASP_CHAR, waspChar.slider);
    attVCOBinary = std::make_unique<SliderAtt>(audioProcessor.apvts, VCO_BINARY, vcoBinary.slider);
    attCmosFilter = std::make_unique<ButtonAtt>(audioProcessor.apvts, CMOS_FILTER, cmosFilter);
    attCVAmount = std::make_unique<SliderAtt>(audioProcessor.apvts, CV_AMOUNT, cvAmount.slider);
    attCVTarget = std::make_unique<ComboAtt>(audioProcessor.apvts, CV_TARGET, cvTarget);

    attModEnvAtk = std::make_unique<SliderAtt>(audioProcessor.apvts, MODENV_ATTACK, modEnvAtk.slider);
    attModEnvDec = std::make_unique<SliderAtt>(audioProcessor.apvts, MODENV_DECAY, modEnvDec.slider);
    attModEnvAmt = std::make_unique<SliderAtt>(audioProcessor.apvts, MODENV_AMOUNT, modEnvAmt.slider);
    attModEnvDest = std::make_unique<ComboAtt>(audioProcessor.apvts, MODENV_DEST, modEnvDest);

    attVelToAmp = std::make_unique<SliderAtt>(audioProcessor.apvts, VEL_TO_AMP, velToAmp.slider);
    attVelToFlt = std::make_unique<SliderAtt>(audioProcessor.apvts, VEL_TO_FILTER, velToFlt.slider);

    attFlt2Type = std::make_unique<ComboAtt>(audioProcessor.apvts, FLT2_TYPE, flt2Type);
    attFlt2Model = std::make_unique<ComboAtt>(audioProcessor.apvts, FLT2_MODEL, flt2Model);
    attCutoff2 = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT2_CUTOFF, cutoff2.slider);
    attReso2 = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT2_RESO, resonance2.slider);
    attFlt2EnvAmt = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT2_ENV_AMT, flt2EnvAmt.slider);
    attFlt2KT = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT2_KEYTRACK, flt2KT.slider);
    attFltRouting = std::make_unique<ComboAtt>(audioProcessor.apvts, FLT_ROUTING, fltRouting);
    attFltParallelMix = std::make_unique<SliderAtt>(audioProcessor.apvts, FLT_PARALLEL_MIX, fltParallelMix.slider);

    attDelayTime = std::make_unique<SliderAtt>(audioProcessor.apvts, DELAY_TIME_MS, delayTime.slider);
    attDelayFeedback = std::make_unique<SliderAtt>(audioProcessor.apvts, DELAY_FEEDBACK, delayFeedback.slider);
    attDelayMix = std::make_unique<SliderAtt>(audioProcessor.apvts, DELAY_MIX, delayMix.slider);

    attMasterVolume = std::make_unique<SliderAtt>(audioProcessor.apvts, MASTER_VOLUME, masterVolume.slider);

    attDxfmEnable = std::make_unique<ButtonAtt>(audioProcessor.apvts, DXFM_ENABLE, dxfmEnable);
    attDxfmBlend = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_BLEND, dxfmBlend.slider);

    attDxCarA = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_CAR_ATK, dxCarA.slider);
    attDxCarD = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_CAR_DEC, dxCarD.slider);
    attDxCarR = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_CAR_REL, dxCarR.slider);
    attDxWave = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_WAVE, dxWave.slider);

    attDxModI = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_INIT, dxModI.slider);
    attDxModD = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_DEC, dxModD.slider);
    attDxModS = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_SUS, dxModS.slider);
    attDxModR = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_REL, dxModR.slider);
    attDxModV = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_VEL, dxModV.slider);

    attDxCoarse = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_COARSE, dxCoarse.slider);
    attDxFine = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_FINE, dxFine.slider);

    attDxThru = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_MOD_THRU, dxThru.slider);
    attDxOctave = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_OCTAVE, dxOctave.slider);
    attDxTune = std::make_unique<SliderAtt>(audioProcessor.apvts, DXFM_TUNE, dxTune.slider);

    attBpFilter2 = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_FILTER2, bpFilter2Btn);
    attBpDelay = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_DELAY, bpDelayBtn);
    attBpDist = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_DIST, bpDistBtn);
    attBpLfo2 = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_LFO2, bpLfo2Btn);
    attBpModEnv = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_MODENV, bpModEnvBtn);
    attBpCv = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_CV, bpCvBtn);
    attBpDualV = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_DUALVOICE, bpDualVBtn);
    attBpWaspChar = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_WASPCHAR, bpWaspCharBtn);
    attBpVcoBin = std::make_unique<ButtonAtt>(audioProcessor.apvts, BYPASS_VCOBIN, bpVcoBinBtn);

    // Assign alternating panel palettes (U-He style)
    assignSectionPalettes();
}

WASPAlphaAudioProcessorEditor::~WASPAlphaAudioProcessorEditor()
{
    osc1Shape.setLookAndFeel(nullptr);
    osc2Shape.setLookAndFeel(nullptr);
    osc3Shape.setLookAndFeel(nullptr);
    fltType.setLookAndFeel(nullptr);
    lfo1Shape.setLookAndFeel(nullptr);
    lfo1Target.setLookAndFeel(nullptr);
    lfo1Sync.setLookAndFeel(nullptr);
    lfo1Reset.setLookAndFeel(nullptr);
    lfo2Shape.setLookAndFeel(nullptr);
    lfo2Target.setLookAndFeel(nullptr);
    lfo2Sync.setLookAndFeel(nullptr);
    lfo2Reset.setLookAndFeel(nullptr);
    distOn.setLookAndFeel(nullptr);
    cmosFilter.setLookAndFeel(nullptr);
    cvTarget.setLookAndFeel(nullptr);
    modEnvDest.setLookAndFeel(nullptr);
    flt2Type.setLookAndFeel(nullptr);
    fltRouting.setLookAndFeel(nullptr);
    fltModel.setLookAndFeel(nullptr);
    flt2Model.setLookAndFeel(nullptr);
    distType.setLookAndFeel(nullptr);

    dxfmEnable.setLookAndFeel(nullptr);
    bpFilter2Btn.setLookAndFeel(nullptr);
    bpDelayBtn.setLookAndFeel(nullptr);
    bpDistBtn.setLookAndFeel(nullptr);
    bpLfo2Btn.setLookAndFeel(nullptr);
    bpModEnvBtn.setLookAndFeel(nullptr);
    bpCvBtn.setLookAndFeel(nullptr);
    bpDualVBtn.setLookAndFeel(nullptr);
    bpWaspCharBtn.setLookAndFeel(nullptr);
    bpVcoBinBtn.setLookAndFeel(nullptr);

    // ==== NEW: preset controls LnF reset ====
    presetSelector.setLookAndFeel(nullptr);
    savePresetButton.setLookAndFeel(nullptr);
    deletePresetButton.setLookAndFeel(nullptr);
    exportPresetButton.setLookAndFeel(nullptr);
    openFolderButton.setLookAndFeel(nullptr);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::setupCombo(juce::ComboBox& box,
    const juce::StringArray& items)
{
    box.setLookAndFeel(&laf);
    int id = 1;
    for (auto& item : items)
        box.addItem(item, id++);
    box.setSelectedId(1, juce::dontSendNotification);
}

//==============================================================================
// U-He style palette cycling. Groups are assigned distinct tones so adjacent
// sections contrast (charcoal / mahogany / amber) as in Concept 1.
void WASPAlphaAudioProcessorEditor::assignSectionPalettes()
{
    secOsc.setPaletteIndex(0);
    secMix.setPaletteIndex(1);

    secFilter.setPaletteIndex(0);
    secAmpEnv.setPaletteIndex(1);
    secFltEnv.setPaletteIndex(2);

    secLfo1.setPaletteIndex(0);
    secLfo2.setPaletteIndex(1);
    secFx.setPaletteIndex(2);
    secCV.setPaletteIndex(0);

    secModEnv.setPaletteIndex(1);
    secVelocity.setPaletteIndex(2);
    secUnison.setPaletteIndex(0);
    secChar.setPaletteIndex(1);

    secFilter2.setPaletteIndex(0);
    secRouting.setPaletteIndex(1);
    secDelay.setPaletteIndex(2);
    secOutput.setPaletteIndex(0);

    secDx.setPaletteIndex(2);    // Deep Burnt Amber — distinct, "hot" module
    secCpu.setPaletteIndex(0);   // Dark Slate Charcoal — neutral utility panel
}

//==============================================================================
// PAINT — CRT-style header, revised for The Stinger branding + preset bar
//==============================================================================
void WASPAlphaAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Main background
    g.fillAll(juce::Colour(WaspLookAndFeel::COL_BODY_BG));

    // Very subtle overall ribbed texture
    g.setColour(juce::Colour(WaspLookAndFeel::COL_WASP_STRIPE).withAlpha(0.22f));
    for (int y = 0; y < getHeight(); y += 4)
        g.fillRect(0, y, getWidth(), 1);

    // Header bar
    juce::Rectangle<int> header(0, 0, getWidth(), 34);
    g.setColour(juce::Colour(0xff0c0605u));
    g.fillRect(header);

    juce::ColourGradient hdrGrad(
        juce::Colour(WaspLookAndFeel::COL_GRAD_ORANGE).withAlpha(0.22f), 0.0f, 0.0f,
        juce::Colour(WaspLookAndFeel::COL_GRAD_RED).withAlpha(0.30f), (float)getWidth(), 0.0f, false);
    g.setGradientFill(hdrGrad);
    g.fillRect(header);

    // Header bottom accent
    juce::ColourGradient accentGrad(
        juce::Colour(WaspLookAndFeel::COL_GRAD_ORANGE), 0.0f, 33.0f,
        juce::Colour(WaspLookAndFeel::COL_GRAD_RED), (float)getWidth(), 33.0f, false);
    g.setGradientFill(accentGrad);
    g.fillRect(0, 33, getWidth(), 2);

    // Plugin name — gradient text so it reads as "mastering hardware".
    // Branding updated from "KillerBee" to "The Stinger" — shorter name
    // means we can afford a slightly larger font without crowding the
    // preset bar on the right.
    {
        const auto font = juce::Font(juce::FontOptions("Courier New", 20.0f, juce::Font::bold));
        juce::Rectangle<int> nameArea(10, 0, 260, 34);
        juce::ColourGradient nameGrad(
            juce::Colour(WaspLookAndFeel::COL_HDR_TEXT_A), (float)nameArea.getX(), 17.0f,
            juce::Colour(WaspLookAndFeel::COL_HDR_TEXT_B), (float)nameArea.getRight(), 17.0f, false);
        g.setGradientFill(nameGrad);
        g.setFont(font);
        g.drawText("The Stinger", nameArea, juce::Justification::centredLeft, false);
    }

    // Subtitle — repositioned to sit right after "The Stinger" wordmark,
    // since the preset bar now occupies the right-hand strip of the header.
    g.setColour(juce::Colour(WaspLookAndFeel::COL_TEXT_SECONDARY));
    g.setFont(juce::FontOptions("Courier New", 8.5f, juce::Font::plain));
    g.drawText("AlphaAudio  |  DronerrEdition  |  W.A.M.",
        268, 0, 200, 34, juce::Justification::centredLeft, false);

    // Small amber dot accents — repositioned to just before the preset bar.
    g.setColour(juce::Colour(WaspLookAndFeel::COL_WASP_AMBER));
    for (int i = 0; i < 3; ++i)
        g.fillEllipse((float)(getWidth() - 468 + i * 8), 14.0f, 5.0f, 5.0f);

    // Sub-osc strip labels
    g.setColour(juce::Colour(WaspLookAndFeel::COL_TEXT_SECONDARY));
    g.setFont(juce::FontOptions("Courier New", 8.5f, juce::Font::plain));
    g.drawText("OSC 1", 14, 40, 120, 12, juce::Justification::centredLeft, false);
    g.drawText("OSC 2", 232, 40, 120, 12, juce::Justification::centredLeft, false);
    g.drawText("OSC 3/SUB", 440, 40, 120, 12, juce::Justification::centredLeft, false);
}

//==============================================================================
// RESIZED — preset bar lives in the top header strip; the seven layout
// helpers lay out the rest of the panel exactly as before.
//==============================================================================
void WASPAlphaAudioProcessorEditor::resized()
{
    // ==== Preset bar (top-right of the header strip) ====
    // The header is 34px tall. The combo takes 20px of it, the four buttons
    // sit immediately to its right, and a small right-edge margin keeps
    // everything off the window edge.
    //
    // Layout: [ PRESET COMBO ............ ] [SAVE] [DELETE] [EXPORT] [FOLDER]
    const int barH = 20;
    const int barY = 7;             // vertically centred in the 34px header
    const int rightPad = 10;

    // Button widths — small, uniform, text-fit. The delete button is slightly
    // wider because "DELETE" is a 6-char word and would clip at the same
    // width as "SAVE".
    const int saveW = 46;
    const int deleteW = 58;
    const int exportW = 58;
    const int folderW = 56;
    const int btnGap = 4;

    const int buttonsTotalW = saveW + deleteW + exportW + folderW + 3 * btnGap;
    const int comboW = 240;
    const int comboX = getWidth() - rightPad - buttonsTotalW - comboW - 6;
    const int comboY = barY + (barH - 20) / 2;

    presetSelector.setBounds(comboX, comboY, comboW, 20);

    int bx = comboX + comboW + 6;
    savePresetButton.setBounds(bx, barY, saveW, barH);  bx += saveW + btnGap;
    deletePresetButton.setBounds(bx, barY, deleteW, barH);  bx += deleteW + btnGap;
    exportPresetButton.setBounds(bx, barY, exportW, barH);  bx += exportW + btnGap;
    openFolderButton.setBounds(bx, barY, folderW, barH);

    // ==== The rest of the panel ====
    layoutRow1_OscAndMix();
    layoutRow2_FilterAndEnvs();
    layoutRow3_LfosFxAndCv();
    layoutRow4_ModEnvVelUnisonChar();
    layoutRow5_Filter2RoutingDelayOutput();
    layoutRow6_DxFm();
    layoutRow7_CpuSaver();
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow1_OscAndMix()
{
    constexpr int PAD = 5;
    constexpr int TOP = 36;
    constexpr int HDR = 16;
    constexpr int GAP = 8;

    int row1Y = TOP + 6;
    int row1H = 110;
    int kSize = 54;
    int comboH = 18;

    int oc1x = 10;
    osc1Shape.setBounds(oc1x, row1Y + HDR + 2, 70, comboH);
    osc1Coarse.setBounds(oc1x + 70 + GAP, row1Y + HDR + 2, kSize, kSize + 14);
    osc1Fine.setBounds(oc1x + 70 + GAP + kSize + GAP, row1Y + HDR + 2, kSize, kSize + 14);
    int osc1End = oc1x + 70 + GAP + kSize + GAP + kSize;

    int o2x = osc1End + GAP + 6;
    osc2Shape.setBounds(o2x, row1Y + HDR + 2, 70, comboH);
    osc2Coarse.setBounds(o2x + 70 + GAP, row1Y + HDR + 2, kSize, kSize + 14);
    osc2Fine.setBounds(o2x + 70 + GAP + kSize + GAP, row1Y + HDR + 2, kSize, kSize + 14);
    int osc2End = o2x + 70 + GAP + kSize + GAP + kSize;

    int o3x = osc2End + GAP + 6;
    osc3Shape.setBounds(o3x, row1Y + HDR + 2, 60, comboH);
    osc3Amount.setBounds(o3x + 60 + GAP, row1Y + HDR + 2, kSize, kSize + 14);
    int osc3End = o3x + 60 + GAP + kSize;

    secOsc.setBounds(PAD, row1Y, (osc3End - PAD) + 6, row1H);

    int mixX = osc3End + 6 + PAD;
    secMix.setBounds(mixX, row1Y, 4 * (kSize + GAP) + 8, row1H);
    mixKnob.setBounds(mixX + 6, row1Y + HDR + 2, kSize, kSize + 14);
    pwKnob.setBounds(mixX + 6 + (kSize + GAP), row1Y + HDR + 2, kSize, kSize + 14);
    fmKnob.setBounds(mixX + 6 + 2 * (kSize + GAP), row1Y + HDR + 2, kSize, kSize + 14);
    rmKnob.setBounds(mixX + 6 + 3 * (kSize + GAP), row1Y + HDR + 2, kSize, kSize + 14);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow2_FilterAndEnvs()
{
    constexpr int PAD = 5;
    constexpr int TOP = 36;
    constexpr int HDR = 16;
    constexpr int GAP = 8;

    int row1Y = TOP + 6;
    int row1H = 110;
    int kSize = 54;
    int comboH = 18;

    int row2Y = row1Y + row1H + PAD;
    int row2H = 118;

    int fltW = 4 * (kSize + GAP) + 78;
    secFilter.setBounds(PAD, row2Y, fltW, row2H);
    fltType.setBounds(PAD + 6, row2Y + HDR + 2, 70, comboH);
    fltModel.setBounds(PAD + 6, row2Y + HDR + 2 + comboH + GAP, 70, comboH);
    cutoff.setBounds(PAD + 6 + 70 + GAP, row2Y + HDR + 2, kSize, kSize + 14);
    resonance.setBounds(PAD + 6 + 70 + GAP + (kSize + GAP), row2Y + HDR + 2, kSize, kSize + 14);
    fltEnvAmt.setBounds(PAD + 6 + 70 + GAP + 2 * (kSize + GAP), row2Y + HDR + 2, kSize, kSize + 14);
    fltKT.setBounds(PAD + 6 + 70 + GAP + 3 * (kSize + GAP), row2Y + HDR + 2, kSize, kSize + 14);

    int ampX = PAD + fltW + PAD;
    int envW = 4 * (kSize + GAP) + 8;
    secAmpEnv.setBounds(ampX, row2Y, envW, row2H);
    ampA.setBounds(ampX + 6, row2Y + HDR + 2, kSize, kSize + 14);
    ampD.setBounds(ampX + 6 + (kSize + GAP), row2Y + HDR + 2, kSize, kSize + 14);
    ampS.setBounds(ampX + 6 + 2 * (kSize + GAP), row2Y + HDR + 2, kSize, kSize + 14);
    ampR.setBounds(ampX + 6 + 3 * (kSize + GAP), row2Y + HDR + 2, kSize, kSize + 14);

    int fenvX = ampX + envW + PAD;
    secFltEnv.setBounds(fenvX, row2Y, envW, row2H);
    fltA.setBounds(fenvX + 6, row2Y + HDR + 2, kSize, kSize + 14);
    fltD.setBounds(fenvX + 6 + (kSize + GAP), row2Y + HDR + 2, kSize, kSize + 14);
    fltS.setBounds(fenvX + 6 + 2 * (kSize + GAP), row2Y + HDR + 2, kSize, kSize + 14);
    fltR.setBounds(fenvX + 6 + 3 * (kSize + GAP), row2Y + HDR + 2, kSize, kSize + 14);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow3_LfosFxAndCv()
{
    constexpr int PAD = 5;
    constexpr int TOP = 36;
    constexpr int HDR = 16;
    constexpr int GAP = 8;

    int row1Y = TOP + 6;
    int row1H = 110;
    int row2Y = row1Y + row1H + PAD;
    int row2H = 118;
    int kSize = 54;
    int comboH = 18;

    int row3Y = row2Y + row2H + PAD;
    int row3H = 118;

    int lfoW = 270;
    secLfo1.setBounds(PAD, row3Y, lfoW, row3H);

    int lComboW = 74;
    int lfoKnobY = row3Y + HDR + 2 + comboH + GAP;
    lfo1Shape.setBounds(PAD + 6, row3Y + HDR + 2, lComboW, comboH);
    lfo1Target.setBounds(PAD + 6 + lComboW + GAP, row3Y + HDR + 2, lComboW, comboH);
    lfo1Freq.setBounds(PAD + 6, lfoKnobY, kSize, kSize + 14);
    lfo1Amount.setBounds(PAD + 6 + (kSize + GAP), lfoKnobY, kSize, kSize + 14);
    lfo1Delay.setBounds(PAD + 6 + 2 * (kSize + GAP), lfoKnobY, kSize, kSize + 14);
    lfo1Sync.setBounds(PAD + 6 + 3 * (kSize + GAP), row3Y + HDR + 2, 66, 18);
    lfo1Reset.setBounds(PAD + 6 + 3 * (kSize + GAP), row3Y + HDR + 24, 66, 18);

    int lfo2X = PAD + lfoW + PAD;
    secLfo2.setBounds(lfo2X, row3Y, lfoW, row3H);

    lfo2Shape.setBounds(lfo2X + 6, row3Y + HDR + 2, lComboW, comboH);
    lfo2Target.setBounds(lfo2X + 6 + lComboW + GAP, row3Y + HDR + 2, lComboW, comboH);
    lfo2Freq.setBounds(lfo2X + 6, lfoKnobY, kSize, kSize + 14);
    lfo2Amount.setBounds(lfo2X + 6 + (kSize + GAP), lfoKnobY, kSize, kSize + 14);
    lfo2Delay.setBounds(lfo2X + 6 + 2 * (kSize + GAP), lfoKnobY, kSize, kSize + 14);
    lfo2Sync.setBounds(lfo2X + 6 + 3 * (kSize + GAP), row3Y + HDR + 2, 66, 18);
    lfo2Reset.setBounds(lfo2X + 6 + 3 * (kSize + GAP), row3Y + HDR + 24, 66, 18);

    int distX = lfo2X + lfoW + PAD;
    int distW = 2 * (kSize + GAP) + 28;
    secFx.setBounds(distX, row3Y, distW, row3H);
    distOn.setBounds(distX + 8, row3Y + HDR + 6, 60, 18);
    distType.setBounds(distX + 76, row3Y + HDR + 6, 70, 18);
    distDrive.setBounds(distX + 8, row3Y + HDR + 30, kSize, kSize + 14);
    distTone.setBounds(distX + 8 + kSize + GAP, row3Y + HDR + 30, kSize, kSize + 14);

    int cvX = distX + distW + PAD;
    int cvW = getWidth() - cvX - PAD;
    secCV.setBounds(cvX, row3Y, cvW, row3H);
    cvAmount.setBounds(cvX + 6, row3Y + HDR + 2, kSize, kSize + 14);
    cvTarget.setBounds(cvX + 6, row3Y + HDR + 2 + kSize + 14 + GAP, juce::jmax(90, cvW - 16), comboH);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow4_ModEnvVelUnisonChar()
{
    constexpr int PAD = 5;
    constexpr int TOP = 36;
    constexpr int HDR = 16;
    constexpr int GAP = 8;

    int row1Y = TOP + 6;
    int row1H = 110;
    int row2Y = row1Y + row1H + PAD;
    int row2H = 118;
    int row3Y = row2Y + row2H + PAD;
    int row3H = 118;
    int kSize = 54;
    int comboH = 18;

    int row4Y = row3Y + row3H + PAD;
    int row4H = 118;

    int modEnvW = 3 * (kSize + GAP) + 8;
    secModEnv.setBounds(PAD, row4Y, modEnvW, row4H);
    modEnvAtk.setBounds(PAD + 6, row4Y + HDR + 2, kSize, kSize + 14);
    modEnvDec.setBounds(PAD + 6 + (kSize + GAP), row4Y + HDR + 2, kSize, kSize + 14);
    modEnvAmt.setBounds(PAD + 6 + 2 * (kSize + GAP), row4Y + HDR + 2, kSize, kSize + 14);

    int modEnvDestY = row4Y + HDR + 2 + kSize + 14 + GAP;
    modEnvDest.setBounds(PAD + 6, modEnvDestY, modEnvW - 12, comboH);

    int velX = PAD + modEnvW + PAD;
    int velW = 2 * (kSize + GAP) + 8;
    secVelocity.setBounds(velX, row4Y, velW, row4H);
    velToAmp.setBounds(velX + 6, row4Y + HDR + 2, kSize, kSize + 14);
    velToFlt.setBounds(velX + 6 + (kSize + GAP), row4Y + HDR + 2, kSize, kSize + 14);

    int detuneX = velX + velW + PAD;
    int detuneW = kSize + 20;
    secUnison.setBounds(detuneX, row4Y, detuneW, row4H);
    dualDetune.setBounds(detuneX + 8, row4Y + HDR + 2, kSize, kSize + 14);

    int charX = detuneX + detuneW + PAD;
    int charW = getWidth() - charX - PAD;
    secChar.setBounds(charX, row4Y, charW, row4H);
    dualVoice.setBounds(charX + 6, row4Y + HDR + 2, kSize, kSize + 14);
    waspChar.setBounds(charX + 6 + (kSize + GAP), row4Y + HDR + 2, kSize, kSize + 14);
    vcoBinary.setBounds(charX + 6 + 2 * (kSize + GAP), row4Y + HDR + 2, kSize, kSize + 14);
    cmosFilter.setBounds(charX + 6 + 3 * (kSize + GAP), row4Y + HDR + 2, 70, 20);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow5_Filter2RoutingDelayOutput()
{
    constexpr int PAD = 5;
    constexpr int TOP = 36;
    constexpr int HDR = 16;
    constexpr int GAP = 8;

    int row1Y = TOP + 6;
    int row1H = 110;
    int row2Y = row1Y + row1H + PAD;
    int row2H = 118;
    int row3Y = row2Y + row2H + PAD;
    int row3H = 118;
    int row4Y = row3Y + row3H + PAD;
    int row4H = 118;
    int kSize = 54;
    int comboH = 18;

    int row5Y = row4Y + row4H + PAD;
    int row5H = 118;

    int flt2W = 4 * (kSize + GAP) + 78;
    secFilter2.setBounds(PAD, row5Y, flt2W, row5H);
    flt2Type.setBounds(PAD + 6, row5Y + HDR + 2, 70, comboH);
    flt2Model.setBounds(PAD + 6, row5Y + HDR + 2 + comboH + GAP, 70, comboH);
    cutoff2.setBounds(PAD + 6 + 70 + GAP, row5Y + HDR + 2, kSize, kSize + 14);
    resonance2.setBounds(PAD + 6 + 70 + GAP + (kSize + GAP), row5Y + HDR + 2, kSize, kSize + 14);
    flt2EnvAmt.setBounds(PAD + 6 + 70 + GAP + 2 * (kSize + GAP), row5Y + HDR + 2, kSize, kSize + 14);
    flt2KT.setBounds(PAD + 6 + 70 + GAP + 3 * (kSize + GAP), row5Y + HDR + 2, kSize, kSize + 14);

    int routeX = PAD + flt2W + PAD;
    int routeW = 160 + GAP + kSize + 12;
    secRouting.setBounds(routeX, row5Y, routeW, row5H);
    fltRouting.setBounds(routeX + 6, row5Y + HDR + 2, 160, comboH);
    fltParallelMix.setBounds(routeX + 6 + 160 + GAP, row5Y + HDR + 2, kSize, kSize + 14);

    int delayX = routeX + routeW + PAD;
    int delayW = 3 * (kSize + GAP) + 8;
    secDelay.setBounds(delayX, row5Y, delayW, row5H);
    delayTime.setBounds(delayX + 6, row5Y + HDR + 2, kSize, kSize + 14);
    delayFeedback.setBounds(delayX + 6 + (kSize + GAP), row5Y + HDR + 2, kSize, kSize + 14);
    delayMix.setBounds(delayX + 6 + 2 * (kSize + GAP), row5Y + HDR + 2, kSize, kSize + 14);

    int outX = delayX + delayW + PAD;
    int outW = getWidth() - outX - PAD;
    secOutput.setBounds(outX, row5Y, outW, row5H);
    masterVolume.setBounds(outX + 6, row5Y + HDR + 2, kSize, kSize + 14);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow6_DxFm()
{
    constexpr int PAD = 5;
    constexpr int TOP = 36;
    constexpr int HDR = 16;

    int row1Y = TOP + 6;
    int row1H = 110;
    int row2Y = row1Y + row1H + PAD;
    int row2H = 118;
    int row3Y = row2Y + row2H + PAD;
    int row3H = 118;
    int row4Y = row3Y + row3H + PAD;
    int row4H = 118;
    int row5Y = row4Y + row4H + PAD;
    int row5H = 118;

    int row6Y = row5Y + row5H + PAD;
    int row6H = 118;

    secDx.setBounds(PAD, row6Y, getWidth() - 2 * PAD, row6H);

    const int leftColW = 78;
    const int leftX = PAD + 6;

    dxfmEnable.setBounds(leftX, row6Y + HDR + 4, leftColW - 4, 18);
    dxfmBlend.setBounds(leftX, row6Y + HDR + 26, 54, 54 + 14);

    const int dxAreaX = leftX + leftColW + 4;
    const int dxAreaW = getWidth() - dxAreaX - PAD - 4;
    const int slotW = dxAreaW / 15;
    const int knobW = juce::jmin(54, slotW - 2);
    const int knobY = row6Y + HDR + 8;

    auto placeSlot = [&](WaspKnob& k, int idx)
        {
            k.setBounds(dxAreaX + idx * slotW, knobY, knobW, knobW + 14);
        };

    placeSlot(dxCarA, 0);
    placeSlot(dxCarD, 1);
    placeSlot(dxCarR, 2);
    placeSlot(dxWave, 3);

    placeSlot(dxModI, 4);
    placeSlot(dxModD, 5);
    placeSlot(dxModS, 6);
    placeSlot(dxModR, 7);
    placeSlot(dxModV, 8);

    placeSlot(dxCoarse, 9);
    placeSlot(dxFine, 10);
    placeSlot(dxThru, 11);
    placeSlot(dxOctave, 12);
    placeSlot(dxTune, 13);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::layoutRow7_CpuSaver()
{
    constexpr int PAD = 5;
    constexpr int TOP = 36;
    constexpr int HDR = 16;

    int row1Y = TOP + 6;
    int row1H = 110;
    int row2Y = row1Y + row1H + PAD;
    int row2H = 118;
    int row3Y = row2Y + row2H + PAD;
    int row3H = 118;
    int row4Y = row3Y + row3H + PAD;
    int row4H = 118;
    int row5Y = row4Y + row4H + PAD;
    int row5H = 118;
    int row6Y = row5Y + row5H + PAD;
    int row6H = 118;

    int row7Y = row6Y + row6H + PAD;
    int row7H = getHeight() - row7Y - PAD;
    if (row7H < 80) row7H = 80;

    secCpu.setBounds(PAD, row7Y, getWidth() - 2 * PAD, row7H);

    const int innerX = PAD + 12;
    const int innerW = getWidth() - 2 * PAD - 24;
    const int colGap = 12;
    const int rowGap = 6;
    const int colW = (innerW - 2 * colGap) / 3;
    const int toggleH = 20;
    const int topY = row7Y + HDR + 10;

    auto placeCell = [&](juce::ToggleButton& b, int col, int row)
        {
            b.setBounds(innerX + col * (colW + colGap),
                topY + row * (toggleH + rowGap),
                colW, toggleH);
        };

    placeCell(bpFilter2Btn, 0, 0);
    placeCell(bpDelayBtn, 1, 0);
    placeCell(bpDistBtn, 2, 0);

    placeCell(bpLfo2Btn, 0, 1);
    placeCell(bpModEnvBtn, 1, 1);
    placeCell(bpCvBtn, 2, 1);

    placeCell(bpDualVBtn, 0, 2);
    placeCell(bpWaspCharBtn, 1, 2);
    placeCell(bpVcoBinBtn, 2, 2);
}

//==============================================================================
// ==== NEW: Preset management implementation ====
//==============================================================================

//==============================================================================
void WASPAlphaAudioProcessorEditor::refreshPresetList()
{
    // Guard against the onChange handler firing while we rebuild the list.
    // Without this, clearing the combo would emit a -1 selection change and
    // the handler would try to load preset -1.
    updatingPresetSelector = true;

    presetSelector.clear(juce::dontSendNotification);

    auto& manager = audioProcessor.getPresetManager();
    const auto& all = manager.getAllPresets();

    // Add every preset with a 1-based item ID (JUCE ComboBox item IDs must
    // be > 0 — 0 means "nothing selected"). The manager's index is
    // therefore ComboBox item ID - 1.
    for (size_t i = 0; i < all.size(); ++i)
    {
        const auto& info = all[i];

        // Compose the display string. Factory presets show just their name;
        // user presets get a bullet so the user can tell them apart at a
        // glance in the dropdown.
        juce::String display;
        if (!info.isFactory)
            display << juce::String::charToString((juce::juce_wchar)0x2022) << " ";  // •

        display << info.name;

        if (info.category.isNotEmpty())
            display << "   [" << info.category << "]";

        presetSelector.addItem(display, (int)i + 1);
    }

    // If we have any presets, select the first one as a sensible default.
    // We don't load it here — the initial APVTS state is whatever the host
    // restored on project load, and we shouldn't stomp on that.
    if (presetSelector.getNumItems() > 0)
        presetSelector.setSelectedId(1, juce::dontSendNotification);

    updatingPresetSelector = false;
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::onPresetSelected(int comboItemId)
{
    if (comboItemId <= 0)
        return;

    // ComboBox item IDs are 1-based; the manager's index is 0-based.
    const int managerIndex = comboItemId - 1;

    auto& manager = audioProcessor.getPresetManager();
    if (managerIndex < 0 || managerIndex >= manager.getNumPresets())
        return;

    manager.loadPreset(managerIndex);
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::onSavePresetClicked()
{
    // Launch a modal AlertWindow asking for the preset name. The dialog
    // returns the typed string via a callback (JUCE's AlertWindow is async
    // by default). All of the save logic happens in the callback, so it
    // runs after the user has entered their name and hit OK.

    auto* window = new juce::AlertWindow("Save Preset",
        "Enter a name for the new preset:",
        juce::MessageBoxIconType::NoIcon);

    window->addTextEditor("name", "", "Name:");

    // Provide a default based on the currently-selected preset, so the user
    // can quickly save a variant of an existing sound without retyping.
    const int currentIdx = presetSelector.getSelectedId() - 1;
    if (currentIdx >= 0)
    {
        auto& manager = audioProcessor.getPresetManager();
        if (currentIdx < manager.getNumPresets())
        {
            const auto& info = manager.getPresetInfo(currentIdx);
            window->getTextEditor("name")->setText(info.name + " (copy)",
                juce::dontSendNotification);
            window->getTextEditor("name")->selectAll();
        }
    }

    window->addButton("Save", 1, juce::KeyPress(juce::KeyPress::returnKey));
    window->addButton("Cancel", 0, juce::KeyPress(juce::KeyPress::escapeKey));

    // Capture a reference to `this` safely — the editor is guaranteed to
    // outlive the AlertWindow because the AlertWindow is modal and owned
    // by the message thread, and the editor is what launched it.
    window->enterModalState(true,
        juce::ModalCallbackFunction::create(
            [this, window](int result)
            {
                // Grab the typed name BEFORE the window is destroyed.
                juce::String name = window->getTextEditorContents("name").trim();

                // JUCE auto-deletes the AlertWindow after the modal state
                // ends (because we passed `true` for `deleteWhenDismissed`).
                // We captured `window` only to read the field — no manual
                // delete needed.

                if (result == 0 || name.isEmpty())
                    return;   // user cancelled or left the field blank

                // Ask the manager to save. The manager's category/author
                // arguments are currently unused (blank) — matching the
                // earlier decision to leave author empty and keep just
                // the preset name.
                auto& manager = audioProcessor.getPresetManager();
                juce::File saved = manager.saveUserPreset(name, "", "", false);

                // If the file already existed, `saveUserPreset` returns the
                // existing file without overwriting. Detect that and offer
                // to overwrite.
                if (saved.existsAsFile())
                {
                    // Was it actually written, or did the manager just
                    // hand back the pre-existing path? Compare the file's
                    // modification time to "now" — if it's more than a
                    // couple of seconds old, it's an existing file.
                    const auto ageMs = juce::Time::getCurrentTime()
                        .toMilliseconds()
                        - saved.getLastModificationTime().toMilliseconds();

                    if (ageMs > 2000)
                    {
                        // Collision. Prompt to overwrite.
                        juce::AlertWindow::showOkCancelBox(
                            juce::MessageBoxIconType::QuestionIcon,
                            "Preset Already Exists",
                            "A preset named \"" + name + "\" already exists. Overwrite it?",
                            "Overwrite", "Cancel", this,
                            juce::ModalCallbackFunction::create(
                                [this, name](int overwriteResult)
                                {
                                    if (overwriteResult == 0)
                                        return;  // cancelled

                                    auto& m = audioProcessor.getPresetManager();
                                    m.saveUserPreset(name, "", "", true);
                                    refreshPresetList();

                                    // Reselect the newly-saved preset so the
                                    // user sees it as the active item.
                                    for (int i = 0; i < presetSelector.getNumItems(); ++i)
                                    {
                                        const int itemId = presetSelector.getItemId(i);
                                        auto& info = m.getPresetInfo(itemId - 1);
                                        if (!info.isFactory && info.name == name)
                                        {
                                            presetSelector.setSelectedId(itemId,
                                                juce::dontSendNotification);
                                            break;
                                        }
                                    }
                                }));
                        return;
                    }
                }

                // No collision — refresh and select the newly-saved preset.
                refreshPresetList();

                auto& m = audioProcessor.getPresetManager();
                for (int i = 0; i < presetSelector.getNumItems(); ++i)
                {
                    const int itemId = presetSelector.getItemId(i);
                    const auto& info = m.getPresetInfo(itemId - 1);
                    if (!info.isFactory && info.name == name)
                    {
                        presetSelector.setSelectedId(itemId, juce::dontSendNotification);
                        break;
                    }
                }
            }),
        true);   // deleteWhenDismissed
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::onDeletePresetClicked()
{
    const int currentIdx = presetSelector.getSelectedId() - 1;
    if (currentIdx < 0)
        return;

    auto& manager = audioProcessor.getPresetManager();
    if (currentIdx >= manager.getNumPresets())
        return;

    const auto& info = manager.getPresetInfo(currentIdx);

    if (info.isFactory)
    {
        // Factory presets can't be deleted — tell the user why.
        juce::AlertWindow::showMessageBoxAsync(
            juce::MessageBoxIconType::InfoIcon,
            "Cannot Delete",
            "Factory presets cannot be deleted. Save your own preset to "
            "create a copy you can modify.");
        return;
    }

    // Confirm before deleting a user preset.
    juce::AlertWindow::showOkCancelBox(
        juce::MessageBoxIconType::WarningIcon,
        "Delete Preset",
        "Delete \"" + info.name + "\"? This cannot be undone.",
        "Delete", "Cancel", this,
        juce::ModalCallbackFunction::create(
            [this, currentIdx](int result)
            {
                if (result == 0)
                    return;  // cancelled

                auto& m = audioProcessor.getPresetManager();
                m.deletePreset(currentIdx);
                refreshPresetList();
            }));
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::onExportPresetClicked()
{
    // Export the current APVTS state to a user-chosen file. This is
    // different from Save — the exported file lives wherever the user
    // puts it, not in the plugin's preset folder. Useful for sharing
    // presets with other Stinger users.

    // Build a default filename from the current preset name, if we have one.
    juce::String suggestedName = "Preset";
    const int currentIdx = presetSelector.getSelectedId() - 1;
    if (currentIdx >= 0)
    {
        auto& manager = audioProcessor.getPresetManager();
        if (currentIdx < manager.getNumPresets())
            suggestedName = manager.getPresetInfo(currentIdx).name;
    }

    // FileChooser is async — it returns immediately and calls the callback
    // when the user picks a file or cancels.
    auto chooser = std::make_shared<juce::FileChooser>(
        "Export Preset As...",
        juce::File::getSpecialLocation(juce::File::userDocumentsDirectory)
        .getChildFile(suggestedName + ".stinger"),
        "*.stinger");

    chooser->launchAsync(
        juce::FileBrowserComponent::saveMode
        | juce::FileBrowserComponent::warnAboutOverwriting,
        [this, chooser, suggestedName](const juce::FileChooser& fc)
        {
            auto chosen = fc.getResult();
            if (chosen == juce::File()) return;   // user cancelled

            // Ensure the extension is .stinger even if the user typed
            // something else.
            if (!chosen.hasFileExtension("stinger"))
                chosen = chosen.withFileExtension("stinger");

            auto& manager = audioProcessor.getPresetManager();
            manager.exportPresetToFile(chosen, suggestedName, "", "");
        });
}

//==============================================================================
void WASPAlphaAudioProcessorEditor::onOpenFolderClicked()
{
    auto& manager = audioProcessor.getPresetManager();
    juce::File dir = manager.getUserPresetDirectory();

    if (!dir.isDirectory())
        dir.createDirectory();

    // revealToUser() opens the system file browser with the folder visible.
    // On Windows it opens Explorer, on macOS it opens Finder, on Linux it
    // opens whichever file manager is registered. If the folder can't be
    // opened for some reason (rare), a silent failure is acceptable — the
    // user can always navigate there manually.
    dir.revealToUser();
}