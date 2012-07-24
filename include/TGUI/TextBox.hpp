/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (VDV_B@hotmail.com)
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


#ifndef _TGUI_TEXT_BOX_INCLUDED_
#define _TGUI_TEXT_BOX_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct TGUI_API TextBox : public OBJECT, OBJECT_BORDERS, OBJECT_ANIMATION
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox(const TextBox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Desturctor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~TextBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox& operator= (const TextBox& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Called when added to a group. The font from the group will be inherited.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void initialize(const sf::Font& globalFont);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Makes a copy of the object.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Creates the text box.
        ///
        /// The text box may resize a little bit. It might be a little bit bigger or smaller than the size passed to this function.
        ///
        /// \param width              The width of the text box (borders included).
        /// \param height             The height of the text box (borders included).
        /// \param textSize           The size of the text.
        /// \param scrollbarPathname  The pathname needed to load the vertical scrollbar.
        ///                           If not provided then there will be no possibility to scroll, thus no text can be added when the textbox is full.
        ///
        /// \return
        ///        - true on success
        ///        - false when scrollbar couldn't be loaded (only if \a scrollbarPathname isn't empty)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool load(unsigned int width, unsigned int height, unsigned int textSize, const std::string scrollbarPathname = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the text box.
        ///
        /// \param width   The new width of the text box
        /// \param height  The new height of the text box
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(float width, float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the text box, unaffected by scaling.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2u getSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the text box, after the scaling transformation.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getScaledSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the pathname that was used to load the scrollbar.
        ///
        /// When no scrollbar was loaded then this function will return an empty string.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getLoadedScrollbarPathname();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the text of the text box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const std::string text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Appends some text to the text that was already in the text box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addText(const std::string text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the text of the text box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getText();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the font of the text.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed by calling the setGlobalFont function from Panel.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(const sf::Font& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the font of the text.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font& getTextFont();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the character size of the text.
        /// The minimum text size is 8.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(const unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the character size of the text.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the maximum character limit.
        ///
        /// Set \a maxChars to 0 to disable the limit.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumCharacters(const unsigned int maxChars = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the maximum character limit.
        ///
        /// This function will return 0 when there is no limit.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximumCharacters();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the border width and border height of the text box.
        ///
        /// \param leftBorder    The width of the left border
        /// \param topBorder     The height of the top border
        /// \param rightBorder   The width of the right border
        /// \param bottomBorder  The height of the bottom border
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorders(unsigned int leftBorder   = 0,
                        unsigned int topBorder    = 0,
                        unsigned int rightBorder  = 0,
                        unsigned int bottomBorder = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the colors from the text box.
        ///
        /// \param backgroundColor                      The color of the background of the text box.
        /// \param textColor                            The color of the text
        /// \param selectedTextColor                    The color of the text when it is selected
        /// \param selectedTextBackgroundColor          The color of the background of the text that is selected
        /// \param unfocusedSelectedTextBackgroundColor The color of the background of the text that is selected when the text box is not focused
        /// \param borderColor                          The color of the borders
        /// \param selectionPointColor                  The color of the flickering selection point
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void changeColors(const sf::Color& backgroundColor                      = sf::Color( 50,  50,  50),
                          const sf::Color& textColor                            = sf::Color(  0,   0,   0),
                          const sf::Color& selectedTextColor                    = sf::Color(255, 255, 255),
                          const sf::Color& selectedTextBackgroundColor          = sf::Color( 10, 110, 255),
                          const sf::Color& unfocusedSelectedTextBackgroundColor = sf::Color(110, 110, 255),
                          const sf::Color& borderColor                          = sf::Color(  0,   0,   0),
                          const sf::Color& selectionPointColor                  = sf::Color(110, 110, 255));

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color that will be used inside the text box.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& backgroundColor);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color that will be used inside the text box.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& textColor);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color of the selected text that will be used inside the text box.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextColor(const sf::Color& selectedTextColor);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color of the selected text that will be used inside the text box.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextBackgroundColor(const sf::Color& selectedTextBackgroundColor);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color of the selected text that will be used inside the text box when the text box is not focused.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setUnfocusedSelectedTextBackgroundColor(const sf::Color& unfocusedSelectedTextBackgroundColor);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the border color that will be used inside the text box.
        ///
        /// \see changeColors
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& borderColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color that is currently being used inside the text box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBackgroundColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color that is currently being used inside the text box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color of the selected text that is currently being used inside the text box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color of the selected text that is currently being used inside the text box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextBackgroundColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color of the selected that is currently being used inside the text box when the text box is not focused.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getUnfocusedSelectedTextBackgroundColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the border color that is currently being used inside the text box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBorderColor();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets the flickering selection point to after a specific character.
        ///
        /// Normally you will not need this function.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectionPointPosition(unsigned int charactersBeforeSelectionPoint);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the scrollbar of the text box.
        ///
        /// Only needed when this wasn't done when creating the text box or if the scrollbar should be changed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setScrollbar(const std::string scrollbarPathname);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes the scrollbar from the text box (if there is one).
        ///
        /// When there are too many lines to fit in the text box then some lines will be removed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeScrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief This will change the width of the selection point.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectionPointWidth(const unsigned int width = 2);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // These functions are used to receive callback from the EventManager.
        // You normally don't need them, but you can use them to simulate an event.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnObject(float x, float y);
        void leftMousePressed(float x, float y);
        void leftMouseReleased(float x, float y);
        void mouseMoved(float x, float y);
        void keyPressed(sf::Keyboard::Key Key);
        void textEntered(char Key);
        void mouseNotOnObject();
        void mouseNoLongerDown();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will search where the selection point should be. It will not change the selection point.
        // It will return after which character the selection point should be.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int findSelectionPointPosition(float posX, float posY);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when you are selecting text.
        // It will find out which part of the text is selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void selectText(float posX, float posY);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // To keep the drawing as fast as possible, all the calculation are done in front by this function.
        // It is called when the text changes, when scrolling, ...
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateDisplayedText();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called by updateDisplayedText and will split the text into five pieces so that the text can
        // be easily drawn.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelectionTexts(float maxLineWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When AnimationManager changes the elapsed time then this function is called.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void update();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Because this struct is derived from sf::Drawable, you can just call the Draw function from your sf::RenderTarget.
        // This function will be called and it will draw the object on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /// The color of the flickering selection pointer
        sf::Color selectionPointColor;

        /// The width in pixels of the flickering selection pointer
        unsigned int selectionPointWidth;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        // The size of the text box
        Vector2u m_Size;

        // Some information about the text
        std::string  m_Text;
        std::string  m_DisplayedText;
        unsigned int m_TextSize;
        unsigned int m_LineHeight;
        unsigned int m_Lines;

        // The maximum characters (0 by default, which means no limit)
        unsigned int m_MaxChars;

        // What is known about the visible lines?
        unsigned int m_TopLine;
        unsigned int m_VisibleLines;

        // Information about the selection
        unsigned int m_SelChars;
        unsigned int m_SelStart;
        unsigned int m_SelEnd;

        // Information about the selection pointer
        sf::Vector2u m_SelectionPointPosition;
        bool m_SelectionPointVisible;

        // Should the text be resplit into the five texts?
        bool m_SelectionTextsNeedUpdate;

        // The colors that are used by the text box
        sf::Color m_BackgroundColor;
        sf::Color m_SelectedTextBgrColor;
        sf::Color m_UnfocusedSelectedTextBgrColor;
        sf::Color m_BorderColor;

        // The sfml Text objects
        sf::Text m_TextBeforeSelection;
        sf::Text m_TextSelection1;
        sf::Text m_TextSelection2;
        sf::Text m_TextAfterSelection1;
        sf::Text m_TextAfterSelection2;

        std::vector<float> m_MultilineSelectionRectWidth;

        // The scrollbar
        Scrollbar* m_Scroll;

        // The pathname used to load the scrollbar (if there is one)
        std::string m_LoadedScrollbarPathname;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_TEXT_BOX_INCLUDED_


