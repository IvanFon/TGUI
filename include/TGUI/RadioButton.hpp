/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_RADIO_BUTTON_HPP
#define TGUI_RADIO_BUTTON_HPP


#include <TGUI/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API RadioButton : public ClickableWidget
    {
      public:

        typedef SharedWidgetPtr<RadioButton> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButton();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButton(const RadioButton& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~RadioButton() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButton& operator= (const RadioButton& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget by calling the copy constructor.
        // This function calls new and if you use this function then you are responsible for calling delete.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual RadioButton* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads the widget.
        ///
        /// \param configFileFilename  Filename of the config file.
        ///
        /// \throw Exception when the config file couldn't be opened.
        /// \throw Exception when the config file didn't contain a "RadioButton" section with the needed information.
        /// \throw Exception when one of the images, described in the config file, couldn't be loaded.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void load(const std::string& configFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filename of the config file that was used to load the widget.
        ///
        /// \return Filename of loaded config file.
        ///         Empty string when no config file was loaded yet.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::string& getLoadedConfigFile() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// \param x X coordinate of the new position
        /// \param y Y coordinate of the new position
        ///
        /// \see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(float x, float y);
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the radio button.
        ///
        /// \param width   The new width of the radio button
        /// \param height  The new height of the radio button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(float width, float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the radio button.
        ///
        /// \return Size of the radio button
        ///
        /// The returned size is just the size of the image, the text is not included in the size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the full size of the radio button.
        ///
        /// \return Full size of the radio button
        ///
        /// The returned size includes the text next to the radio button.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Checks the radio button.
        ///
        /// It will tell its parent to uncheck all the other radio buttons.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void check();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unchecks the radio button
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void uncheck();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns whether the radio button is checked or not.
        ///
        /// \return Is the radio button checked?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isChecked() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the text of the radio button.
        ///
        /// \param text  The new text to draw next to the radio button.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the text of the radio button.
        ///
        /// \return The text that is drawn next to the radio button.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the font of the text.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// \param font  The new font
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(const sf::Font& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the font of the text.
        ///
        /// \return Pointer to the font that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font* getTextFont() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the color of the text.
        ///
        /// \param color  New text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the color of the text.
        ///
        /// \return The current text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the character size of the text.
        ///
        /// \param size  The new text size.
        ///              When the size is set to 0 then the text is auto-sized.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the character size of the text.
        ///
        /// \return Character size of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Allow (or disallow) the radio button to be checked/unchecked by clicking on the text next to the radio button.
        ///
        /// \param acceptTextClick  Will clicking on the text trigger a checked/unchecked event?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void allowTextClick(bool acceptTextClick = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the transparency of the widget.
        ///
        /// \param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void keyPressed(const sf::Event::KeyEvent& event);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetFocused();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is a (slow) way to set properties on the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is a (slow) way to get properties of the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void getProperty(std::string property, std::string& value) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Returns a list of all properties that can be used in setProperty and getProperty.
        // The second value in the pair is the type of the property (e.g. int, uint, string, ...).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to RadioButton.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum RadioButtonCallbacks
        {
            Checked = ClickableWidgetCallbacksCount * 1,                      ///< RadioButton was checked
            Unchecked = ClickableWidgetCallbacksCount * 2,                    ///< RadioButton was unchecked
            SpaceKeyPressed = ClickableWidgetCallbacksCount * 8,              ///< Space key was pressed
            ReturnKeyPressed = ClickableWidgetCallbacksCount * 16,            ///< Return key was pressed
            AllRadioButtonCallbacks = ClickableWidgetCallbacksCount * 32 - 1, ///< All trigger defined in RadioButton and its base classes
            RadioButtonCallbacksCount = ClickableWidgetCallbacksCount * 32
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::string m_loadedConfigFile;

        // This is the checked flag. When the radio button is checked then this variable will be true.
        bool m_checked;

        // When this boolean is true (default) then the radio button will also be checked by clicking on the text.
        bool m_allowTextClick;

        // This will contain the text that is written next to radio button.
        sf::Text m_text;

        // This will store the size of the text ( 0 to auto size )
        unsigned int m_textSize;

        Texture m_textureUnchecked;
        Texture m_textureChecked;
        Texture m_textureHover;
        Texture m_textureFocused;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_RADIO_BUTTON_HPP
