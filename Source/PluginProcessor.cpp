#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PresetManager.h"

//==============================================================================
// Parameter Layout
//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout WASPAlphaAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    using namespace WaspParams;

    // Osc 1
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ OSC1_SHAPE, 1 }, "Osc-1 Shape",
        juce::StringArray{ "Saw", "Square", "Triangle", "Sine", "303-Saw" }, 0));
    layout.add(std::make_unique<juce::AudioParameterInt>(
        juce::ParameterID{ OSC1_COARSE, 1 }, "Osc-1 Coarse", -24, 24, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ OSC1_FINE, 1 }, "Osc-1 Fine",
        juce::NormalisableRange<float>(-100.0f, 100.0f, 1.0f), 0.0f));

    // Osc 2
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ OSC2_SHAPE, 1 }, "Osc-2 Shape",
        juce::StringArray{ "Saw", "Square", "Triangle", "Sine", "303-Saw" }, 0));
    layout.add(std::make_unique<juce::AudioParameterInt>(
        juce::ParameterID{ OSC2_COARSE, 1 }, "Osc-2 Coarse", -24, 24, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ OSC2_FINE, 1 }, "Osc-2 Fine",
        juce::NormalisableRange<float>(-100.0f, 100.0f, 1.0f), 0.0f));

    // Osc 3 (sub/noise)
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ OSC3_SHAPE, 1 }, "Osc-3 Shape",
        juce::StringArray{ "Sub", "Sub-Sub", "Noise" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ OSC3_AMOUNT, 1 }, "Osc-3 Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));

    // Mix / Mod
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ OSC_MIX, 1 }, "Osc Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ PULSE_WIDTH, 1 }, "Pulse Width",
        juce::NormalisableRange<float>(0.05f, 0.95f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FM_AMOUNT, 1 }, "FM",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ RM_AMOUNT, 1 }, "RM",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));

    // Amp Envelope
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ AMP_ATTACK, 1 }, "Amp Attack",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.01f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ AMP_DECAY, 1 }, "Amp Decay",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.1f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ AMP_SUSTAIN, 1 }, "Amp Sustain",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.7f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ AMP_RELEASE, 1 }, "Amp Release",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.3f));

    // Filter Envelope
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_ATTACK, 1 }, "Filter Attack",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.01f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_DECAY, 1 }, "Filter Decay",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.3f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_SUSTAIN, 1 }, "Filter Sustain",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_RELEASE, 1 }, "Filter Release",
        juce::NormalisableRange<float>(0.001f, 8.0f, 0.001f, 0.4f), 0.5f));

    // Filter
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_KEYTRACK, 1 }, "Filter Keytrack",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ FLT_TYPE, 1 }, "Filter Type",
        juce::StringArray{ "LP12", "LP24", "HP12", "BP12" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_CUTOFF, 1 }, "Cutoff",
        juce::NormalisableRange<float>(20.0f, 18000.0f, 0.1f, 0.3f), 2000.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_RESO, 1 }, "Resonance",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_ENV_AMT, 1 }, "Envelope Amount",
        juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.5f));

    // Filter 2 — dual multimode resonant filter (KillerBee)
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT2_KEYTRACK, 1 }, "Filter 2 Keytrack",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ FLT2_TYPE, 1 }, "Filter 2 Type",
        juce::StringArray{ "LP12", "LP24", "HP12", "BP12" }, 2)); // default HP12 so series mode is useful out of the box
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT2_CUTOFF, 1 }, "Cutoff 2",
        juce::NormalisableRange<float>(20.0f, 18000.0f, 0.1f, 0.3f), 4000.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT2_RESO, 1 }, "Resonance 2",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT2_ENV_AMT, 1 }, "Envelope Amount 2",
        juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ FLT_ROUTING, 1 }, "Filter Routing",
        juce::StringArray{ "Filter 1 Only", "Filter 2 Only", "Series (1->2)", "Parallel" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ FLT_PARALLEL_MIX, 1 }, "Filter Parallel Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f)); // 0 = all Filter1, 1 = all Filter2

    // Filter model: Ladder (default, unchanged behaviour) vs Chamberlin SVF May still be buggy
    // (TS-404/303-style acid character). Independent per filter.
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ FLT_MODEL, 1 }, "Filter Model",
        juce::StringArray{ "Ladder", "Chamberlin" }, 0));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ FLT2_MODEL, 1 }, "Filter 2 Model",
        juce::StringArray{ "Ladder", "Chamberlin" }, 0));

    // LFO 1
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ LFO1_SHAPE, 1 }, "Lfo-1 Shape",
        juce::StringArray{ "Sine", "Triangle", "Saw", "RevSaw", "Square", "S&H" }, 0));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ LFO1_TARGET, 1 }, "Lfo-1 Target",
        juce::StringArray{ "Pitch", "Osc1 Pitch", "Osc2 Pitch", "Pulse Width", "Filter", "Amp", "Resonance" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO1_AMOUNT, 1 }, "Lfo-1 Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO1_FREQ, 1 }, "Lfo-1 Freq",
        juce::NormalisableRange<float>(0.01f, 20.0f, 0.001f, 0.4f), 2.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ LFO1_SYNC, 1 }, "Lfo-1 Sync", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ LFO1_RESET, 1 }, "Lfo-1 Reset", false));

    // LFO 2
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ LFO2_SHAPE, 1 }, "Lfo-2 Shape",
        juce::StringArray{ "Sine", "Triangle", "Saw", "RevSaw", "Square", "S&H" }, 0));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ LFO2_TARGET, 1 }, "Lfo-2 Target",
        juce::StringArray{ "Pitch", "Osc1 Pitch", "Osc2 Pitch", "Pulse Width", "Filter", "Amp", "Resonance" }, 0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO2_AMOUNT, 1 }, "Lfo-2 Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO2_FREQ, 1 }, "Lfo-2 Freq",
        juce::NormalisableRange<float>(0.01f, 20.0f, 0.001f, 0.4f), 3.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ LFO2_SYNC, 1 }, "Lfo-2 Sync", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ LFO2_RESET, 1 }, "Lfo-2 Reset", false));

    // Distortion
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ DIST_ON, 1 }, "Distortion On", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DIST_DRIVE, 1 }, "Dist Drive",
        juce::NormalisableRange<float>(1.0f, 20.0f, 0.01f), 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DIST_TONE, 1 }, "Dist Tone",
        juce::NormalisableRange<float>(200.0f, 8000.0f, 1.0f, 0.4f), 2000.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DIST_MIX, 1 }, "Dist Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f)); // 1.0 = fully wet, matches old (only) behaviour
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ DIST_TYPE, 1 }, "Dist Type",
        juce::StringArray{ "Soft", "Hard" }, 0)); // 0=existing softClip curve, 1=hard digital clip (TS-404 style)

    // Character
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DUAL_VOICE, 1 }, "Dual Voice",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ WASP_CHAR, 1 }, "Wasp",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ VCO_BINARY, 1 }, "VCO Binary",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));

    // CMOS filter mode (authentic EDP WASP transmission-gate filter emulation)
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ CMOS_FILTER, 1 }, "CMOS Filter", false));

    // CV (Control Voltage) — modulates a chosen destination at audio rate from Osc1
    // This lets you use Osc1 as a true CV source into the filter or pitch (FM-style via CV path)
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ CV_AMOUNT, 1 }, "CV Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ CV_TARGET, 1 }, "CV Target",
        juce::StringArray{ "Filter Cutoff", "Osc2 Pitch", "Pulse Width", "Amp" }, 0));

    // Mod Env (one-shot AD generator, EDP WASP MOD ENV section)
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ MODENV_ATTACK, 1 }, "Mod Env Attack",
        juce::NormalisableRange<float>(0.001f, 4.0f, 0.001f, 0.4f), 0.01f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ MODENV_DECAY, 1 }, "Mod Env Decay",
        juce::NormalisableRange<float>(0.001f, 4.0f, 0.001f, 0.4f), 0.2f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ MODENV_AMOUNT, 1 }, "Mod Env Amount",
        juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ MODENV_DEST, 1 }, "Mod Env Destination",
        juce::StringArray{ "Pulse Width", "LFO1 Amount", "Osc1 Level", "Osc2 Pitch" }, 0));

    // Velocity  
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ VEL_TO_AMP, 1 }, "Velocity to Amp",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ VEL_TO_FILTER, 1 }, "Velocity to Filter",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));

    // LFO onset delay
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO1_DELAY, 1 }, "Lfo-1 Delay",
        juce::NormalisableRange<float>(0.0f, 4.0f, 0.001f, 0.5f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ LFO2_DELAY, 1 }, "Lfo-2 Delay",
        juce::NormalisableRange<float>(0.0f, 4.0f, 0.001f, 0.5f), 0.0f));

    // True unison detune depth for Dual Voice (cents)
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DUAL_DETUNE, 1 }, "Dual Voice Detune",
        juce::NormalisableRange<float>(0.0f, 50.0f, 0.1f), 8.0f));

    // Delay (KillerBee addition) — simple single-tap feedback delay.
    // Time uses a skew so the usable 50ms-1s "human" range gets most of the knob travel,
    // rather than being crammed into the first few degrees of rotation.
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DELAY_TIME_MS, 1 }, "Delay Time",
        juce::NormalisableRange<float>(1.0f, 2000.0f, 0.1f, 0.35f), 350.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DELAY_FEEDBACK, 1 }, "Delay Feedback",
        juce::NormalisableRange<float>(0.0f, 0.95f, 0.001f), 0.3f)); // capped below 1.0 so it can't runaway
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DELAY_MIX, 1 }, "Delay Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f)); // 0 = off by default, opt-in

       layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ MASTER_VOLUME, 1 }, "Master Volume",
        juce::NormalisableRange<float>(-60.0f, 6.0f, 0.01f, 3.0f), 0.0f));
   // Master on/off. Default false so nothing changes for existing patches.
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ DXFM_ENABLE, 1 }, "DX FM Enable", false));

    // Output blend: 0 = pure subtractive, 1 = pure DX FM.
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_BLEND, 1 }, "DX FM Blend",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));

    // Carrier envelope (Alpha-DX "carrier" had no sustain knob — its amp env
    // always decays to zero, so we expose attack / decay / release only).
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_CAR_ATK, 1 }, "DX Carrier Attack",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_CAR_DEC, 1 }, "DX Carrier Decay",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_CAR_REL, 1 }, "DX Carrier Release",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.3f));

    // Alpha-DX "rich" / waveform term.
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_WAVE, 1 }, "DX Waveform",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));

    // Modulator envelope (Alpha-DX "modulator" ADSR).
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_INIT, 1 }, "DX Mod Init",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_DEC, 1 }, "DX Mod Decay",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_SUS, 1 }, "DX Mod Sus",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_REL, 1 }, "DX Mod Rel",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_VEL, 1 }, "DX Mod Vel",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));

    // Modulator : carrier frequency ratio.
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_COARSE, 1 }, "DX Coarse",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_FINE, 1 }, "DX Fine",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));

    // Mod-thru: dry modulator leak into output.
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_MOD_THRU, 1 }, "DX Mod Thru",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));

    // Pitch — octave shift + fine tune.
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_OCTAVE, 1 }, "DX Octave",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ DXFM_TUNE, 1 }, "DX Fine Tune",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));

    // ========================================================================
    // ==== NEW: CPU Saver bypass toggles ====
    // All default false (= section active), so existing patches are unchanged.
    // When true, the corresponding section is skipped entirely in processBlock.
    // ========================================================================
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ BYPASS_FILTER2,   1 }, "Bypass Filter 2", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ BYPASS_DELAY,     1 }, "Bypass Delay", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ BYPASS_DIST,      1 }, "Bypass Distortion", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ BYPASS_LFO2,      1 }, "Bypass LFO 2", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ BYPASS_MODENV,    1 }, "Bypass Mod Env", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ BYPASS_CV,        1 }, "Bypass CV", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ BYPASS_DUALVOICE, 1 }, "Bypass Dual Voice", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ BYPASS_WASPCHAR,  1 }, "Bypass Wasp Char", false));
    layout.add(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ BYPASS_VCOBIN,    1 }, "Bypass VCO Binary", false));

    return layout;
}

//==============================================================================
WASPAlphaAudioProcessor::WASPAlphaAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    apvts(*this, nullptr, "WASPAlphaState", createParameterLayout())
{
    using namespace WaspParams;
    // Register listener for all params
    for (auto* param : apvts.processor.getParameters())
    {
        if (auto* p = dynamic_cast<juce::RangedAudioParameter*> (param))
            apvts.addParameterListener(p->getParameterID(), this);
    }
    presetManager = std::make_unique<PresetManager>(apvts);
}

WASPAlphaAudioProcessor::~WASPAlphaAudioProcessor()
{
    
    presetManager.reset();

    for (auto* param : apvts.processor.getParameters())
    {
        if (auto* p = dynamic_cast<juce::RangedAudioParameter*> (param))
            apvts.removeParameterListener(p->getParameterID(), this);
    }
}

//==============================================================================
void WASPAlphaAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Defensive clamp: guards every calculation below (and inside prepare()
    // calls for voices/delay/etc) against a placeholder/invalid value some
    // hosts pass during an initial validation pass, before real audio is
    // selected. See SimpleDelay::prepare() for the specific crash this fixes.
    sampleRate = juce::jlimit(8000.0, 384000.0, sampleRate);
    samplesPerBlock = juce::jmax(1, samplesPerBlock);

    currentSampleRate = sampleRate;
    currentBlockSize = samplesPerBlock;

    for (auto& v : voices)
    {
        v.setSampleRate(sampleRate);
        v.isActive = false;
        v.noteHeld = false;
        v.filter.reset();
        v.filter2.reset();
        v.chamberlinF.reset();
        v.chamberlinF2.reset();
        // ==== NEW: reset DX FM state so no stale phase/envelope leaks in ====
        v.dx.reset();
    }

    lfo1.setSampleRate(sampleRate);
    lfo2.setSampleRate(sampleRate);

    delayL.prepare(sampleRate);
    delayR.prepare(sampleRate);

    distDryL.assign((size_t)samplesPerBlock, 0.0f);
    distDryR.assign((size_t)samplesPerBlock, 0.0f);

    juce::dsp::ProcessSpec spec{ sampleRate, (juce::uint32)samplesPerBlock, 2u };
    distToneFilter.prepare(spec);
    *distToneFilter.state = *juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(
        sampleRate, 1000.0f);
    lastDistTone = 1000.0f; // matches the initial coefficients just set, so the
    // first real block doesn't recompute for nothing

// ==== NEW: latch the pitch bend default and clear mod wheel ====
    pitchBendGlobal = 1.0;
    modWheelValue = 0.0f;

    // Prime DX FM coefficients once so the very first block already has
    // sensible values, even before any parameter change fires.
    updateDxParams();

    isPrepared = true;
}

void WASPAlphaAudioProcessor::releaseResources()
{
    // Host must call prepareToPlay again before processBlock is safe to run —
    // matches the isPrepared guard added to processBlock.
    isPrepared = false;
}

bool WASPAlphaAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // We never declare an input bus in BusesProperties (see the constructor),
    // so getMainInputChannelSet() is already always disabled() for any layout
    // a host could negotiate — this check can't change behaviour, it's just
    // an explicit, self-documenting statement of intent for a VST3 instrument.
    if (layouts.getMainInputChannelSet() != juce::AudioChannelSet::disabled())
        return false;

    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

//==============================================================================
void WASPAlphaAudioProcessor::parameterChanged(const juce::String& paramID, float newValue)
{
    juce::ignoreUnused(paramID, newValue);
}

//==============================================================================
// ==== NEW: DX FM coefficient refresh ====
// Reads the current DX FM parameters from the APVTS and recomputes the
// per-block coefficient set. Cheap enough to run every block — this
// guarantees the FM voice tracks live knob moves without needing a
// parameterChanged listener wired up for each one.
void WASPAlphaAudioProcessor::updateDxParams()
{
    using namespace WaspParams;

    const float ifs = (float)(1.0 / currentSampleRate);

    // Parameter reads. Every read is a fresh APVTS load so the values are
    // consistent with whatever the host has most recently set.
    const float pOctave = apvts.getRawParameterValue(DXFM_OCTAVE)->load();
    const float pTune = apvts.getRawParameterValue(DXFM_TUNE)->load();
    const float pCoarse = apvts.getRawParameterValue(DXFM_COARSE)->load();
    const float pFine = apvts.getRawParameterValue(DXFM_FINE)->load();
    const float pInit = apvts.getRawParameterValue(DXFM_MOD_INIT)->load();
    const float pModDec = apvts.getRawParameterValue(DXFM_MOD_DEC)->load();
    const float pModRel = apvts.getRawParameterValue(DXFM_MOD_REL)->load();
    const float pCarAtk = apvts.getRawParameterValue(DXFM_CAR_ATK)->load();
    const float pCarDec = apvts.getRawParameterValue(DXFM_CAR_DEC)->load();
    const float pCarRel = apvts.getRawParameterValue(DXFM_CAR_REL)->load();
    const float pWave = apvts.getRawParameterValue(DXFM_WAVE)->load();
    const float pThru = apvts.getRawParameterValue(DXFM_MOD_THRU)->load();

    // Octave shift mirrors Alpha-DX: floor(oct * 6.9) - 2
    const float octaveShift = std::floor(pOctave * 6.9f) - 2.0f;

    // Fine tune mirrors Alpha-DX's noteOn: 2*tune-1 maps 0..1 to -1..+1 semitone
    // (the DX engine applies the fine offset inside voice tuning; here we bias
    // the whole DX tune by the same amount so it stays musically parallel.)
    const float fineShift = (pTune + pTune) - 1.0f;

    // Base tune (Hz per sample unit at note 0), matching Alpha-DX's
    // tune = 8.175798915644 * ifs * 2^octaveShift. The fine shift is applied
    // as a semitone multiplier on top.
    dxTune = 8.175798915644f * ifs * std::pow(2.0f, octaveShift)
        * std::pow(2.0f, fineShift / 12.0f);

    // Coarse: squared integer 0..40 (Alpha-DX's cr = floor(40.1 * r^2))
    float rati = std::floor(40.1f * pCoarse * pCoarse);

    // Fine: fractional lookup table (Alpha-DX's fr)
    float ratf;
    if (pFine < 0.5f)
    {
        ratf = 0.2f * pFine * pFine;
    }
    else
    {
        int idx = static_cast<int>(8.9f * pFine);
        switch (idx)
        {
        case 4: ratf = 0.25f;       break;
        case 5: ratf = 0.33333333f; break;
        case 6: ratf = 0.50f;       break;
        case 7: ratf = 0.66666667f; break;
        default: ratf = 0.75f;      break;
        }
    }
    // dxRatio is the modulator's angular increment in the recursive resonator
    dxRatio = 1.570796326795f * (rati + ratf);

    // Envelope depths (Alpha-DX uses 0.0002 * x^2 in both cases)
    dxDepth = 0.0002f * pInit * pInit;
    dxDept2 = 0.0002f * apvts.getRawParameterValue(DXFM_MOD_SUS)->load()
        * apvts.getRawParameterValue(DXFM_MOD_SUS)->load();

    // Envelope coefficients. These match Alpha-DX's updateParameters():
    //   catt = 1 - exp(-ifs * exp(8 - 8*attack))
    //   cdec = (decay > 0.98) ? 1 : exp(-ifs * exp(5 - 8*decay))
    //   crel = exp(-ifs * exp(5 - 5*release))
    //   mdec = 1 - exp(-ifs * exp(6 - 7*modDecay))
    //   mrel = 1 - exp(-ifs * exp(5 - 8*modRel))
    dxCatt = 1.0f - std::exp(-ifs * std::exp(8.0f - 8.0f * pCarAtk));
    dxCdec = (pCarDec > 0.98f) ? 1.0f : std::exp(-ifs * std::exp(5.0f - 8.0f * pCarDec));
    dxCrel = std::exp(-ifs * std::exp(5.0f - 5.0f * pCarRel));
    dxMdec = 1.0f - std::exp(-ifs * std::exp(6.0f - 7.0f * pModDec));
    dxMrel = 1.0f - std::exp(-ifs * std::exp(5.0f - 8.0f * pModRel));

    // Carrier harmonic richness (Alpha-DX's "rich"): 0.5 - 3 * wave^2
    dxRich = 0.50f - 3.0f * pWave * pWave;

    // Mod-thru mix (Alpha-DX's modmix): 0.25 * thru^2
    dxModMix = 0.25f * pThru * pThru;

    // Output gain matches Alpha-DX's initial volume figure.
    dxVolume = 0.0035f;
}

//==============================================================================
// ==== NEW: per-voice DX FM initialisation ====
// Called at note-on when the DX FM module is enabled. Lifts the setup math
// straight from Alpha-DX's noteOn() so the character carries over.
void WASPAlphaAudioProcessor::initDxVoice(WaspVoice& v, int midiNote, int velocity)
{
    auto& d = v.dx;

    // Reset everything to a known state first.
    d.reset();
    d.active = true;

    // v.tuning was already computed by the subtractive voice's noteOn path.
    // Alpha-DX uses exactly this value to scale both envelopes.
    const double tuning = v.tuning;

    // Velocity -> envelope depth. Alpha-DX: (64 + modVel * (vel - 64))
    const float modVel = apvts.getRawParameterValue(WaspParams::DXFM_MOD_VEL)->load();
    const float velScale = 64.0f + modVel * (static_cast<float>(velocity) - 64.0f);

    // Depth = keyTrack * velScale, where keyTrack is min(tuning, 50)
    const double keyTrack = std::min(tuning, 50.0);
    d.menv = static_cast<double>(dxDepth) * keyTrack * velScale;
    d.mlev = static_cast<double>(dxDept2) * keyTrack * velScale;
    d.mdec = static_cast<double>(dxMdec);

    // Modulator recursive oscillator setup.
    // dcar for the modulator is ratio * carrier increment.
    d.dcar = static_cast<double>(dxTune) * pitchBendGlobal * tuning;
    d.dmod = static_cast<double>(dxRatio) * d.dcar;
    d.mod0 = 0.0;
    d.mod1 = std::sin(d.dmod);
    d.dmod = 2.0 * std::cos(d.dmod);

    // Carrier envelope init. Alpha-DX uses (1.5 - wave) * volume * (vel + 10)
    const float wave = apvts.getRawParameterValue(WaspParams::DXFM_WAVE)->load();
    d.env = (1.5f - wave) * dxVolume * (static_cast<float>(velocity) + 10.0f);
    d.catt = static_cast<double>(dxCatt);
    d.cenv = 0.0;
    d.cdec = static_cast<double>(dxCdec);
}

//==============================================================================
// ==== NEW: single-sample DX FM voice render ====
// This is Alpha-DX's renderVoice() body, adapted to write one sample of FM
// audio into `out` and share the subtractive voice's amp-envelope value so
// both engines fade out together on note-off.
void WASPAlphaAudioProcessor::renderDxVoice(WaspVoice& v, float& out, float ampEnv)
{
    auto& d = v.dx;

    // Bail if this DX voice is already silent. Matches Alpha-DX's guard.
    if (!d.active && d.env < 0.0003)
        return;

    // Carrier envelope decay + smoothing (Alpha-DX code).
    // d.cdec and d.catt are cached per-voice at note-on; the processor writes
    // updated values into the voice each block for live tracking.
    d.env *= d.cdec;
    d.cenv += d.catt * (d.env - d.cenv);

    // Recursive one-pole resonator — this is Alpha-DX's modulator oscillator.
    // Not a phase-accumulator sine; the two-pole recursion gives it a
    // slightly "dirty" analogue character that's part of the Alpha-DX sound.
    double x = d.dmod * d.mod0 - d.mod1;
    d.mod1 = d.mod0;
    d.mod0 = x;

    // Modulator envelope: simple one-pole approach toward mlev (sustain).
    d.menv += d.mdec * (d.mlev - d.menv);

    // Carrier phase update: phase increment + modulator displacement.
    // d.dcar is the carrier's base increment; x is the current modulator
    // output; d.menv scales how hard the modulator pushes.
    const double phase = d.carPhase + d.dcar + x * d.menv;

    // Wrap into the +-1 range that the Alpha-DX polynomial sine expects.
    double wrapped = phase;
    while (wrapped > 1.0) wrapped -= 2.0;
    while (wrapped < -1.0) wrapped += 2.0;
    d.carPhase = wrapped;

    // Alpha-DX's cubic-rich sine approximation. dxRich controls the amount
    // of 3rd-harmonic content baked into the carrier.
    const double p2 = wrapped * wrapped;
    const double p3 = p2 * wrapped;
    const float sine = static_cast<float>(wrapped + p3 * (dxRich * p2 - 1.0 - dxRich));

    // Mod-thru: leak the raw modulator into the output. This is what gives
    // FM patches their metallic edge (Alpha-DX's modmix).
    const float mix = sine + dxModMix * static_cast<float>(d.mod1);

    // Final contribution, scaled by the shared amp envelope.
    out += static_cast<float>(d.cenv * static_cast<double>(mix)) * ampEnv;

    // Mark the DX voice silent when its carrier envelope has decayed away.
    if (d.cenv < 0.0003 && !v.noteHeld)
        d.active = false;
}

//==============================================================================
int WASPAlphaAudioProcessor::findFreeVoice()
{
    // 1. Prefer a fully silent voice
    for (int i = 0; i < MAX_VOICES; ++i)
        if (!voices[i].isActive) return i;

    // 2. Steal the quietest voice that is in release (noteHeld == false)
    int    stealIdx = -1;
    double quietest = 1.0e9;
    for (int i = 0; i < MAX_VOICES; ++i)
    {
        if (!voices[i].noteHeld && voices[i].ampEnv.value < quietest)
        {
            quietest = voices[i].ampEnv.value;
            stealIdx = i;
        }
    }
    if (stealIdx >= 0) return stealIdx;

    // 3. Last resort: steal the quietest active voice regardless
    stealIdx = 0;
    quietest = voices[0].ampEnv.value;
    for (int i = 1; i < MAX_VOICES; ++i)
    {
        if (voices[i].ampEnv.value < quietest)
        {
            quietest = voices[i].ampEnv.value;
            stealIdx = i;
        }
    }
    return stealIdx;
}

int WASPAlphaAudioProcessor::findVoiceForNote(int midiNote)
{
    // Match on noteHeld so we can find voices still in release phase
    for (int i = 0; i < MAX_VOICES; ++i)
        if (voices[i].noteHeld && voices[i].midiNote == midiNote) return i;
    return -1;
}

void WASPAlphaAudioProcessor::handleMidiEvent(const juce::MidiMessage& msg)
{
    if (msg.isNoteOn())
    {
        int note = msg.getNoteNumber();
        double freq = juce::MidiMessage::getMidiNoteInHertz(note);

        // LFO delay always retriggers on a new note; phase only resets if RESET is engaged
        lfo1.resetDelay();
        lfo2.resetDelay();
        if (apvts.getRawParameterValue(WaspParams::LFO1_RESET)->load() > 0.5f)
            lfo1.reset();
        if (apvts.getRawParameterValue(WaspParams::LFO2_RESET)->load() > 0.5f)
            lfo2.reset();

        float vel = juce::jlimit(0.0f, 1.0f, msg.getFloatVelocity());
        int vi = findFreeVoice();
        voices[vi].noteOn(note, freq, vel);
        voices[vi].filter.reset();
        voices[vi].filter2.reset();
        voices[vi].chamberlinF.reset();
        voices[vi].chamberlinF2.reset();

        // ==== NEW: initialise the DX FM voice when the module is enabled ====
        // Only touches FM state when the module is on; otherwise the voice's
        // dx struct stays zeroed and renderDxVoice() is never called.
        if (apvts.getRawParameterValue(WaspParams::DXFM_ENABLE)->load() > 0.5f)
            initDxVoice(voices[vi], note, msg.getVelocity());
    }
    else if (msg.isNoteOff())
    {
        int vi = findVoiceForNote(msg.getNoteNumber());
        if (vi >= 0)
        {
            voices[vi].noteOff();
            // ==== NEW: DX FM release ====
            // The DX voice's own release is driven by the amp envelope it
            // shares with the subtractive voice, so on the DX side we just
            // swap the decay coefficient for the release coefficient. Both
            // envelopes then decay to zero together.
            auto& d = voices[vi].dx;
            if (d.active)
            {
                d.cdec = static_cast<double>(dxCrel);
                // Kill the modulator sustain so the FM side also fades.
                d.mlev = 0.0;
                d.mdec = static_cast<double>(dxMrel);
            }
        }
    }
    else if (msg.isAllNotesOff() || msg.isAllSoundOff())
    {
        for (auto& v : voices)
        {
            v.noteOff();
            v.isActive = false;
            v.noteHeld = false;
            // ==== NEW: clear DX state on all-notes-off too ====
            v.dx.reset();
        }
    }
    // ==== NEW: mod wheel (CC1) ====
    // Latched here for the DX FM vibrato path (and available to any future
    // subtractive vibrato path). Simply normalised to 0..1.
    else if (msg.isController() && msg.getControllerNumber() == 1)
    {
        modWheelValue = static_cast<float>(msg.getControllerValue()) / 127.0f;
    }
    // ==== NEW: pitch bend ====
    // Alpha-DX applied pitch bend directly to its carrier increments. Here we
    // store a multiplier that the subtractive and DX FM paths both reference.
    // Range: +-2 semitones (a common default; widen later if desired).
    else if (msg.isPitchWheel())
    {
        const float bend = (static_cast<float>(msg.getPitchWheelValue()) - 8192.0f) / 8192.0f; // -1..1
        pitchBendGlobal = static_cast<double>(std::pow(2.0f, bend * 2.0f / 12.0f));
    }
}

//==============================================================================
// Helper: midi note to Hz with semitone/cent offset
static double midiToHz(int note, int coarse, float fineCents)
{
    double totalCents = (double)(note + coarse) * 100.0 + (double)fineCents;
    return 440.0 * std::pow(2.0, (totalCents - 6900.0) / 1200.0);
}

// Soft clip (tanh approx) for Wasp character
static float softClip(float x, float drive)
{
    float driven = x * drive;
    // Fast tanh approximation
    float ax = std::abs(driven);
    float z = driven * (27.0f + ax * ax) / (27.0f + 9.0f * ax * ax);
    return z / drive;
}

// Hard digital clip — the blunter, more aggressive distortion character
// associated with late-90s software synths (TS-404 included), which
// favoured flat-out sample clamping over smooth analog-style saturation.
static float hardClip(float x, float drive)
{
    const float driven = x * drive;
    return juce::jlimit(-1.0f, 1.0f, driven) / drive;
}

// Dispatches a single filter stage to either the Moog-style ladder (existing
// WaspFilter) or the Chamberlin SVF, per the FLT_MODEL/FLT2_MODEL choice —
// keeps the routing switch below from having to duplicate this branch four times.
static float processFilterStage(int model, WaspFilter& ladder, ChamberlinFilter& cham,
    float in, float cutoff, float reso, int type, bool cmos)
{
    if (model == 1)
        return cham.process(in, cutoff, reso, type);
    return ladder.process(in, cutoff, reso, type, cmos);
}

//==============================================================================
void WASPAlphaAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    // Some hosts' plugin validation passes call processBlock before ever
    // calling prepareToPlay. distToneFilter has undefined behaviour if
    // .process() runs before .prepare() ever ran on it — bail out silently
    // (buffer.clear() above already ran, so output is just silence) rather
    // than touch anything that assumes prepareToPlay has happened.
    if (!isPrepared)
        return;

    // --- Collect all parameters once per block ---
    using namespace WaspParams;

    float pOsc1Shape = apvts.getRawParameterValue(OSC1_SHAPE)->load();
    float pOsc1Coarse = apvts.getRawParameterValue(OSC1_COARSE)->load();
    float pOsc1Fine = apvts.getRawParameterValue(OSC1_FINE)->load();
    float pOsc2Shape = apvts.getRawParameterValue(OSC2_SHAPE)->load();
    float pOsc2Coarse = apvts.getRawParameterValue(OSC2_COARSE)->load();
    float pOsc2Fine = apvts.getRawParameterValue(OSC2_FINE)->load();
    float pOsc3Shape = apvts.getRawParameterValue(OSC3_SHAPE)->load();
    float pOsc3Amt = apvts.getRawParameterValue(OSC3_AMOUNT)->load();
    float pOscMix = apvts.getRawParameterValue(OSC_MIX)->load();
    float pPW = apvts.getRawParameterValue(PULSE_WIDTH)->load();
    float pFM = apvts.getRawParameterValue(FM_AMOUNT)->load();
    float pRM = apvts.getRawParameterValue(RM_AMOUNT)->load();

    float pAmpA = apvts.getRawParameterValue(AMP_ATTACK)->load();
    float pAmpD = apvts.getRawParameterValue(AMP_DECAY)->load();
    float pAmpS = apvts.getRawParameterValue(AMP_SUSTAIN)->load();
    float pAmpR = apvts.getRawParameterValue(AMP_RELEASE)->load();
    float pFltA = apvts.getRawParameterValue(FLT_ATTACK)->load();
    float pFltD = apvts.getRawParameterValue(FLT_DECAY)->load();
    float pFltS = apvts.getRawParameterValue(FLT_SUSTAIN)->load();
    float pFltR = apvts.getRawParameterValue(FLT_RELEASE)->load();

    float pFltKT = apvts.getRawParameterValue(FLT_KEYTRACK)->load();
    float pFltType = apvts.getRawParameterValue(FLT_TYPE)->load();
    float pCutoff = apvts.getRawParameterValue(FLT_CUTOFF)->load();
    float pReso = apvts.getRawParameterValue(FLT_RESO)->load();
    float pFltEnv = apvts.getRawParameterValue(FLT_ENV_AMT)->load();

    float pFlt2KT = apvts.getRawParameterValue(FLT2_KEYTRACK)->load();
    float pFlt2Type = apvts.getRawParameterValue(FLT2_TYPE)->load();
    float pCutoff2 = apvts.getRawParameterValue(FLT2_CUTOFF)->load();
    float pReso2 = apvts.getRawParameterValue(FLT2_RESO)->load();
    float pFlt2Env = apvts.getRawParameterValue(FLT2_ENV_AMT)->load();
    int   pFltRoute = (int)apvts.getRawParameterValue(FLT_ROUTING)->load();
    float pFltParMix = apvts.getRawParameterValue(FLT_PARALLEL_MIX)->load();
    int   pFltModel = (int)apvts.getRawParameterValue(FLT_MODEL)->load();
    int   pFlt2Model = (int)apvts.getRawParameterValue(FLT2_MODEL)->load();

    float pDelayTimeMs = apvts.getRawParameterValue(DELAY_TIME_MS)->load();
    float pDelayFb = apvts.getRawParameterValue(DELAY_FEEDBACK)->load();
    float pDelayMix = apvts.getRawParameterValue(DELAY_MIX)->load();
    float pMasterVolDb = apvts.getRawParameterValue(MASTER_VOLUME)->load();
    float pMasterGain = juce::Decibels::decibelsToGain(pMasterVolDb, -60.0f);

    float pL1Shape = apvts.getRawParameterValue(LFO1_SHAPE)->load();
    float pL1Target = apvts.getRawParameterValue(LFO1_TARGET)->load();
    float pL1Amt = apvts.getRawParameterValue(LFO1_AMOUNT)->load();
    float pL1Freq = apvts.getRawParameterValue(LFO1_FREQ)->load();

    float pL2Shape = apvts.getRawParameterValue(LFO2_SHAPE)->load();
    float pL2Target = apvts.getRawParameterValue(LFO2_TARGET)->load();
    float pL2Amt = apvts.getRawParameterValue(LFO2_AMOUNT)->load();
    float pL2Freq = apvts.getRawParameterValue(LFO2_FREQ)->load();

    float pDistOn = apvts.getRawParameterValue(DIST_ON)->load();
    float pDistDrv = apvts.getRawParameterValue(DIST_DRIVE)->load();
    int   pDistType = (int)apvts.getRawParameterValue(DIST_TYPE)->load();
    float pDistTone = apvts.getRawParameterValue(DIST_TONE)->load();
    float pDistMix = apvts.getRawParameterValue(DIST_MIX)->load();
    float pDualV = apvts.getRawParameterValue(DUAL_VOICE)->load();
    float pWasp = apvts.getRawParameterValue(WASP_CHAR)->load();
    float pVCOBin = apvts.getRawParameterValue(VCO_BINARY)->load();
    bool  pCmos = apvts.getRawParameterValue(CMOS_FILTER)->load() > 0.5f;
    float pCVAmt = apvts.getRawParameterValue(CV_AMOUNT)->load();
    int   pCVTarget = (int)apvts.getRawParameterValue(CV_TARGET)->load();

    float pModEnvA = apvts.getRawParameterValue(MODENV_ATTACK)->load();
    float pModEnvD = apvts.getRawParameterValue(MODENV_DECAY)->load();
    float pModEnvAmt = apvts.getRawParameterValue(MODENV_AMOUNT)->load();
    int   pModEnvDest = (int)apvts.getRawParameterValue(MODENV_DEST)->load();

    float pVelAmp = apvts.getRawParameterValue(VEL_TO_AMP)->load();
    float pVelFlt = apvts.getRawParameterValue(VEL_TO_FILTER)->load();

    float pLfo1Delay = apvts.getRawParameterValue(LFO1_DELAY)->load();
    float pLfo2Delay = apvts.getRawParameterValue(LFO2_DELAY)->load();
    float pDualDetune = apvts.getRawParameterValue(DUAL_DETUNE)->load();

    // ==== NEW: read DX FM + CPU Saver state once per block ====
    const bool  dxOn = apvts.getRawParameterValue(DXFM_ENABLE)->load() > 0.5f;
    const float dxBlend = apvts.getRawParameterValue(DXFM_BLEND)->load();

    const bool bpFilter2 = apvts.getRawParameterValue(BYPASS_FILTER2)->load() > 0.5f;
    const bool bpDelay = apvts.getRawParameterValue(BYPASS_DELAY)->load() > 0.5f;
    const bool bpDist = apvts.getRawParameterValue(BYPASS_DIST)->load() > 0.5f;
    const bool bpLfo2 = apvts.getRawParameterValue(BYPASS_LFO2)->load() > 0.5f;
    const bool bpModEnv = apvts.getRawParameterValue(BYPASS_MODENV)->load() > 0.5f;
    const bool bpCv = apvts.getRawParameterValue(BYPASS_CV)->load() > 0.5f;
    const bool bpDualV = apvts.getRawParameterValue(BYPASS_DUALVOICE)->load() > 0.5f;
    const bool bpWaspChar = apvts.getRawParameterValue(BYPASS_WASPCHAR)->load() > 0.5f;
    const bool bpVcoBin = apvts.getRawParameterValue(BYPASS_VCOBIN)->load() > 0.5f;

    // Refresh DX FM coefficients once per block. Cheap, and it guarantees the
    // FM voice tracks knob moves in real time without needing a listener per
    // parameter. Guarded by dxOn so it costs nothing when the module is off.
    if (dxOn)
        updateDxParams();

    // Defensive channel-count guard. isBusesLayoutSupported only accepts an
    // exact stereo layout, so this should never trigger in normal use — but
    // some hosts' plugin validation passes probe processBlock with buffers
    // that don't match the negotiated layout before real audio settles in.
    // buffer.getWritePointer(1) below is an out-of-bounds write on anything
    // less than 2 channels; that's a real crash risk that was previously
    // masked by the prepareToPlay sample-rate bug crashing first — now that
    // that one's fixed, this is the next thing worth guarding defensively.
    if (buffer.getNumChannels() != 2)
        return; // buffer.clear() above already ran, so output stays silent rather than crashing

    float* left = buffer.getWritePointer(0);
    float* right = buffer.getWritePointer(1);
    int    numSamples = buffer.getNumSamples();

    // MIDI event iterator
    auto midiIt = midiMessages.begin();

    for (int sample = 0; sample < numSamples; ++sample)
    {
        // Process MIDI events scheduled up to this sample
        while (midiIt != midiMessages.end())
        {
            auto meta = *midiIt;
            if (meta.samplePosition > sample) break;
            handleMidiEvent(meta.getMessage());
            ++midiIt;
        }

        // Tick LFOs (delay gain fades the LFO in after its onset delay elapses)
        double lfo1Gain = lfo1.delayGain((double)pLfo1Delay);
        double lfo1Val = lfo1.tick((double)pL1Freq, (int)pL1Shape) * (double)pL1Amt * lfo1Gain;

        // ==== NEW: LFO2 tick skipped entirely when bypassed ====
        double lfo2Gain = 0.0;
        double lfo2Val = 0.0;
        if (!bpLfo2)
        {
            lfo2Gain = lfo2.delayGain((double)pLfo2Delay);
            lfo2Val = lfo2.tick((double)pL2Freq, (int)pL2Shape) * (double)pL2Amt * lfo2Gain;
        }

        float mixOut = 0.0f;
        int   activeCount = 0;

        for (auto& v : voices)
        {
            // Skip voices that are fully silent (neither active nor in release tail)
            if (!v.isActive) continue;

            // --- Frequencies ---
            double f1 = midiToHz(v.midiNote, (int)pOsc1Coarse, pOsc1Fine);
            double f2 = midiToHz(v.midiNote, (int)pOsc2Coarse, pOsc2Fine);

            // ==== NEW: Mod Env tick skipped entirely when bypassed ====
            double modEnvRaw = 0.0;
            double modEnvSig = 0.0;
            if (!bpModEnv)
            {
                modEnvRaw = v.modEnv.tick((double)pModEnvA, (double)pModEnvD);
                modEnvSig = modEnvRaw * (double)pModEnvAmt; // signed, -1..1 scaled by amount knob
            }

            // Per-voice local copies of the shared LFO values, so Mod Env can scale
            // "LFO1 AMT" independently for each currently-sounding voice.
            double lfo1ValLocal = lfo1Val;
            double lfo2ValLocal = lfo2Val;
            if (!bpModEnv && pModEnvDest == 1) // LFO1 Amount
                lfo1ValLocal *= juce::jlimit(0.0, 2.0, 1.0 + modEnvSig);

            // Osc2 Pitch mod-env destination (applied directly to f2 below alongside LFO pitch mod)
            if (!bpModEnv && pModEnvDest == 3)
                f2 *= std::pow(2.0, modEnvSig * 12.0 / 12.0);

            // LFO pitch modulation
            double pitchLfo1 = 0.0, pitchLfo2 = 0.0;
            if ((int)pL1Target == 0) { pitchLfo1 = lfo1ValLocal; }
            if ((int)pL1Target == 1) { f1 *= std::pow(2.0, lfo1ValLocal * 2.0 / 12.0); }
            if ((int)pL1Target == 2) { f2 *= std::pow(2.0, lfo1ValLocal * 2.0 / 12.0); }
            if (!bpLfo2)
            {
                if ((int)pL2Target == 0) { pitchLfo2 = lfo2ValLocal; }
                if ((int)pL2Target == 1) { f1 *= std::pow(2.0, lfo2ValLocal * 2.0 / 12.0); }
                if ((int)pL2Target == 2) { f2 *= std::pow(2.0, lfo2ValLocal * 2.0 / 12.0); }
            }

            f1 *= std::pow(2.0, (pitchLfo1 + pitchLfo2) * 2.0 / 12.0);
            f2 *= std::pow(2.0, (pitchLfo1 + pitchLfo2) * 2.0 / 12.0);

            // ==== NEW: pitch bend is now applied to the subtractive engine ====
            // Alpha-DX applied bend to its carrier; here we apply it to both
            // oscillators so the subtractive engine bends too. This was
            // missing entirely before.
            f1 *= pitchBendGlobal;
            f2 *= pitchBendGlobal;

            // VCO Binary: quantises pitch to binary-divider steps (4 steps per octave)
            if (!bpVcoBin && pVCOBin > 0.0f)
            {
                double stepsOctave = 4.0;
                auto quantize = [&](double freq)
                    {
                        double midiF = 12.0 * std::log2(freq / 440.0) + 69.0;
                        double step = std::round(midiF * stepsOctave / 12.0);
                        double qMidi = step * 12.0 / stepsOctave;
                        return 440.0 * std::pow(2.0, (qMidi - 69.0) / 12.0);
                    };
                double qf1 = quantize(f1);
                double qf2 = quantize(f2);
                f1 = f1 + pVCOBin * (qf1 - f1);
                f2 = f2 + pVCOBin * (qf2 - f2);
            }

            // PW modulation from LFO + Mod Env
            double pw = (double)pPW;
            if ((int)pL1Target == 3) pw = juce::jlimit(0.05, 0.95, pw + lfo1ValLocal * 0.4);
            if (!bpLfo2 && (int)pL2Target == 3) pw = juce::jlimit(0.05, 0.95, pw + lfo2ValLocal * 0.4);
            if (!bpModEnv && pModEnvDest == 0) pw = juce::jlimit(0.05, 0.95, pw + modEnvSig * 0.4);

            // --- Oscillators ---
            // FM: osc1 modulates osc2 frequency
            float osc1Raw = v.oscSample(v.osc1Phase, f1, (int)pOsc1Shape, pw);

            // ==== NEW: CV path skipped entirely when bypassed ====
            // CV: use Osc1 output as a control voltage into chosen destination.
            double cvSig = 0.0;
            double f2CV = f2;
            double pwCV = pw;
            double cvCutoffMult = 1.0;
            double cvAmpMod = 1.0;
            if (!bpCv && pCVAmt > 0.0f)
            {
                cvSig = (double)osc1Raw * (double)pCVAmt;
                switch (pCVTarget)
                {
                case 0: // Filter Cutoff — CV sweeps filter ±3 octaves
                    cvCutoffMult = std::pow(2.0, cvSig * 3.0);
                    break;
                case 1: // Osc2 Pitch — classic hard sync / FM alternative
                    f2CV *= std::pow(2.0, cvSig * 2.0 / 12.0);
                    break;
                case 2: // Pulse Width
                    pwCV = juce::jlimit(0.05, 0.95, pw + cvSig * 0.4);
                    break;
                case 3: // Amp — tremolo / AM from Osc1
                    cvAmpMod = juce::jlimit(0.0, 1.0, 0.5 + cvSig * 0.5);
                    break;
                default: break;
                }
            }

            // Mod Env -> Osc1 Level destination
            if (!bpModEnv && pModEnvDest == 2)
                osc1Raw *= (float)juce::jlimit(0.0, 1.0, 1.0 + modEnvSig);

            double fmMod = 1.0 + (double)pFM * (double)osc1Raw * 4.0;
            float osc2Raw = v.oscSample(v.osc2Phase, f2CV * fmMod, (int)pOsc2Shape, pwCV);

            // RM: ring mod of osc1 * osc2
            float rmSig = osc1Raw * osc2Raw;
            float osc12 = osc1Raw * (1.0f - pOscMix) + osc2Raw * pOscMix;
            osc12 = osc12 * (1.0f - pRM) + rmSig * pRM;

            // ==== NEW: Dual Voice skipped entirely when bypassed ====
            // Dual Voice: true unison — a second detuned oscillator pair, summed in,
            // replacing the old fake stereo-width hack. DUAL_VOICE (0..1) is the blend
            // of the detuned layer, DUAL_DETUNE (cents) is how far it's detuned.
            if (!bpDualV && pDualV > 0.0f)
            {
                double detuneMult = std::pow(2.0, (double)pDualDetune / 1200.0);
                float osc1B = v.oscSample(v.osc1PhaseB, f1 * detuneMult, (int)pOsc1Shape, pw);
                float osc2B = v.oscSample(v.osc2PhaseB, f2CV * detuneMult * fmMod, (int)pOsc2Shape, pwCV);
                float osc12B = osc1B * (1.0f - pOscMix) + osc2B * pOscMix;
                osc12 = osc12 * (1.0f - 0.5f * pDualV) + osc12B * (0.5f * pDualV);
            }

            // Osc3 (sub / noise)
            float osc3Raw = v.osc3Sample(v.osc3Phase, v.baseFreq, (int)pOsc3Shape);
            float osc3Mix = osc12 * (1.0f - pOsc3Amt) + osc3Raw * pOsc3Amt;

            // ==== NEW: Wasp character skipped entirely when bypassed ====
            // Wasp character: quantised CMOS-divider grit
            float waspSig = osc3Mix;
            if (!bpWaspChar && pWasp > 0.0f)
            {
                float quant = std::round(osc3Mix * 8.0f) / 8.0f;
                waspSig = osc3Mix * (1.0f - pWasp) + quant * pWasp;
            }

            // --- Filter ---
            double fltEnvVal = v.fltEnv.tick((double)pFltA, (double)pFltD, (double)pFltS, (double)pFltR);

            // Velocity -> Filter Envelope: at VEL_TO_FILTER = 0 velocity has no effect (env always
            // reaches full depth); at 1.0 the env's depth scales linearly with note-on velocity.
            // Same sqrt velocity curve as the amp envelope, for consistency.
            double fltVelScale = (1.0 - (double)pVelFlt) + (double)pVelFlt * std::sqrt((double)v.velocity);
            fltEnvVal *= fltVelScale;

            // Keytrack
            double baseNote = 60.0;
            double noteSemis = (double)v.midiNote - baseNote;
            double ktMult = std::pow(2.0, noteSemis * (double)pFltKT / 12.0);
            double cutoffFlt = (double)pCutoff * ktMult;

            // Envelope modulation: +/- 3 octaves
            double envMod = (double)pFltEnv * fltEnvVal;
            cutoffFlt *= std::pow(2.0, envMod * 3.0);

            // CV filter modulation
            cutoffFlt *= cvCutoffMult;

            // LFO filter mod
            if ((int)pL1Target == 4) cutoffFlt *= std::pow(2.0, lfo1ValLocal * 2.0);
            if (!bpLfo2 && (int)pL2Target == 4) cutoffFlt *= std::pow(2.0, lfo2ValLocal * 2.0);

            cutoffFlt = juce::jlimit(20.0, (currentSampleRate * 0.49), cutoffFlt);

            // ==== NEW: Filter 2 cutoff computed only when Filter 2 is used ====
            // Filter 2 cutoff (independent keytrack + knobs, same env/CV/LFO treatment).
            // Skipped when bpFilter2 is on, or when routing selects Filter-1-only,
            // since nothing downstream will read it.
            double cutoffFlt2 = 0.0;
            const bool needFlt2 = !bpFilter2 && (pFltRoute == 1 || pFltRoute == 2 || pFltRoute == 3);
            if (needFlt2)
            {
                double ktMult2 = std::pow(2.0, noteSemis * (double)pFlt2KT / 12.0);
                cutoffFlt2 = (double)pCutoff2 * ktMult2;
                double envMod2 = (double)pFlt2Env * fltEnvVal;
                cutoffFlt2 *= std::pow(2.0, envMod2 * 3.0);
                cutoffFlt2 *= cvCutoffMult;
                if ((int)pL1Target == 4) cutoffFlt2 *= std::pow(2.0, lfo1ValLocal * 2.0);
                if (!bpLfo2 && (int)pL2Target == 4) cutoffFlt2 *= std::pow(2.0, lfo2ValLocal * 2.0);
                cutoffFlt2 = juce::jlimit(20.0, (currentSampleRate * 0.49), cutoffFlt2);
            }

            // LFO -> Resonance (target index 6). Scaled at 0.5 so a full-depth
            // LFO sweeps roughly the whole 0..1 resonance range rather than
            // immediately pinning it — matches the scale used for cutoff/PW mods.
            float resoFlt = pReso;
            float resoFlt2 = pReso2;
            if ((int)pL1Target == 6) resoFlt = juce::jlimit(0.0f, 1.0f, resoFlt + (float)lfo1ValLocal * 0.5f);
            if (!bpLfo2 && (int)pL2Target == 6) resoFlt = juce::jlimit(0.0f, 1.0f, resoFlt + (float)lfo2ValLocal * 0.5f);
            if ((int)pL1Target == 6) resoFlt2 = juce::jlimit(0.0f, 1.0f, resoFlt2 + (float)lfo1ValLocal * 0.5f);
            if (!bpLfo2 && (int)pL2Target == 6) resoFlt2 = juce::jlimit(0.0f, 1.0f, resoFlt2 + (float)lfo2ValLocal * 0.5f);

            // ==== NEW: if Filter 2 is bypassed, force routing to Filter-1-only ====
            const int effectiveRoute = bpFilter2 ? 0 : pFltRoute;

            // Call filter(s), dispatching each stage to Ladder or Chamberlin per
            // FLT_MODEL/FLT2_MODEL. FLT_ROUTING: 0=Filter1 only, 1=Filter2 only,
            // 2=Series (1->2), 3=Parallel (blended)
            float filtered;
            switch (effectiveRoute)
            {
            case 1: // Filter 2 only
                filtered = processFilterStage(pFlt2Model, v.filter2, v.chamberlinF2,
                    waspSig, (float)cutoffFlt2, resoFlt2, (int)pFlt2Type, pCmos);
                break;
            case 2: // Series: Filter 1 into Filter 2
            {
                float stage1 = processFilterStage(pFltModel, v.filter, v.chamberlinF,
                    waspSig, (float)cutoffFlt, resoFlt, (int)pFltType, pCmos);
                filtered = processFilterStage(pFlt2Model, v.filter2, v.chamberlinF2,
                    stage1, (float)cutoffFlt2, resoFlt2, (int)pFlt2Type, pCmos);
                break;
            }
            case 3: // Parallel: both filters fed the same dry signal, blended
            {
                float stage1 = processFilterStage(pFltModel, v.filter, v.chamberlinF,
                    waspSig, (float)cutoffFlt, resoFlt, (int)pFltType, pCmos);
                float stage2 = processFilterStage(pFlt2Model, v.filter2, v.chamberlinF2,
                    waspSig, (float)cutoffFlt2, resoFlt2, (int)pFlt2Type, pCmos);
                filtered = stage1 * (1.0f - pFltParMix) + stage2 * pFltParMix;
                break;
            }
            default: // Filter 1 only
                filtered = processFilterStage(pFltModel, v.filter, v.chamberlinF,
                    waspSig, (float)cutoffFlt, resoFlt, (int)pFltType, pCmos);
                break;
            }

            // --- Amp Envelope ---
            double ampEnvVal = v.ampEnv.tick((double)pAmpA, (double)pAmpD, (double)pAmpS, (double)pAmpR);

            // Velocity -> Amp Envelope depth. Uses a square-root curve rather than
            // linear: linear velocity meant a mid-strength hit (vel ~64/127) cut
            // amplitude by exactly -6dB with no shaping at all, which read as
            // "too sensitive"/"gets quiet fast". sqrt(velocity) keeps quiet hits
            // quiet but brings mid-to-high velocities up to a more usable level —
            // vel 64/127 now lands around -3dB instead of -6dB.
            double velocityCurved = std::sqrt((double)v.velocity);
            double ampVelScale = (1.0 - (double)pVelAmp) + (double)pVelAmp * velocityCurved;
            ampEnvVal *= ampVelScale;

            // LFO + CV amp mod
            double ampMod = cvAmpMod;
            if ((int)pL1Target == 5) ampMod *= juce::jlimit(0.0, 1.0, 1.0 + lfo1ValLocal);
            if (!bpLfo2 && (int)pL2Target == 5) ampMod *= juce::jlimit(0.0, 1.0, 1.0 + lfo2ValLocal);

            float voiceSig = filtered * (float)(ampEnvVal * ampMod);

            // ==== NEW: DX FM contribution ====
            // Only rendered when the module is enabled. Writes into dxOut and
            // is mixed below. Skipping the entire render call when disabled
            // is the main CPU saving of the module.
            float dxOut = 0.0f;
            if (dxOn)
            {
                renderDxVoice(v, dxOut, (float)ampEnvVal);
            }

            // Sum the two engines per the blend parameter. When blend is 0,
            // dxOut is scaled to nothing and the subtractive path runs alone;
            // when blend is 1, dxOut is the whole voice. When blend is in
            // between, both engines sound together with a taper on the
            // subtractive side so total energy stays reasonable.
            if (dxOn && dxBlend > 0.0f)
            {
                voiceSig *= (1.0f - 0.5f * dxBlend);
                voiceSig += dxOut * dxBlend;
            }

            mixOut += voiceSig;
            ++activeCount;

            // Update isActive AFTER rendering this sample so the final release
            // sample is never dropped (this was the original note-off bug root cause)
            if (v.ampEnv.isActive() == false)
                v.isActive = false;
        }

        // Voice mix headroom. This used to divide by activeCount, which meant a
        // single held note played at full volume but adding a second held note
        // instantly cut BOTH by -6dB, a third cut further, etc — notes changing
        // loudness just because other notes were added/released is the "gets
        // quiet fast" behaviour that was reported. A fixed per-voice gain keeps
        // a single note's level constant regardless of polyphony; the tanh soft
        // limiter after Master Volume (below) catches the rare case where many
        // voices + high resonance stack up and would otherwise clip.
        constexpr float kVoiceGain = 0.5f;
        mixOut *= kVoiceGain;
        juce::ignoreUnused(activeCount);

        // Voice synthesis writes the clean, undistorted signal here. Distortion,
        // Delay, Master Volume, and the safety limiter are now separate passes
        // below (in that order) rather than interleaved in this loop — needed
        // so Distortion can have a proper dry/wet blend, and so its Tone
        // filtering happens where it belongs in the chain (right after the
        // waveshaper, not tacked on after Master Volume/the limiter like before).
        float lSig = mixOut;
        float rSig = mixOut;

        left[sample] = lSig;
        right[sample] = rSig;
    }

    // ==== NEW: Distortion stage skipped entirely when bypassed ====
    // --- Distortion (waveshaper + Tone filter, as one dry/wet-blended stage) ---
    if (!bpDist && pDistOn > 0.5f)
    {
        // Real-time-safe: resize-if-needed only touches the vector when it's
        // actually too small (never true in the normal case, since
        // prepareToPlay already sized these to samplesPerBlock).
        if ((int)distDryL.size() < numSamples) distDryL.resize((size_t)numSamples);
        if ((int)distDryR.size() < numSamples) distDryR.resize((size_t)numSamples);

        for (int i = 0; i < numSamples; ++i)
        {
            distDryL[(size_t)i] = left[i];
            distDryR[(size_t)i] = right[i];
            if (pDistType == 1)
            {
                left[i] = hardClip(left[i], pDistDrv);
                right[i] = hardClip(right[i], pDistDrv);
            }
            else
            {
                left[i] = softClip(left[i], pDistDrv);
                right[i] = softClip(right[i], pDistDrv);
            }
        }

        // Only recompute coefficients (which heap-allocate internally via
        // makeFirstOrderHighPass) when the Tone knob has actually moved —
        // doing this unconditionally every block is a real-time-safety
        // issue (allocation on the audio thread) even though it's not
        // itself a crash under normal desktop conditions.
        if (!juce::approximatelyEqual(pDistTone, lastDistTone))
        {
            lastDistTone = pDistTone;
            *distToneFilter.state = *juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(
                currentSampleRate, pDistTone);
        }

        juce::dsp::AudioBlock<float>       block(buffer);
        juce::dsp::ProcessContextReplacing<float> ctx(block);
        distToneFilter.process(ctx);

        // Dry/wet blend — this is the fix for "only the delta gets through":
        // at Mix < 1.0, the Tone highpass (which can remove nearly all the
        // bass/fundamental at high Tone settings) no longer removes it from
        // the WHOLE signal, only from the wet portion; the dry portion keeps
        // the full-spectrum fundamental intact.
        for (int i = 0; i < numSamples; ++i)
        {
            left[i] = distDryL[(size_t)i] * (1.0f - pDistMix) + left[i] * pDistMix;
            right[i] = distDryR[(size_t)i] * (1.0f - pDistMix) + right[i] * pDistMix;
        }
    }

    // ==== NEW: Delay stage skipped entirely when bypassed ====
    // --- Delay (single-tap feedback, opt-in via mix — 0 by default) ---
    if (!bpDelay && pDelayMix > 0.0001f)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            left[i] = delayL.process(left[i], pDelayTimeMs / 1000.0f, pDelayFb, pDelayMix);
            right[i] = delayR.process(right[i], pDelayTimeMs / 1000.0f, pDelayFb, pDelayMix);
        }
    }

    // --- Master Volume + safety soft limiter ---
    // tanh is near-linear (and so inaudible) for normal signal levels, and only
    // engages as levels approach/exceed 0dBFS — a safety net for when several
    // voices, high resonance, and/or delay feedback stack up, rather than a
    // tone-shaping effect. Threshold chosen so typical single-note playing at
    // Master Volume = 0dB never touches it.
    constexpr float kLimiterThreshold = 1.6f;
    for (int i = 0; i < numSamples; ++i)
    {
        left[i] = std::tanh((left[i] * pMasterGain) / kLimiterThreshold) * kLimiterThreshold;
        right[i] = std::tanh((right[i] * pMasterGain) / kLimiterThreshold) * kLimiterThreshold;
    }
}

//==============================================================================
juce::AudioProcessorEditor* WASPAlphaAudioProcessor::createEditor()
{
    return new WASPAlphaAudioProcessorEditor(*this);
}

//==============================================================================
void WASPAlphaAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void WASPAlphaAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr && xml->hasTagName(apvts.state.getType()))
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WASPAlphaAudioProcessor();
}