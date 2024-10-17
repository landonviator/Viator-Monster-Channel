#pragma once
#ifndef PresetBrowser_h
#define PresetBrowser_h
#include <juce_gui_basics/juce_gui_basics.h>
#include "../../Global/Parameters.h"
#include "../lookandfeel/MenuLAF.h"
#include "../look.h"

class PluginProcessor;

class PresetBrowser  : public juce::Component, public juce::ActionBroadcaster
{
public:
    PresetBrowser(PluginProcessor&);
    ~PresetBrowser() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    juce::ComboBox& getMenu() { return _presetMenu; };

    // presets
    void savePreset();
    void importPreset();
    void loadPreset(const juce::String& filePath);
    void populateMenu();
    void setPresetFolderLocation();
    void populateFactoryMenu();
    void prepareFactoryMenu();
    void createPresetFolder();
    void populateSubMenu(std::vector<juce::File>& presets, const juce::StringArray& fileNames, juce::PopupMenu& menu, int offset);
    void recallMenuState();

    bool getDoesPresetFolderExist()
    {
        auto folderPath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory);
        auto path = folderPath.getFullPathName();
        auto pluginName = _projectName;
        path.append("/", juce::CharPointer_UTF8::getBytesRequiredFor(path.getCharPointer()));
        path.append(pluginName, juce::CharPointer_UTF8::getBytesRequiredFor(pluginName.getCharPointer()));
        juce::File _folder(path);
        return _folder.isDirectory();
    };

    enum class Direction
    {
        kLeft,
        kRight
    };
    
    enum class PresetType
    {
        kMix,
        kDrums,
        kSynth,
        kVocal,
        kGeetar,
        kBass,
        kMisc
    };
    
    void addFactoryFiles(const void* wav, size_t wavSize, const juce::String& fileName, PresetType presetType);
    void addSectionHeader(const juce::String& text, juce::PopupMenu& menu);
    juce::PopupMenu& getMixMenu(){return _mixMenu;}
    juce::PopupMenu& getDrumsMenu(){return _drumsMenu;}
    juce::PopupMenu& getSynthMenu(){return _synthMenu;}
    juce::PopupMenu& getVocalsMenu(){return _vocalMenu;}
    juce::PopupMenu& getGuitarMenu(){return _geetarMenu;}
    juce::PopupMenu& getBassMenu(){return _bassMenu;}
    
private:
    std::vector<viator::ParameterData::SliderParameterData> _sliderParams;
    std::vector<viator::ParameterData::ButtonParameterData> _btnParams;
    std::vector<viator::ParameterData::MenuParameterData> _menuParams;
    PluginProcessor& audioProcessor;
    juce::String _projectName;

    // buttons
    juce::OwnedArray<juce::TextButton> _buttons;
    juce::StringArray _buttonNameTexts =
    {
      "<", ">"
    };

    juce::ComboBox _presetMenu;
    juce::Array<juce::File> _xmlFiles;
    juce::StringArray _xmlFilePaths;

private:

    // buttons
    void initButtons();
    int getButtonIndex(const juce::String& name);
    void navigateMenuOnButtonClick(Direction newDirection);

    // presets
    void initMenu();
    void saveMenuState();
    void resetState();
    void makeMenuSelection();
    void saveParamsToFile(const juce::File& fileToSave);
    void countNumberXMLElements(juce::XmlElement* element);
    void writeParamsToXML(juce::XmlElement* element);
    void showPresetErrorMessage();
    int getXMLByName(juce::String name);
    int numXMLParameters = 0;
    std::unique_ptr<juce::FileChooser> _myChooser;
    juce::File _folderPath;
    juce::File _exportFile;
    int previousMenuID;
    
    std::vector<juce::File> _drumPresets;
    juce::StringArray _drumFileNames;
    std::vector<juce::File> _kickPresets;
    juce::StringArray _kickFileNames;
    std::vector<juce::File> _synthPresets;
    juce::StringArray _synthFileNames;
    std::vector<juce::File> _vocalPresets;
    juce::StringArray _vocalFileNames;
    std::vector<juce::File> _geetarPresets;
    juce::StringArray _geetarFileNames;
    std::vector<juce::File> _bassPresets;
    juce::StringArray _bassFileNames;
    std::vector<juce::File> _mixPresets;
    juce::StringArray _mixFileNames;
    std::vector<juce::File> _miscPresets;
    juce::StringArray _miscFileNames;
    
    juce::PopupMenu _factoryMenu;
    juce::PopupMenu _mixMenu;
    juce::PopupMenu _drumsMenu;
    juce::PopupMenu _synthMenu;
    juce::PopupMenu _vocalMenu;
    juce::PopupMenu _geetarMenu;
    juce::PopupMenu _bassMenu;
    juce::PopupMenu _miscMenu;

    viator::CustomMenu menuLAF;
    
private:

    const int _numButtons = 2;
    int numParams = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetBrowser)
};

#endif
