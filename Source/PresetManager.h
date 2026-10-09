#pragma once
#include <JuceHeader.h>

//==============================================================================
// The Stinger — Preset Manager
//
// Owns the factory preset table, the user preset folder, and the logic to
// move preset data in and out of the APVTS. All preset I/O happens on the
// message thread only — nothing in this class touches the audio thread.
//
// File format: single-file XML, one .stinger file per user preset.
// Factory presets are baked into the binary as C++ data (see PresetManager.cpp).
//==============================================================================

class PresetManager
{
public:
    //==========================================================================
    // One entry in the available-presets list. Either a factory preset
    // (isFactory == true, factoryIndex valid) or a user preset (isFactory ==
    // false, file valid). The editor builds its ComboBox from a vector of
    // these, in the same order.
    //==========================================================================
    struct PresetInfo
    {
        juce::String  name;         // display name, e.g. "Bright E.Piano"
        juce::String  category;     // e.g. "FM Piano"
        juce::String  author;       // e.g. "Factory" or a user name
        bool          isFactory = true;
        int           factoryIndex = -1;  // valid iff isFactory
        juce::File    file;               // valid iff !isFactory
    };

    //==========================================================================
    // Construction / lifecycle
    //==========================================================================
    PresetManager(juce::AudioProcessorValueTreeState& apvts);
    ~PresetManager() = default;

    // Rescans the user preset folder and rebuilds the available-presets
    // list. Call this once at startup, and again after any save/delete so
    // the list stays in sync with the disk.
    void refresh();

    //==========================================================================
    // Queries
    //==========================================================================
    int                       getNumPresets() const;
    const PresetInfo& getPresetInfo(int index) const;
    const std::vector<PresetInfo>& getAllPresets() const { return presets; }

    // Returns the index of the preset currently loaded, or -1 if the current
    // state doesn't match any known preset (e.g. the user has moved knobs
    // since loading). This is a best-effort match — it compares every
    // parameter value against each preset and returns the first exact hit.
    // Slow on paper but trivial in practice (32 presets × ~50 params).
    int getCurrentPresetIndex() const;

    //==========================================================================
    // Loading
    //==========================================================================
    // Loads the preset at `index` into the APVTS. Every parameter is written
    // via setValueNotifyingHost so the editor UI reflects the change
    // immediately. Returns false if the index is out of range or the preset
    // is a user preset whose file no longer exists.
    bool loadPreset(int index);

    // Loads a preset from an arbitrary XML file (not necessarily in the
    // user preset folder). Useful for importing a preset someone sent you.
    // Returns false if the file can't be parsed or isn't a Stinger preset.
    bool loadPresetFromFile(const juce::File& file);

    //==========================================================================
    // Saving
    //==========================================================================
    // Saves the current APVTS state as a new user preset. If a preset with
    // the same name already exists, this returns the existing file's path
    // and does NOT overwrite — the caller should prompt the user or append
    // a suffix. (Alternative behaviour — overwriting — is available via the
    // `allowOverwrite` flag.)
    //
    // Returns the file that was written, or an invalid File on failure.
    juce::File saveUserPreset(const juce::String& name,
        const juce::String& category,
        const juce::String& author,
        bool allowOverwrite = false);

    // Exports the current APVTS state to a user-chosen file. Used by the
    // editor's "Export..." menu item. Returns true on success.
    bool exportPresetToFile(const juce::File& destination,
        const juce::String& name,
        const juce::String& category,
        const juce::String& author);

    //==========================================================================
    // Deleting
    //==========================================================================
    // Deletes the preset at `index` if it's a user preset. Factory presets
    // cannot be deleted — returns false for them.
    bool deletePreset(int index);

    //==========================================================================
    // Utility
    //==========================================================================
    // Returns the directory where user presets are stored. Created on
    // demand if it doesn't exist.
    juce::File getUserPresetDirectory() const;

    // Converts an XML element (as produced by writePresetXml) back into a
    // parameter set and loads it into the APVTS. Used internally by
    // loadPreset and loadPresetFromFile. Exposed publicly so the editor can
    // verify a preset before committing to a load, if it ever wants to.
    bool applyPresetXml(const juce::XmlElement& xml);

    // Serialises the current APVTS state to an XML element with the given
    // metadata. Used internally by every save path. Exposed publicly so the
    // editor can preview the XML if it ever wants to show it.
    std::unique_ptr<juce::XmlElement> writePresetXml(const juce::String& name,
        const juce::String& category,
        const juce::String& author) const;

private:
    //==========================================================================
    // Internal helpers
    //==========================================================================

    // Reads every parameter from the APVTS and writes them into the given
    // XML element as <PARAM id="..." value="..."/> children.
    void writeParametersToXml(juce::XmlElement& parent) const;

    // Reads every <PARAM> from the given XML element and applies it to the
    // APVTS. Ignores any params not present in the APVTS (so old presets
    // survive added parameters) and any params not present in the XML
    // (so new presets don't need every value spelled out).
    void applyParametersFromXml(const juce::XmlElement& parent);

    // Scans the user preset directory and appends any .stinger files to
    // `presets`. Called from refresh().
    void scanUserPresets();

    // Reads name/category/author metadata from a user preset file. Returns
    // false if the file can't be parsed.
    bool readUserPresetMetadata(const juce::File& file,
        juce::String& name,
        juce::String& category,
        juce::String& author) const;

    //==========================================================================
    // Factory preset table
    //==========================================================================
    // The factory presets are stored as a static array in PresetManager.cpp.
    // Each entry has a name, category, author, and a vector of
    // {paramID, value} pairs. This is the C++ equivalent of an embedded XML
    // file, but without the runtime parse cost.
    //
    // Defined in PresetManager.cpp to keep this header lean.
    struct FactoryPreset
    {
        juce::String name;
        juce::String category;
        juce::String author;
        std::vector<std::pair<juce::String, float>> params;  // paramID -> value
    };

    static const std::vector<FactoryPreset>& getFactoryPresets();

    //==========================================================================
    // State
    //==========================================================================
    juce::AudioProcessorValueTreeState& apvts;

    // Flat list of all available presets, factory first then user.
    // Rebuilt by refresh().
    std::vector<PresetInfo> presets;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetManager)
};