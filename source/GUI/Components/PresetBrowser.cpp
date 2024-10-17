#include "PresetBrowser.h"
#include "../../PluginProcessor.h"

PresetBrowser::PresetBrowser(PluginProcessor &p) : audioProcessor(p)
{
    setComponentID("Preset");
    _projectName = audioProcessor.getProjectName();

    auto folderPath = audioProcessor.getVariableTree().getProperty("presetFolder");
    if (folderPath != "")
    {
        _folderPath = folderPath;
    }

    initButtons();
    initMenu();
}

PresetBrowser::~PresetBrowser()
{
    _presetMenu.removeMouseListener(this);
    _presetMenu.setLookAndFeel(nullptr);
}

void PresetBrowser::paint(juce::Graphics &g)
{
}

void PresetBrowser::resized()
{
    const auto buttonWidth = getWidth() * 0.1;
    const auto buttonHeight = getHeight();
    const auto menuHeight = buttonHeight;
    const auto menuWidth = getWidth() * 0.8;
    const auto topMargin = 0;
    auto compX = 0;

    _buttons[getButtonIndex("<")]->setBounds(compX, topMargin, buttonWidth, buttonHeight);
    _presetMenu.setBounds(_buttons[getButtonIndex("<")]->getRight(), topMargin, menuWidth, menuHeight);
    _buttons[getButtonIndex(">")]->setBounds(_presetMenu.getRight(), topMargin, buttonWidth, buttonHeight);
}

#pragma mark Buttons
void PresetBrowser::initButtons()
{
    for (int i = 0; i < _numButtons; i++)
    {
        _buttons.add(std::make_unique<juce::TextButton>(_buttonNameTexts[i]));
        _buttons[i]->setComponentID("Preset");
        _buttons[i]->setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
        _buttons[i]->setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::transparentBlack);
        _buttons[i]->setColour(juce::TextButton::ColourIds::textColourOffId, viator::colors::monster_comp_outline);
        _buttons[i]->setColour(juce::TextButton::ColourIds::textColourOnId, viator::colors::monster_comp_outline);
        addAndMakeVisible(_buttons[i]);
    }

    _buttons[getButtonIndex("<")]->setClickingTogglesState(false);
    _buttons[getButtonIndex(">")]->setClickingTogglesState(false);

    _buttons[getButtonIndex("<")]->onClick = [this]()
    {
        navigateMenuOnButtonClick(Direction::kLeft);
        saveMenuState();
    };

    _buttons[getButtonIndex(">")]->onClick = [this]()
    {
        navigateMenuOnButtonClick(Direction::kRight);
        saveMenuState();
    };
}

void PresetBrowser::navigateMenuOnButtonClick(Direction newDirection)
{
    auto currentIndex = _presetMenu.getSelectedId();
    auto num = _presetMenu.getNumItems();

    if (newDirection == Direction::kLeft)
    {
        int previousIndex = currentIndex - 1;
        if (previousIndex <= 0)
            previousIndex = num;

        _presetMenu.setSelectedId(previousIndex);
    }

    if (newDirection == Direction::kRight)
    {
        int nextIndex = currentIndex + 1;
        if (nextIndex > num)
            nextIndex = 1;

        _presetMenu.setSelectedId(nextIndex);
    }
}

#pragma mark Menus and Presets
void PresetBrowser::initMenu()
{
    addAndMakeVisible(_presetMenu);
    _presetMenu.setComponentID("Preset");
    _presetMenu.setTextWhenNothingSelected("Presets");
    _presetMenu.addMouseListener(this, false);
    _presetMenu.setLookAndFeel(&menuLAF);

    _presetMenu.onChange = [this]()
    {
        auto notNegative = _presetMenu.getSelectedId() >= 1;
        auto presetChanged = _presetMenu.getSelectedId() != previousMenuID;
        if (notNegative && presetChanged)
        {
            previousMenuID = _presetMenu.getSelectedId();
            makeMenuSelection();
        }
    };
}

void PresetBrowser::populateMenu()
{
    resetState();

    juce::PopupMenu _userMenu;

    auto folderPath = audioProcessor.getVariableTree().getProperty("presetFolder").toString();
    auto presetFolder = juce::File(folderPath);
    presetFolder.findChildFiles(_xmlFiles, juce::File::TypesOfFileToFind::findFiles, true, "*.xml");
    _xmlFiles.sort();

    for (int i = 0; i < _xmlFiles.size(); ++i)
    {
        _xmlFilePaths.insert(i, _xmlFiles[i].getFullPathName());
        juce::String fileName = _xmlFiles[i].getFileNameWithoutExtension();
        _userMenu.addItem(juce::PopupMenu::Item(fileName).setID(i + 1));
    }

    _presetMenu.getRootMenu()->addSubMenu("User", _userMenu);
    populateFactoryMenu();

    _presetMenu.getRootMenu()->addSeparator();
    _presetMenu.getRootMenu()->addItem(juce::PopupMenu::Item("Save").setAction(
        [this]()
        {
            savePreset();
        }
    ));
    _presetMenu.getRootMenu()->addItem(juce::PopupMenu::Item("Load").setAction(
        [this]()
        {
            importPreset();
        }
    ));
}

int PresetBrowser::getXMLByName(juce::String name)
{
    int id;

    for (int i = 0; i < _xmlFiles.size(); ++i)
    {
        if (_xmlFiles[i].getFileName() == name)
        {
            id = i + 1;
        }
    }

    jassert(id > 0);
    return id;
}

void PresetBrowser::prepareFactoryMenu()
{
    _drumPresets.clear();
    _drumFileNames.clear();
    _kickPresets.clear();
    _kickFileNames.clear();
    _synthPresets.clear();
    _synthFileNames.clear();
    _vocalPresets.clear();
    _vocalFileNames.clear();
    _geetarPresets.clear();
    _geetarFileNames.clear();
    _bassPresets.clear();
    _bassFileNames.clear();
    _mixPresets.clear();
    _mixFileNames.clear();
    _miscPresets.clear();
    _miscFileNames.clear();
}

void PresetBrowser::addSectionHeader(const juce::String &text, juce::PopupMenu &menu)
{
    menu.addSectionHeader(text);
    menu.addSeparator();
}

void PresetBrowser::populateFactoryMenu()
{
    _xmlFiles.sort();

    _factoryMenu.clear();

    _mixMenu.clear();
    _drumsMenu.clear();
    _synthMenu.clear();
    _vocalMenu.clear();
    _geetarMenu.clear();
    _bassMenu.clear();
    _miscMenu.clear();

    int offset = _xmlFiles.size();

    populateSubMenu(_mixPresets, _mixFileNames, _mixMenu, offset);
    offset += _mixPresets.size();

    populateSubMenu(_drumPresets, _drumFileNames, _drumsMenu, offset);
    offset += _drumPresets.size();

    populateSubMenu(_synthPresets, _synthFileNames, _synthMenu, offset);
    offset += _synthPresets.size();

    populateSubMenu(_vocalPresets, _vocalFileNames, _vocalMenu, offset);
    offset += _vocalPresets.size();

    populateSubMenu(_geetarPresets, _geetarFileNames, _geetarMenu, offset);
    offset += _geetarPresets.size();

    populateSubMenu(_bassPresets, _bassFileNames, _bassMenu, offset);
    offset += _bassPresets.size();

    populateSubMenu(_miscPresets, _miscFileNames, _miscMenu, offset);
    offset += _miscPresets.size();

    _factoryMenu.addSubMenu("Mix Bus", _mixMenu);
    _factoryMenu.addSubMenu("Drums", _drumsMenu);
    _factoryMenu.addSubMenu("Synth", _synthMenu);
    _factoryMenu.addSubMenu("Vocals", _vocalMenu);
    _factoryMenu.addSubMenu("Guitar", _geetarMenu);
    _factoryMenu.addSubMenu("Bass", _bassMenu);
    _factoryMenu.addSubMenu("Misc", _miscMenu);
    _presetMenu.getRootMenu()->addSubMenu("Factory", _factoryMenu);
}

void PresetBrowser::populateSubMenu(std::vector<juce::File> &presets,
                                    const juce::StringArray &fileNames,
                                    juce::PopupMenu &menu,
                                    int offset)
{
    for (int i = 0; i < presets.size(); ++i)
    {
        auto newIndex = offset + i;
        _xmlFilePaths.insert(newIndex, presets[i].getFullPathName());
        juce::String fileName = presets[i].getFileNameWithoutExtension();
        auto name = fileNames[i];
        menu.addItem(juce::PopupMenu::Item(fileNames[i]).setID(newIndex + 1));
    }
}

void PresetBrowser::addFactoryFiles(const void *wav,
                                    size_t wavSize,
                                    const juce::String &fileName,
                                    PresetType presetType)
{
    // Load audio data from a file embedded in the BinaryData
    juce::MemoryBlock memoryBlock(wav, wavSize);

    juce::File tempFile = juce::File::createTempFile(fileName);
    juce::FileOutputStream outputStream(tempFile);
    outputStream.write(memoryBlock.getData(), memoryBlock.getSize());
    outputStream.flush();
    juce::File audioFile = tempFile.getFullPathName();

    switch (presetType)
    {
        case PresetType::kMix:
        {
            _mixPresets.emplace_back(audioFile.getFullPathName());
            _mixFileNames.add(fileName);
            break;
        }

        case PresetType::kMisc:
        {
            _miscPresets.emplace_back(audioFile.getFullPathName());
            _miscFileNames.add(fileName);
            break;
        }

        case PresetType::kDrums:
        {
            _drumPresets.emplace_back(audioFile.getFullPathName());
            _drumFileNames.add(fileName);
            break;
        }

        case PresetType::kSynth:
        {
            _synthPresets.emplace_back(audioFile.getFullPathName());
            _synthFileNames.add(fileName);
            break;
        }

        case PresetType::kVocal:
        {
            _vocalPresets.emplace_back(audioFile.getFullPathName());
            _vocalFileNames.add(fileName);
            break;
        }

        case PresetType::kGeetar:
        {
            _geetarPresets.emplace_back(audioFile.getFullPathName());
            _geetarFileNames.add(fileName);
            break;
        }

        case PresetType::kBass:
        {
            _bassPresets.emplace_back(audioFile.getFullPathName());
            _bassFileNames.add(fileName);
            break;
        }
    }
}

void PresetBrowser::resetState()
{
    _xmlFiles.clear();
    _presetMenu.clear();
}

void PresetBrowser::saveMenuState()
{
    auto currentIndex = _presetMenu.getSelectedItemIndex();

    if (currentIndex > 0)
    {
        //audioProcessor.getVariableTree().setProperty("presetMenu", currentIndex, nullptr);
    }
}

void PresetBrowser::recallMenuState()
{
}

void PresetBrowser::makeMenuSelection()
{
    loadPreset(_xmlFilePaths[_presetMenu.getSelectedItemIndex()]);
    saveMenuState();
}

int PresetBrowser::getButtonIndex(const juce::String &name)
{
    int index = -1;

    for (int i = 0; i < _numButtons; i++)
    {
        if (_buttons[i]->getName() == name)
        {
            index = i;
        }
    }

    jassert(index > -1);
    return index;
}

void PresetBrowser::savePreset()
{
    _myChooser =
        std::make_unique<juce::FileChooser>("Please select the location to save your preset...", _folderPath, "*.xml");

    auto folderChooserFlags = juce::FileBrowserComponent::saveMode;

    juce::String choiceName = "";

    _myChooser->launchAsync(folderChooserFlags, [this, choiceName](const juce::FileChooser &chooser)
    {
        juce::File file(chooser.getResult());

        const auto &name = file.getFullPathName();

        if (name != "")
        {
            saveParamsToFile(file);
            populateMenu();
            auto choice = getXMLByName(file.getFileName());
            _presetMenu.setSelectedId(choice);
        }
    });
}

void PresetBrowser::importPreset()
{
    // open the file chooser
    _myChooser =
        std::make_unique<juce::FileChooser>("Please select the location to save your preset...", _exportFile, "*.xml");

    // set the flags
    auto folderChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    // launch the file chooser
    _myChooser->launchAsync(folderChooserFlags, [this](const juce::FileChooser &chooser)
    {
        // get the xml file
        juce::File file(chooser.getResult());

        // load the preset
        loadPreset(file.getFullPathName());
    });
}

void PresetBrowser::loadPreset(const juce::String &filePath)
{
    // get the xml file
    juce::File file(filePath);

    // get the xml data
    juce::String xmlData;

    // create an input stream from the chosen file
    std::unique_ptr<juce::FileInputStream> inputStream(file.createInputStream());
    if (inputStream != nullptr)
    {
        xmlData = inputStream->readEntireStreamAsString();
    }

    // make xml doc from data
    juce::XmlDocument xmlDoc(xmlData);

    // parse the xml data
    if (xmlDoc.parse(xmlData))
    {
        auto rootElement = xmlDoc.getDocumentElement();
        juce::String appName = _projectName;

        // make sure the file is for this plugin
        if (rootElement != nullptr && rootElement->hasTagName(appName))
        {
            auto paramElement = rootElement->getFirstChildElement();
            writeParamsToXML(paramElement);
        }
    }
}

void PresetBrowser::saveParamsToFile(const juce::File &fileToSave)
{
    juce::String appName = _projectName;
    juce::XmlElement xml(appName);

    // get ref to params
    auto sliderParams = audioProcessor.getParameterMap().getSliderParams();

    // Add parameters to the XML document
    for (auto &param : sliderParams)
    {
        auto identifier = param.paramID;
        float value = audioProcessor.get_tree_state().getRawParameterValue(identifier)->load();
        juce::XmlElement *paramElement = xml.createNewChildElement("Parameter");
        paramElement->setAttribute(identifier,
                                   value);
    }

    // get ref to params
    auto btnParams = audioProcessor.getParameterMap().getButtonParams();

    // Add parameters to the XML document
    for (auto &param : btnParams)
    {
        auto identifier = param.paramID;
        float value = audioProcessor.get_tree_state().getRawParameterValue(identifier)->load();
        juce::XmlElement *paramElement = xml.createNewChildElement("Parameter");
        paramElement->setAttribute(identifier,
                                   value);
    }

    // get ref to params
    auto menuParams = audioProcessor.getParameterMap().getMenuParams();

    // Add parameters to the XML document
    for (auto &param : menuParams)
    {
        auto identifier = param.paramID;
        float value = audioProcessor.get_tree_state().getRawParameterValue(identifier)->load();
        juce::XmlElement *paramElement = xml.createNewChildElement("Parameter");
        paramElement->setAttribute(identifier,
                                   value);
    }

    // Write the XML document to the file
    xml.writeTo(fileToSave);
}

void PresetBrowser::createPresetFolder()
{
    // Get the user's document directory as the base folder
    juce::File folderPath = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory);

    // Construct the full path by appending the project name
    juce::File folder = folderPath.getChildFile(_projectName);

    // Create the directory if it does not exist
    if (!folder.exists())
    {
        folder.createDirectory();
    }

    _folderPath = folder.getFullPathName();
    audioProcessor.getVariableTree().setProperty("presetFolder", _folderPath.getFullPathName(), nullptr);

    juce::File defaultXmlFile = _folderPath.getChildFile("Default.xml");

    if (!defaultXmlFile.existsAsFile())
    {
        saveParamsToFile(defaultXmlFile);
    }

    populateMenu();
}

void PresetBrowser::countNumberXMLElements(juce::XmlElement *element)
{
    while (element != nullptr)
    {
        for (int i = 0; i < element->getNumAttributes(); ++i)
        {
            numXMLParameters++;
        }

        element = element->getNextElement();
    }
}

void PresetBrowser::writeParamsToXML(juce::XmlElement *element)
{
    while (element != nullptr)
    {
        for (int i = 0; i < element->getNumAttributes(); ++i)
        {
            juce::String paramName = element->getAttributeName(i);
            double paramValue = element->getDoubleAttribute(paramName);
            audioProcessor.get_tree_state().getParameterAsValue(paramName) = paramValue;
        }

        element = element->getNextElement();
    }
}

void PresetBrowser::showPresetErrorMessage()
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon,
                                           "Load Unuccessful",
                                           "Either this preset is for a different plugin or lines were deleted from the XML file.");
}

void PresetBrowser::setPresetFolderLocation()
{
    // Show a file save dialog to choose the export location
    _myChooser = std::make_unique<juce::FileChooser>("Please select the location to save your preset...");

    auto folderChooserFlags = juce::FileBrowserComponent::canSelectDirectories;

    _myChooser->launchAsync(folderChooserFlags, [this](const juce::FileChooser &chooser)
    {
        juce::File file(chooser.getResult());

        if (file.isDirectory())
        {
            _folderPath = file.getFullPathName();
            audioProcessor.getVariableTree().setProperty("presetFolder", file.getFullPathName(), nullptr);
        }
    });
}
