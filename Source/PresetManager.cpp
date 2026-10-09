#include "PresetManager.h"

//==============================================================================
// The Stinger — Preset Manager implementation
//==============================================================================

//==============================================================================
// Factory preset table.
//
// Each preset is a list of {paramID, value} pairs. Missing params keep their
// current APVTS value when the preset is applied — this is intentional, so
// adding new parameters in future doesn't require updating every preset.
//
// The values here come from the Alpha-DX preset translation table. The `dxfm_*`
// params drive the DX FM engine; the subtractive params set the complementary
// subtractive layer for hybrid presets. `dxfm_enable` and `dxfm_blend` are
// always present so the preset fully determines which engine is heard.
//==============================================================================

// Shorthand for building the parameter vectors below. Keeps the table
// readable and compact.
namespace {
    using P = std::pair<juce::String, float>;

    // Convenience: wraps a parameter name and value as a pair.
    inline P p(const char* id, float v) { return { juce::String(id), v }; }
}

const std::vector<PresetManager::FactoryPreset>& PresetManager::getFactoryPresets()
{
    // Built once, on first call, and cached for the lifetime of the process.
    static const std::vector<FactoryPreset> factory = []
        {
            std::vector<FactoryPreset> presets;

            // ---------------------------------------------------------------------
            // Helper: build a preset from a name, category, and a list of params.
            // ---------------------------------------------------------------------
            auto make = [](const char* name, const char* category,
                std::initializer_list<P> params) -> FactoryPreset
                {
                    FactoryPreset fp;
                    fp.name = name;
                    fp.category = category;
                    fp.author = "Factory";
                    fp.params.assign(params.begin(), params.end());
                    return fp;
                };

            // ---------------------------------------------------------------------
            // 01 — Bright E.Piano
            // Pure FM. No subtractive layer.
            // ---------------------------------------------------------------------
            presets.push_back(make("Bright E.Piano", "FM Piano", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    1.0f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.65f),
                p("dxfm_car_rel",  0.44f),
                p("dxfm_wave",     0.45f),
                p("dxfm_mod_init", 0.23f),
                p("dxfm_mod_dec",  0.80f),
                p("dxfm_mod_sus",  0.05f),
                p("dxfm_mod_rel",  0.80f),
                p("dxfm_mod_vel",  0.90f),
                p("dxfm_coarse",   0.84f),
                p("dxfm_fine",     0.33f),
                p("dxfm_mod_thru", 0.00f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                }));

            // ---------------------------------------------------------------------
            // 02 — Jazz E.Piano
            // ---------------------------------------------------------------------
            presets.push_back(make("Jazz E.Piano", "FM Piano", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    1.0f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.50f),
                p("dxfm_car_rel",  0.10f),
                p("dxfm_wave",     0.18f),
                p("dxfm_mod_init", 0.44f),
                p("dxfm_mod_dec",  0.34f),
                p("dxfm_mod_sus",  0.24f),
                p("dxfm_mod_rel",  0.80f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.67f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.00f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                }));

            // ---------------------------------------------------------------------
            // 03 — E.Piano Pad
            // Hybrid — FM dominant, soft subtractive pad underneath.
            // ---------------------------------------------------------------------
            presets.push_back(make("E.Piano Pad", "FM Pad", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.85f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.70f),
                p("dxfm_car_rel",  0.40f),
                p("dxfm_wave",     0.43f),
                p("dxfm_mod_init", 0.27f),
                p("dxfm_mod_dec",  0.47f),
                p("dxfm_mod_sus",  0.22f),
                p("dxfm_mod_rel",  0.80f),
                p("dxfm_mod_vel",  0.97f),
                p("dxfm_coarse",   0.23f),
                p("dxfm_fine",     0.18f),
                p("dxfm_mod_thru", 0.84f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                // Subtractive support layer
                p("osc1_shape",    0.0f),    // Saw
                p("osc1_coarse",   0.0f),
                p("osc1_fine",    -8.0f),
                p("osc2_shape",    0.0f),    // Saw
                p("osc2_coarse",  12.0f),
                p("osc2_fine",     8.0f),
                p("osc3_amount",   0.15f),
                p("osc_mix",       0.50f),
                p("pulse_width",   0.50f),
                p("flt_cutoff", 3200.0f),
                p("flt_reso",      0.20f),
                p("flt_env_amt",   0.25f),
                p("flt_keytrack",  0.20f),
                p("flt_type",      0.0f),
                p("amp_attack",    0.05f),
                p("amp_decay",     0.70f),
                p("amp_sustain",   0.55f),
                p("amp_release",   0.70f),
                p("flt_attack",    0.05f),
                p("flt_decay",     0.60f),
                p("flt_sustain",   0.40f),
                p("flt_release",   0.60f),
                p("vel_to_amp",    0.70f),
                p("vel_to_filter", 0.20f),
                }));

            // ---------------------------------------------------------------------
            // 04 — Fuzzy E.Piano
            // ---------------------------------------------------------------------
            presets.push_back(make("Fuzzy E.Piano", "FM Piano", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.90f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.70f),
                p("dxfm_car_rel",  0.40f),
                p("dxfm_wave",     0.28f),
                p("dxfm_mod_init", 0.60f),
                p("dxfm_mod_dec",  0.67f),
                p("dxfm_mod_sus",  0.31f),
                p("dxfm_mod_rel",  0.80f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.32f),
                p("dxfm_fine",     0.22f),
                p("dxfm_mod_thru", 0.64f),
                p("dxfm_octave",   0.51f),
                p("dxfm_tune",     0.50f),
                // Subtractive layer
                p("osc1_shape",    0.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    4.0f),    // 303
                p("osc2_coarse",  12.0f),
                p("osc2_fine",     5.0f),
                p("osc3_amount",   0.10f),
                p("osc_mix",       0.50f),
                p("flt_cutoff", 4500.0f),
                p("flt_reso",      0.25f),
                p("flt_env_amt",   0.40f),
                p("flt_keytrack",  0.00f),
                p("flt_type",      1.0f),    // LP24
                p("amp_attack",    0.00f),
                p("amp_decay",     0.65f),
                p("amp_sustain",   0.25f),
                p("amp_release",   0.50f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.55f),
                p("flt_sustain",   0.25f),
                p("flt_release",   0.40f),
                p("vel_to_amp",    0.50f),
                }));

            // ---------------------------------------------------------------------
            // 05 — Soft Chimes
            // ---------------------------------------------------------------------
            presets.push_back(make("Soft Chimes", "Bell", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    1.0f),
                p("dxfm_car_atk",  0.40f),
                p("dxfm_car_dec",  0.60f),
                p("dxfm_car_rel",  0.65f),
                p("dxfm_wave",     0.40f),
                p("dxfm_mod_init", 0.39f),
                p("dxfm_mod_dec",  0.25f),
                p("dxfm_mod_sus",  0.16f),
                p("dxfm_mod_rel",  0.90f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.76f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.30f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                }));

            // ---------------------------------------------------------------------
            // 06 — Harpsichord
            // ---------------------------------------------------------------------
            presets.push_back(make("Harpsichord", "Pluck", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.85f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.34f),
                p("dxfm_car_rel",  0.00f),
                p("dxfm_wave",     0.84f),
                p("dxfm_mod_init", 0.88f),
                p("dxfm_mod_dec",  0.10f),
                p("dxfm_mod_sus",  0.41f),
                p("dxfm_mod_rel",  0.74f),
                p("dxfm_mod_vel",  0.00f),
                p("dxfm_coarse",   0.28f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.65f),
                p("dxfm_octave",   0.60f),
                p("dxfm_tune",     0.50f),
                // Subtractive pluck
                p("osc1_shape",    1.0f),    // Sqr
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    4.0f),    // 303
                p("osc2_coarse",  12.0f),
                p("osc2_fine",     3.0f),
                p("osc3_amount",   0.20f),
                p("osc_mix",       0.50f),
                p("pulse_width",   0.35f),
                p("rm_amount",     0.15f),
                p("flt_cutoff", 6000.0f),
                p("flt_reso",      0.25f),
                p("flt_env_amt",   0.55f),
                p("flt_type",      0.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.30f),
                p("amp_sustain",   0.00f),
                p("amp_release",   0.05f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.20f),
                p("flt_sustain",   0.00f),
                p("flt_release",   0.05f),
                p("vel_to_amp",    0.90f),
                }));

            // ---------------------------------------------------------------------
            // 07 — Funk Clav
            // ---------------------------------------------------------------------
            presets.push_back(make("Funk Clav", "Pluck", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.80f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.40f),
                p("dxfm_car_rel",  0.10f),
                p("dxfm_wave",     0.30f),
                p("dxfm_mod_init", 0.88f),
                p("dxfm_mod_dec",  0.16f),
                p("dxfm_mod_sus",  0.59f),
                p("dxfm_mod_rel",  0.80f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.36f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.87f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                // Subtractive clav
                p("osc1_shape",    0.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    1.0f),
                p("osc2_coarse",  12.0f),
                p("osc2_fine",     6.0f),
                p("osc3_amount",   0.15f),
                p("osc_mix",       0.50f),
                p("pulse_width",   0.30f),
                p("flt_cutoff", 3800.0f),
                p("flt_reso",      0.55f),
                p("flt_env_amt",   0.65f),
                p("flt_keytrack",  0.20f),
                p("flt_type",      1.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.35f),
                p("amp_sustain",   0.05f),
                p("amp_release",   0.15f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.25f),
                p("flt_sustain",   0.00f),
                p("flt_release",   0.10f),
                p("vel_to_amp",    0.90f),
                p("vel_to_filter", 0.30f),
                p("dist_on",       1.0f),
                p("dist_drive",    1.5f),
                p("dist_tone",  4000.0f),
                p("dist_mix",      0.25f),
                }));

            // ---------------------------------------------------------------------
            // 08 — Sitar
            // ---------------------------------------------------------------------
            presets.push_back(make("Sitar", "Pluck", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.75f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.50f),
                p("dxfm_car_rel",  0.70f),
                p("dxfm_wave",     0.42f),
                p("dxfm_mod_init", 0.15f),
                p("dxfm_mod_dec",  0.75f),
                p("dxfm_mod_sus",  0.49f),
                p("dxfm_mod_rel",  0.77f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.23f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.63f),
                p("dxfm_octave",   0.40f),
                p("dxfm_tune",     0.50f),
                // Subtractive sitar
                p("osc1_shape",    4.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",    12.0f),
                p("osc2_shape",    0.0f),
                p("osc2_coarse",   7.0f),
                p("osc2_fine",   -12.0f),
                p("osc3_amount",   0.15f),
                p("osc_mix",       0.50f),
                p("rm_amount",     0.20f),
                p("flt_cutoff", 2600.0f),
                p("flt_reso",      0.45f),
                p("flt_env_amt",   0.55f),
                p("flt_keytrack",  0.30f),
                p("flt_type",      3.0f),    // BP12
                p("amp_attack",    0.00f),
                p("amp_decay",     0.50f),
                p("amp_sustain",   0.10f),
                p("amp_release",   0.70f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.40f),
                p("flt_sustain",   0.10f),
                p("flt_release",   0.60f),
                p("vel_to_amp",    0.50f),
                p("vel_to_filter", 0.20f),
                }));

            // ---------------------------------------------------------------------
            // 09 — Chiff Organ
            // ---------------------------------------------------------------------
            presets.push_back(make("Chiff Organ", "Organ", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.70f),
                p("dxfm_car_atk",  0.60f),
                p("dxfm_car_dec",  0.99f),
                p("dxfm_car_rel",  0.40f),
                p("dxfm_wave",     0.28f),
                p("dxfm_mod_init", 0.57f),
                p("dxfm_mod_dec",  0.30f),
                p("dxfm_mod_sus",  0.05f),
                p("dxfm_mod_rel",  0.24f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.32f),
                p("dxfm_fine",     0.28f),
                p("dxfm_mod_thru", 0.82f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                // Subtractive organ
                p("osc1_shape",    1.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    1.0f),
                p("osc2_coarse",  12.0f),
                p("osc2_fine",     0.0f),
                p("osc3_shape",    0.0f),
                p("osc3_amount",   0.35f),
                p("osc_mix",       0.50f),
                p("flt_cutoff", 5000.0f),
                p("flt_reso",      0.05f),
                p("flt_env_amt",   0.10f),
                p("flt_type",      0.0f),
                p("amp_attack",    0.35f),
                p("amp_decay",     0.90f),
                p("amp_sustain",   0.95f),
                p("amp_release",   0.50f),
                p("flt_attack",    0.30f),
                p("flt_decay",     0.90f),
                p("flt_sustain",   0.90f),
                p("flt_release",   0.50f),
                p("vel_to_amp",    0.50f),
                }));

            // ---------------------------------------------------------------------
            // 10 — Tinkle
            // ---------------------------------------------------------------------
            presets.push_back(make("Tinkle", "Bell", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    1.0f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.50f),
                p("dxfm_car_rel",  0.65f),
                p("dxfm_wave",     0.00f),
                p("dxfm_mod_init", 0.40f),
                p("dxfm_mod_dec",  0.55f),
                p("dxfm_mod_sus",  0.26f),
                p("dxfm_mod_rel",  0.90f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.37f),
                p("dxfm_fine",     0.65f),
                p("dxfm_mod_thru", 0.41f),
                p("dxfm_octave",   0.80f),
                p("dxfm_tune",     0.50f),
                }));

            // ---------------------------------------------------------------------
            // 11 — Space Pad
            // ---------------------------------------------------------------------
            presets.push_back(make("Space Pad", "Pad", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.55f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.70f),
                p("dxfm_car_rel",  0.52f),
                p("dxfm_wave",     0.34f),
                p("dxfm_mod_init", 0.52f),
                p("dxfm_mod_dec",  0.72f),
                p("dxfm_mod_sus",  0.28f),
                p("dxfm_mod_rel",  0.73f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.23f),
                p("dxfm_fine",     0.20f),
                p("dxfm_mod_thru", 0.43f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                // Subtractive pad
                p("osc1_shape",    0.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",   -15.0f),
                p("osc2_shape",    0.0f),
                p("osc2_coarse",   7.0f),
                p("osc2_fine",    15.0f),
                p("osc3_amount",   0.20f),
                p("osc_mix",       0.50f),
                p("fm_amount",     0.10f),
                p("rm_amount",     0.10f),
                p("flt_cutoff", 2800.0f),
                p("flt_reso",      0.30f),
                p("flt_env_amt",   0.40f),
                p("flt_keytrack",  0.30f),
                p("flt_type",      0.0f),
                p("amp_attack",    0.08f),
                p("amp_decay",     0.80f),
                p("amp_sustain",   0.70f),
                p("amp_release",   0.85f),
                p("flt_attack",    0.10f),
                p("flt_decay",     0.70f),
                p("flt_sustain",   0.55f),
                p("flt_release",   0.75f),
                p("vel_to_amp",    0.50f),
                p("vel_to_filter", 0.30f),
                p("lfo1_target",   4.0f),    // Filter
                p("lfo1_freq",     0.30f),
                p("lfo1_amount",   0.30f),
                p("dual_voice",    0.60f),
                p("dual_detune",  12.0f),
                p("delay_mix",     0.25f),
                p("delay_time_ms", 450.0f),
                p("delay_feedback", 0.40f),
                }));

            // ---------------------------------------------------------------------
            // 12 — Koto
            // ---------------------------------------------------------------------
            presets.push_back(make("Koto", "Pluck", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.85f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.24f),
                p("dxfm_car_rel",  0.00f),
                p("dxfm_wave",     0.53f),
                p("dxfm_mod_init", 0.88f),
                p("dxfm_mod_dec",  0.10f),
                p("dxfm_mod_sus",  0.60f),
                p("dxfm_mod_rel",  0.74f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.39f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.48f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                // Subtractive pluck
                p("osc1_shape",    4.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    0.0f),
                p("osc2_coarse",  12.0f),
                p("osc2_fine",     3.0f),
                p("osc3_amount",   0.10f),
                p("osc_mix",       0.45f),
                p("flt_cutoff", 4500.0f),
                p("flt_reso",      0.45f),
                p("flt_env_amt",   0.65f),
                p("flt_keytrack",  0.25f),
                p("flt_type",      3.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.25f),
                p("amp_sustain",   0.00f),
                p("amp_release",   0.15f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.20f),
                p("flt_sustain",   0.00f),
                p("flt_release",   0.10f),
                p("vel_to_amp",    0.50f),
                }));

            // ---------------------------------------------------------------------
            // 13 — Harp
            // ---------------------------------------------------------------------
            presets.push_back(make("Harp", "Pluck", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.90f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.50f),
                p("dxfm_car_rel",  0.70f),
                p("dxfm_wave",     0.40f),
                p("dxfm_mod_init", 0.16f),
                p("dxfm_mod_dec",  0.35f),
                p("dxfm_mod_sus",  0.00f),
                p("dxfm_mod_rel",  0.28f),
                p("dxfm_mod_vel",  0.90f),
                p("dxfm_coarse",   0.16f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.00f),
                p("dxfm_octave",   0.62f),
                p("dxfm_tune",     0.50f),
                // Subtractive pluck
                p("osc1_shape",    4.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    3.0f),
                p("osc2_coarse",  12.0f),
                p("osc2_fine",     0.0f),
                p("osc3_amount",   0.05f),
                p("osc_mix",       0.50f),
                p("flt_cutoff", 5500.0f),
                p("flt_reso",      0.20f),
                p("flt_env_amt",   0.50f),
                p("flt_keytrack",  0.15f),
                p("flt_type",      0.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.45f),
                p("amp_sustain",   0.00f),
                p("amp_release",   0.35f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.35f),
                p("flt_sustain",   0.00f),
                p("flt_release",   0.30f),
                p("vel_to_amp",    0.90f),
                }));

            // ---------------------------------------------------------------------
            // 14 — Jazz Guitar
            // ---------------------------------------------------------------------
            presets.push_back(make("Jazz Guitar", "Pluck", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.85f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.50f),
                p("dxfm_car_rel",  0.10f),
                p("dxfm_wave",     0.26f),
                p("dxfm_mod_init", 0.49f),
                p("dxfm_mod_dec",  0.25f),
                p("dxfm_mod_sus",  0.25f),
                p("dxfm_mod_rel",  0.80f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.39f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.15f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                // Subtractive body
                p("osc1_shape",    3.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    3.0f),
                p("osc2_coarse",  12.0f),
                p("osc2_fine",     0.0f),
                p("osc3_amount",   0.15f),
                p("osc_mix",       0.50f),
                p("flt_cutoff", 3000.0f),
                p("flt_reso",      0.20f),
                p("flt_env_amt",   0.35f),
                p("flt_keytrack",  0.10f),
                p("flt_type",      0.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.50f),
                p("amp_sustain",   0.20f),
                p("amp_release",   0.40f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.40f),
                p("flt_sustain",   0.20f),
                p("flt_release",   0.35f),
                p("vel_to_amp",    0.70f),
                }));

            // ---------------------------------------------------------------------
            // 15 — Steel Drum
            // ---------------------------------------------------------------------
            presets.push_back(make("Steel Drum", "Percussion", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.90f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.30f),
                p("dxfm_car_rel",  0.51f),
                p("dxfm_wave",     0.58f),
                p("dxfm_mod_init", 0.00f),
                p("dxfm_mod_dec",  0.10f),
                p("dxfm_mod_sus",  0.30f),
                p("dxfm_mod_rel",  0.73f),
                p("dxfm_mod_vel",  1.00f),
                p("dxfm_coarse",   0.48f),
                p("dxfm_fine",     0.73f),
                p("dxfm_mod_thru", 0.00f),
                p("dxfm_octave",   0.60f),
                p("dxfm_tune",     0.50f),
                // Subtractive metallic ring
                p("osc1_shape",    3.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    3.0f),
                p("osc2_coarse",   7.0f),
                p("osc2_fine",     0.0f),
                p("osc3_amount",   0.10f),
                p("osc_mix",       0.50f),
                p("rm_amount",     0.20f),
                p("flt_cutoff", 3500.0f),
                p("flt_reso",      0.55f),
                p("flt_env_amt",   0.40f),
                p("flt_keytrack",  0.30f),
                p("flt_type",      3.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.30f),
                p("amp_sustain",   0.05f),
                p("amp_release",   0.50f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.25f),
                p("flt_sustain",   0.05f),
                p("flt_release",   0.40f),
                p("vel_to_amp",    0.90f),
                p("vel_to_filter", 0.50f),
                }));

            // ---------------------------------------------------------------------
            // 16 — Log Drum
            // ---------------------------------------------------------------------
            presets.push_back(make("Log Drum", "Percussion", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    1.0f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.30f),
                p("dxfm_car_rel",  0.50f),
                p("dxfm_wave",     0.15f),
                p("dxfm_mod_init", 0.47f),
                p("dxfm_mod_dec",  0.08f),
                p("dxfm_mod_sus",  0.16f),
                p("dxfm_mod_rel",  0.50f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.32f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.02f),
                p("dxfm_octave",   0.40f),
                p("dxfm_tune",     0.50f),
                }));

            // ---------------------------------------------------------------------
            // 17 — Trumpet
            // ---------------------------------------------------------------------
            presets.push_back(make("Trumpet", "Brass", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.65f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.99f),
                p("dxfm_car_rel",  0.10f),
                p("dxfm_wave",     0.71f),
                p("dxfm_mod_init", 0.00f),
                p("dxfm_mod_dec",  0.20f),
                p("dxfm_mod_sus",  0.45f),
                p("dxfm_mod_rel",  0.80f),
                p("dxfm_mod_vel",  0.00f),
                p("dxfm_coarse",   0.23f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.00f),
                p("dxfm_octave",   0.60f),
                p("dxfm_tune",     0.50f),
                // Subtractive brass
                p("osc1_shape",    0.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     8.0f),
                p("osc2_shape",    0.0f),
                p("osc2_coarse",  12.0f),
                p("osc2_fine",    -8.0f),
                p("osc3_amount",   0.10f),
                p("osc_mix",       0.50f),
                p("fm_amount",     0.15f),
                p("flt_cutoff", 4000.0f),
                p("flt_reso",      0.30f),
                p("flt_env_amt",   0.40f),
                p("flt_keytrack",  0.20f),
                p("flt_type",      1.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.90f),
                p("amp_sustain",   0.85f),
                p("amp_release",   0.30f),
                p("flt_attack",    0.08f),
                p("flt_decay",     0.60f),
                p("flt_sustain",   0.55f),
                p("flt_release",   0.40f),
                p("vel_to_amp",    0.70f),
                p("vel_to_filter", 0.30f),
                p("dist_on",       1.0f),
                p("dist_drive",    1.4f),
                p("dist_tone",  5000.0f),
                p("dist_mix",      0.25f),
                }));

            // ---------------------------------------------------------------------
            // 18 — Horn
            // ---------------------------------------------------------------------
            presets.push_back(make("Horn", "Brass", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.65f),
                p("dxfm_car_atk",  0.28f),
                p("dxfm_car_dec",  0.99f),
                p("dxfm_car_rel",  0.28f),
                p("dxfm_wave",     0.22f),
                p("dxfm_mod_init", 0.18f),
                p("dxfm_mod_dec",  0.40f),
                p("dxfm_mod_sus",  0.30f),
                p("dxfm_mod_rel",  0.80f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.23f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.48f),
                p("dxfm_octave",   0.40f),
                p("dxfm_tune",     0.50f),
                // Subtractive horn
                p("osc1_shape",    0.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     5.0f),
                p("osc2_shape",    1.0f),
                p("osc2_coarse",  12.0f),
                p("osc2_fine",    -5.0f),
                p("osc3_amount",   0.10f),
                p("osc_mix",       0.50f),
                p("pulse_width",   0.40f),
                p("fm_amount",     0.10f),
                p("flt_cutoff", 3200.0f),
                p("flt_reso",      0.25f),
                p("flt_env_amt",   0.45f),
                p("flt_keytrack",  0.20f),
                p("flt_type",      1.0f),
                p("amp_attack",    0.10f),
                p("amp_decay",     0.90f),
                p("amp_sustain",   0.85f),
                p("amp_release",   0.40f),
                p("flt_attack",    0.15f),
                p("flt_decay",     0.60f),
                p("flt_sustain",   0.55f),
                p("flt_release",   0.50f),
                p("vel_to_amp",    0.60f),
                p("vel_to_filter", 0.20f),
                }));

            // ---------------------------------------------------------------------
            // 19 — Reed 1
            // ---------------------------------------------------------------------
            presets.push_back(make("Reed 1", "Reed", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.70f),
                p("dxfm_car_atk",  0.22f),
                p("dxfm_car_dec",  0.99f),
                p("dxfm_car_rel",  0.25f),
                p("dxfm_wave",     0.70f),
                p("dxfm_mod_init", 0.24f),
                p("dxfm_mod_dec",  0.31f),
                p("dxfm_mod_sus",  0.26f),
                p("dxfm_mod_rel",  0.90f),
                p("dxfm_mod_vel",  0.76f),
                p("dxfm_coarse",   0.17f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.80f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                // Subtractive reed
                p("osc1_shape",    4.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    1.0f),
                p("osc2_coarse",  12.0f),
                p("osc2_fine",     5.0f),
                p("osc3_amount",   0.05f),
                p("osc_mix",       0.50f),
                p("pulse_width",   0.35f),
                p("flt_cutoff", 3500.0f),
                p("flt_reso",      0.35f),
                p("flt_env_amt",   0.50f),
                p("flt_keytrack",  0.25f),
                p("flt_type",      3.0f),
                p("amp_attack",    0.05f),
                p("amp_decay",     0.90f),
                p("amp_sustain",   0.80f),
                p("amp_release",   0.35f),
                p("flt_attack",    0.10f),
                p("flt_decay",     0.60f),
                p("flt_sustain",   0.50f),
                p("flt_release",   0.50f),
                p("vel_to_amp",    0.60f),
                p("vel_to_filter", 0.20f),
                }));

            // ---------------------------------------------------------------------
            // 20 — Reed 2
            // ---------------------------------------------------------------------
            presets.push_back(make("Reed 2", "Reed", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.85f),
                p("dxfm_car_atk",  0.22f),
                p("dxfm_car_dec",  0.99f),
                p("dxfm_car_rel",  0.25f),
                p("dxfm_wave",     0.18f),
                p("dxfm_mod_init", 0.24f),
                p("dxfm_mod_dec",  0.31f),
                p("dxfm_mod_sus",  0.36f),
                p("dxfm_mod_rel",  0.90f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.45f),
                p("dxfm_fine",     0.07f),
                p("dxfm_mod_thru", 0.00f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                // Subtractive support
                p("osc1_shape",    0.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    1.0f),
                p("osc2_coarse",   7.0f),
                p("osc2_fine",     0.0f),
                p("osc3_amount",   0.05f),
                p("osc_mix",       0.50f),
                p("pulse_width",   0.40f),
                p("flt_cutoff", 3000.0f),
                p("flt_reso",      0.25f),
                p("flt_env_amt",   0.45f),
                p("flt_keytrack",  0.20f),
                p("flt_type",      0.0f),
                p("amp_attack",    0.05f),
                p("amp_decay",     0.90f),
                p("amp_sustain",   0.80f),
                p("amp_release",   0.35f),
                p("flt_attack",    0.10f),
                p("flt_decay",     0.60f),
                p("flt_sustain",   0.50f),
                p("flt_release",   0.50f),
                p("vel_to_amp",    0.60f),
                p("vel_to_filter", 0.20f),
                }));

            // ---------------------------------------------------------------------
            // 21 — Violin
            // ---------------------------------------------------------------------
            presets.push_back(make("Violin", "Strings", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.60f),
                p("dxfm_car_atk",  0.70f),
                p("dxfm_car_dec",  0.99f),
                p("dxfm_car_rel",  0.42f),
                p("dxfm_wave",     0.74f),
                p("dxfm_mod_init", 0.75f),
                p("dxfm_mod_dec",  0.39f),
                p("dxfm_mod_sus",  0.51f),
                p("dxfm_mod_rel",  0.80f),
                p("dxfm_mod_vel",  0.32f),
                p("dxfm_coarse",   0.23f),
                p("dxfm_fine",     0.14f),
                p("dxfm_mod_thru", 0.76f),
                p("dxfm_octave",   0.68f),
                p("dxfm_tune",     0.50f),
                // Subtractive violin
                p("osc1_shape",    0.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     5.0f),
                p("osc2_shape",    0.0f),
                p("osc2_coarse",  12.0f),
                p("osc2_fine",    -5.0f),
                p("osc3_amount",   0.10f),
                p("osc_mix",       0.50f),
                p("fm_amount",     0.15f),
                p("flt_cutoff", 3800.0f),
                p("flt_reso",      0.35f),
                p("flt_env_amt",   0.55f),
                p("flt_keytrack",  0.30f),
                p("flt_type",      1.0f),
                p("amp_attack",    0.15f),
                p("amp_decay",     0.90f),
                p("amp_sustain",   0.80f),
                p("amp_release",   0.70f),
                p("flt_attack",    0.20f),
                p("flt_decay",     0.70f),
                p("flt_sustain",   0.60f),
                p("flt_release",   0.70f),
                p("vel_to_amp",    0.50f),
                p("vel_to_filter", 0.30f),
                p("lfo1_target",   0.0f),    // Pitch
                p("lfo1_freq",     5.50f),
                p("lfo1_amount",   0.10f),
                p("lfo2_target",   4.0f),    // Filter
                p("lfo2_freq",     0.50f),
                p("lfo2_amount",   0.20f),
                }));

            // ---------------------------------------------------------------------
            // 22 — Chunky Bass
            // ---------------------------------------------------------------------
            presets.push_back(make("Chunky Bass", "Bass", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.75f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.40f),
                p("dxfm_car_rel",  0.00f),
                p("dxfm_wave",     0.58f),
                p("dxfm_mod_init", 0.47f),
                p("dxfm_mod_dec",  0.25f),
                p("dxfm_mod_sus",  0.10f),
                p("dxfm_mod_rel",  0.50f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.28f),
                p("dxfm_fine",     0.13f),
                p("dxfm_mod_thru", 0.59f),
                p("dxfm_octave",   0.40f),
                p("dxfm_tune",     0.50f),
                // Subtractive bass
                p("osc1_shape",    0.0f),
                p("osc1_coarse", -12.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    0.0f),
                p("osc2_coarse", -12.0f),
                p("osc2_fine",     5.0f),
                p("osc3_shape",    0.0f),
                p("osc3_amount",   0.30f),
                p("osc_mix",       0.50f),
                p("flt_cutoff", 1800.0f),
                p("flt_reso",      0.35f),
                p("flt_env_amt",   0.60f),
                p("flt_type",      1.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.40f),
                p("amp_sustain",   0.10f),
                p("amp_release",   0.25f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.30f),
                p("flt_sustain",   0.05f),
                p("flt_release",   0.20f),
                p("vel_to_amp",    0.70f),
                p("vel_to_filter", 0.20f),
                }));

            // ---------------------------------------------------------------------
            // 23 — E.Bass
            // ---------------------------------------------------------------------
            presets.push_back(make("E.Bass", "Bass", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.80f),
                p("dxfm_car_atk",  0.23f),
                p("dxfm_car_dec",  0.50f),
                p("dxfm_car_rel",  0.10f),
                p("dxfm_wave",     0.18f),
                p("dxfm_mod_init", 0.39f),
                p("dxfm_mod_dec",  0.09f),
                p("dxfm_mod_sus",  0.25f),
                p("dxfm_mod_rel",  0.15f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.40f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.82f),
                p("dxfm_octave",   0.20f),
                p("dxfm_tune",     0.50f),
                // Subtractive bass
                p("osc1_shape",    0.0f),
                p("osc1_coarse", -12.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    1.0f),
                p("osc2_coarse", -12.0f),
                p("osc2_fine",     0.0f),
                p("osc3_shape",    0.0f),
                p("osc3_amount",   0.25f),
                p("osc_mix",       0.50f),
                p("pulse_width",   0.35f),
                p("flt_cutoff", 2200.0f),
                p("flt_reso",      0.25f),
                p("flt_env_amt",   0.45f),
                p("flt_type",      1.0f),
                p("amp_attack",    0.02f),
                p("amp_decay",     0.50f),
                p("amp_sustain",   0.30f),
                p("amp_release",   0.20f),
                p("flt_attack",    0.02f),
                p("flt_decay",     0.40f),
                p("flt_sustain",   0.20f),
                p("flt_release",   0.20f),
                p("vel_to_amp",    0.80f),
                p("vel_to_filter", 0.30f),
                }));

            // ---------------------------------------------------------------------
            // 24 — Clunk Bass
            // ---------------------------------------------------------------------
            presets.push_back(make("Clunk Bass", "Bass", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.85f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.60f),
                p("dxfm_car_rel",  0.40f),
                p("dxfm_wave",     0.52f),
                p("dxfm_mod_init", 0.45f),
                p("dxfm_mod_dec",  0.32f),
                p("dxfm_mod_sus",  0.05f),
                p("dxfm_mod_rel",  0.90f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.23f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.11f),
                p("dxfm_octave",   0.20f),
                p("dxfm_tune",     0.50f),
                // Subtractive clunk
                p("osc1_shape",    4.0f),
                p("osc1_coarse", -12.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    0.0f),
                p("osc2_coarse", -12.0f),
                p("osc2_fine",     0.0f),
                p("osc3_shape",    0.0f),
                p("osc3_amount",   0.20f),
                p("osc_mix",       0.50f),
                p("flt_cutoff", 1500.0f),
                p("flt_reso",      0.30f),
                p("flt_env_amt",   0.50f),
                p("flt_type",      0.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.60f),
                p("amp_sustain",   0.10f),
                p("amp_release",   0.40f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.40f),
                p("flt_sustain",   0.05f),
                p("flt_release",   0.30f),
                p("vel_to_amp",    0.70f),
                p("vel_to_filter", 0.20f),
                }));

            // ---------------------------------------------------------------------
            // 25 — Thick Bass
            // ---------------------------------------------------------------------
            presets.push_back(make("Thick Bass", "Bass", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.70f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.60f),
                p("dxfm_car_rel",  0.40f),
                p("dxfm_wave",     0.44f),
                p("dxfm_mod_init", 0.29f),
                p("dxfm_mod_dec",  0.35f),
                p("dxfm_mod_sus",  0.10f),
                p("dxfm_mod_rel",  0.90f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.17f),
                p("dxfm_fine",     0.15f),
                p("dxfm_mod_thru", 0.31f),
                p("dxfm_octave",   0.40f),
                p("dxfm_tune",     0.50f),
                // Thick subtractive bass
                p("osc1_shape",    0.0f),
                p("osc1_coarse", -12.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    0.0f),
                p("osc2_coarse", -12.0f),
                p("osc2_fine",     7.0f),
                p("osc3_shape",    0.0f),
                p("osc3_amount",   0.40f),
                p("osc_mix",       0.50f),
                p("flt_cutoff", 1600.0f),
                p("flt_reso",      0.40f),
                p("flt_env_amt",   0.55f),
                p("flt_type",      1.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.60f),
                p("amp_sustain",   0.20f),
                p("amp_release",   0.40f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.40f),
                p("flt_sustain",   0.10f),
                p("flt_release",   0.30f),
                p("vel_to_amp",    0.70f),
                p("vel_to_filter", 0.20f),
                }));

            // ---------------------------------------------------------------------
            // 26 — Sine Bass
            // ---------------------------------------------------------------------
            presets.push_back(make("Sine Bass", "Bass", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    1.0f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.60f),
                p("dxfm_car_rel",  0.49f),
                p("dxfm_wave",     0.12f),
                p("dxfm_mod_init", 0.10f),
                p("dxfm_mod_dec",  0.40f),
                p("dxfm_mod_sus",  0.00f),
                p("dxfm_mod_rel",  0.90f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.17f),
                p("dxfm_fine",     0.15f),
                p("dxfm_mod_thru", 0.01f),
                p("dxfm_octave",   0.40f),
                p("dxfm_tune",     0.50f),
                }));

            // ---------------------------------------------------------------------
            // 27 — Square Bass
            // ---------------------------------------------------------------------
            presets.push_back(make("Square Bass", "Bass", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.70f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.60f),
                p("dxfm_car_rel",  0.10f),
                p("dxfm_wave",     0.30f),
                p("dxfm_mod_init", 0.35f),
                p("dxfm_mod_dec",  0.67f),
                p("dxfm_mod_sus",  0.10f),
                p("dxfm_mod_rel",  0.15f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.32f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.73f),
                p("dxfm_octave",   0.20f),
                p("dxfm_tune",     0.50f),
                // Square bass
                p("osc1_shape",    1.0f),
                p("osc1_coarse", -12.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    1.0f),
                p("osc2_coarse", -12.0f),
                p("osc2_fine",     7.0f),
                p("osc3_shape",    0.0f),
                p("osc3_amount",   0.30f),
                p("osc_mix",       0.50f),
                p("flt_cutoff", 1800.0f),
                p("flt_reso",      0.30f),
                p("flt_env_amt",   0.40f),
                p("flt_type",      1.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.60f),
                p("amp_sustain",   0.10f),
                p("amp_release",   0.20f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.40f),
                p("flt_sustain",   0.05f),
                p("flt_release",   0.20f),
                p("vel_to_amp",    0.70f),
                }));

            // ---------------------------------------------------------------------
            // 28 — Upright Bass 1
            // ---------------------------------------------------------------------
            presets.push_back(make("Upright Bass 1", "Bass", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.65f),
                p("dxfm_car_atk",  0.30f),
                p("dxfm_car_dec",  0.50f),
                p("dxfm_car_rel",  0.40f),
                p("dxfm_wave",     0.30f),
                p("dxfm_mod_init", 0.18f),
                p("dxfm_mod_dec",  0.54f),
                p("dxfm_mod_sus",  0.00f),
                p("dxfm_mod_rel",  0.70f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.28f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.03f),
                p("dxfm_octave",   0.40f),
                p("dxfm_tune",     0.50f),
                // Upright subtractive
                p("osc1_shape",    0.0f),
                p("osc1_coarse", -12.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    3.0f),
                p("osc2_coarse", -24.0f),
                p("osc2_fine",     0.0f),
                p("osc3_shape",    0.0f),
                p("osc3_amount",   0.30f),
                p("osc_mix",       0.40f),
                p("flt_cutoff", 1200.0f),
                p("flt_reso",      0.20f),
                p("flt_env_amt",   0.40f),
                p("flt_keytrack",  0.10f),
                p("flt_type",      1.0f),
                p("amp_attack",    0.05f),
                p("amp_decay",     0.50f),
                p("amp_sustain",   0.20f),
                p("amp_release",   0.40f),
                p("flt_attack",    0.05f),
                p("flt_decay",     0.40f),
                p("flt_sustain",   0.20f),
                p("flt_release",   0.40f),
                p("vel_to_amp",    0.80f),
                p("vel_to_filter", 0.30f),
                }));

            // ---------------------------------------------------------------------
            // 29 — Upright Bass 2
            // ---------------------------------------------------------------------
            presets.push_back(make("Upright Bass 2", "Bass", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.65f),
                p("dxfm_car_atk",  0.30f),
                p("dxfm_car_dec",  0.50f),
                p("dxfm_car_rel",  0.40f),
                p("dxfm_wave",     0.55f),
                p("dxfm_mod_init", 0.46f),
                p("dxfm_mod_dec",  0.07f),
                p("dxfm_mod_sus",  0.07f),
                p("dxfm_mod_rel",  0.70f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.36f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.47f),
                p("dxfm_octave",   0.40f),
                p("dxfm_tune",     0.50f),
                // Upright subtractive (brighter variant)
                p("osc1_shape",    0.0f),
                p("osc1_coarse", -12.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    0.0f),
                p("osc2_coarse", -12.0f),
                p("osc2_fine",     4.0f),
                p("osc3_shape",    0.0f),
                p("osc3_amount",   0.25f),
                p("osc_mix",       0.50f),
                p("flt_cutoff", 1600.0f),
                p("flt_reso",      0.25f),
                p("flt_env_amt",   0.45f),
                p("flt_keytrack",  0.10f),
                p("flt_type",      1.0f),
                p("amp_attack",    0.05f),
                p("amp_decay",     0.50f),
                p("amp_sustain",   0.20f),
                p("amp_release",   0.40f),
                p("flt_attack",    0.05f),
                p("flt_decay",     0.40f),
                p("flt_sustain",   0.20f),
                p("flt_release",   0.40f),
                p("vel_to_amp",    0.80f),
                p("vel_to_filter", 0.30f),
                }));

            // ---------------------------------------------------------------------
            // 30 — Harmonics
            // ---------------------------------------------------------------------
            presets.push_back(make("Harmonics", "Bell", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.90f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.50f),
                p("dxfm_car_rel",  0.50f),
                p("dxfm_wave",     0.15f),
                p("dxfm_mod_init", 0.33f),
                p("dxfm_mod_dec",  0.20f),
                p("dxfm_mod_sus",  0.00f),
                p("dxfm_mod_rel",  0.70f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.28f),
                p("dxfm_fine",     0.00f),
                p("dxfm_mod_thru", 0.08f),
                p("dxfm_octave",   0.50f),
                p("dxfm_tune",     0.50f),
                // Subtractive harmonic
                p("osc1_shape",    3.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc2_shape",    3.0f),
                p("osc2_coarse",  19.0f),
                p("osc2_fine",     0.0f),
                p("osc3_amount",   0.10f),
                p("osc_mix",       0.50f),
                p("flt_cutoff", 4000.0f),
                p("flt_reso",      0.20f),
                p("flt_env_amt",   0.30f),
                p("flt_keytrack",  0.20f),
                p("flt_type",      0.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.50f),
                p("amp_sustain",   0.20f),
                p("amp_release",   0.50f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.40f),
                p("flt_sustain",   0.20f),
                p("flt_release",   0.40f),
                p("vel_to_amp",    0.50f),
                }));

            // ---------------------------------------------------------------------
            // 31 — Scratch
            // ---------------------------------------------------------------------
            presets.push_back(make("Scratch", "FX", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    0.75f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.50f),
                p("dxfm_car_rel",  0.00f),
                p("dxfm_wave",     0.82f),
                p("dxfm_mod_init", 0.58f),
                p("dxfm_mod_dec",  0.63f),
                p("dxfm_mod_sus",  0.00f),
                p("dxfm_mod_rel",  0.00f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.00f),
                p("dxfm_fine",     0.24f),
                p("dxfm_mod_thru", 0.24f),
                p("dxfm_octave",   0.60f),
                p("dxfm_tune",     0.50f),
                // Subtractive scratch
                p("osc1_shape",    4.0f),
                p("osc1_coarse",   0.0f),
                p("osc1_fine",     0.0f),
                p("osc3_shape",    2.0f),    // Noise
                p("osc3_amount",   0.40f),
                p("osc_mix",       0.50f),
                p("rm_amount",     0.30f),
                p("flt_cutoff", 3000.0f),
                p("flt_reso",      0.35f),
                p("flt_env_amt",   0.60f),
                p("flt_type",      3.0f),
                p("amp_attack",    0.00f),
                p("amp_decay",     0.40f),
                p("amp_sustain",   0.00f),
                p("amp_release",   0.15f),
                p("flt_attack",    0.00f),
                p("flt_decay",     0.30f),
                p("flt_sustain",   0.00f),
                p("flt_release",   0.10f),
                p("vel_to_amp",    0.90f),
                p("vel_to_filter", 0.40f),
                }));

            // ---------------------------------------------------------------------
            // 32 — Syn Tom
            // ---------------------------------------------------------------------
            presets.push_back(make("Syn Tom", "Percussion", {
                p("dxfm_enable",   1.0f),
                p("dxfm_blend",    1.0f),
                p("dxfm_car_atk",  0.00f),
                p("dxfm_car_dec",  0.36f),
                p("dxfm_car_rel",  0.35f),
                p("dxfm_wave",     1.00f),
                p("dxfm_mod_init", 0.00f),
                p("dxfm_mod_dec",  0.00f),
                p("dxfm_mod_sus",  0.20f),
                p("dxfm_mod_rel",  0.50f),
                p("dxfm_mod_vel",  0.50f),
                p("dxfm_coarse",   0.00f),
                p("dxfm_fine",     0.11f),
                p("dxfm_mod_thru", 0.30f),
                p("dxfm_octave",   0.65f),
                p("dxfm_tune",     0.50f),
                }));

            return presets;
        }();

    return factory;
}

//==============================================================================
// Construction
//==============================================================================
PresetManager::PresetManager(juce::AudioProcessorValueTreeState& state)
    : apvts(state)
{
    // Ensure the user preset folder exists (created on demand).
    getUserPresetDirectory();

    // Build the initial available-presets list.
    refresh();
}

//==============================================================================
// refresh — rebuild the flat list of factory + user presets
//==============================================================================
void PresetManager::refresh()
{
    presets.clear();

    // Factory presets first.
    const auto& factory = getFactoryPresets();
    presets.reserve(factory.size() + 8);
    for (size_t i = 0; i < factory.size(); ++i)
    {
        PresetInfo info;
        info.name = factory[i].name;
        info.category = factory[i].category;
        info.author = factory[i].author;
        info.isFactory = true;
        info.factoryIndex = (int)i;
        presets.push_back(info);
    }

    // Then user presets, scanned from disk.
    scanUserPresets();
}

//==============================================================================
void PresetManager::scanUserPresets()
{
    juce::File dir = getUserPresetDirectory();
    if (!dir.isDirectory()) return;

    // Get all .stinger files, sorted alphabetically by name.
    auto files = dir.findChildFiles(juce::File::findFiles, false, "*.stinger");
    files.sort();

    for (const auto& f : files)
    {
        PresetInfo info;
        info.file = f;
        info.isFactory = false;
        info.factoryIndex = -1;

        // Try to read metadata from the file. If it fails, we still add the
        // preset (with a fallback name derived from the filename) so the user
        // can see and delete a broken file rather than having it silently
        // disappear.
        if (!readUserPresetMetadata(f, info.name, info.category, info.author))
        {
            info.name = f.getFileNameWithoutExtension();
            info.category = "(unreadable)";
            info.author = "";
        }

        presets.push_back(info);
    }
}

//==============================================================================
// Queries
//==============================================================================
int PresetManager::getNumPresets() const
{
    return (int)presets.size();
}

const PresetManager::PresetInfo& PresetManager::getPresetInfo(int index) const
{
    // Caller is responsible for range-checking. Clamp defensively anyway so
    // a bad index can't crash the host.
    if (index < 0) index = 0;
    if (index >= (int)presets.size()) index = (int)presets.size() - 1;
    return presets[(size_t)index];
}

//==============================================================================
// getCurrentPresetIndex — find the preset matching the current APVTS state
//==============================================================================
int PresetManager::getCurrentPresetIndex() const
{
    // For each preset, check whether every parameter it specifies matches the
    // current APVTS value. If we find a full match, return its index.
    //
    // We compare with a small tolerance because parameter values are floats
    // that pass through normalisation. Anything within 1e-4 counts as equal.
    constexpr float kTolerance = 1e-4f;

    auto paramMatches = [&](const juce::String& id, float target) -> bool
        {
            if (auto* p = apvts.getParameter(id))
            {
                float current = p->getValue(); // normalised 0..1
                // Convert target to normalised space too — the factory table
                // stores values in the parameter's natural range, so we need
                // the parameter's own conversion. getNormalisableRange() gives
                // us the ability to convertRangeTo0To1.
                float normalised = p->getNormalisableRange().convertTo0to1(target);
                return std::abs(current - normalised) < kTolerance;
            }
            // Parameter not found — don't treat this as a match failure, since
            // some factory presets may reference params that were removed. Just
            // skip it.
            return true;
        };

    const auto& factory = getFactoryPresets();

    // Check factory presets.
    for (size_t i = 0; i < factory.size(); ++i)
    {
        bool allMatch = true;
        for (const auto& kv : factory[i].params)
        {
            if (!paramMatches(kv.first, kv.second))
            {
                allMatch = false;
                break;
            }
        }
        if (allMatch)
            return (int)i;
    }

    // (User presets are not compared — they can be arbitrarily large and
    // comparing them on every repaint would be wasteful. The editor will
    // just show "Custom" or the last-selected name if the user has moved
    // knobs since loading.)

    return -1;
}

//==============================================================================
// loadPreset — write a preset's values into the APVTS
//==============================================================================
bool PresetManager::loadPreset(int index)
{
    if (index < 0 || index >= (int)presets.size())
        return false;

    const auto& info = presets[(size_t)index];

    if (info.isFactory)
    {
        // Apply the factory preset's parameter list directly.
        const auto& factory = getFactoryPresets();
        if (info.factoryIndex < 0 || info.factoryIndex >= (int)factory.size())
            return false;

        const auto& fp = factory[(size_t)info.factoryIndex];

        for (const auto& kv : fp.params)
        {
            if (auto* p = apvts.getParameter(kv.first))
            {
                // setValueNotifyingHost expects a normalised 0..1 value.
                // The factory table stores natural-range values, so we
                // convert using the parameter's own range.
                float normalised = p->getNormalisableRange().convertTo0to1(kv.second);
                p->setValueNotifyingHost(normalised);
            }
        }
        return true;
    }
    else
    {
        // User preset — load from file.
        return loadPresetFromFile(info.file);
    }
}

//==============================================================================
bool PresetManager::loadPresetFromFile(const juce::File& file)
{
    if (!file.existsAsFile())
        return false;

    auto xml = juce::parseXML(file);
    if (xml == nullptr)
        return false;

    if (!xml->hasTagName("STINGER_PRESET"))
        return false;

    return applyPresetXml(*xml);
}

//==============================================================================
// Saving
//==============================================================================
juce::File PresetManager::saveUserPreset(const juce::String& name,
    const juce::String& category,
    const juce::String& author,
    bool allowOverwrite)
{
    if (name.isEmpty())
        return {};

    juce::File dir = getUserPresetDirectory();
    if (!dir.isDirectory())
        return {};

    // Build a safe filename from the preset name. Remove characters that
    // Windows / macOS / Linux don't like in filenames.
    auto safeName = juce::File::createLegalFileName(name);
    if (safeName.isEmpty())
        safeName = "Untitled";

    juce::File dest = dir.getChildFile(safeName + ".stinger");

    if (dest.existsAsFile() && !allowOverwrite)
    {
        // Caller should have prompted. Return the existing path so they can
        // decide whether to retry with a new name or confirm overwrite.
        return dest;
    }

    auto xml = writePresetXml(name, category, author);
    if (xml == nullptr)
        return {};

    if (!xml->writeTo(dest))
        return {};

    // Rescan so the new file appears in the list.
    refresh();

    return dest;
}

//==============================================================================
bool PresetManager::exportPresetToFile(const juce::File& destination,
    const juce::String& name,
    const juce::String& category,
    const juce::String& author)
{
    auto xml = writePresetXml(name, category, author);
    if (xml == nullptr)
        return false;

    return xml->writeTo(destination);
}

//==============================================================================
// Deleting
//==============================================================================
bool PresetManager::deletePreset(int index)
{
    if (index < 0 || index >= (int)presets.size())
        return false;

    const auto& info = presets[(size_t)index];

    // Factory presets can't be deleted.
    if (info.isFactory)
        return false;

    if (!info.file.existsAsFile())
        return false;

    if (!info.file.deleteFile())
        return false;

    // Rescan so the deleted entry disappears from the list.
    refresh();

    return true;
}

//==============================================================================
// Utility
//==============================================================================
juce::File PresetManager::getUserPresetDirectory() const
{
    // Use JUCE's standard user-application-data directory, keyed on the
    // plugin's name. This gives us:
    //   Windows: %APPDATA%\<Company>\<Plugin>\Presets\
    //   macOS:   ~/Library/Application Support/<Company>/<Plugin>/Presets/
    //   Linux:   ~/.config/<Company>/<Plugin>/Presets/
    //
    // PropertiesFile::getDefaultAppDataDirectory() uses the same root, so
    // this is the canonical place for user data on each platform.
    auto appData = juce::File::getSpecialLocation(
        juce::File::userApplicationDataDirectory);

    juce::File dir = appData
        .getChildFile("ZoneDx")            // company folder
        .getChildFile("The Stinger")       // plugin folder
        .getChildFile("Presets");          // presets subfolder

    if (!dir.isDirectory())
        dir.createDirectory();

    return dir;
}

//==============================================================================
// XML serialisation
//==============================================================================
std::unique_ptr<juce::XmlElement> PresetManager::writePresetXml(
    const juce::String& name,
    const juce::String& category,
    const juce::String& author) const
{
    auto root = std::make_unique<juce::XmlElement>("STINGER_PRESET");
    root->setAttribute("version", 1);
    root->setAttribute("name", name);
    root->setAttribute("category", category);
    root->setAttribute("author", author);

    auto* params = root->createNewChildElement("PARAMETERS");
    writeParametersToXml(*params);

    return root;
}

//==============================================================================
void PresetManager::writeParametersToXml(juce::XmlElement& parent) const
{
    // Iterate every parameter in the APVTS and write its current normalised
    // value. We store the value in the parameter's NATURAL range (Hz, ms,
    // semitones, dB) rather than the normalised 0..1 form, because that's
    // what a human reading the XML wants to see — 350.0 for a delay time is
    // far more legible than 0.6356.
    for (auto* param : apvts.processor.getParameters())
    {
        if (auto* p = dynamic_cast<juce::RangedAudioParameter*> (param))
        {
            const auto& range = p->getNormalisableRange();
            float natural = range.convertFrom0to1(p->getValue());

            auto* child = parent.createNewChildElement("PARAM");
            child->setAttribute("id", p->getParameterID());
            child->setAttribute("value", (double)natural);
        }
    }
}

//==============================================================================
bool PresetManager::applyPresetXml(const juce::XmlElement& xml)
{
    if (!xml.hasTagName("STINGER_PRESET"))
        return false;

    auto* params = xml.getChildByName("PARAMETERS");
    if (params == nullptr)
        return false;

    applyParametersFromXml(*params);
    return true;
}

//==============================================================================
void PresetManager::applyParametersFromXml(const juce::XmlElement& parent)
{
    for (auto* child : parent.getChildWithTagNameIterator("PARAM"))
    {
        const juce::String id = child->getStringAttribute("id");
        if (id.isEmpty()) continue;

        if (auto* p = apvts.getParameter(id))
        {
            float natural = (float)child->getDoubleAttribute("value", 0.0);
            float normalised = p->getNormalisableRange().convertTo0to1(natural);
            p->setValueNotifyingHost(normalised);
        }
        // If the parameter doesn't exist, silently skip — this lets old
        // presets survive parameter removal, and newer presets survive
        // being loaded on an older build.
    }
}

//==============================================================================
bool PresetManager::readUserPresetMetadata(const juce::File& file,
    juce::String& name,
    juce::String& category,
    juce::String& author) const
{
    if (!file.existsAsFile())
        return false;

    auto xml = juce::parseXML(file);
    if (xml == nullptr)
        return false;

    if (!xml->hasTagName("STINGER_PRESET"))
        return false;

    name = xml->getStringAttribute("name", file.getFileNameWithoutExtension());
    category = xml->getStringAttribute("category", "");
    author = xml->getStringAttribute("author", "");

    return true;
}