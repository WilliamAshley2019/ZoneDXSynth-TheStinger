#pragma once
#include <JuceHeader.h>
#include "PresetManager.h"

//==============================================================================
// The Stinger — A tribute to Synths since 1978
// AlphaAudio by William Ashley Music
//
//==============================================================================

//==============================================================================
// APVTS Parameter IDs
//==============================================================================
namespace WaspParams
{
    // Oscillator 1
    static constexpr const char* OSC1_SHAPE = "osc1_shape";
    static constexpr const char* OSC1_COARSE = "osc1_coarse";
    static constexpr const char* OSC1_FINE = "osc1_fine";

    // Oscillator 2
    static constexpr const char* OSC2_SHAPE = "osc2_shape";
    static constexpr const char* OSC2_COARSE = "osc2_coarse";
    static constexpr const char* OSC2_FINE = "osc2_fine";

    // Oscillator 3 (Sub / Noise osc)
    static constexpr const char* OSC3_SHAPE = "osc3_shape";
    static constexpr const char* OSC3_AMOUNT = "osc3_amount";

    // Mix / Modulation
    static constexpr const char* OSC_MIX = "osc_mix";
    static constexpr const char* PULSE_WIDTH = "pulse_width";
    static constexpr const char* FM_AMOUNT = "fm_amount";
    static constexpr const char* RM_AMOUNT = "rm_amount";

    // Amp Envelope
    static constexpr const char* AMP_ATTACK = "amp_attack";
    static constexpr const char* AMP_DECAY = "amp_decay";
    static constexpr const char* AMP_SUSTAIN = "amp_sustain";
    static constexpr const char* AMP_RELEASE = "amp_release";

    // Filter Envelope
    static constexpr const char* FLT_ATTACK = "flt_attack";
    static constexpr const char* FLT_DECAY = "flt_decay";
    static constexpr const char* FLT_SUSTAIN = "flt_sustain";
    static constexpr const char* FLT_RELEASE = "flt_release";

    // Filter
    static constexpr const char* FLT_KEYTRACK = "flt_keytrack";
    static constexpr const char* FLT_TYPE = "flt_type";
    static constexpr const char* FLT_CUTOFF = "flt_cutoff";
    static constexpr const char* FLT_RESO = "flt_reso";
    static constexpr const char* FLT_ENV_AMT = "flt_env_amt";

    // Filter 2 (dual multimode resonant filter — Stinger addition)
    static constexpr const char* FLT2_KEYTRACK = "flt2_keytrack";
    static constexpr const char* FLT2_TYPE = "flt2_type";
    static constexpr const char* FLT2_CUTOFF = "flt2_cutoff";
    static constexpr const char* FLT2_RESO = "flt2_reso";
    static constexpr const char* FLT2_ENV_AMT = "flt2_env_amt";
    static constexpr const char* FLT_ROUTING = "flt_routing";     // 0=F1 only,1=F2 only,2=Series,3=Parallel
    static constexpr const char* FLT_PARALLEL_MIX = "flt_parallel_mix"; // blend for Parallel routing

    // Filter model: Ladder (existing Moog-style WaspFilter) vs Chamberlin SVF
    // (TS-404/303-style acid character — self-oscillates more aggressively).
    // Independent per filter so e.g. Filter 1 can be Chamberlin while Filter 2
    // stays Ladder for series/parallel routing.
    static constexpr const char* FLT_MODEL = "flt_model";  // 0=Ladder, 1=Chamberlin
    static constexpr const char* FLT2_MODEL = "flt2_model"; // 0=Ladder, 1=Chamberlin

    // LFO 1
    static constexpr const char* LFO1_SHAPE = "lfo1_shape";
    static constexpr const char* LFO1_TARGET = "lfo1_target";
    static constexpr const char* LFO1_AMOUNT = "lfo1_amount";
    static constexpr const char* LFO1_FREQ = "lfo1_freq";
    static constexpr const char* LFO1_SYNC = "lfo1_sync";
    static constexpr const char* LFO1_RESET = "lfo1_reset";

    // LFO 2
    static constexpr const char* LFO2_SHAPE = "lfo2_shape";
    static constexpr const char* LFO2_TARGET = "lfo2_target";
    static constexpr const char* LFO2_AMOUNT = "lfo2_amount";
    static constexpr const char* LFO2_FREQ = "lfo2_freq";
    static constexpr const char* LFO2_SYNC = "lfo2_sync";
    static constexpr const char* LFO2_RESET = "lfo2_reset";

    // FX / Character
    static constexpr const char* DIST_ON = "dist_on";
    static constexpr const char* DIST_DRIVE = "dist_drive";
    static constexpr const char* DIST_TONE = "dist_tone";
    static constexpr const char* DIST_MIX = "dist_mix"; // dry/wet — was missing entirely
    static constexpr const char* DIST_TYPE = "dist_type"; // 0=Soft (existing curve), 1=Hard (TS-404 style)
    static constexpr const char* DUAL_VOICE = "dual_voice";
    static constexpr const char* WASP_CHAR = "wasp_char";   // "Wasp" character mode
    static constexpr const char* VCO_BINARY = "vco_binary";  // Binary divider ladder

    // Delay (Stinger addition — simple single-tap feedback delay)
    static constexpr const char* DELAY_TIME_MS = "delay_time_ms";
    static constexpr const char* DELAY_FEEDBACK = "delay_feedback";
    static constexpr const char* DELAY_MIX = "delay_mix";

    // Master output volume, in dB — was previously missing entirely, meaning there
    // was no way to compensate for the polyphony/velocity gain-staging issues fixed
    // in this pass. -60..+6 dB, unity (0 dB) default.
    static constexpr const char* MASTER_VOLUME = "master_volume";
    // CMOS filter emulation + CV
    static constexpr const char* CMOS_FILTER = "cmos_filter"; // toggle CMOS vs Moog-style
    static constexpr const char* CV_AMOUNT = "cv_amount";   // Control Voltage depth
    static constexpr const char* CV_TARGET = "cv_target";   // CV destination

    // Mod Env — one-shot AD generator (EDP WASP "MOD ENV" section)
    static constexpr const char* MODENV_ATTACK = "modenv_attack";
    static constexpr const char* MODENV_DECAY = "modenv_decay";
    static constexpr const char* MODENV_AMOUNT = "modenv_amount";
    static constexpr const char* MODENV_DEST = "modenv_dest"; // PW / LFO1 AMT / OSC1 LEVEL / OSC2 PITCH

    // Velocity — depth of note velocity into Amp Env and Filter Env  
    static constexpr const char* VEL_TO_AMP = "vel_to_amp";
    static constexpr const char* VEL_TO_FILTER = "vel_to_filter";

    // LFO delay (onset delay before the LFO starts affecting its target)  
    static constexpr const char* LFO1_DELAY = "lfo1_delay";
    static constexpr const char* LFO2_DELAY = "lfo2_delay";

    // True unison detune amount for Dual Voice (replaces the old fake stereo-width hack)
    static constexpr const char* DUAL_DETUNE = "dual_detune";

    // ============================================================================
    // ==== DX FM module (Alpha-DX compatibility layer) ====
    // A self-contained 2-op FM voice engine that runs in parallel with the
    // subtractive engine. When DXFM_ENABLE is off, the entire module is
    // skipped in processBlock — no cycles burned, no audio touched.
    // ============================================================================

    // Master on/off for the whole DX FM module. When false, the FM voice
    // state is never initialised at note-on and never ticked in processBlock.
    static constexpr const char* DXFM_ENABLE = "dxfm_enable";

    // Output blend: 0.0 = pure subtractive engine, 1.0 = pure DX FM engine.
    // Anything in between sums both engines (with a taper on the subtractive
    // side so total energy stays reasonable as the blend rises).
    static constexpr const char* DXFM_BLEND = "dxfm_blend";

    // --- Carrier envelope (Alpha-DX "carrier" ADSR: had no sustain knob) ---
    static constexpr const char* DXFM_CAR_ATK = "dxfm_car_atk";
    static constexpr const char* DXFM_CAR_DEC = "dxfm_car_dec";
    static constexpr const char* DXFM_CAR_REL = "dxfm_car_rel";

    // Alpha-DX "rich" term — biases the carrier's polynomial sine toward
    // brighter (lower values) or purer (higher values) timbres.
    static constexpr const char* DXFM_WAVE = "dxfm_wave";

    // --- Modulator envelope (Alpha-DX "modulator" ADSR: init/decay/sus/rel) ---
    static constexpr const char* DXFM_MOD_INIT = "dxfm_mod_init";   // peak depth (INI)
    static constexpr const char* DXFM_MOD_DEC = "dxfm_mod_dec";    // decay rate
    static constexpr const char* DXFM_MOD_SUS = "dxfm_mod_sus";    // sustain level
    static constexpr const char* DXFM_MOD_REL = "dxfm_mod_rel";    // release rate
    static constexpr const char* DXFM_MOD_VEL = "dxfm_mod_vel";    // velocity -> depth scaling

    // --- Modulator : carrier frequency ratio ---
    // Coarse: integer 0..40, squared curve (Alpha-DX "cr")
    // Fine:   fractional {0.2, 0.25, 1/3, 1/2, 2/3, 3/4}, lookup table (Alpha-DX "fr")
    static constexpr const char* DXFM_COARSE = "dxfm_coarse";
    static constexpr const char* DXFM_FINE = "dxfm_fine";

    // --- Mod-thru: dry modulator signal mixed into output (Alpha-DX "modmix") ---
    static constexpr const char* DXFM_MOD_THRU = "dxfm_mod_thru";

    // --- Pitch ---
    static constexpr const char* DXFM_OCTAVE = "dxfm_octave";     // octave shift, 0..1 maps -2..+5
    static constexpr const char* DXFM_TUNE = "dxfm_tune";       // fine tune, 0..1 maps -1..+1 semitone

    // ============================================================================
    // ==== CPU Saver bypass toggles ====
    // Each toggle, when ON (true), skips its section's runtime work entirely.
    // When OFF (false, default), the section behaves exactly as before — so
    // existing patches are unchanged on load.
    // ============================================================================
    static constexpr const char* BYPASS_FILTER2 = "bypass_filter2";   // skip Filter 2 + routing
    static constexpr const char* BYPASS_DELAY = "bypass_delay";     // skip delay line
    static constexpr const char* BYPASS_DIST = "bypass_dist";      // skip distortion + tone
    static constexpr const char* BYPASS_LFO2 = "bypass_lfo2";      // skip LFO2 tick + all its routing
    static constexpr const char* BYPASS_MODENV = "bypass_modenv";    // skip Mod Env tick + all its routing
    static constexpr const char* BYPASS_CV = "bypass_cv";        // skip CV path (Osc1 -> dest)
    static constexpr const char* BYPASS_DUALVOICE = "bypass_dualvoice"; // skip second detuned osc pair
    static constexpr const char* BYPASS_WASPCHAR = "bypass_waspchar";  // skip Wasp quantisation
    static constexpr const char* BYPASS_VCOBIN = "bypass_vcobin";    // skip VCO Binary quantisation
}

//==============================================================================
// Simple Moog-style ladder filter (4-pole / 2-pole selectable)
struct WaspFilter
{
    double s[4] = { 0.0, 0.0, 0.0, 0.0 };
    double sampleRate = 44100.0;

    void reset() { for (auto& x : s) x = 0.0; }

    void setSampleRate(double sr) { sampleRate = sr; }

    // type: 0=LP12, 1=LP24, 2=HP12, 3=BP12
    // cmosMode: emulates CMOS transmission-gate filter (harder clipping, less resonance swell)
    float process(float input, float cutoffHz, float resonance, int type, bool cmosMode = false)
    {
        double f = 2.0 * juce::MathConstants<double>::pi * (double)cutoffHz / sampleRate;
        f = juce::jlimit(0.001, 0.499, f);
        double k = (double)resonance * 3.99;
        double t1 = f * 0.9892;  // original Moog-style integrator coefficient
        double x = (double)input - k * s[3];

        double y0, y1, y2, y3;

        if (cmosMode)
        {
            // CMOS transmission-gate model:
            // Each stage clips softly (CMOS switches have hard Vdd/Vss rails),
            // and the resonance feedback is attenuated (CMOS filters self-limit
            // rather than oscillating cleanly at high Q).
            // We model this as: tanh-saturated integrators + reduced feedback.
            double kCmos = (double)resonance * 1.8;  // CMOS resonance caps at ~1.8 before self-limit
            double xC = (double)input - kCmos * s[3];
            // Hard-rail soft-clip to ±1 (CMOS Vdd/Vss behaviour)
            auto cmosClip = [](double v) -> double {
                return v / (1.0 + std::abs(v));  // fast soft clip mimicking transmission gate limiting
                };
            y0 = cmosClip(s[0] + t1 * (xC - s[0]));
            y1 = cmosClip(s[1] + t1 * (y0 - s[1]));
            y2 = cmosClip(s[2] + t1 * (y1 - s[2]));
            y3 = cmosClip(s[3] + t1 * (y2 - s[3]));
        }
        else
        {
            // Original Moog-style linear ladder
            y0 = x * t1 + s[0] * (1.0 - t1);
            y1 = y0 * t1 + s[1] * (1.0 - t1);
            y2 = y1 * t1 + s[2] * (1.0 - t1);
            y3 = y2 * t1 + s[3] * (1.0 - t1);
        }

        s[0] = y0;  s[1] = y1;  s[2] = y2;  s[3] = y3;

        float out;
        switch (type)
        {
        case 1: out = (float)y3;          break; // LP24
        case 2: out = (float)(x - y2);     break; // HP12
        case 3: out = (float)(y1 - y3);    break; // BP12
        default: out = (float)y1;          break; // LP12
        }

        if (cmosMode)
        {
            // Makeup gain: cmosClip's v/(1+|v|) shape compresses toward ±1 at
            // every one of the 4 cascaded stages, so CMOS mode reads noticeably
            // quieter than the linear ladder at the same knob settings even
            // though nothing about the musical setting changed — a genuine
            // loudness mismatch between the two modes, not a stylistic
            // difference. This constant is an approximate compensation (not
            // measured/calibrated against a reference) — treat it as a
            // starting point to tune further by ear against non-CMOS mode.
            constexpr float kCmosMakeupGain = 1.4f;
            out *= kCmosMakeupGain;
        }

        return out;
    }
};

//==============================================================================
// Chamberlin state-variable filter (Hal Chamberlin, "Musical Applications of
// Microprocessors", 1980) — the filter topology behind the TB-303's acid
// squelch and widely used in late-90s software synths (TS-404 included) for
// its more aggressive self-oscillation compared to a Moog-style ladder.
// Single 12dB/octave stage; unlike WaspFilter this has no built-in 24dB mode. 
// This is still buggy at some configurations need to bug test more
struct ChamberlinFilter
{
    double low = 0.0, band = 0.0;
    double sampleRate = 44100.0;

    void reset() { low = band = 0.0; }
    void setSampleRate(double sr) { sampleRate = sr; }

    // type: 0=LP12, 1=HP12, 2=BP12 (matches the first three WaspFilter type
    // indices loosely; LP24's extra pole has no Chamberlin equivalent here,
    // so a model switch to Chamberlin while FLT_TYPE is set to LP24 just
    // falls back to this filter's LP output).
    float process(float input, float cutoffHz, float resonance, int type)
    {
        // The classic 1990s tuning coefficient approximation for this
        // topology — stable well below Nyquist, which is why cutoff is
        // clamped to a conservative fraction of sampleRate here rather than
        // the tighter 0.49 WaspFilter uses (Chamberlin tends to misbehave
        // closer to Nyquist than the ladder does).
        const double f = 2.0 * std::sin(juce::MathConstants<double>::pi *
            juce::jlimit(0.001, 0.45, (double)cutoffHz / sampleRate));

        // Damping: reso=0 -> heavily damped (q=2.0), reso=1 -> near-self-oscillating.
        double q = 2.0 * (1.0 - (double)juce::jlimit(0.0f, 1.0f, resonance));
        if (q < 0.05) q = 0.05; // hard floor — prevents the feedback term exploding

        const double high = (double)input - low - q * band;
        band += f * high;
        low += f * band;

        switch (type)
        {
        case 1: return (float)high; // HP12
        case 2: return (float)band; // BP12
        default: return (float)low; // LP12 (also covers LP24 — see note above)
        }
    }
};

//==============================================================================
// Simple ADSR
struct WaspEnv
{
    enum class Stage { Idle, Attack, Decay, Sustain, Release };
    Stage stage = Stage::Idle;
    double value = 0.0;
    double sampleRate = 44100.0;

    void setSampleRate(double sr) { sampleRate = sr; }
    void noteOn() { stage = Stage::Attack; }
    void noteOff() { if (stage != Stage::Idle) stage = Stage::Release; }
    bool isActive() const { return stage != Stage::Idle; }

    double tick(double attack, double decay, double sustain, double release)
    {
        // Times in seconds
        switch (stage)
        {
        case Stage::Attack:
            value += 1.0 / (attack * sampleRate + 1.0);
            if (value >= 1.0) { value = 1.0; stage = Stage::Decay; }
            break;
        case Stage::Decay:
            value -= (1.0 - sustain) / (decay * sampleRate + 1.0);
            if (value <= sustain) { value = sustain; stage = Stage::Sustain; }
            break;
        case Stage::Sustain:
            value = sustain;
            break;
        case Stage::Release:
            value -= value / (release * sampleRate + 1.0);
            if (value < 0.0001) { value = 0.0; stage = Stage::Idle; }
            break;
        default: value = 0.0; break;
        }
        return value;
    }
};

//==============================================================================
// One-shot AD "Mod Env" — aims for EDP WASP MOD ENV section: rises over
// Attack, falls over Decay, then sits at 0 (does NOT sustain or loop).
// Retriggered on every note-on.
struct WaspModEnv
{
    enum class Stage { Idle, Attack, Decay };
    Stage  stage = Stage::Idle;
    double value = 0.0;
    double sampleRate = 44100.0;

    void setSampleRate(double sr) { sampleRate = sr; }
    void noteOn() { stage = Stage::Attack; value = 0.0; }

    double tick(double attack, double decay)
    {
        switch (stage)
        {
        case Stage::Attack:
            value += 1.0 / (attack * sampleRate + 1.0);
            if (value >= 1.0) { value = 1.0; stage = Stage::Decay; }
            break;
        case Stage::Decay:
            value -= 1.0 / (decay * sampleRate + 1.0);
            if (value <= 0.0) { value = 0.0; stage = Stage::Idle; }
            break;
        default:
            value = 0.0;
            break;
        }
        return value;
    }
};

//==============================================================================
// Simple single-tap feedback delay (mono line, used once per output channel).
// Time is free-running (ms) — not tempo-synced yet, that's a natural next step
// once this basic version is confirmed working.
struct SimpleDelay
{
    std::vector<float> buffer;
    int    writePos = 0;
    double sampleRate = 44100.0;

    void prepare(double sr, double maxSeconds = 2.5)
    {
        // Defensive clamp: some hosts (including FL Studio's own plugin
        // scan/validation pass) call prepareToPlay with a placeholder sample
        // rate — 0, negative, or otherwise abnormal — before real audio is
        // ever selected. Casting an out-of-range double straight to size_t
        // below is undefined behaviour and can produce an astronomical
        // allocation size, which throws/hangs and takes the whole host down
        // with no crash report. Clamp to a sane audio range first.
        sr = juce::jlimit(8000.0, 384000.0, sr);
        sampleRate = sr;
        size_t numSamples = (size_t)juce::jmax(4.0, sr * maxSeconds) + 4;
        buffer.assign(numSamples, 0.0f);
        writePos = 0;
    }

    void reset()
    {
        std::fill(buffer.begin(), buffer.end(), 0.0f);
        writePos = 0;
    }

    // feedback is pre-clamped by the caller to keep the line stable (<= 0.95)
    float process(float in, float delaySeconds, float feedback, float mix)
    {
        if (buffer.empty()) return in;

        int delaySamples = (int)juce::jlimit(1.0, (double)buffer.size() - 2.0, delaySeconds * sampleRate);
        int readPos = writePos - delaySamples;
        if (readPos < 0) readPos += (int)buffer.size();

        float delayed = buffer[(size_t)readPos];
        buffer[(size_t)writePos] = in + delayed * feedback;

        writePos = (writePos + 1) % (int)buffer.size();

        return in * (1.0f - mix) + delayed * mix;
    }
};

//==============================================================================
// LFO
struct WaspLfo
{
    double phase = 0.0;
    double sampleRate = 44100.0;
    double holdValue = 0.0;  // for S&H
    double delayTimer = 0.0; // seconds elapsed since last reset, for onset delay

    void setSampleRate(double sr) { sampleRate = sr; }
    void reset() { phase = 0.0; delayTimer = 0.0; }
    void resetDelay() { delayTimer = 0.0; } // delay retriggers every note regardless of the RESET (phase) toggle

    // Returns the delay envelope (0 while waiting, ramps 0->1 over ~10ms once past delayTime,
    // to avoid a click when the LFO output snaps in)
    double delayGain(double delayTimeSeconds)
    {
        if (sampleRate <= 0.0) return 1.0; // guard against divide-by-zero if ticked before setSampleRate
        delayTimer += 1.0 / sampleRate;
        if (delayTimeSeconds <= 0.0) return 1.0;
        double past = delayTimer - delayTimeSeconds;
        if (past <= 0.0) return 0.0;
        return juce::jlimit(0.0, 1.0, past * sampleRate / 480.0); // ~10ms fade-in
    }

    double tick(double freqHz, int shape)
    {
        double out = 0.0;
        switch (shape)
        {
        case 0: out = std::sin(phase * juce::MathConstants<double>::twoPi); break;  // Sine
        case 1: out = (phase < 0.5) ? (phase * 4.0 - 1.0) : (3.0 - phase * 4.0); break; // Triangle
        case 2: out = 1.0 - 2.0 * phase; break;       // Saw
        case 3: out = 2.0 * phase - 1.0; break;       // RevSaw
        case 4: out = (phase < 0.5) ? 1.0 : -1.0; break; // Square
        case 5: // S&H — resample on every phase reset
        {
            // Capture old phase before advance, detect wrap
            double oldPhase = phase;
            double inc = freqHz / sampleRate;
            double newPhase = oldPhase + inc;
            if (newPhase >= 1.0 || oldPhase == 0.0)  // wrapped or freshly reset
                holdValue = (double)juce::Random::getSystemRandom().nextFloat() * 2.0 - 1.0;
            out = holdValue;
            // Advance phase manually here; skip the common advance below
            phase = newPhase >= 1.0 ? newPhase - 1.0 : newPhase;
            return out;
        }
        default: break;
        }
        phase += freqHz / sampleRate;
        if (phase >= 1.0) phase -= 1.0;
        return out;
    }
};

//==============================================================================
// DX FM voice state (per-voice)
// Holds the modulator + carrier state for the Alpha-DX-style FM layer.
// Reset to zero whenever the voice is stolen or the module is disabled, so
// no stale state ever leaks between notes or between enable/disable cycles.
struct DxVoiceState
{
    double carPhase = 0.0;   // carrier phase, unipolar +-1 range
    double modPhase = 0.0;   // modulator phase (kept for parity, unused in FM math)

    // Recursive one-pole resonator state (Alpha-DX's mod0/mod1 pair). The
    // modulator is generated by a two-pole recursive oscillator rather than a
    // phase-accumulator sine — this is what makes Alpha-DX's FM character
    // slightly "dirty" compared to a textbook DX7 operator.
    double mod0 = 0.0;
    double mod1 = 0.0;
    double dmod = 0.0;       // resonant coefficient (2*cos(w0))

    // Modulator envelope state
    double menv = 0.0;       // current modulator envelope level
    double mlev = 0.0;       // sustain level for the modulator envelope
    double mdec = 0.0;       // modulator decay coefficient (cached per block)

    // Carrier envelope state
    double cenv = 0.0;       // smoothed carrier envelope
    double env = 0.0;       // carrier envelope target
    double catt = 0.0;       // attack coefficient (cached per block)
    double cdec = 0.0;       // decay coefficient (cached per block)

    // Cached per-voice coefficients (refreshed per block from the processor's
    // DX FM parameter set — so they track knob changes without needing a
    // parameterChanged listener for every single one).
    double dcar = 0.0;       // carrier phase increment (tune * pitchBend * tuning)

    bool   active = false;   // true between note-on and envelope silence

    void reset()
    {
        carPhase = modPhase = 0.0;
        mod0 = mod1 = dmod = 0.0;
        menv = mlev = mdec = 0.0;
        cenv = env = catt = cdec = 0.0;
        dcar = 0.0;
        active = false;
    }
};

//==============================================================================
// Voice
struct WaspVoice
{
    int    midiNote = -1;
    double baseFreq = 0.0;

    // Per-voice tuning multiplier, matching Alpha-DX's `tuning`.
    // Used by the DX FM engine to scale envelope depths by pitch (key track).
    // Computed at note-on from the MIDI note number ONLY. The DX FM engine's
    // fine-tune offset is applied separately inside the processor's
    // initDxVoice() — this keeps the voice's `tuning` a pure function of
    // pitch, so it can be reused by the subtractive engine if ever needed.
    double tuning = 1.0;

    bool   noteHeld = false;  // true while MIDI key is physically depressed
    bool   isActive = false;  // true while amp envelope is producing sound (including release)
    float  velocity = 1.0f;   // normalised 0..1 note-on velocity

    // Oscillator phases (main pair)
    double osc1Phase = 0.0;
    double osc2Phase = 0.0;
    double osc3Phase = 0.0;

    // Detuned "dual voice" companion phases (second unison layer, XT "DUAL" switch)
    double osc1PhaseB = 0.0;
    double osc2PhaseB = 0.0;

    WaspFilter filter;
    WaspFilter filter2; // dual multimode filter
    ChamberlinFilter chamberlinF;  // alternate model for filter  (TS-404 acid character)
    ChamberlinFilter chamberlinF2; // alternate model for filter2
    WaspEnv    ampEnv;
    WaspEnv    fltEnv;
    WaspModEnv modEnv;

    // DX FM per-voice state.
    // Zero-initialised; only ticked when the DX FM module is enabled.
    DxVoiceState dx;

    double sampleRate = 44100.0;

    void setSampleRate(double sr)
    {
        sampleRate = sr;
        filter.setSampleRate(sr);
        filter2.setSampleRate(sr);
        chamberlinF.setSampleRate(sr);
        chamberlinF2.setSampleRate(sr);
        ampEnv.setSampleRate(sr);
        fltEnv.setSampleRate(sr);
        modEnv.setSampleRate(sr);
    }

    void noteOn(int note, double freq, float vel)
    {
        midiNote = note;
        baseFreq = freq;
        noteHeld = true;
        isActive = true;
        velocity = vel;
        osc1Phase = osc2Phase = osc3Phase = 0.0;
        osc1PhaseB = osc2PhaseB = 0.0;

        // Compute the tuning multiplier used by the DX FM engine.
        // Alpha-DX's formula (without the fine-shift, which is applied later
        // inside the processor's initDxVoice()):
        //     tuning = exp(0.05776226505 * note)
        // The constant 0.05776226505 = ln(2) / 12, giving a semitone-step
        // exponential curve. Small positive values that scale smoothly with
        // pitch. Range for MIDI note 0..127 ≈ 1.0 .. 1500.
        tuning = std::exp(0.05776226505 * (double)note);

        ampEnv.noteOn();
        fltEnv.noteOn();
        modEnv.noteOn();
        dx.reset();
    }

    void noteOff()
    {
        noteHeld = false;
        ampEnv.noteOff();
        fltEnv.noteOff();
        // DX FM release: carrier env target drops to zero via the release
        // coefficient that the processor writes into dx.cdec on note-off.
        // Handled in the processor's handleMidiEvent, since we need the
        // parameter set to compute dxCrel.
    }

    // Generate one sample of a given oscillator waveform
    float oscSample(double& phase, double freq, int shape, double pw)
    {
        float out = 0.0f;
        switch (shape)
        {
        case 0: // Saw (with trivial PolyBLEP not implemented — simple for now)
            out = (float)(1.0 - 2.0 * phase);
            break;
        case 1: // Square (with PW)
        {
            double pwClamped = juce::jlimit(0.05, 0.95, pw);
            out = (phase < pwClamped) ? 1.0f : -1.0f;
            break;
        }
        case 2: // Triangle
            out = (float)((phase < 0.5) ? (4.0 * phase - 1.0) : (3.0 - 4.0 * phase));
            break;
        case 3: // Sine
            out = (float)std::sin(phase * juce::MathConstants<double>::twoPi);
            break;
        case 4: // 303-Saw — exponential capacitor-discharge curve (TS-404/acid character)
        {
            // A plain saw is a straight ramp; the TB-303's saw isn't, because
            // it's generated by a capacitor discharging through a resistor,
            // which follows an exponential curve rather than a straight line.
            // That curve is what gives the acid saw its distinctive "scooped"
            // attack and fatter-sounding fundamental versus a trivial saw.
            constexpr double curve = 3.0;
            const double expNorm = 1.0 - std::exp(-curve); // recomputed per call — cheap, and
            // avoids any static-local init concern
            // on the audio thread
            double shaped = (1.0 - std::exp(-curve * phase)) / expNorm; // 0..1
            out = (float)(1.0 - 2.0 * shaped); // remap to 1..-1, same polarity as plain saw
            break;
        }
        default: break;
        }
        phase += freq / sampleRate;
        if (phase >= 1.0) phase -= 1.0;
        return out;
    }

    // Generate one sample for the sub/noise oscillator
    float osc3Sample(double& phase, double baseFreq_, int shape)
    {
        float out = 0.0f;
        switch (shape)
        {
        case 0: // Sub (-1 octave square)
        {
            double f = baseFreq_ * 0.5;
            out = (phase < 0.5) ? 1.0f : -1.0f;
            phase += f / sampleRate;
            if (phase >= 1.0) phase -= 1.0;
            break;
        }
        case 1: // Sub-sub (-2 octave square)
        {
            double f = baseFreq_ * 0.25;
            out = (phase < 0.5) ? 1.0f : -1.0f;
            phase += f / sampleRate;
            if (phase >= 1.0) phase -= 1.0;
            break;
        }
        case 2: // Noise
            out = (float)(juce::Random::getSystemRandom().nextFloat() * 2.0f - 1.0f);
            break;
        default: break;
        }
        return out;
    }
};

//==============================================================================
// Main Processor
//==============================================================================
class WASPAlphaAudioProcessor : public juce::AudioProcessor,
    public juce::AudioProcessorValueTreeState::Listener
{
public:
    WASPAlphaAudioProcessor();
    ~WASPAlphaAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "The Stinger"; }
    bool acceptsMidi()  const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 8.0; }  // matches max release param

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void parameterChanged(const juce::String& paramID, float newValue) override;

    juce::AudioProcessorValueTreeState apvts;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    // ==== Preset manager accessor ====
    // The editor uses this to build its preset ComboBox, load presets when
    // the user picks one, and save the current state as a new preset.
    PresetManager& getPresetManager() { return *presetManager; }
    const PresetManager& getPresetManager() const { return *presetManager; }

private:
    // Voices (max 8 + dual voice doubles it conceptually)
    static constexpr int MAX_VOICES = 8;
    WaspVoice voices[MAX_VOICES];

    // LFOs (shared across voices)
    WaspLfo lfo1, lfo2;

    // Delay (Stinger addition) — one line per output channel
    SimpleDelay delayL, delayR;

    // ==== Preset manager ====
    // Constructed in the processor's constructor, after the APVTS is ready.
    // Unique-ptr so it can be forward-declared through the header without
    // pulling PresetManager.cpp's factory table into every translation unit
    // that includes this header.
    std::unique_ptr<PresetManager> presetManager;

    // Pre-sized dry-signal scratch buffers for the distortion dry/wet blend —
    // sized once in prepareToPlay so processBlock never allocates on the
    // audio thread. The resize-if-needed check in processBlock is a safety
    // net (a no-op in the normal case) for the rare host that changes block
    // size without calling prepareToPlay again.
    std::vector<float> distDryL, distDryR;

    // Distortion HP filter (tone shaping)
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>> distToneFilter;

    double currentSampleRate = 44100.0;
    int    currentBlockSize = 512;

    // Set true only at the end of prepareToPlay, checked at the top of
    // processBlock. Some hosts' plugin validation passes call processBlock
    // before ever calling prepareToPlay; distToneFilter (a
    // juce::dsp::ProcessorDuplicator) has undefined behaviour if .process()
    // runs before .prepare() ever ran on it, and currentSampleRate's default
    // member initialiser (44100.0) would silently pass a "< 8000" style
    // check even in that scenario, so that check alone doesn't catch this —
    // an explicit flag is the actual fix.
    bool isPrepared = false;

    // Caches the last Distortion Tone value so the IIR coefficients (which
    // internally heap-allocate via makeFirstOrderHighPass) are only
    // recomputed when the knob actually moves, not unconditionally every
    // block — real-time-safety fix.
    float lastDistTone = -1.0f;

    // ==== DX FM module state ====
    // Mod wheel position (0..1), latched from MIDI CC1. Used by the DX FM
    // vibrato path (when MW>Vib is engaged) and by the subtractive engine's
    // own vibrato path if that ever gets wired up.
    float modWheelValue = 0.0f;

    // DX FM coefficients, recomputed once per block from the parameter set.
    // These mirror the Alpha-DX engine's own internal variables so the FM
    // math can be lifted over with as few translation errors as possible.
    float dxTune = 0.0f;    // base tune (Hz per sample unit, post octave shift)
    float dxRatio = 0.0f;    // modulator:carrier frequency ratio (radians)
    float dxDepth = 0.0f;    // modulator envelope peak depth
    float dxDept2 = 0.0f;    // modulator envelope sustain depth
    float dxCatt = 0.0f;    // carrier attack coefficient
    float dxCdec = 0.0f;    // carrier decay coefficient
    float dxCrel = 0.0f;    // carrier release coefficient
    float dxMdec = 0.0f;    // modulator decay coefficient
    float dxMrel = 0.0f;    // modulator release coefficient
    float dxRich = 0.0f;    // carrier harmonic richness (Alpha-DX "rich")
    float dxModMix = 0.0f;    // mod-thru dry modulator leak
    float dxVolume = 0.0035f; // DX FM output gain (matches Alpha-DX's initial value)

    // Latest latched pitch-bend multiplier (from the host or MIDI pitch wheel).
    // Kept here so both the subtractive and DX FM paths can reference the
    // same value without duplicating the bend calculation.
    double pitchBendGlobal = 1.0;

    // Refreshes dxTune..dxVolume from the current APVTS values. Called once
    // per processBlock when the DX FM module is enabled — cheap enough that
    // it doesn't need caching, and it guarantees the FM voice always tracks
    // live knob moves.
    void updateDxParams();

    // Per-voice DX FM render. Writes one sample of FM audio into `out`.
    // `ampEnv` is the current amp-envelope value (shared with the subtractive
    // voice) so both engines fade together on note-off.
    void renderDxVoice(WaspVoice& v, float& out, float ampEnv);

    // Re-initialises a voice's DX FM state at note-on. Reads the current DX
    // FM parameters and writes the per-voice cached coefficients. Called from
    // handleMidiEvent's note-on branch only when the module is enabled.
    //
    // NOTE: the body of this function lives in PluginProcessor.cpp, NOT here.
    // Do not define it inline in the class — doing so causes redefinition
    // errors when PluginProcessor.cpp also defines it.
    void initDxVoice(WaspVoice& v, int midiNote, int velocity);

    // MIDI handling
    void handleMidiEvent(const juce::MidiMessage& msg);
    int  findFreeVoice();
    int  findVoiceForNote(int midiNote);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WASPAlphaAudioProcessor)
};