#include "SliderLAF.h"

namespace viator
{

CustomDial::CustomDial()
{
    
}
void CustomDial::drawRotarySlider
(
 juce::Graphics &g,
    int x,
    int y,
    int width,
    int height,
    float sliderPos,
    float rotaryStartAngle,
    float rotaryEndAngle,
 juce::Slider &slider
)
{
    _sliderName = slider.getName();

    const auto reduction_amount = static_cast<float>(static_cast<float>(width) * 0.03f);
    const auto dialBounds =
        juce::Rectangle<int> (x, y, width, height)
        .toFloat().reduced(reduction_amount, reduction_amount);

    auto centre = dialBounds.getCentre();
    constexpr float sizeScalar = 0.6f;
    auto fullRadius =
        juce::jmin (dialBounds.getWidth() * sizeScalar, dialBounds.getHeight() * sizeScalar);

    /** Dot color*/
    g.setColour (muted_white);
    centre = dialBounds.getCentre();

    /** Draw dots */
    constexpr int num_dots = 12;
    for (int i = 0; i < num_dots; ++i)
    {
        const float dotSize = static_cast<float>(width) * 0.025f;

        /** IF you change the number of dots, do i / (num dots - 1) */
        const auto angle =
            juce::jmap (static_cast<float>(i) / static_cast<float>((num_dots - 1)),
                rotaryStartAngle, rotaryEndAngle);

        /** Dot distance from slider center */
        const auto point =
            centre.getPointOnCircumference
            (fullRadius - static_cast<float>(width) * 0.06f, angle);

        /** Dot thickness*/
        g.fillEllipse (point.getX() - 1, point.getY() - 1, dotSize, dotSize);
    }

    fullRadius -= static_cast<float>(width) / 14.5f;

    const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    /** Track thickness*/
    const float lineWidthMultiplier = static_cast<float>(width) * 0.035f;
    const auto lineWidth = juce::jmin (lineWidthMultiplier, fullRadius * 0.5f);

    const auto dialRadius = fullRadius - 3.0f * lineWidth;
    g.setColour(juce::Colours::transparentBlack);
    g.fillEllipse (centre.getX() - dialRadius,
        centre.getY() - dialRadius,
        dialRadius * 2.0f,
        dialRadius * 2.0f);

    /** Dial outline color*/
    g.setColour (muted_white);

    constexpr auto scale = 2.0f;

    /** Dial outline thickness*/
    g.drawEllipse (centre.getX() - dialRadius,
        centre.getY() - dialRadius,
        dialRadius * scale,
        dialRadius * scale,
        lineWidth * 0.5f);

    /** Dial tick color*/
    g.setColour (gold);
    juce::Path dialTick;
    dialTick.startNewSubPath (centre.getPointOnCircumference (dialRadius - lineWidth, toAngle));

    /** Dial tick length*/
    dialTick.lineTo (centre.getPointOnCircumference ((dialRadius - lineWidth) * 0.6f, toAngle));

    /** Dial tick thickness*/
    g.strokePath (dialTick, juce::PathStrokeType (lineWidth * 0.75f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    _sliderWidth = slider.getWidth();
}

void CustomDial::drawLabel (juce::Graphics& g, juce::Label& label)
{
    g.fillAll (label.findColour (juce::Label::backgroundColourId));

    label.setEditable(true);
    
    if (! label.isBeingEdited())
    {
        const auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const auto font (viator::Fonts::bold(static_cast<float>(_sliderWidth) * 0.1f));

        g.setColour (label.findColour (juce::Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);

        const auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());
        
        juce::String labelText;
        if (auto* parentComponent = label.getParentComponent())
        {
            if (const auto* slider = dynamic_cast<juce::Slider*>(parentComponent))
            {
                // Check if the mouse is over the slider
                const bool isMouseOver = slider->isMouseOver() || slider->isMouseButtonDown();
                
                // Get the slider value and suffix
                float value;
                
                if (_dialValueType == ValueType::kInt)
                {
                    value = static_cast<int>(slider->getValue());
                }
                
                else
                {
                    value = slider->getValue();
                }
                
                const juce::String suffix = slider->getTextValueSuffix();
                
                // Determine the text to display based on the mouse over state
                if (isMouseOver)
                {

                    labelText = juce::String(getRoundedValue(value)) + suffix;
                }

                else
                {
                    labelText = slider->getName();
                }
            }
        }
        
        g.drawFittedText (labelText, textArea, label.getJustificationType(),
                          juce::jmax (1, static_cast<int>(static_cast<float>(textArea.getHeight()) / font.getHeight())),
                          label.getMinimumHorizontalScale());

        g.setColour (label.findColour (juce::Label::outlineColourId).withMultipliedAlpha (alpha));
    }
}

float CustomDial::getRoundedValue(float input) {
    return std::ceil(input * 100.0f) / 100.0f;
}

ChickenHeadDial::ChickenHeadDial()
{

}
void ChickenHeadDial::drawRotarySlider
(
 juce::Graphics &g,
 int x,
 int y,
 int width,
 int height,
 float sliderPos,
 float rotaryStartAngle,
 float rotaryEndAngle,
 juce::Slider &slider
)
{
    _sliderName = slider.getName();

    const auto reduction_amount = static_cast<float>(width) * 0.03f;
    const auto dialBounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(reduction_amount, reduction_amount);

    auto centre = dialBounds.getCentre();
    constexpr float sizeScalar = 0.7f;
    auto fullRadius = juce::jmin(dialBounds.getWidth() * sizeScalar, dialBounds.getHeight() * sizeScalar);

    g.setColour(muted_white);
    centre = dialBounds.getCentre();

    /** Draw dots */
    constexpr int num_dots = 12;
    for (int i = 0; i < num_dots; ++i)
    {
        const float dotSize = static_cast<float>(width) * 0.025f;

        /** IF you change the number of dots, do i / (num dots - 1) */
        const auto angle = juce::jmap(static_cast<float>(i) / static_cast<float>((num_dots - 1)), rotaryStartAngle, rotaryEndAngle);

        /** Dot distance from slider center */
        const auto point = centre.getPointOnCircumference(fullRadius - static_cast<float>(width) * 0.15f, angle);

        /** Dot thickness */
        g.fillEllipse(point.getX() - 1, point.getY() - 1, dotSize, dotSize);
    }

    fullRadius -= static_cast<float>(width) / 14.5f;

    const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    const float lineWidthMultiplier = static_cast<float>(width) * 0.035f;
    const auto lineWidth = juce::jmin(lineWidthMultiplier, fullRadius * 0.5f);

    const auto dialRadius = fullRadius - 3.0f * lineWidth;
    g.setColour(juce::Colours::transparentBlack);
    g.fillEllipse(centre.getX() - dialRadius,
                  centre.getY() - dialRadius,
                  dialRadius * 2.0f,
                  dialRadius * 2.0f);

    g.setColour(muted_white);

    constexpr auto scale = 1.0f;

    // Define the dimensions and position of the rounded rectangle
    float rectWidth = width * 0.2f; // 10% of the component's width
    float rectHeight = height * 0.6f; // 30% of the component's height
    float rectRadius = rectWidth * 0.25f; // Radius for rounded corners

    // Create a Path for the rounded rectangle
    juce::Path dialRect;
    dialRect.addRoundedRectangle(-rectWidth / 2, -rectHeight / 2, rectWidth, rectHeight, rectRadius);

    // Apply rotation based on the dial value
    float angle = toAngle; // Use the calculated angle
    juce::AffineTransform transform = juce::AffineTransform::rotation(angle)
        .translated(centre.getX(), centre.getY());
    dialRect.applyTransform(transform);

    // Draw the rounded rectangle
    g.strokePath(dialRect, juce::PathStrokeType(2.0f));

    /** Dial tick color*/
    g.setColour (gold);
    juce::Path dialTick;
    dialTick.startNewSubPath (centre.getPointOnCircumference (fullRadius * 0.3f, toAngle));

    /** Dial tick length*/
    dialTick.lineTo (centre.getPointOnCircumference ((dialRadius - lineWidth) * 0.65f, toAngle));

    /** Dial tick thickness*/
    g.strokePath (dialTick, juce::PathStrokeType (lineWidth * 0.75f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    _sliderWidth = slider.getWidth();
}


void ChickenHeadDial::drawLabel (juce::Graphics& g, juce::Label& label)
{
    g.fillAll (label.findColour (juce::Label::backgroundColourId));

    label.setEditable(true);

    if (! label.isBeingEdited())
    {
        const auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const auto font (viator::Fonts::bold(static_cast<float>(_sliderWidth) * 0.1f));

        g.setColour (label.findColour (juce::Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);

        const auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

        juce::String labelText;
        if (auto* parentComponent = label.getParentComponent())
        {
            if (const auto* slider = dynamic_cast<juce::Slider*>(parentComponent))
            {
                // Check if the mouse is over the slider
                const bool isMouseOver = slider->isMouseOver() || slider->isMouseButtonDown();

                // Get the slider value and suffix
                float value;

                if (_dialValueType == ValueType::kInt)
                {
                    value = static_cast<int>(slider->getValue());
                }

                else
                {
                    value = slider->getValue();
                }

                const juce::String suffix = slider->getTextValueSuffix();

                // Determine the text to display based on the mouse over state
                if (isMouseOver)
                {
                    if (std::fmod(value, 1.0) == 0.0) {
                        labelText = juce::String(static_cast<int>(value)) + ".00 " + suffix;
                    }

                    else {
                        labelText = juce::String(getRoundedValue(value)) + suffix;
                    }
                }
                else
                {
                    labelText = slider->getName();
                }
            }
        }

        g.drawFittedText (labelText, textArea, label.getJustificationType(),
                          juce::jmax (1, static_cast<int>(static_cast<float>(textArea.getHeight()) / font.getHeight())),
                          label.getMinimumHorizontalScale());

        g.setColour (label.findColour (juce::Label::outlineColourId).withMultipliedAlpha (alpha));
    }
}

float ChickenHeadDial::getRoundedValue(float input) {
    return std::ceil(input * 100.0f) / 100.0f;
}

WaveyDial::WaveyDial()
{

}
void WaveyDial::drawRotarySlider
(
 juce::Graphics &g,
    int x,
    int y,
    int width,
    int height,
    float sliderPos,
    float rotaryStartAngle,
    float rotaryEndAngle,
 juce::Slider &slider
)
{
    _sliderName = slider.getName();

    const auto reduction_amount = static_cast<float>(static_cast<float>(width) * 0.03f);
    const auto dialBounds =
        juce::Rectangle<int> (x, y, width, height)
        .toFloat().reduced(reduction_amount, reduction_amount);

    auto centre = dialBounds.getCentre();
    constexpr float sizeScalar = 0.6f;
    auto fullRadius =
        juce::jmin (dialBounds.getWidth() * sizeScalar, dialBounds.getHeight() * sizeScalar);

    /** Dot color*/
    g.setColour (muted_white);
    centre = dialBounds.getCentre();

    /** Draw dots */
    constexpr int num_dots = 12;
    for (int i = 0; i < num_dots; ++i)
    {
        const float dotSize = static_cast<float>(width) * 0.025f;

        /** IF you change the number of dots, do i / (num dots - 1) */
        const auto angle =
            juce::jmap (static_cast<float>(i) / static_cast<float>((num_dots - 1)),
                rotaryStartAngle, rotaryEndAngle);

        /** Dot distance from slider center */
        const auto point =
            centre.getPointOnCircumference
            (fullRadius - static_cast<float>(width) * 0.06f, angle);

        /** Dot thickness*/
        g.fillEllipse (point.getX() - 1, point.getY() - 1, dotSize, dotSize);
    }

    fullRadius -= static_cast<float>(width) / 14.5f;

    const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    /** Track thickness*/
    const float lineWidthMultiplier = static_cast<float>(width) * 0.035f;
    const auto lineWidth = juce::jmin (lineWidthMultiplier, fullRadius * 0.5f);

    const auto dialRadius = fullRadius - 3.0f * lineWidth;
    g.setColour(juce::Colours::transparentBlack);
    g.fillEllipse (centre.getX() - dialRadius,
        centre.getY() - dialRadius,
        dialRadius * 2.0f,
        dialRadius * 2.0f);

    /** Dial outline color*/
    g.setColour (muted_white);

    constexpr auto scale = 2.0f;

    // WAVEY CIRCLE
    juce::Path wavyPath;

    const float twoPi = juce::MathConstants<float>::twoPi;
    const int numSteps = 100;
    float angleStep = twoPi / numSteps;
    auto waveSize = 0.7;

    for (int i = 0; i <= numSteps; ++i)
    {
        float angle = i * angleStep;
        float sineWave = std::sin(11 * angle) * (fullRadius * 0.025);
        float x = centre.getX() + (fullRadius * waveSize + sineWave) * std::cos(angle);
        float y = centre.getY() + (fullRadius * waveSize + sineWave) * std::sin(angle);

        if (i == 0)
        {
            wavyPath.startNewSubPath(x, y);
        }
        else
        {
            wavyPath.lineTo(x, y);
        }
    }

    // Ensure the path is closed to create a filled shape
    wavyPath.closeSubPath();

    // Apply rotation around the center of the dial
    juce::AffineTransform transformWave = juce::AffineTransform::rotation(toAngle, centre.getX(), centre.getY());
    wavyPath.applyTransform(transformWave);

    // Fill the path with color
    g.setColour(muted_white);
    g.strokePath(wavyPath, juce::PathStrokeType(2.0f));

    /** Dial tick color*/
    g.setColour (gold);
    juce::Path dialTick;
    dialTick.startNewSubPath (centre.getPointOnCircumference (dialRadius - lineWidth, toAngle));

    /** Dial tick length*/
    dialTick.lineTo (centre.getPointOnCircumference ((dialRadius - lineWidth) * 0.6f, toAngle));

    /** Dial tick thickness*/
    g.strokePath (dialTick, juce::PathStrokeType (lineWidth * 0.75f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    _sliderWidth = slider.getWidth();
}

void WaveyDial::drawLabel (juce::Graphics& g, juce::Label& label)
{
    g.fillAll (label.findColour (juce::Label::backgroundColourId));

    label.setEditable(true);

    if (! label.isBeingEdited())
    {
        const auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const auto font (viator::Fonts::bold(static_cast<float>(_sliderWidth) * 0.1f));

        g.setColour (label.findColour (juce::Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);

        const auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

        juce::String labelText;
        if (auto* parentComponent = label.getParentComponent())
        {
            if (const auto* slider = dynamic_cast<juce::Slider*>(parentComponent))
            {
                // Check if the mouse is over the slider
                const bool isMouseOver = slider->isMouseOver() || slider->isMouseButtonDown();

                // Get the slider value and suffix
                float value;

                if (_dialValueType == ValueType::kInt)
                {
                    value = static_cast<int>(slider->getValue());
                }

                else
                {
                    value = slider->getValue();
                }

                const juce::String suffix = slider->getTextValueSuffix();

                // Determine the text to display based on the mouse over state
                if (isMouseOver)
                {

                    labelText = juce::String(getRoundedValue(value)) + suffix;
                }
                else
                {
                    labelText = slider->getName();
                }
            }
        }

        g.drawFittedText (labelText, textArea, label.getJustificationType(),
                          juce::jmax (1, static_cast<int>(static_cast<float>(textArea.getHeight()) / font.getHeight())),
                          label.getMinimumHorizontalScale());

        g.setColour (label.findColour (juce::Label::outlineColourId).withMultipliedAlpha (alpha));
    }
}

float WaveyDial::getRoundedValue(float input) {
    return std::ceil(input * 100.0f) / 100.0f;
}

Fader::Fader()
{

}

void Fader::drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                       float sliderPos,
                                       float minSliderPos,
                                       float maxSliderPos,
                                       const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    auto trackWidth = juce::jmin (6.0f, slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f);

    juce::Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                 slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));

    juce::Point<float> endPoint (slider.isHorizontal() ? (float) (width + x) : startPoint.x,
                               slider.isHorizontal() ? startPoint.y : (float) y);

    g.setColour(slider.findColour(juce::Slider::ColourIds::trackColourId));
    g.drawRoundedRectangle(slider.getWidth() * 0.45, 3, slider.getWidth() * 0.1, slider.getHeight() * 0.9 - 3, 3.0f, 1.0f);

    juce::Path valueTrack;
    juce::Point<float> minPoint, maxPoint, thumbPoint;

    auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
    auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;

    minPoint = startPoint;
    maxPoint = { kx, ky };

    valueTrack.startNewSubPath (minPoint);
    valueTrack.lineTo (maxPoint);
    g.setColour (slider.findColour(juce::Slider::ColourIds::trackColourId));
    g.strokePath (valueTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });

    g.setColour (muted_white);
    g.drawRoundedRectangle (slider.getLocalBounds().toFloat().withSizeKeepingCentre(slider.getWidth() * 0.75, slider.getHeight() * 0.05).withCentre (maxPoint), 6.0f, 2.0f);
}

void Fader::drawLabel (juce::Graphics& g, juce::Label& label)
{
    label.setEditable(true);

    if (! label.isBeingEdited())
    {
        const auto font (viator::Fonts::bold(static_cast<float>(label.getWidth()) * 0.2f));

        g.setColour (juce::Colours::white);
        g.setFont (font);

        const auto textArea = label.getLocalBounds();

        juce::String labelText;
        if (auto* parentComponent = label.getParentComponent())
        {
            if (const auto* slider = dynamic_cast<juce::Slider*>(parentComponent))
            {
                // Check if the mouse is over the slider
                const bool isMouseOver = slider->isMouseOver() || slider->isMouseButtonDown();

                // Get the slider value and suffix
                float value;

                if (_dialValueType == ValueType::kInt)
                {
                    value = static_cast<int>(slider->getValue());
                }

                else
                {
                    value = slider->getValue();
                }

                const juce::String suffix = slider->getTextValueSuffix();

                // Determine the text to display based on the mouse over state
                if (isMouseOver)
                {
                    labelText = juce::String(getRoundedValue(value)) + suffix;
                }
                else
                {
                    labelText = slider->getName();
                }
            }
        }

        g.drawFittedText (labelText, textArea, label.getJustificationType(), 1);
    }
}

float Fader::getRoundedValue(const float input)
{
    return std::ceil(input * 100.0f) / 100.0f;
}

}