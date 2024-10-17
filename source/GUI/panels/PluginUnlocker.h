#pragma once
#ifndef PluginUnlocker_h
#define PluginUnlocker_h

#include "../lookandfeel/Colors.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_gui_extra/juce_gui_extra.h"

namespace viator
{

class PluginUnlocker  : public juce::Component, public juce::ChangeBroadcaster, public juce::ActionBroadcaster
{
public:
    PluginUnlocker();
    ~PluginUnlocker() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setProductID(const juce::String productID){_productID = productID;};
    void setProductName(const juce::String& productName);
    void verifyLicense();
    void insertXmlEntry(const juce::String& key, const juce::String& value);
    void setXmlLocation();
    void saveXmlFile();
    int getCurrentTrialTime();
    
    enum class LicenseState
    {
        kLocked,
        kUnlocked,
        kTrial
    };
    
    LicenseState& getLicenseState(){return _licenseState;};
    void setLicenseState(LicenseState nVS){_licenseState = nVS;};
    
    juce::String gTS(){return _trialTimeAttribute;};

private:
    //juce::URL _gl {"https://api.gumroad.com/v2/licenses/verify"};
    juce::URL _gumroadUrl {"42.nQGcvMmNu7RXvklKmUWax8VXj4xXu01K1IyKrk1Xk41bkM2K1UlboYVd"};
    juce::String _productIdUrlPostData {"12.l.mbuQVciQ2WoQVO"};
    juce::String _licenseUrlPostData {"13.lvVZiUlayU1WqUVd8."};
    juce::TextEditor _licenseField;
    juce::Label _licenseLabel;
    juce::TextEditor _emailField;
    juce::Label _emailLabel;
    
    juce::Label _statusLabel;
    juce::TextButton _submitButton;
    juce::TextButton _evaluateButton;
    
    juce::Label _welcomeLabel;
    
    juce::TextButton _discordBtn {"Discord"};
    juce::HyperlinkButton linkButton;
    juce::URL link {"https://discord.gg/zcmjABjVn8"};
    
    juce::OwnedArray<juce::TextEditor> _inputFields;
    juce::OwnedArray<juce::Label> _inputFieldLabels;
    void setInputFieldsProps();
    void setInputFieldsLabelsProps();
    
    void submitLicenseRequest(const juce::String& productLicense, const juce::String& userEmail);
    bool getIsLicenseValid(const juce::String& userLicense);
    void handleUnlockSuccess();
    void handleUnlockFailure(const juce::String& message);
    
    juce::String _userSubmittedLicense {""};
    juce::String _userSubmittedEmail {""};
    juce::String _productID {""};
    juce::String _productName {""};
    juce::String getMachineID();
    juce::String getScrambledName(const juce::String& nameToScramble);
    bool verifyScrambledName(const juce::String& scrambledName, const juce::String& correctName);
    
    bool _fileExistsAndIsValid = false;
    
    LicenseState _licenseState = LicenseState::kLocked;
    
    juce::File _xmlFile;
    juce::String _folderName {""};
    std::unique_ptr<juce::XmlElement> _xmlDoc;
    juce::String _machineIdAttribute =  "MUEwQTJCYkMyRGRFZUZmRzMzSHhJaUpLbEw0TW1Obk9vUDVRcVJyU3NUNlV1VnZWeFc3WXlaejA5OF8";
    juce::String _trialTimeAttribute = "MUEwQTJCYkMyRGFZUZmRzMzSHhJaUpbEw0TW1Obk9vUDVRcVJyU3NUlV1VnZWeFc3WXlajA5OF8";
    
    void readLicenseRequestResponse(juce::URL url, juce::String postData, const juce::String& license, const juce::String& email);
    void verifyLicenseRequestResponse(juce::var& jsonResult, const juce::String& license, const juce::String& email);
    
    juce::String getunscrambledName(const juce::String& nameTounscramble);
    
    juce::String _unfriendlyMessage {"17.m8lY0M1Z48VcxMWYrYlX0QF"};
    juce::String _submitName {"6.SUmXskFc"};
    juce::String _evaluateName {"8.EYWXrUWXzUF"};
    juce::String _actionMessage {"12.igVXtcVYjMEcgQWY"};
    juce::String _genericInvalidMessage {"34.TgVYfjlal8FH48VcfTlazUlbkQFHoMGHt8FcfXWXrkFYt."};
    juce::String _successMessage {"22.VEFaoQVXzk1atAxb0M1XkM2blUGag."};
    juce::String _xmlExtension {"4.tfWarA"};
    juce::String _licensePattern {"35.XgEVXgEVXgUKXgEVXgEVXgUKXgEVXgEVXgUKXgEVXgEVXgE"};
    juce::String _successName {"7.yU2XiU1byA"};
    juce::String _purchaseName {"8.vUmbigVXyUF"};
    juce::String _emailName {"5.k0VXowF"};
    juce::String _licenseName {"11.rk1Xk41bk80ZkkG"};
    juce::String _licenseFailMessage {"56.TgVYfHWYiUVZ1UFYfPVXzEFHj8VYy41IzARagQ2XnABcnUFHkgGbkMFckQFHjEFcgABc4AWYy4B"};
    juce::String _emailFailMessage {"61.TgVZyARYsEVZrARZyAhauQGHgM2buMVZgQWYjAxcoQGZfDFHrk1Xk41bkAhYuIGHzgVZyABbx8FY0MFct."};
    juce::String _periodName {"1.t."};
    juce::String _xName {"3.mf0I"};
    
    void dummyCheck(juce::var& jsonResult, const juce::String& license, const juce::String& email);
    juce::String extractNumericPrefix(const juce::String& input);
    juce::String removeNumericPrefix(const juce::String& input);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginUnlocker)
};

}

#endif
