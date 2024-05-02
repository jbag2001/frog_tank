/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/clock_screen_screen/clock_screenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

clock_screenViewBase::clock_screenViewBase() :
    flexButtonCallback(this, &clock_screenViewBase::flexButtonCallbackHandler),
    sliderValueChangedCallback(this, &clock_screenViewBase::sliderValueChangedCallbackHandler)
{
    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    bg.setPosition(0, 0, 480, 272);
    bg.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    add(bg);

    minute_slider.setXY(66, 196);
    minute_slider.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_SLIDER_HORIZONTAL_THICK_TRACK_SMALL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_SLIDER_HORIZONTAL_THICK_FILLER_SMALL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_FILL_PRESSED_ID));
    minute_slider.setupHorizontalSlider(16, 11, 0, 0, 200);
    minute_slider.setValueRange(0, 59);
    minute_slider.setValue(0);
    minute_slider.setNewValueCallback(sliderValueChangedCallback);
    add(minute_slider);

    hour_slider.setXY(66, 76);
    hour_slider.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_SLIDER_HORIZONTAL_THICK_TRACK_SMALL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_SLIDER_HORIZONTAL_THICK_FILLER_SMALL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_FILL_PRESSED_ID));
    hour_slider.setupHorizontalSlider(16, 11, 0, 0, 200);
    hour_slider.setValueRange(0, 23);
    hour_slider.setValue(0);
    hour_slider.setNewValueCallback(sliderValueChangedCallback);
    add(hour_slider);

    cancel_icon.setBitmap(touchgfx::Bitmap(BITMAP_CLOSE_ICON_ID));
    cancel_icon.setPosition(366, 36, 80, 80);
    cancel_icon.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    add(cancel_icon);

    confirm_icon.setBitmap(touchgfx::Bitmap(BITMAP_CHECK_ICON_ID));
    confirm_icon.setPosition(366, 156, 80, 80);
    confirm_icon.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    add(confirm_icon);

    min_bwd.setXY(32, 198);
    min_bwd.setBitmap(touchgfx::Bitmap(BITMAP_BACK_ID));
    add(min_bwd);

    hour_bwd.setXY(32, 78);
    hour_bwd.setBitmap(touchgfx::Bitmap(BITMAP_BACK_ID));
    add(hour_bwd);

    min_fwd.setXY(304, 198);
    min_fwd.setBitmap(touchgfx::Bitmap(BITMAP_NEXT_ID));
    add(min_fwd);

    hour_fwd.setXY(304, 78);
    hour_fwd.setBitmap(touchgfx::Bitmap(BITMAP_NEXT_ID));
    add(hour_fwd);

    hour_bwd_btn.setBoxWithBorderPosition(0, 0, 32, 32);
    hour_bwd_btn.setBorderSize(5);
    hour_bwd_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    hour_bwd_btn.setAlpha(0);
    hour_bwd_btn.setAction(flexButtonCallback);
    hour_bwd_btn.setPosition(32, 78, 32, 32);
    add(hour_bwd_btn);

    hour_fwd_btn.setBoxWithBorderPosition(0, 0, 32, 32);
    hour_fwd_btn.setBorderSize(5);
    hour_fwd_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    hour_fwd_btn.setAlpha(0);
    hour_fwd_btn.setAction(flexButtonCallback);
    hour_fwd_btn.setPosition(304, 78, 32, 32);
    add(hour_fwd_btn);

    min_bwd_btn.setBoxWithBorderPosition(0, 0, 32, 32);
    min_bwd_btn.setBorderSize(5);
    min_bwd_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    min_bwd_btn.setAlpha(0);
    min_bwd_btn.setAction(flexButtonCallback);
    min_bwd_btn.setPosition(32, 198, 32, 32);
    add(min_bwd_btn);

    min_fwd_btn.setBoxWithBorderPosition(0, 0, 32, 32);
    min_fwd_btn.setBorderSize(5);
    min_fwd_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    min_fwd_btn.setAlpha(0);
    min_fwd_btn.setAction(flexButtonCallback);
    min_fwd_btn.setPosition(304, 198, 32, 32);
    add(min_fwd_btn);

    cancel_btn.setBoxWithBorderPosition(0, 0, 80, 80);
    cancel_btn.setBorderSize(5);
    cancel_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    cancel_btn.setAlpha(0);
    cancel_btn.setAction(flexButtonCallback);
    cancel_btn.setPosition(366, 38, 80, 80);
    add(cancel_btn);

    confirm_btn.setBoxWithBorderPosition(0, 0, 80, 80);
    confirm_btn.setBorderSize(5);
    confirm_btn.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    confirm_btn.setAlpha(0);
    confirm_btn.setAction(flexButtonCallback);
    confirm_btn.setPosition(366, 156, 80, 80);
    add(confirm_btn);

    hour_label.setXY(125, 58);
    hour_label.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    hour_label.setLinespacing(0);
    hour_label.setTypedText(touchgfx::TypedText(T___SINGLEUSE_WK62));
    add(hour_label);

    hour_text.setXY(190, 58);
    hour_text.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    hour_text.setLinespacing(0);
    Unicode::snprintf(hour_textBuffer, HOUR_TEXT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_8CS9).getText());
    hour_text.setWildcard(hour_textBuffer);
    hour_text.resizeToCurrentText();
    hour_text.setTypedText(touchgfx::TypedText(T___SINGLEUSE_C8EY));
    add(hour_text);

    min_label.setXY(119, 176);
    min_label.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    min_label.setLinespacing(0);
    min_label.setTypedText(touchgfx::TypedText(T___SINGLEUSE_6S60));
    add(min_label);

    min_text.setXY(203, 176);
    min_text.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    min_text.setLinespacing(0);
    Unicode::snprintf(min_textBuffer, MIN_TEXT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_9XMV).getText());
    min_text.setWildcard(min_textBuffer);
    min_text.resizeToCurrentText();
    min_text.setTypedText(touchgfx::TypedText(T___SINGLEUSE_O9MS));
    add(min_text);
}

clock_screenViewBase::~clock_screenViewBase()
{

}

void clock_screenViewBase::setupScreen()
{

}

void clock_screenViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &cancel_btn)
    {
        //cancel_go_home
        //When cancel_btn clicked change screen to home_screen
        //Go to home_screen with screen transition towards North
        application().gotohome_screenScreenSlideTransitionNorth();
    }
    if (&src == &confirm_btn)
    {
        //confirm_go_home
        //When confirm_btn clicked change screen to home_screen
        //Go to home_screen with screen transition towards North
        application().gotohome_screenScreenSlideTransitionNorth();
        //updateTime
        //When confirm_btn clicked call virtual function
        //Call updateTime
        updateTime();
    }
    if (&src == &hour_bwd_btn)
    {
        //lowHour
        //When hour_bwd_btn clicked call virtual function
        //Call lowHour
        lowHour();
    }
    if (&src == &hour_fwd_btn)
    {
        //incHour
        //When hour_fwd_btn clicked call virtual function
        //Call incHour
        incHour();
    }
    if (&src == &min_bwd_btn)
    {
        //lowMin
        //When min_bwd_btn clicked call virtual function
        //Call lowMin
        lowMin();
    }
    if (&src == &min_fwd_btn)
    {
        //incMin
        //When min_fwd_btn clicked call virtual function
        //Call incMin
        incMin();
    }
}

void clock_screenViewBase::sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &hour_slider)
    {
        //hourChange
        //When hour_slider value changed call virtual function
        //Call hourChange
        hourChange(value);
    }
    if (&src == &minute_slider)
    {
        //minChange
        //When minute_slider value changed call virtual function
        //Call minChange
        minChange(value);
    }
}
