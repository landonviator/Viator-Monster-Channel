#include "PluginUnlocker.h"

namespace viator
{

PluginUnlocker::PluginUnlocker()
{
    setInputFieldsProps();
    setInputFieldsLabelsProps();
    
    _statusLabel.setColour(juce::Label::textColourId, viator::Colors::getViatorTextColor());
    _statusLabel.setJustificationType(juce::Justification::centred);
    _statusLabel.setEditable(false);
    addAndMakeVisible(_statusLabel);
    
    addAndMakeVisible(_welcomeLabel);
    _welcomeLabel.setColour(juce::Label::textColourId, viator::Colors::getViatorTextColor());
    _welcomeLabel.setJustificationType(juce::Justification::centred);
    _welcomeLabel.setText("Thank you for purchasing a Viator DSP product! I hope this product empowers your music-making flow and becomes a valuable tool in your creative arsenal. I've poured my passion and expertise into developing Viator DSP to inspire and enhance your musical journey!", juce::dontSendNotification);
    _welcomeLabel.setEditable(false);
    
    _discordBtn.setClickingTogglesState(false);
    addAndMakeVisible(_discordBtn);
    
    linkButton.setURL(link);
    addAndMakeVisible(linkButton);
    _discordBtn.onClick = [this]()
    {
        linkButton.triggerClick();
    };
    
    _submitButton.setClickingTogglesState(false);
    _submitButton.setButtonText(getunscrambledName(_submitName));
    addAndMakeVisible(_submitButton);
    
    _submitButton.onClick = [this]()
    {
        handleUnlockSuccess();
    };
    
    sendSynchronousChangeMessage();
}

PluginUnlocker::~PluginUnlocker()
{
}

void PluginUnlocker::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black.withAlpha(0.8f));
    auto unlockWidth = getWidth() * 0.66;
    auto unlockHeight = getHeight() * 0.66;
    auto rect = getLocalBounds().withSizeKeepingCentre(unlockWidth, unlockHeight);
    
    viator::Colors::setRainbowGradient(g, rect, 1.0f);
    g.drawRoundedRectangle(rect.toFloat(), 0.0f, 1.0f);
    g.setColour(viator::Colors::getPrimaryBGColor());
    g.fillRoundedRectangle(rect.toFloat(), 3.0f);
}

void PluginUnlocker::resized()
{
    // helpful vars
    auto unlockWidth = getWidth() * 0.66;
    auto unlockHeight = getHeight() * 0.66;
    auto rect = getLocalBounds().withSizeKeepingCentre(unlockWidth, unlockHeight);
    
    auto compX = rect.getX() + rect.getWidth() * 0.13;
    auto compY = rect.getY() + rect.getHeight() * 0.4;
    
    auto labelWidth = rect.getWidth() * 0.1;
    auto labelHeight = labelWidth * 0.3;
    
    auto inputWidth = rect.getWidth() * 0.55;
    auto inputHeight = labelHeight * 1.25;
    
    auto padding = 3.0;
    
    auto buttonWidth = rect.getWidth() * 0.1;
    auto buttonHeight = buttonWidth * 0.5;
    
    // license
    _inputFieldLabels[0]->setBounds(compX, compY, labelWidth, labelHeight);
    compX += labelWidth;
    _inputFields[0]->setBounds(compX, compY, inputWidth, inputHeight);
    compY += labelHeight * padding;
    
    _inputFieldLabels[1]->setBounds(_inputFieldLabels[0]->getX(), compY, labelWidth, labelHeight);
    _inputFields[1]->setBounds(_inputFields[0]->getX(), compY, inputWidth, inputHeight);
    compY += labelHeight * padding;
    compX += labelWidth * 2.22;
    for (auto& label : _inputFieldLabels)
    {
        label->setFont(juce::Font("Helvetica", rect.getHeight() * 0.03, juce::Font::FontStyleFlags::bold));
    }
    
    // submit button
    const auto discordX = getWidth() * 0.75;
    const auto discordY = getHeight() * 0.74;
    _submitButton.setBounds(compX, compY, buttonWidth, buttonHeight);
    _evaluateButton.setBounds(_inputFields[1]->getRight() - buttonWidth, compY, buttonWidth, buttonHeight);

    // status label
    _statusLabel.setBounds(_inputFields[0]->getX(), _submitButton.getBottom() + _inputFields[1]->getHeight(), _inputFields[1]->getWidth(), _inputFields[1]->getHeight() * 4.0);
    _statusLabel.setFont(juce::Font("Helvetica", rect.getHeight() * 0.03, juce::Font::FontStyleFlags::bold));
    
    // welcome label
    const auto welcomeY = compY * 0.33;
    const auto welcomeHeight = _inputFields[0]->getY() - welcomeY;
    _welcomeLabel.setBounds(_inputFieldLabels[0]->getX(), welcomeY, labelWidth * 2.0 + inputWidth, welcomeHeight);
    _welcomeLabel.setFont(juce::Font("Helvetica", rect.getHeight() * 0.03, juce::Font::FontStyleFlags::plain));
}

void PluginUnlocker::setInputFieldsProps()
{
    for (int i = 0; i < 2; ++i)
    {
        _inputFields.add(std::make_unique<juce::TextEditor>());
        _inputFields[i]->setMultiLine(true);
        _inputFields[i]->setColour(juce::TextEditor::ColourIds::outlineColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
        _inputFields[i]->setColour(juce::TextEditor::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
        _inputFields[i]->setColour(juce::TextEditor::ColourIds::highlightColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
        _inputFields[i]->getLookAndFeel().setColour(juce::TextEditor::ColourIds::textColourId, viator::Colors::getViatorTextColor());
        _inputFields[i]->setTextToShowWhenEmpty(i == 0 ? "your license..." : "your email...", viator::Colors::getViatorTextColor());
        addAndMakeVisible(*_inputFields[i]);
    }
}

void PluginUnlocker::setInputFieldsLabelsProps()
{
    for (int i = 0; i < 2; ++i)
    {
        _inputFieldLabels.add(std::make_unique<juce::Label>());
        _inputFieldLabels[i]->setColour(juce::Label::textColourId, viator::Colors::getViatorTextColor());
        _inputFieldLabels[i]->setText(i == 0 ? "License: " : "Email: ", juce::dontSendNotification);
        addAndMakeVisible(*_inputFieldLabels[i]);
    }
}

void PluginUnlocker::submitLicenseRequest(const juce::String& productLicense, const juce::String& userEmail)
{
    jassert(_productID != "");
    
    juce::URL url(getunscrambledName(_gumroadUrl.toString(false)));
    juce::String postData = juce::String(getunscrambledName(_productIdUrlPostData)) + _productID +
                            juce::String(getunscrambledName(_licenseUrlPostData)) + productLicense;
    
    std::unique_ptr<juce::InputStream> stream(url.withPOSTData(postData).createInputStream(juce::URL::InputStreamOptions (juce::URL::ParameterHandling::inAddress)
                                                                                           .withConnectionTimeoutMs (60000)
                                                                                           .withNumRedirectsToFollow (0)));
    readLicenseRequestResponse(url, postData, productLicense, userEmail);
}

void PluginUnlocker::handleUnlockSuccess()
{
    sendActionMessage("unlock");
}

void PluginUnlocker::handleUnlockFailure(const juce::String& message)
{
    _statusLabel.setText(message, juce::dontSendNotification);
    _licenseState = LicenseState::kLocked;
    sendActionMessage(getunscrambledName(_actionMessage));
}

void PluginUnlocker::insertXmlEntry(const juce::String& key, const juce::String& value)
{
    juce::XmlElement* paramElement = _xmlDoc->getChildByName(key);
    
    if (paramElement == nullptr)
    {
        juce::XmlElement* newElement = new juce::XmlElement(key);
        newElement->setAttribute(key, value);
        _xmlDoc->addChildElement(newElement);
    }
    
    else
    {
        paramElement->setAttribute(key, value);
    }
    
    setXmlLocation();
    saveXmlFile();
}

void PluginUnlocker::setXmlLocation()
{
    _xmlFile = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory).getChildFile(getunscrambledName(_periodName) + getScrambledName(_folderName));
    
    if (!_xmlFile.exists())
    {
        _xmlFile.createDirectory();
    }
}

void PluginUnlocker::saveXmlFile()
{
    juce::File fileToSave = _xmlFile.getChildFile(getScrambledName(_folderName) + getunscrambledName(_xmlExtension));
    _xmlDoc->writeTo(fileToSave);
}

int PluginUnlocker::getCurrentTrialTime()
{
    juce::String xmlData;
    juce::File xmlFile = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory).getChildFile(getunscrambledName(_periodName) + getScrambledName(_folderName))
                        .getChildFile(getScrambledName(_folderName) + getunscrambledName(_xmlExtension));
    if (!xmlFile.exists())
    {
        return 0;
    }
    
    std::unique_ptr<juce::FileInputStream> inputStream(xmlFile.createInputStream());
    if (inputStream != nullptr)
    {
        xmlData = inputStream->readEntireStreamAsString();
    }
    
    juce::XmlDocument xmlDoc(xmlData);
    
    if (xmlDoc.parse(xmlData))
    {
        auto rootElement = xmlDoc.getDocumentElement();
        
        if (rootElement != nullptr && rootElement->hasTagName(_folderName))
        {
            juce::XmlElement* cTE = rootElement->getChildByName(_trialTimeAttribute);
            
            if (cTE != nullptr)
            {
                juce::String result = cTE->getStringAttribute(_trialTimeAttribute);
                return std::stoi(result.toStdString());
            }
        }
    }
    
    return 0;
}

void PluginUnlocker::verifyLicense()
{
    DBG("Name: " << getunscrambledName(_periodName));
    auto extracted = extractNumericPrefix(_folderName);
    juce::String _attM = "";
    
    juce::String xmlData;
    juce::File xmlFile = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory).getChildFile(getunscrambledName(_periodName) + getScrambledName(_folderName))
                        .getChildFile(getScrambledName(_folderName) + getunscrambledName(_xmlExtension));
    
    std::unique_ptr<juce::FileInputStream> inputStream(xmlFile.createInputStream());
    if (inputStream != nullptr)
    {
        xmlData = inputStream->readEntireStreamAsString();
    }
    
    juce::XmlDocument xmlDoc(xmlData);
    
    if (xmlDoc.parse(xmlData))
    {
        auto rootElement = xmlDoc.getDocumentElement();
        
        if (rootElement != nullptr && rootElement->hasTagName(_folderName.removeCharacters(extracted)))
        {
            juce::XmlElement* mDE = rootElement->getChildByName(_machineIdAttribute);
            if (mDE != nullptr)
            {
                juce::String machineIDValue = mDE->getStringAttribute(_machineIdAttribute);
                _attM = machineIDValue;
            }
        }
    }

    // TODO: add dummy logic that checks the same things and "looks" like it sends an unlock action message
    auto machineID = getMachineID();
    if (verifyScrambledName(_attM, getMachineID()))
    {
        _fileExistsAndIsValid = true;
        insertXmlEntry(_machineIdAttribute, getScrambledName(getMachineID()));
        _licenseState = LicenseState::kUnlocked;
        sendActionMessage(getunscrambledName(_actionMessage));
    }
    
    else
    {
        if (_licenseState == LicenseState::kTrial) return;
        
        _licenseState = LicenseState::kLocked;
        
        auto message = getunscrambledName(_actionMessage);
        sendActionMessage(message);
    }
}

bool PluginUnlocker::getIsLicenseValid(const juce::String &userLicense)
{
    juce::String p = getunscrambledName(_licensePattern);

    for (int i = 0; i < p.length(); ++i)
    {
        if (p[i] == 'X')
        {
            if (!juce::CppTokeniserFunctions::isHexDigit(userLicense[i]))
                return false;
        }
        
        else if (p[i] != userLicense[i])
        {
            return false;
        }
    }

    return true;
}

juce::String PluginUnlocker::getMachineID()
{
    #if JUCE_MAC
        return juce::SystemStats::getMachineIdentifiers(juce::SystemStats::MachineIdFlags::uniqueId)[0];
    #elif JUCE_WINDOWS
        return juce::SystemStats::getMachineIdentifiers(juce::SystemStats::MachineIdFlags::legacyUniqueId)[0];
    #endif
}

juce::String PluginUnlocker::getScrambledName(const juce::String& nameToScramble)
{
    juce::MemoryBlock buffer (nameToScramble.toUTF8(), nameToScramble.length());
    return buffer.toBase64Encoding().toStdString();
}

juce::String PluginUnlocker::getunscrambledName(const juce::String& nameTounscramble)
{
    juce::MemoryBlock buffer (nameTounscramble.toUTF8(), nameTounscramble.length());
    
    if (buffer.fromBase64Encoding(nameTounscramble))
    {
        return buffer.toString();
    }
    
    return "could not unscamble";
}

bool PluginUnlocker::verifyScrambledName(const juce::String& scrambledName, const juce::String& correctName)
{
    juce::MemoryBlock buffer (correctName.toUTF8(), correctName.length());
    return buffer.toBase64Encoding().toStdString() == scrambledName;
}

void PluginUnlocker::setProductName(const juce::String& productName)
{
    _folderName = getScrambledName(productName).removeCharacters(".");
    auto extracted = extractNumericPrefix(_folderName);
    _xmlDoc = std::make_unique<juce::XmlElement>(_folderName.removeCharacters(extracted));
}

void PluginUnlocker::readLicenseRequestResponse(juce::URL url, juce::String postData, const juce::String& license, const juce::String& email)
{
    std::unique_ptr<juce::InputStream> stream(url.withPOSTData(postData).createInputStream(juce::URL::InputStreamOptions (juce::URL::ParameterHandling::inAddress)
                                                                                           .withConnectionTimeoutMs (60000)
                                                                                           .withNumRedirectsToFollow (0)));
    if (stream != nullptr)
    {
        juce::String result = stream->readEntireStreamAsString();
        juce::var jsonResult;
        
        if (juce::JSON::parse(result, jsonResult))
        {
            if (jsonResult.isObject())
            {
                dummyCheck(jsonResult, license, email);
                verifyLicenseRequestResponse(jsonResult, license, email);
                dummyCheck(jsonResult, license, email);
            }
        }
    }
}

void PluginUnlocker::verifyLicenseRequestResponse (juce::var& jsonResult, const juce::String& license, const juce::String& email)
{
//    juce::var successValue = jsonResult.getProperty(getunscrambledName(_successName), juce::var::undefined());
//    juce::var emailValue = jsonResult.getProperty(getunscrambledName(_purchaseName), juce::var::undefined()).getProperty(getunscrambledName(_emailName), juce::var::undefined());
//    juce::var licenseValue = jsonResult.getProperty(getunscrambledName(_purchaseName), juce::var::undefined()).getProperty(getunscrambledName(_licenseName), juce::var::undefined());
//    
//    auto licenseIsValid = emailValue.toString() == email && licenseValue.toString() == license;
//    
//    if (!successValue.isBool() || !emailValue.isString() || !licenseValue.isString())
//    {
//        handleUnlockFailure(getunscrambledName(_licenseFailMessage));
//        return;
//    }
//    
//    if (!successValue || !licenseIsValid)
//    {
//        handleUnlockFailure(getunscrambledName(_emailFailMessage));
//        return;
//    }
    
    handleUnlockSuccess();
}

void PluginUnlocker::dummyCheck(juce::var& jsonResult, const juce::String& license, const juce::String& email)
{
    const auto dummySize = 1000;
    juce::var successValue = jsonResult.getProperty(getunscrambledName(_successName), juce::var::undefined());
    juce::var emailValue = jsonResult.getProperty(getunscrambledName(_purchaseName), juce::var::undefined()).getProperty(getunscrambledName(_emailName), juce::var::undefined());
    juce::var licenseValue = jsonResult.getProperty(getunscrambledName(_purchaseName), juce::var::undefined()).getProperty(getunscrambledName(_licenseName), juce::var::undefined());
    
    for (int i = 0; i < dummySize; i++)
    {
        if (successValue.isBool() || emailValue.isString() || licenseValue.isString())
        {
            _unfriendlyMessage.clear();
            _unfriendlyMessage = "Validation successfull!";
        }
    }
}

juce::String PluginUnlocker::extractNumericPrefix(const juce::String& input)
{
    juce::String numberPart;

    for (auto character : input)
    {
        if (juce::CharacterFunctions::isDigit(character))
        {
            numberPart += character;
        }
        
        else
        {
            break;
        }
    }

    return numberPart;
}

juce::String PluginUnlocker::removeNumericPrefix(const juce::String& input)
{
    int index = 0;

    while (index < input.length() && juce::CharacterFunctions::isDigit(input[index]))
    {
        ++index;
    }

    return input.substring(index);
}

} // namespace

