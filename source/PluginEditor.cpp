#include "PluginEditor.h"

PluginEditor::PluginEditor(PluginProcessor &p)
    : AudioProcessorEditor(&p), audio_processor(p)
{
    addAndMakeVisible(input_meter);
    addAndMakeVisible(output_meter);

    init_editors();
    init_page_buttons();
    init_hq_menu();
    init_stereo_menu();
    initSliders();
    init_tooltip_window();

    audio_processor.get_preset_browser().setColour(juce::ComboBox::ColourIds::textColourId,
                                                   viator::colors::monster_text_color);
    audio_processor.get_preset_browser().getLookAndFeel().setColour(juce::PopupMenu::textColourId,
                                                                    viator::colors::monster_text_color);
    addAndMakeVisible(audio_processor.get_preset_browser());

    init_buttons();

    addAndMakeVisible(info_panel);
    info_panel.setVisible(false);
    settings_button->onClick = [this]()
    {
        info_panel.setVisible(settings_button->getToggleState());
        module_editors[0]->setVisible(!settings_button->getToggleState());
    };

    startTimerHz(30);

    const auto saved_width = static_cast<int>(audio_processor.getVariableTree().getProperty("width"));
    const auto saved_height = static_cast<int>(audio_processor.getVariableTree().getProperty("height"));

    // WINDOW SIZE INITIALIZATION
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(2.0f);
    setResizeLimits(600,300,1800,900);
    setSize(saved_width == 0 ? 1000 : saved_width, saved_height == 0 ? 500 : saved_height);
}

PluginEditor::~PluginEditor()
{
    if (auto *preamp = dynamic_cast<viator::PreampEditor *>(module_editors[0].get()))
    {
        preamp->removeActionListener(this);
        preamp->removeMouseListener(this);
    }

    for (const auto &button : page_buttons)
    {
        button->setLookAndFeel(nullptr);
    }

    for (const auto &slider : sliders)
    {
        slider->removeMouseListener(this);
        slider->setLookAndFeel(nullptr);
    }

    power_button->removeMouseListener(this);
    settings_button->removeMouseListener(this);
    preset_a_button->removeMouseListener(this);
    preset_b_button->removeMouseListener(this);

    stereo_menu.setLookAndFeel(nullptr);
    stereo_menu.removeMouseListener(this);
    hq_menu.setLookAndFeel(nullptr);
    hq_menu.removeMouseListener(this);

    module_editors.clear();

    stopTimer();
}

void PluginEditor::paint(juce::Graphics &g)
{
    // BACKGROUND IMAGE
    const auto background_image =
        juce::ImageCache::getFromMemory(BinaryData::lofitexture_png,
                                        BinaryData::lofitexture_pngSize);
    g.drawImageWithin(
        background_image, 0, 0, getWidth(), getHeight(),
        juce::RectanglePlacement::stretchToFit);

    // LOGO
    const auto logo_width = getWidth() * 0.25;
    const auto logo_height = logo_width * 0.2182;
    const auto logo = juce::ImageCache::getFromMemory(BinaryData::landon_png, BinaryData::landon_pngSize);
    g.drawImageWithin(
        logo, 0, 0,
        static_cast<int>(logo_width), static_cast<int>(logo_height),
        juce::RectanglePlacement::stretchToFit);

    // BACKGROUND COLOR
    g.setColour(juce::Colours::black.withAlpha(0.3f));
    g.fillRect(getLocalBounds());
}

void PluginEditor::resized()
{
    // EDITORS POSITIONS
    auto compY = static_cast<int>(getHeight() * 0.15);
    module_editors[0]->setBounds(getLocalBounds()
                                     .withSizeKeepingCentre(static_cast<int>(getWidth() * 0.9),
                                                            static_cast<int>(getHeight() * 0.7))
                                     .withY(compY));

    auto presetX = juce::roundToInt(getWidth() * 0.35);
    auto presetY = juce::roundToInt(getHeight() * 0.025);
    auto presetWidth = juce::roundToInt(getWidth() * 0.3);
    const auto presetHeight = juce::jmax(static_cast<int>(getHeight() * 0.06), 23);
    audio_processor.get_preset_browser().setBounds(presetX, presetY, presetWidth, presetHeight);

    presetWidth = juce::roundToInt(getWidth() * 0.1);
    presetX += juce::roundToInt(getWidth() * 0.32);
    stereo_menu.setBounds(presetX, presetY, presetWidth, presetHeight);

    presetX += juce::roundToInt(getWidth() * 0.12);
    hq_menu.setBounds(presetX, presetY, presetWidth, presetHeight);

    presetX += juce::roundToInt(getWidth() * 0.12);
    presetY = juce::roundToInt(getHeight() * 0.03);
    presetWidth = juce::roundToInt(getWidth() * 0.023);
    power_button->setBounds(presetX, presetY, presetWidth, presetWidth);

    const auto settings_size = juce::roundToInt(getWidth() * 0.04);
    presetX = juce::roundToInt(getWidth() - getWidth() * 0.08);
    presetY = 0;
    settings_button->setBounds(presetX, presetY, settings_size * 2.5, settings_size);

    presetX = juce::roundToInt(getWidth() * 0.27);
    presetY = juce::roundToInt(getHeight() * 0.03);
    preset_a_button->setBounds(presetX, presetY, presetWidth, presetWidth);

    presetX += juce::roundToInt(getWidth() * 0.036);
    preset_b_button->setBounds(presetX, presetY, presetWidth, presetWidth);

    auto compX = 0;
    compY = juce::roundToInt(getHeight() * 0.36);
    auto compWidth = juce::roundToInt(getWidth() * 0.053);
    auto compHeight = juce::roundToInt(getHeight() * 0.35);

    sliders[0]->setBounds(compX, compY, compWidth, compHeight);
    sliders[0]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, compWidth, 32);

    compX = getWidth() - compWidth;
    sliders[1]->setBounds(compX, compY, compWidth, compHeight);
    sliders[1]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, compWidth, 32);

    compX = juce::roundToInt(getWidth() * 0.024);
    compY = juce::roundToInt(getHeight() * 0.36);
    compWidth = juce::roundToInt(getWidth() * 0.006);
    compHeight = juce::roundToInt(getHeight() * 0.315);
    input_meter.setBounds(compX, compY, compWidth, compHeight);

    compX = sliders[1]->getX() + juce::roundToInt((sliders[1]->getWidth() * 0.45) + 1);
    compWidth = juce::roundToInt(sliders[1]->getWidth() * 0.1);
    output_meter.setBounds(compX, compY, compWidth, compHeight);

    info_panel.setBounds(getLocalBounds().withSizeKeepingCentre(juce::roundToInt(getWidth() * 0.9), static_cast<int>(getHeight() * 0.8)));

    tooltip_window.setBounds(getLocalBounds().removeFromBottom(juce::roundToInt(getHeight() * 0.145)));
    tooltip_window.setFont(viator::Fonts::regular(static_cast<float>(getHeight()) * 0.03f, 0.15f));

    audio_processor.getVariableTree().setProperty("width", getWidth(), nullptr);
    audio_processor.getVariableTree().setProperty("height", getHeight(), nullptr);
}

void PluginEditor::init_page_buttons()
{
    juce::StringArray button_texts = {"Saturation"};

    for (int i = 0; i < button_texts.size(); ++i)
    {
        page_buttons.emplace_back(std::make_unique<juce::TextButton>());
        page_buttons[i]->setButtonText(button_texts[i]);
        page_buttons[i]->setRadioGroupId(page_button_radio_id);
        page_buttons[i]->setClickingTogglesState(true);
        page_buttons[i]->setColour(juce::TextButton::ColourIds::buttonColourId,
                                   juce::Colours::black.withAlpha(0.25f));
        page_buttons[i]->setColour(juce::TextButton::ColourIds::buttonOnColourId,
                                   juce::Colour(161, 121, 83));
        page_buttons[i]->setColour(juce::ComboBox::ColourIds::outlineColourId,
                                   juce::Colour(120, 130, 140));
        page_buttons[i]->setLookAndFeel(&text_button_laf);
        addAndMakeVisible(*page_buttons[i]);

        // EDITOR SHOW/HIDE LOGIC
        page_buttons[i]->onClick = [this, i]()
        {
            close_editors();
            module_editors[i]->setVisible(true);
        };
    }

    page_buttons[0]->setToggleState(true, juce::sendNotification);
}

void PluginEditor::init_editors()
{
    module_editors.emplace_back(std::make_unique<viator::PreampEditor>(audio_processor));

    for (auto &module_editor : module_editors)
    {
        addAndMakeVisible(*module_editor);
        module_editor->addMouseListener(this, true);
        module_editor->setVisible(false);
    }

    if (auto *preamp = dynamic_cast<viator::PreampEditor *>(module_editors[0].get()))
    {
        preamp->addActionListener(this);
    }
}

void PluginEditor::close_editors() const
{
    for (auto &editor : module_editors)
    {
        editor->setVisible(false);
    }
}

void PluginEditor::actionListenerCallback(const juce::String &message)
{
    if (message == "unlock")
    {
        resized();
    }

    if (message == "sliderChanged")
    {
        if (auto *preamp = dynamic_cast<viator::PreampEditor *>(module_editors[0].get()))
        {
            const auto &sliders = preamp->getSliders();

            for (const auto &slider : sliders)
            {
                save_preset(slider->getComponentID(), static_cast<float>(slider->getValue()));
            }
        }
    }
}

void PluginEditor::init_hq_menu()
{
    // PROPERTIES
    const juce::StringArray choices = {"HQ Off", "HQ X2", "HQ X4", "HQ X8", "HQ X16"};

    for (int i = 0; i < choices.size(); ++i)
    {
        hq_menu.addItem(choices[i], i + 1);
    }

    hq_menu.setColour(juce::ComboBox::ColourIds::textColourId, viator::colors::monster_text_color);
    hq_menu.getLookAndFeel().setColour(juce::PopupMenu::textColourId, viator::colors::monster_text_color);
    hq_menu.addMouseListener(this, false);

    hq_menu.setTooltip("Select the level of oversampling to reduce aliasing and improve audio quality. Higher "
                       "settings (up to 16x) provide cleaner, more accurate processing at the cost of increased "
                       "CPU usage.");

    hq_menu.setLookAndFeel(&menuLAF);
    addAndMakeVisible(hq_menu);

    // LOGIC
    hq_menu.onChange = [this]()
    {
        audio_processor.set_hq_mode(static_cast<PluginProcessor::HQMode>(hq_menu.getSelectedId() - 1));
        audio_processor.getVariableTree().setProperty("hqMenu", hq_menu.getSelectedId() - 1, nullptr);
        save_preset("hqMenu", static_cast<float>(hq_menu.getSelectedId()));
    };

    // INIT SAVED STATE
    const auto saved_menu_state = static_cast<int>(audio_processor.getVariableTree().getProperty("hqMenu")) + 1;
    hq_menu.setSelectedId(saved_menu_state);
    audio_processor.getPresetA()["hqMenu"] = static_cast<float>(saved_menu_state);
    audio_processor.getPresetB()["hqMenu"] = static_cast<float>(saved_menu_state);
}

void PluginEditor::init_stereo_menu()
{
    // PROPERTIES
    const juce::StringArray choices = {"Stereo", "Mono", "Mid", "Side"};

    for (int i = 0; i < choices.size(); ++i)
    {
        stereo_menu.addItem(choices[i], i + 1);
    }

    stereo_menu.setColour(juce::ComboBox::ColourIds::textColourId, viator::colors::monster_text_color);
    stereo_menu.getLookAndFeel().setColour(juce::PopupMenu::textColourId, viator::colors::monster_text_color);
    stereo_menu.setComponentID("stereoMenu");
    stereo_menu.addMouseListener(this, false);

    stereo_menu.setTooltip("Choose the processing mode for your signal. Stereo applies effects to the full stereo "
                           "field, Mono sums the signal to mono for centered processing, Mid targets the center "
                           "of the stereo field, and Sides focuses on the outer edges, allowing precise control "
                           "over the spatial characteristics of your sound.");

    stereo_menu.setLookAndFeel(&menuLAF);
    addAndMakeVisible(stereo_menu);

    // LOGIC
    stereo_menu.onChange = [this]()
    {
        audio_processor.set_stereo_mode(static_cast<PluginProcessor::StereoMode>(stereo_menu.getSelectedId() - 1));
        audio_processor.getVariableTree().setProperty("stereoMenu", stereo_menu.getSelectedId() - 1, nullptr);
        save_preset("stereoMenu", static_cast<float>(stereo_menu.getSelectedId()));
    };

    // INIT SAVED STATE
    const auto saved_menu_state = static_cast<int>(audio_processor.getVariableTree().getProperty("stereoMenu")) + 1;
    stereo_menu.setSelectedId(saved_menu_state);
    audio_processor.getPresetA()["stereoMenu"] = static_cast<float>(saved_menu_state);
    audio_processor.getPresetB()["stereoMenu"] = static_cast<float>(saved_menu_state);
}

void PluginEditor::setControlButtonProps(std::unique_ptr<juce::DrawableButton> &button,
                                         const juce::Drawable *offImage,
                                         const juce::Drawable *onImage,
                                         const juce::String &name)
{
    button = std::make_unique<juce::DrawableButton>(name,
                                                    juce::DrawableButton::ButtonStyle::ImageStretched);
    button->setClickingTogglesState(true);
    button->setImages(offImage, nullptr, nullptr, nullptr, onImage);
    button->setColour(juce::DrawableButton::ColourIds::backgroundColourId, juce::Colour());
    button->setColour(juce::DrawableButton::ColourIds::backgroundOnColourId, juce::Colour());
    addAndMakeVisible(button.get());
}

void PluginEditor::initSliders()
{
    const juce::StringArray slider_ids = {ViatorParameters::inputID, ViatorParameters::outputID};
    const juce::StringArray slider_names = {ViatorParameters::inputName, ViatorParameters::outputName};

    for (int i = 0; i < 2; ++i)
    {
        sliders.emplace_back(std::make_unique<juce::Slider>());
        sliderAtts.emplace_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
                                    (audio_processor.get_tree_state(), slider_ids[i], *sliders[i]));
        sliders[i]->setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        sliders[i]->setName(slider_names[i]);
        sliders[i]->setComponentID(slider_ids[i]);
        sliders[i]->setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::transparentBlack);
        sliders[i]->addMouseListener(this, false);
        sliders[i]->setLookAndFeel(&faderLAF);
        addAndMakeVisible(*sliders[i]);
    }

    sliders[0]->setTooltip("Control the overall input level with the Global Input knob. Increase to drive the "
                           "signal harder into the processing chain for more intense effects, or decrease to "
                           "maintain headroom and prevent distortion.");

    sliders[1]->setTooltip("Adjust the overall output level with the Global Output knob. Use this to fine-tune "
                           "the final volume after all processing, ensuring a balanced signal that matches your "
                           "desired loudness while avoiding clipping or distortion.");

    // LOGIC
    sliders[0]->onValueChange = [this]()
    {
        applyInputToDriveViewer();
        save_preset(sliders[0]->getComponentID(), static_cast<float>(sliders[0]->getValue()));
    };

    applyInputToDriveViewer();

    // LOGIC
    sliders[1]->onValueChange = [this]()
    {
        applyOutputToDriveViewer();
        save_preset(sliders[1]->getComponentID(), static_cast<float>(sliders[1]->getValue()));
    };

    applyOutputToDriveViewer();
}

void PluginEditor::applyInputToDriveViewer() const
{
    if (auto *preamp = dynamic_cast<viator::PreampEditor *>(module_editors[0].get()))
    {
        const auto slider_value = static_cast<float>(sliders[0]->getValue());
        preamp->getViewer().set_global_input(slider_value);
    }
}

void PluginEditor::applyOutputToDriveViewer() const
{
    if (auto *preamp = dynamic_cast<viator::PreampEditor *>(module_editors[0].get()))
    {
        const auto slider_value = static_cast<float>(sliders[1]->getValue());
        preamp->getViewer().set_global_output(slider_value);
    }
}

void PluginEditor::timerCallback()
{
    input_meter.setLevel(audio_processor.GetInputLevel());
    output_meter.setLevel(audio_processor.GetOutputLevel());
}

void PluginEditor::init_buttons()
{
    const std::unique_ptr<juce::Drawable> powerOff{
        juce::Drawable::createFromImageData(BinaryData::fadpowerswitch_svg,
                                            BinaryData::fadpowerswitch_svgSize)};
    const std::unique_ptr<juce::Drawable> powerOn{
        juce::Drawable::createFromImageData(BinaryData::fadpowerswitch_svg,
                                            BinaryData::fadpowerswitch_svgSize)};
    powerOff->replaceColour(juce::Colours::black, juce::Colour(120, 130, 140));
    powerOn->replaceColour(juce::Colours::black, juce::Colour(255, 255, 90));
    setControlButtonProps(power_button, powerOff.get(), powerOn.get(), "Power");
    power_att =
        std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            audio_processor.get_tree_state(),
            ViatorParameters::pluginPowerID, *power_button);

    const std::unique_ptr<juce::Drawable> settingsOff{
        juce::Drawable::createFromImageData(BinaryData::info_svg,
                                            BinaryData::info_svgSize)};
    const std::unique_ptr<juce::Drawable> settingsOn{
        juce::Drawable::createFromImageData(BinaryData::info_svg,
                                            BinaryData::info_svgSize)};
    settingsOff->replaceColour(juce::Colour(233, 224, 52), juce::Colour(120, 130, 140));
    settingsOn->replaceColour(juce::Colour(233, 224, 52), juce::Colour(255, 255, 90));
    setControlButtonProps(settings_button, settingsOff.get(), settingsOn.get(), "Settings");

    const std::unique_ptr<juce::Drawable> aOff{
        juce::Drawable::createFromImageData(BinaryData::fadpreseta_svg,
                                            BinaryData::fadpreseta_svgSize)};
    const std::unique_ptr<juce::Drawable> aOn{
        juce::Drawable::createFromImageData(BinaryData::fadpreseta_svg,
                                            BinaryData::fadpreseta_svgSize)};
    aOff->replaceColour(juce::Colours::black, juce::Colour(120, 130, 140));
    aOn->replaceColour(juce::Colours::black, juce::Colour(255, 255, 90));
    setControlButtonProps(preset_a_button, aOff.get(), aOn.get(), "A");

    const std::unique_ptr<juce::Drawable> bOff{
        juce::Drawable::createFromImageData(BinaryData::fadpresetb_svg,
                                            BinaryData::fadpresetb_svgSize)};
    const std::unique_ptr<juce::Drawable> bOn{
        juce::Drawable::createFromImageData(BinaryData::fadpresetb_svg,
                                            BinaryData::fadpresetb_svgSize)};
    bOff->replaceColour(juce::Colours::black, juce::Colour(120, 130, 140));
    bOn->replaceColour(juce::Colours::black, juce::Colour(255, 255, 90));
    setControlButtonProps(preset_b_button, bOff.get(), bOn.get(), "B");

    power_button->addMouseListener(this, false);
    power_button->setTooltip("Enable or disable audio processing globally.");

    settings_button->addMouseListener(this, false);
    settings_button->setTooltip("More info, links to documents, support, and other stuff.");

    preset_a_button->setRadioGroupId(1000);
    preset_a_button->addMouseListener(this, false);
    preset_a_button->setTooltip("Switch to preset A. While A is selected, all changes are recorded into A.");
    preset_b_button->setRadioGroupId(1000);
    preset_b_button->addMouseListener(this, false);
    preset_b_button->setTooltip("Switch to preset B. While B is selected, all changes are recorded into B.");

    preset_a_button->setToggleState(true, juce::sendNotification);

    preset_a_button->onClick = [this]()
    {
        apply_preset(true);
    };

    preset_b_button->onClick = [this]()
    {
        apply_preset(false);
    };
}

void PluginEditor::apply_preset(const bool isPresetA)
{
    auto &preset_map = isPresetA ? audio_processor.getPresetA() : audio_processor.getPresetB();
    const auto &tree = audio_processor.get_tree_state();

    for (const auto &item : preset_map)
    {
        tree.getParameterAsValue(item.first) = item.second;
    }

    stereo_menu.setSelectedId(static_cast<int>(preset_map["stereoMenu"]), juce::sendNotification);
    hq_menu.setSelectedId(static_cast<int>(preset_map["hqMenu"]), juce::sendNotification);
}

void PluginEditor::save_preset(const juce::String &param, const float paramValue) const
{
    auto &preset_map = preset_a_button->getToggleState() ? audio_processor.getPresetA() : audio_processor.getPresetB();
    preset_map[param] = paramValue;
}

void PluginEditor::init_tooltip_window()
{
    tooltip_window.setJustificationType(juce::Justification::centred);
    tooltip_window.setColour(juce::Label::ColourIds::textColourId, viator::colors::monster_text_color);
    tooltip_window.setEditable(false);
    addAndMakeVisible(tooltip_window);
}

void PluginEditor::mouseEnter(const juce::MouseEvent &e)
{
    if (const auto slider = dynamic_cast<juce::Slider*>(e.eventComponent))
    {
        tooltip_window.setText(slider->getTooltip(), juce::dontSendNotification);
    }

    if (const auto menu = dynamic_cast<juce::ComboBox*>(e.eventComponent))
    {
        tooltip_window.setText(menu->getTooltip(), juce::dontSendNotification);
    }

    if (const auto button = dynamic_cast<juce::DrawableButton*>(e.eventComponent))
    {
        tooltip_window.setText(button->getTooltip(), juce::dontSendNotification);
    }
}

void PluginEditor::mouseExit(const juce::MouseEvent &e)
{
    if (auto slider = dynamic_cast<juce::Slider*>(e.eventComponent))
    {
        tooltip_window.setText("", juce::dontSendNotification);
    }

    if (auto menu = dynamic_cast<juce::ComboBox*>(e.eventComponent))
    {
        tooltip_window.setText("", juce::dontSendNotification);
    }

    if (auto button = dynamic_cast<juce::DrawableButton*>(e.eventComponent))
    {
        tooltip_window.setText("", juce::dontSendNotification);
    }
}