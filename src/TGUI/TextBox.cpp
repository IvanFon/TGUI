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


#include <TGUI/TGUI.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// TODO: Find bug: typing text makes the view go back to the top (with scrollbar)
///       Find bug: selection point is on the wrong position when scrolling.
///
///       Fix behavior problem: When pressing the down arrow when the selection point is at the beginning of the text,
///                             the selection point moves at the end of the line because it is not allowed to be in front.
///                             This problem will be hard to correct: m_DisplayedText may not be used as reference to m_SelEnd.

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextBox::TextBox() :
    selectionPointColor          (110, 110, 255),
    selectionPointWidth          (2),
    m_Size                       (360, 200),
    m_Text                       (""),
    m_DisplayedText              (""),
    m_TextSize                   (30),
    m_LineHeight                 (0),
    m_Lines                      (1),
    m_MaxChars                   (0),
    m_TopLine                    (1),
    m_VisibleLines               (1),
    m_SelChars                   (0),
    m_SelStart                   (0),
    m_SelEnd                     (0),
    m_SelectionPointPosition     (0, 0),
    m_SelectionPointVisible      (true),
    m_Scroll                     (NULL),
    m_LoadedScrollbarPathname    ("")
    {
        m_ObjectType = textBox;

        changeColors();

        m_RenderTexture = new sf::RenderTexture();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextBox::TextBox(const TextBox& copy) :
    OBJECT                         (copy),
    selectionPointColor            (copy.selectionPointColor),
    selectionPointWidth            (copy.selectionPointWidth),
    m_Size                         (copy.m_Size),
    m_Text                         (copy.m_Text),
    m_DisplayedText                (copy.m_DisplayedText),
    m_TextSize                     (copy.m_TextSize),
    m_LineHeight                   (copy.m_LineHeight),
    m_Lines                        (copy.m_Lines),
    m_MaxChars                     (copy.m_MaxChars),
    m_TopLine                      (copy.m_TopLine),
    m_VisibleLines                 (copy.m_VisibleLines),
    m_SelChars                     (copy.m_SelChars),
    m_SelStart                     (copy.m_SelStart),
    m_SelEnd                       (copy.m_SelEnd),
    m_SelectionPointPosition       (copy.m_SelectionPointPosition),
    m_SelectionPointVisible        (copy.m_SelectionPointVisible),
    m_BackgroundColor              (copy.m_BackgroundColor),
    m_TextColor                    (copy.m_TextColor),
    m_SelectedTextColor            (copy.m_SelectedTextColor),
    m_SelectedTextBgrColor         (copy.m_SelectedTextBgrColor),
    m_UnfocusedSelectedTextBgrColor(copy.m_UnfocusedSelectedTextBgrColor),
    m_BorderColor                  (copy.m_BorderColor),
    m_TextBeforeSelection          (copy.m_TextBeforeSelection),
    m_TextSelection                (copy.m_TextSelection),
    m_TextAfterSelection           (copy.m_TextAfterSelection),
    m_LoadedScrollbarPathname      (copy.m_LoadedScrollbarPathname)
    {
        // Copy the render texture
        if (m_RenderTexture->create(copy.m_RenderTexture->getSize().x, copy.m_RenderTexture->getSize().y) == false)
            m_Loaded = false;

        // If there is a scrollbar then copy it
        if (copy.m_Scroll != NULL)
            m_Scroll = new Scrollbar(*copy.m_Scroll);
        else
            m_Scroll = NULL;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextBox::~TextBox()
    {
        if (m_Scroll != NULL)
            delete m_Scroll;

        delete m_RenderTexture;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextBox& TextBox::operator= (const TextBox& right)
    {
        if (this != &right)
        {
            // If there already was a scrollbar then delete it now
            if (m_Scroll != NULL)
            {
                delete m_Scroll;
                m_Scroll = NULL;
            }

            TextBox temp(right);
            this->OBJECT::operator=(right);

            std::swap(selectionPointColor,             temp.selectionPointColor);
            std::swap(selectionPointWidth,             temp.selectionPointWidth);
            std::swap(m_Size,                          temp.m_Size);
            std::swap(m_Text,                          temp.m_Text);
            std::swap(m_DisplayedText,                 temp.m_DisplayedText);
            std::swap(m_TextSize,                      temp.m_TextSize);
            std::swap(m_LineHeight,                    temp.m_LineHeight);
            std::swap(m_Lines,                         temp.m_Lines);
            std::swap(m_MaxChars,                      temp.m_MaxChars);
            std::swap(m_TopLine,                       temp.m_TopLine);
            std::swap(m_VisibleLines,                  temp.m_VisibleLines);
            std::swap(m_SelChars,                      temp.m_SelChars);
            std::swap(m_SelStart,                      temp.m_SelStart);
            std::swap(m_SelEnd,                        temp.m_SelEnd);
            std::swap(m_SelectionPointPosition,        temp.m_SelectionPointPosition);
            std::swap(m_SelectionPointVisible,         temp.m_SelectionPointVisible);
            std::swap(m_BackgroundColor,               temp.m_BackgroundColor);
            std::swap(m_TextColor,                     temp.m_TextColor);
            std::swap(m_SelectedTextColor,             temp.m_SelectedTextColor);
            std::swap(m_SelectedTextBgrColor,          temp.m_SelectedTextBgrColor);
            std::swap(m_UnfocusedSelectedTextBgrColor, temp.m_UnfocusedSelectedTextBgrColor);
            std::swap(m_BorderColor,                   temp.m_BorderColor);
            std::swap(m_TextBeforeSelection,           temp.m_TextBeforeSelection);
            std::swap(m_TextSelection,                 temp.m_TextSelection);
            std::swap(m_TextAfterSelection,            temp.m_TextAfterSelection);
            std::swap(m_Scroll,                        temp.m_Scroll);
            std::swap(m_LoadedScrollbarPathname,       temp.m_LoadedScrollbarPathname);
            std::swap(m_RenderTexture,                 temp.m_RenderTexture);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool TextBox::load(unsigned int width, unsigned int height, unsigned int textSize, const std::string scrollbarPathname)
    {
        // When everything is loaded successfully, this will become true.
        m_Loaded = false;

        // If there already was a scrollbar then delete it now
        if (m_Scroll != NULL)
        {
            delete m_Scroll;
            m_Scroll = NULL;
        }

        // There is a minimum width
        if (width < (50 + m_LeftBorder + m_RightBorder))
            width = 50 + m_LeftBorder + m_RightBorder;

        // There is a minimum text size
        if (textSize < 8)
            textSize = 8;

        // Store the values
        m_Size.x = width;
        m_Size.y = height;
        m_LoadedScrollbarPathname = scrollbarPathname;

        // Set the text size
        setTextSize(textSize);

        // Create the render texture
        if (m_RenderTexture->create(m_Size.x - m_LeftBorder - m_RightBorder, m_Size.y - m_TopBorder - m_BottomBorder) == false)
            return false;

/// The scrollbar is not fully working yet
m_Loaded = true;
return true;

        // If there is a scrollbar then load it
        if (scrollbarPathname.empty() == false)
        {
            // load the scrollbar and check if it failed
            m_Scroll = new Scrollbar();
            if (m_Scroll->load(scrollbarPathname) == false)
            {
                // The scrollbar couldn't be loaded so it must be deleted
                delete m_Scroll;
                m_Scroll = NULL;

                return false;
            }
            else // The scrollbar was loaded successfully
            {
                // The scrollbar has to be vertical
                m_Scroll->verticalScroll = true;

                // Set the low value
                m_Scroll->setLowValue(m_Size.y - m_TopBorder - m_BottomBorder);

                m_Loaded = true;
                return true;
            }
        }
        else
        {
            m_Loaded = true;
            return true;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setSize(float width, float height)
    {
        // Don't do anything when the text box wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Reset the scale
        setScale(1, 1);

        // The calculations require an unsigned integer
        unsigned int uiHeight = static_cast<unsigned int>(height);

        // There is a minimum width
        if (m_Scroll == NULL)
            width = TGUI_MAXIMUM(50 + m_LeftBorder + m_RightBorder, width);
        else
            width = TGUI_MAXIMUM(50 + m_LeftBorder + m_RightBorder + m_Scroll->m_TextureArrowNormal->getSize().x, width);

        // There is also a minimum height
        if (m_Scroll == NULL)
        {
            // If there is a text then it should still fit inside the text box
            if (m_Text.size() > 0)
            {
                if (m_Size.y < ((m_Lines * m_LineHeight) - m_TopBorder - m_BottomBorder))
                    m_Size.y = (m_Lines * m_LineHeight) - m_TopBorder - m_BottomBorder;
            }
            else // There are no items
            {
                // At least one item should fit inside the text box
                if (m_Size.y < (m_LineHeight - m_TopBorder - m_BottomBorder))
                    m_Size.y = m_LineHeight - m_TopBorder - m_BottomBorder;
            }
        }
        else // There is a scrollbar
        {
            // At least one item should fit inside the text box
            if (m_Size.y < (m_LineHeight - m_TopBorder - m_BottomBorder))
                m_Size.y = m_LineHeight - m_TopBorder - m_BottomBorder;
        }

        // There is also a minimum height
        if (uiHeight < (m_LineHeight + m_TopBorder + m_BottomBorder))
        {
            uiHeight = m_LineHeight + m_TopBorder + m_BottomBorder;
        }
        else // The height isn't too low
        {
            // Calculate two perfect heights
            unsigned int height1 = ((uiHeight - m_TopBorder - m_BottomBorder) / m_LineHeight) * m_LineHeight;
            unsigned int height2 = (((uiHeight - m_TopBorder - m_BottomBorder) / m_LineHeight) + 1) * m_LineHeight;

            // Calculate the difference with the original one
            unsigned int difference1, difference2;

            if ((uiHeight - m_TopBorder - m_BottomBorder) > height1)
                difference1 = (uiHeight - m_TopBorder - m_BottomBorder) - height1;
            else
                difference1 = height1 - (uiHeight - m_TopBorder - m_BottomBorder);

            if ((uiHeight - m_TopBorder - m_BottomBorder) > height2)
                difference2 = (uiHeight - m_TopBorder - m_BottomBorder) - height2;
            else
                difference2 = height2 - (uiHeight - m_TopBorder - m_BottomBorder);

            // Find out which one is closest to the original height and adjust the height
            if (difference1 < difference2)
                uiHeight = height1 + m_TopBorder + m_BottomBorder;
            else
                uiHeight = height2 + m_TopBorder + m_BottomBorder;
        }

        // Store the values
        m_Size.x = static_cast<unsigned int>(width);
        m_Size.y = uiHeight;

        // Create the render texture
        if (m_RenderTexture->create(m_Size.x - m_LeftBorder - m_RightBorder, m_Size.y - m_TopBorder - m_BottomBorder) == false)
            m_Loaded = false;

        // If there is a scrollbar then change it
        if (m_Scroll != NULL)
        {
            // Set the low value
            m_Scroll->setLowValue(m_Size.y - m_TopBorder - m_BottomBorder);
        }

        // The size of the textbox has changed, update the text
        updateDisplayedText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setText(const std::string text)
    {
        // Don't do anything when the text box wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Store the text
        m_Text = text;

        // Set the selection point behind the last character
        setSelectionPointPosition(m_Text.length());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2u TextBox::getSize() const
    {
        return m_Size;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f TextBox::getScaledSize() const
    {
        return Vector2f(m_Size.x * getScale().x, m_Size.y * getScale().y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string TextBox::getLoadedScrollbarPathname()
    {
        return m_LoadedScrollbarPathname;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string TextBox::getText()
    {
        return m_Text;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setTextFont(const sf::Font& font)
    {
/// TODO: Support selection => also set the font in other text objects
        m_TextBeforeSelection.setFont(font);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Font& TextBox::getTextFont()
    {
        return m_TextBeforeSelection.getFont();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setTextSize(const unsigned int size)
    {
        // Store the new text size
        m_TextSize = size;

        // Change the text size
        m_TextBeforeSelection.setCharacterSize(m_TextSize);
        m_TextSelection.setCharacterSize(m_TextSize);
        m_TextAfterSelection.setCharacterSize(m_TextSize);

        // Calculate the height of one line (a little bigger than text height)
        m_LineHeight = m_TextSize * 10 / 8;

        // There is also a minimum height
        if (m_Size.y < (m_LineHeight + m_TopBorder + m_BottomBorder))
        {
            m_Size.y = m_LineHeight + m_TopBorder + m_BottomBorder;
        }
        else // The height is ok
        {
            // Calculate two perfect heights
            unsigned int height1 = ((m_Size.y - m_TopBorder - m_BottomBorder) / m_LineHeight) * m_LineHeight;
            unsigned int height2 = (((m_Size.y - m_TopBorder - m_BottomBorder) / m_LineHeight) + 1) * m_LineHeight;

            // Calculate the difference with the original one
            unsigned int difference1, difference2;

            if ((m_Size.y - m_TopBorder - m_BottomBorder) > height1)
                difference1 = (m_Size.y - m_TopBorder - m_BottomBorder) - height1;
            else
                difference1 = height1 - (m_Size.y - m_TopBorder - m_BottomBorder);

            if ((m_Size.y - m_TopBorder - m_BottomBorder) > height2)
                difference2 = (m_Size.y - m_TopBorder - m_BottomBorder) - height2;
            else
                difference2 = height2 - (m_Size.y - m_TopBorder - m_BottomBorder);

            // Find out which one is closest to the original height and adjust the height
            if (difference1 < difference2)
                m_Size.y = height1 + m_TopBorder + m_BottomBorder;
            else
                m_Size.y = height2 + m_TopBorder + m_BottomBorder;
        }

        // The size has changed, update the text
        updateDisplayedText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int TextBox::getTextSize()
    {
        return m_TextSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setMaximumCharacters(const unsigned int maxChars)
    {
        // Set the new character limit ( 0 to disable the limit )
        m_MaxChars = maxChars;

        // If there is a character limit then check if it is exeeded
        if ((m_MaxChars > 0) && (m_Text.length() > m_MaxChars))
        {
            // Remove all the excess characters
            while (m_Text.length() > m_MaxChars)
                m_Text.erase(m_Text.length()-1, 1);

            // If we passed here then the internal text has changed. We also need to change the one to display.
            m_TextBeforeSelection.setString(m_DisplayedText);
            m_TextSelection.setString(std::string(""));
            m_TextAfterSelection.setString(std::string(""));

            // Set the selection point behind the last character
            setSelectionPointPosition(m_DisplayedText.length());
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int TextBox::getMaximumCharacters()
    {
        return m_MaxChars;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setBorders(unsigned int leftBorder, unsigned int topBorder, unsigned int rightBorder, unsigned int bottomBorder)
    {
        // Don't do anything when the text box wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Set the new border size
        m_LeftBorder   = leftBorder;
        m_TopBorder    = topBorder;
        m_RightBorder  = rightBorder;
        m_BottomBorder = bottomBorder;

        // There is a minimum width
        if (m_Size.x < (50 + m_LeftBorder + m_RightBorder))
            m_Size.x = 50 + m_LeftBorder + m_RightBorder;

        // There is also a minimum height (when there is no scrollbar)
        if (m_Scroll == NULL)
        {
            // If there is a text then it should still fit inside the text box
            if (m_Text.size() > 0)
            {
                if (m_Size.y < ((m_Lines * m_LineHeight) - m_TopBorder - m_BottomBorder))
                    m_Size.y = (m_Lines * m_LineHeight) - m_TopBorder - m_BottomBorder;
            }
            else // There are no items
            {
                // At least one item should fit inside the text box
                if (m_Size.y < (m_LineHeight - m_TopBorder - m_BottomBorder))
                    m_Size.y = m_LineHeight - m_TopBorder - m_BottomBorder;
            }
        }

        // Calculate two perfect heights
        unsigned int height1 = ((m_Size.y - m_TopBorder - m_BottomBorder) / m_LineHeight) * m_LineHeight;
        unsigned int height2 = (((m_Size.y - m_TopBorder - m_BottomBorder) / m_LineHeight) + 1) * m_LineHeight;

        // Calculate the difference with the original one
        unsigned int difference1, difference2;

        if ((m_Size.y - m_TopBorder - m_BottomBorder) > height1)
            difference1 = (m_Size.y - m_TopBorder - m_BottomBorder) - height1;
        else
            difference1 = height1 - (m_Size.y - m_TopBorder - m_BottomBorder);

        if ((m_Size.y - m_TopBorder - m_BottomBorder) > height2)
            difference2 = (m_Size.y - m_TopBorder - m_BottomBorder) - height2;
        else
            difference2 = height2 - (m_Size.y - m_TopBorder - m_BottomBorder);

        // Find out which one is closest to the original height and adjust the height
        if (difference1 < difference2)
            m_Size.y = height1 + m_TopBorder + m_BottomBorder;
        else
            m_Size.y = height2 + m_TopBorder + m_BottomBorder;

        // Recreate the render texture
        if (m_RenderTexture->create(m_Size.x - m_LeftBorder - m_RightBorder, m_Size.y - m_TopBorder - m_BottomBorder) == false)
            m_Loaded = false;

        // Check if there is a scrollbar
        if (m_Scroll != NULL)
        {
            // Set the low value
            m_Scroll->setLowValue(m_Size.y - m_TopBorder - m_BottomBorder);
        }

        // The space for the text has changed, so update the text
        updateDisplayedText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::changeColors(const sf::Color& backgroundColor,
                               const sf::Color& color,
                               const sf::Color& selectedColor,
                               const sf::Color& selectedBgrColor,
                               const sf::Color& unfocusedSelectedBgrColor,
                               const sf::Color& borderColor)
    {
        m_BackgroundColor               = backgroundColor;
        m_TextColor                     = color;
        m_SelectedTextColor             = selectedColor;
        m_SelectedTextBgrColor          = selectedBgrColor;
        m_UnfocusedSelectedTextBgrColor = unfocusedSelectedBgrColor;
        m_BorderColor                   = borderColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& TextBox::getBackgroundColor()
    {
        return m_BackgroundColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& TextBox::getTextColor()
    {
        return m_TextColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& TextBox::getSelectedTextColor()
    {
        return m_SelectedTextColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& TextBox::getSelectedTextBackgroundColor()
    {
        return m_SelectedTextBgrColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& TextBox::getUnfocusedSelectedTextBackgroundColor()
    {
        return m_UnfocusedSelectedTextBgrColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& TextBox::getSelectionPointColor()
    {
        return selectionPointColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& TextBox::getBorderColor()
    {
        return m_BorderColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setSelectionPointPosition(unsigned int charactersBeforeSelectionPoint)
    {
        // The selection point position has to stay inside the string
        if (charactersBeforeSelectionPoint > m_Text.length())
            charactersBeforeSelectionPoint = m_Text.length();

        // Set the selection point to the correct position
        m_SelChars = 0;
        m_SelStart = charactersBeforeSelectionPoint;
        m_SelEnd = charactersBeforeSelectionPoint;

        // Change our three texts
        m_TextBeforeSelection.setString(m_DisplayedText);
        m_TextSelection.setString("");
        m_TextAfterSelection.setString("");

        // Update the text
        updateDisplayedText();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool TextBox::setScrollbar(const std::string scrollbarPathname)
    {
        // Do nothing when the string is empty
        if (scrollbarPathname.empty() == true)
            return false;

        // If the scrollbar was already created then delete it first
        if (m_Scroll != NULL)
            delete m_Scroll;

        // load the scrollbar and check if it failed
        m_Scroll = new Scrollbar();
        if(m_Scroll->load(scrollbarPathname) == false)
        {
            // The scrollbar couldn't be loaded so it must be deleted
            delete m_Scroll;
            m_Scroll = NULL;

            return false;
        }
        else // The scrollbar was loaded successfully
        {
            // The scrollbar has to be vertical
            m_Scroll->verticalScroll = true;

            // Set the low value
            m_Scroll->setLowValue(m_Size.y - m_TopBorder - m_BottomBorder);

            // Tell the scrollbar how many pixels the text contains
            m_Scroll->setMaximum(m_Lines * m_LineHeight);

            return true;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::removeScrollbar()
    {
        // Delete the scrollbar
        delete m_Scroll;
        m_Scroll = NULL;

        m_TopLine = 1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::setSelectionPointWidth(const unsigned int width)
    {
        selectionPointWidth = width;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool TextBox::mouseOnObject(float x, float y)
    {
        // Don't do anything when the text box wasn't loaded correctly
        if (m_Loaded == false)
            return false;

        // Get the current position and scale
        Vector2f position = getPosition();
        Vector2f curScale = getScale();

        // Pass the event to the scrollbar (if there is one)
        if (m_Scroll != NULL)
        {
            // Temporarily set the position and scale of the scroll
            m_Scroll->setPosition(position.x + ((m_Size.x - m_RightBorder) * curScale.x) - m_Scroll->getSize().x, position.y + (m_TopBorder * curScale.y));
            m_Scroll->setScale(1, (curScale.y * (m_Size.y- m_TopBorder - m_BottomBorder)) / m_Scroll->getSize().y);

            // Pass the event
            m_Scroll->mouseOnObject(x, y);

            // Reset the position and scale
            m_Scroll->setPosition(0, 0);
            m_Scroll->setScale(1, 1);
        }

        // Check if the mouse is on top of the listbox
        if ((x > (position.x + (m_LeftBorder * curScale.x))) && (x < (position.x + ((m_Size.x - m_RightBorder) * curScale.x)))
         && (y > (position.y + (m_TopBorder * curScale.y))) && (y < (position.y + ((m_Size.y - m_BottomBorder) * curScale.y))))
        {
            return true;
        }
        else // The mouse is not on top of the listbox
        {
            m_MouseHover = false;
            return false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::leftMousePressed(float x, float y)
    {
        // Don't do anything when the text box wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Set the mouse down flag to true
        m_MouseDown = true;

        // This will be true when the click didn't occur on the scrollbar
        bool clickedOnTextBox = true;

        // If there is a scrollbar then pass the event
        if (m_Scroll != NULL)
        {
            // Get the current scale
            Vector2f curScale = getScale();

            // Temporarily set the position and scale of the scroll
            m_Scroll->setPosition(getPosition().x + ((m_Size.x - m_RightBorder) * curScale.x) - m_Scroll->getSize().x, getPosition().y + (m_TopBorder * curScale.y));
            m_Scroll->setScale(1, (curScale.y * (m_Size.y- m_TopBorder - m_BottomBorder)) / m_Scroll->getSize().y);

            // Pass the event
            if (m_Scroll->mouseOnObject(x, y))
            {
                m_Scroll->leftMousePressed(x, y);
                clickedOnTextBox = false;
            }

            // Reset the position and scale
            m_Scroll->setPosition(0, 0);
            m_Scroll->setScale(1, 1);
        }

        // If the click occured on the text box
        if (clickedOnTextBox)
        {
            // Check if the text box was already focused
            if ((m_Focused) || ((!m_Focused) && (m_SelChars == 0)))
            {
                // Set the new selection point
                setSelectionPointPosition(static_cast<unsigned int>(findSelectionPointPosition(x - getPosition().x - m_LeftBorder - 4, y - getPosition().y - m_TopBorder)));

                // Set the mouse down flag
                m_MouseDown = true;
            }

            // The selection point should be visible
            m_SelectionPointVisible = true;
            m_AnimationTimeElapsed = sf::Time();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::leftMouseReleased(float x, float y)
    {
        // Don't do anything when the text box wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // If there is a scrollbar then pass it the event
        if (m_Scroll != NULL)
        {
            // Only pass the event when the scrollbar still thinks the mouse is down
            if (m_Scroll->m_MouseDown == true)
            {
                // Remember the old scrollbar value
                unsigned int oldValue = m_Scroll->m_Value;

                // Get the current scale
                Vector2f curScale = getScale();

                // Temporarily set the position and scale of the scroll
                m_Scroll->setPosition(getPosition().x + ((m_Size.x - m_RightBorder) * curScale.x) - m_Scroll->getSize().x, getPosition().y + (m_TopBorder * curScale.y));
                m_Scroll->setScale(1, (curScale.y * (m_Size.y- m_TopBorder - m_BottomBorder)) / m_Scroll->getSize().y);

                // Pass the event
                m_Scroll->leftMouseReleased(x, y);

                // Reset the position and scale
                m_Scroll->setPosition(0, 0);
                m_Scroll->setScale(1, 1);

                // If the value of the scrollbar has changed then update the text
                if (oldValue != m_Scroll->m_Value)
                    updateDisplayedText();
            }
        }

        m_MouseDown = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::mouseMoved(float x, float y)
    {
        // Don't do anything when the text box wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Get the current scale
        Vector2f curScale = getScale();

        // If there is a scrollbar then pass the event
        if (m_Scroll != NULL)
        {
            // Temporarily set the position and scale of the scroll
            m_Scroll->setPosition(getPosition().x + ((m_Size.x - m_RightBorder) * curScale.x) - m_Scroll->getSize().x, getPosition().y + (m_TopBorder * curScale.y));
            m_Scroll->setScale(1, (curScale.y * (m_Size.y- m_TopBorder - m_BottomBorder)) / m_Scroll->getSize().y);

            // Check if you are dragging the thumb of the scrollbar
            if ((m_Scroll->m_MouseDown) && (m_Scroll->m_MouseDownOnThumb))
            {
                // Remember the old scrollbar value
                unsigned int oldValue = m_Scroll->m_Value;

                // Pass the event, even when the mouse is not on top of the scrollbar
                m_Scroll->mouseMoved(x, y);

                // If the value of the scrollbar has changed then update the text
                if (oldValue != m_Scroll->m_Value)
                    updateDisplayedText();
            }
            else // You are just moving the mouse
            {
                // When the mouse is on top of the scrollbar then pass the mouse move event
                if (m_Scroll->mouseOnObject(x, y))
                    m_Scroll->mouseMoved(x, y);
            }

            // Reset the position and scale
            m_Scroll->setPosition(0, 0);
            m_Scroll->setScale(1, 1);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::mouseNotOnObject()
    {
        m_MouseHover = false;

        if (m_Scroll != NULL)
            m_Scroll->m_MouseHover = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::mouseNoLongerDown()
    {
        m_MouseDown = false;

        if (m_Scroll != NULL)
            m_Scroll->m_MouseDown = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::keyPressed(sf::Keyboard::Key key)
    {
        // Don't do anything when the edit box wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Check if one of the correct keys was pressed
        if (key == sf::Keyboard::Left)
        {
            // Check if we have selected some text
            if (m_SelChars > 0)
            {
                // We will not move the selection point, but just undo the selection
                if (m_SelStart < m_SelEnd)
                    setSelectionPointPosition(m_SelStart);
                else
                    setSelectionPointPosition(m_SelEnd);
            }
            else // When we didn't select any text
            {
                // You don't have to do anything when the selection point is at the beginning of the text
                if (m_SelEnd > 0)
                {
/// TODO: Scroll up when you go to the invisible line
///       Maybe this should happen in setSelectionPointPosition.
                    // Move the selection point to the left
                    setSelectionPointPosition(m_SelEnd - 1);
                }
            }

            // Our selection point has moved, it should be visible
            m_SelectionPointVisible = true;
            m_AnimationTimeElapsed = sf::Time();
        }
        else if (key == sf::Keyboard::Right)
        {
            // Check if we have selected some text
            if (m_SelChars > 0)
            {
                // We will not move the selection point, but just undo the selection
                if (m_SelStart < m_SelEnd)
                    setSelectionPointPosition(m_SelEnd);
                else
                    setSelectionPointPosition(m_SelStart);
            }
            else // When we didn't select any text
            {
                // You don't have to do anything when the selection point is at the end of the text
                if (m_SelEnd < m_Text.length())
                {
/// TODO: Scroll down when you go to the invisible line
///       Maybe this should happen in setSelectionPointPosition.
                    // Move the selection point to the left
                    setSelectionPointPosition(m_SelEnd + 1);
                }
            }

            // Our selection point has moved, it should be visible
            m_SelectionPointVisible = true;
            m_AnimationTimeElapsed = sf::Time();
        }
        else if (key == sf::Keyboard::Up)
        {
/// TODO: Scroll up when you go to the invisible line
///       Maybe this should happen in setSelectionPointPosition.

            bool newlineAdded = false;
            unsigned int newlinesAdded = 0;

            unsigned int character;
            unsigned int newTopPosition;
            sf::Vector2u newPosition;

            int distanceX;
            int previousdistanceX = m_Size.x;

            // Loop through all characters
            for (unsigned int i=0; i<m_SelEnd; ++i)
            {
                // Make sure there is no newline in the text
                if (m_Text[i] != '\n')
                {
                    // Check if there is a newline in the displayed text
                    if (m_DisplayedText[i + newlinesAdded] == '\n')
                    {
                        // A newline was added here
                        ++newlinesAdded;
                        newlineAdded = true;
                    }
                }
                else // The newline occurs in the text itself
                    newlineAdded = false;
            }

            // Get the position of the character behind the selection point
            sf::Vector2u originalPosition = sf::Vector2u(m_TextBeforeSelection.findCharacterPos(m_SelEnd + newlinesAdded));

            // Try to find the line above the selection point
            for (character=m_SelEnd; character > 0; --character)
            {
                // Get the top position of the character before it
                newTopPosition = static_cast<unsigned int>(m_TextBeforeSelection.findCharacterPos(character+newlinesAdded-1).y);

                // Check if the the character is on the line above the original one
                if (newTopPosition < originalPosition.y)
                    break;
            }

            // Our selection point has moved, it should be visible
            m_SelectionPointVisible = true;
            m_AnimationTimeElapsed = sf::Time();

            // Don't do anything when the selection point is on the first line
            if (character > 0)
            {
                // Try to find the closest character
                for ( ; character > 0; --character)
                {
                    // Get the position of the character before it
                    newPosition = sf::Vector2u(m_TextBeforeSelection.findCharacterPos(character+newlinesAdded-1));

                    // The character must remain on the same line
                    if (newPosition.y < newTopPosition)
                    {
                        // We have found the character that we were looking for
                        setSelectionPointPosition(character + newlineAdded);
                        return;
                    }

                    // Calculate the distance to the original position
                    distanceX = newPosition.x - originalPosition.x;

                    // Check if the distance is going away again
                    if (abs(distanceX) > previousdistanceX)
                    {
                        // We have found the character that we were looking for
                        setSelectionPointPosition(character + newlineAdded);
                        return;
                    }

                    // Remember the previous distance
                    previousdistanceX = abs(distanceX);
                }

                // If you pass here then the selection point should be at the beginning of the text
                setSelectionPointPosition(0);
            }
        }
        else if (key == sf::Keyboard::Down)
        {
/// TODO: Scroll down when you go to the invisible line
///       Maybe this should happen in setSelectionPointPosition.

            bool newlineAdded = false;
            unsigned int newlinesAdded = 0;

            unsigned int character;
            unsigned int newTopPosition;
            sf::Vector2u newPosition;

            int distanceX;
            int previousdistanceX = m_Size.x;

            // Loop through all characters
            for (unsigned int i=0; i<m_Text.length(); ++i)
            {
                // Make sure there is no newline in the text
                if (m_Text[i] != '\n')
                {
                    // Check if there is a newline in the displayed text
                    if (m_DisplayedText[i + newlinesAdded] == '\n')
                    {
                        // A newline was added here
                        ++newlinesAdded;
                        newlineAdded = true;

                        // Stop when the newline behind the selection point was found
                        if (i > m_SelEnd)
                            break;
                    }
                }
                else // The newline occurs in the text itself
                {
                    newlineAdded = false;

                    // Stop when the newline behind the selection point was found
                    if (i > m_SelEnd)
                        break;
                }
            }

            // Get the position of the character behind the selection point
            sf::Vector2u originalPosition = sf::Vector2u(m_TextBeforeSelection.findCharacterPos(m_SelEnd+newlinesAdded-newlineAdded));

            // Try to find the line below the selection point
            for (character=m_SelEnd; character < m_Text.length(); ++character)
            {
                // Get the top position of the character after it
                newTopPosition = static_cast<unsigned int>(m_TextBeforeSelection.findCharacterPos(character+newlinesAdded-newlineAdded+1).y);

                // Check if the the character is on the line below the original one
                if (newTopPosition > originalPosition.y)
                    break;
            }

            // Our selection point has moved, it should be visible
            m_SelectionPointVisible = true;
            m_AnimationTimeElapsed = sf::Time();

            // Don't do anything when the selection point is on the last line
            if (character < m_Text.length())
            {
                // Try to find the closest character
                for ( ; character < m_Text.length(); ++character)
                {
                    // Get the position of the character after it
                    newPosition = sf::Vector2u(m_TextBeforeSelection.findCharacterPos(character+newlinesAdded-newlineAdded+1));

                    // The character must remain on the same line
                    if (newPosition.y > newTopPosition)
                    {
                        // We have found the character that we were looking for
                        setSelectionPointPosition(character - newlineAdded);
                        return;
                    }

                    // Calculate the distance to the original position
                    distanceX = newPosition.x - originalPosition.x;

                    // Check if the distance is going away again
                    if (abs(distanceX) > previousdistanceX)
                    {
                        // We have found the character that we were looking for
                        setSelectionPointPosition(character - newlineAdded);
                        return;
                    }

                    // Remember the previous distance
                    previousdistanceX = abs(distanceX);
                }

                // If you pass here then the selection point should be at the end of the text
                setSelectionPointPosition(m_Text.length());
            }
        }
        else if (key == sf::Keyboard::Home)
        {
/// TODO: Scroll up when you go to the invisible first line
///       Maybe this should happen in setSelectionPointPosition.
            // Set the selection point to the beginning of the text
            setSelectionPointPosition(0);

            // Our selection point has moved, it should be visible
            m_SelectionPointVisible = true;
            m_AnimationTimeElapsed = sf::Time();
        }
        else if (key == sf::Keyboard::End)
        {
/// TODO: Scroll down when you go to the invisible first line
///       Maybe this should happen in setSelectionPointPosition.
            // Set the selection point behind the text
            setSelectionPointPosition(m_Text.length());

            // Our selection point has moved, it should be visible
            m_SelectionPointVisible = true;
            m_AnimationTimeElapsed = sf::Time();
        }
        else if (key == sf::Keyboard::Return)
        {
            // Add a newline
            textEntered('\n');
        }
        else if (key == sf::Keyboard::BackSpace)
        {
            // Make sure that we didn't select any characters
            if (m_SelChars == 0)
            {
                // We can't delete any characters when you are at the beginning of the string
                if (m_SelEnd == 0)
                    return;

/// TODO: Scroll up when you go to the invisible line
///       Maybe this should happen in setSelectionPointPosition.

                // Erase the character
                m_Text.erase(m_SelEnd-1, 1);

                // Set the selection point back on the correct position
                setSelectionPointPosition(m_SelEnd - 1);
            }
            else // When you did select some characters
            {
            deleteSelectedCharacters:

                // Check if they were selected from left to right
                if (m_SelStart < m_SelEnd)
                {

/// TODO: Scroll up when you go to the invisible line
///       Maybe this should happen in setSelectionPointPosition.

                    // Erase the characters
                    m_Text.erase(m_SelStart, m_SelChars);

                    // Set the selection point back on the correct position
                    setSelectionPointPosition(m_SelStart);
                }
                else // When the text is selected from right to left
                {
                    // Erase the characters
                    m_Text.erase(m_SelEnd, m_SelChars);

                    // Set the selection point back on the correct position
                    setSelectionPointPosition(m_SelEnd);
                }
            }

            // The selection point should be visible again
            m_SelectionPointVisible = true;
            m_AnimationTimeElapsed = sf::Time();

            // Add the callback (if the user requested it)
            if (callbackID > 0)
            {
                Callback callback;
                callback.callbackID = callbackID;
                callback.trigger    = Callback::textChanged;
                callback.text       = m_Text;
                m_Parent->addCallback(callback);
            }
        }
        else if (key == sf::Keyboard::Delete)
        {
            // Make sure that no text is selected
            if (m_SelChars == 0)
            {
                // When the selection point is at the end of the line then you can't delete anything
                if (m_SelEnd == m_Text.length())
                    return;

                // Erase the character
                m_Text.erase(m_SelEnd, 1);

                // Set the selection point back on the correct position
                setSelectionPointPosition(m_SelEnd);
            }
            else // You did select some characters
            {
                // This code is exactly the same as when pressing backspace
                goto deleteSelectedCharacters;
            }

            // The selection point should be visible again
            m_SelectionPointVisible = true;
            m_AnimationTimeElapsed = sf::Time();

            // Add the callback (if the user requested it)
            if (callbackID > 0)
            {
                Callback callback;
                callback.callbackID = callbackID;
                callback.trigger    = Callback::textChanged;
                callback.text       = m_Text;
                m_Parent->addCallback(callback);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::textEntered(char key)
    {
        // Don't do anything when the text box wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // If there were selected characters then delete them first
        if (m_SelChars != 0)
            keyPressed(sf::Keyboard::BackSpace);

        // Make sure we don't exceed our maximum characters limit
        if ((m_MaxChars > 0) && (m_Text.length() + 1 > m_MaxChars))
                return;

        // If there is a limit in the amount of lines then make a simulation
        if (m_Scroll == NULL)
        {
            float maxLineWidth;

            // Calculate the maximum line width
            if (m_Scroll == NULL)
                maxLineWidth = m_Size.x - m_LeftBorder - m_RightBorder - 4;
            else
                maxLineWidth = m_Size.x - m_LeftBorder - m_TopBorder - m_Scroll->getScaledSize().x - 4;

            // If the width is negative then the text box is too small to be displayed
            if (maxLineWidth < 0)
                maxLineWidth = 0;

            // Make some preparations
            sf::Text tempText(m_TextBeforeSelection);
            unsigned int beginChar = 0;
            unsigned int newlinesAdded = 0;

            std::string text = m_Text;
            text.insert(text.begin() + m_SelEnd, key);

            std::string displayedText = text;
            unsigned int lines = 1;

            // Loop through every character
            for (unsigned i=1; i < text.length() + 1; ++i)
            {
                // Make sure the character is not a newline
                if (text[i-1] != '\n')
                {
                    // Add the next character to the text object
                    tempText.setString(text.substr(beginChar, i - beginChar));

                    // Check if the string still fits on the line
                    if (tempText.findCharacterPos(i).x > maxLineWidth)
                    {
                        // Insert the new line character
                        displayedText.insert(displayedText.begin() + i + newlinesAdded - 1, '\n');

                        // Prepare to find the next line end
                        beginChar = i - 1;
                        ++newlinesAdded;
                        ++lines;
                    }
                }
                else // The character was a newline
                {
                    beginChar = i;
                    ++lines;
                }

                // Check if you passed this limit
                if (lines > (m_Size.y - m_TopBorder - m_BottomBorder) / m_LineHeight)
                {
                    // The character can't be added
                    return;
                }
            }
        }

        // Insert our character
        m_Text.insert(m_Text.begin() + m_SelEnd, key);

        // Move our selection point forward
        setSelectionPointPosition(m_SelEnd + 1);

        // The selection point should be visible again
        m_SelectionPointVisible = true;
        m_AnimationTimeElapsed = sf::Time();

        // Add the callback (if the user requested it)
        if (callbackID > 0)
        {
            Callback callback;
            callback.callbackID = callbackID;
            callback.trigger    = Callback::textChanged;
            callback.text       = m_Text;
            m_Parent->addCallback(callback);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int TextBox::findSelectionPointPosition(float posX, float posY)
    {
        // This code will crash when the text box is empty. We need to avoid this.
        if (m_Text.length() == 0)
            return 0;

        // Check if there is a scrollbar
        if (m_Scroll != NULL)
        {
/// TODO: Support scrollbar
        }
        else // There is no scrollbar
        {
            // Find out on which line you clicked
            unsigned int line = posY / m_LineHeight + 1;

/// TODO: Support selection
            // Check if you clicked behind all characters
            if ((line > m_Lines) || ((line == m_Lines) && (posX > m_TextBeforeSelection.findCharacterPos(m_DisplayedText.length()).x)))
            {
                // The selection point should be behind the last character
                return m_Text.length();
            }
            else // You clicked inside the text
            {
                // Prepare to skip part of the text
                std::string tempString = m_DisplayedText;
                std::string::size_type newLinePos = 0;

                // Only remove lines when there are lines to remove
                if (line > 1)
                {
                    unsigned int i=1;

                    // If the first character is a newline then remove it if needed
                    if (m_Text[0] == '\n')
                        ++i;

                    // Skip the lines above the line where you clicked
                    for ( ; i<line; ++i)
                        newLinePos = tempString.find('\n', newLinePos + 1);

                    // Remove the first lines
                    tempString.erase(0, newLinePos + 1);
                }

                // Only keep one line
                std::string::size_type newLinePos2 = tempString.find('\n');
                if (newLinePos2 != std::string::npos)
                    tempString.erase(newLinePos2);

                // Create a temporary text object
                sf::Text tempText(m_TextBeforeSelection);

                // We are going to calculate the number of newlines we have added
                unsigned int newlinesAdded = 0;
                unsigned int totalNewlinesAdded = 0;
                unsigned int beginChar = 0;
                std::string  tempString2 = m_DisplayedText;

                // Calculate the maximum line width
                float maxLineWidth = m_Size.x - m_LeftBorder - m_RightBorder - 4;

                // If the width is negative then the text box is too small to be displayed
                if (maxLineWidth < 0)
                    maxLineWidth = 0;

                // Loop through every character
                for (unsigned i=1; (i < m_Text.length() + 1) && (totalNewlinesAdded != line - 1); ++i)
                {
                    // Make sure the character is not a newline
                    if (m_Text[i-1] != '\n')
                    {
                        // Add the next character to the text object
                        tempText.setString(m_Text.substr(beginChar, i - beginChar));

                        // Check if the string still fits on the line
                        if (tempText.findCharacterPos(i).x > maxLineWidth)
                        {
                            // Insert the new line character
                            tempString2.insert(tempString2.begin() + i + newlinesAdded - 1, '\n');

                            // Prepare to find the next line end
                            beginChar = i - 1;
                            ++newlinesAdded;
                            ++totalNewlinesAdded;
                        }
                    }
                    else // The character was a newline
                    {
                        beginChar = i;
                        ++totalNewlinesAdded;
                    }
                }

                // Store the single line that we found a while ago in the temporary text object
                tempText.setString(tempString);

                // If the line contains nothing but a newline character then put the selction point on that line
                if (tempString.length() == 0)
                {
                    if (line > 1)
                        return newLinePos + 1;
                    else
                        return newLinePos;
                }

                // Try to find between which characters the mouse is standing
                for (unsigned int i=1; i<=tempString.length(); ++i)
                {
                    if (posX < (tempText.findCharacterPos(i-1).x + tempText.findCharacterPos(i).x) / 2.f)
                    {
                        if (line > 1)
                            return newLinePos + i - newlinesAdded;
                        else
                            return newLinePos + i - 1;
                    }

                }

                // Check if you clicked behind the last character on the line
                if (tempText.findCharacterPos(tempString.length()).x - (((3.f * tempText.findCharacterPos(tempString.length()-1).x) + tempText.findCharacterPos(tempString.length()).x) / 2.f))
                {
                    if (line > 1)
                        return newLinePos + tempString.length() + 1 - newlinesAdded;
                    else
                        return newLinePos + tempString.length();
                }
            }
        }

        // Something went wrong, don't move the selection point position
        return m_SelEnd;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::updateDisplayedText()
    {
        // Don't continue when the text box wasn't loaded correctly
        if (m_Loaded == false)
            return;

        float maxLineWidth;

        // Calculate the maximum line width
        if (m_Scroll == NULL)
            maxLineWidth = m_Size.x - m_LeftBorder - m_RightBorder - 4;
        else
            maxLineWidth = m_Size.x - m_LeftBorder - m_TopBorder - m_Scroll->getScaledSize().x - 4;

        // If the width is negative then the text box is too small to be displayed
        if (maxLineWidth < 0)
            maxLineWidth = 0;

        // Make some preparations
        sf::Text tempText(m_TextBeforeSelection);
        unsigned int beginChar = 0;
        unsigned int newlinesAdded = 0;
        unsigned int newlinesAddedBeforeSelection = 0;

        m_DisplayedText = m_Text;
        m_Lines = 1;

        // Loop through every character
        for (unsigned i=1; i < m_Text.length() + 1; ++i)
        {
            // Make sure the character is not a newline
            if (m_Text[i-1] != '\n')
            {
                // Add the next character to the text object
                tempText.setString(m_Text.substr(beginChar, i - beginChar));

                // Check if the string still fits on the line
                if (tempText.findCharacterPos(i).x > maxLineWidth)
                {
                    // Insert the new line character
                    m_DisplayedText.insert(m_DisplayedText.begin() + i + newlinesAdded - 1, '\n');

                    // Prepare to find the next line end
                    beginChar = i - 1;
                    ++newlinesAdded;
                    ++m_Lines;
                }
            }
            else // The character was a newline
            {
                beginChar = i;
                ++m_Lines;
            }

            // Find the position of the selection point
            if (m_SelEnd == i - 1)
                newlinesAddedBeforeSelection = newlinesAdded;

            // Check if there is a limit in the amount of lines
            if (m_Scroll == NULL)
            {
                // Check if you passed this limit
                if (m_Lines > (m_Size.y - m_TopBorder - m_BottomBorder) / m_LineHeight)
                {
                    // Remove all exceeding lines
                    m_DisplayedText.erase(i-1);
                    m_Text.erase(i-1);

                    // We counted one line too much
                    --m_Lines;

                    break;
                }
            }
        }

        // Find the position of the selection point
        if (m_SelEnd == m_Text.length())
            newlinesAddedBeforeSelection = newlinesAdded;

        // Check if there is a scrollbar
        if (m_Scroll != NULL)
        {
            // Tell the scrollbar how many pixels the text contains
            m_Scroll->setMaximum(m_Lines * m_LineHeight);

            // Calculate the top line
            m_TopLine = m_Scroll->m_Value / m_LineHeight + 1;

            // Calculate the number of visible lines
            if ((m_Scroll->m_Value % m_LineHeight) == 0)
                m_VisibleLines = TGUI_MINIMUM((m_Size.y - m_LeftBorder - m_TopBorder) / m_LineHeight, m_Lines);
            else
                m_VisibleLines = TGUI_MINIMUM(((m_Size.y - m_LeftBorder - m_TopBorder) / m_LineHeight) + 1, m_Lines);
        }
        else // There is no scrollbar
        {
            // You are always at the top line
            m_TopLine = 1;

            // Calculate the number of visible lines
            m_VisibleLines = TGUI_MINIMUM((m_Size.y - m_LeftBorder - m_TopBorder) / m_LineHeight, m_Lines);
        }

        // Check if there are multiple lines
        if (m_Lines > 1)
        {
            std::string::size_type newLinePos;

            // Create a temporary string to remove part of the text
            std::string tempText = m_DisplayedText;

            // Remove line by line
            for (unsigned int i=1; i<m_TopLine; ++i)
            {
                // Where is the new line in the string?
                newLinePos = tempText.find('\n');

                // Erase the text until the new line
                if (newLinePos != std::string::npos)
                    tempText.erase(0, newLinePos + 1);
                else
                {
                    // It should be impossible to get here. The number of lines differs from the stored number.
                    m_Loaded = false;
                }
            }

            // Reset the position
            newLinePos = 0;

            // Only remove the last lines if they no longer fit inside the text box
            if (m_Lines - m_VisibleLines - m_TopLine + 1 > 0)
            {
                // Skip all the visible lines
                for (unsigned int i=0; i<m_VisibleLines; ++i)
                    newLinePos = tempText.find('\n', newLinePos + 1);

                // Remove the remaining lines
                tempText.erase(newLinePos);
            }

/// TODO: Support selection
            // Store the remaining lines
            m_TextBeforeSelection.setString(tempText);
        }
        else // There is only one line
        {
/// TODO: Support selection
            // Set the text to be displayed
            m_TextBeforeSelection.setString(m_DisplayedText);
        }

        // Set the position of the selection point
        m_SelectionPointPosition = sf::Vector2u(m_TextBeforeSelection.findCharacterPos(m_SelEnd + newlinesAddedBeforeSelection));

        // Only do the check when the selection point is not standing at the first character
        if ((m_SelEnd > 0) && (m_SelEnd + newlinesAddedBeforeSelection > 0))
        {
            // If you are at the end of the line then also set the selection point there, instead of at the beginning of the next line
            if ((m_Text[m_SelEnd - 1] != '\n') && (m_DisplayedText[m_SelEnd + newlinesAddedBeforeSelection - 1] == '\n'))
                m_SelectionPointPosition = sf::Vector2u(m_TextBeforeSelection.findCharacterPos(m_SelEnd + newlinesAddedBeforeSelection - 1));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::update()
    {
        // Only show/hide the selection point every half second
        if (m_AnimationTimeElapsed < sf::milliseconds(500))
            return;

        // Reset the elapsed time
        m_AnimationTimeElapsed = sf::Time();

        // Only update when the editbox is visible
        if (m_Visible == false)
            return;

        // Switch the value of the visible flag
        m_SelectionPointVisible = m_SelectionPointVisible ? false : true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Don't draw anything when the text box wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Adjust the transformation
        states.transform *= getTransform();

        // Store the transformation
        sf::Transform oldTransform = states.transform;

        // Draw the borders
        sf::RectangleShape Back(Vector2f(static_cast<float>(m_Size.x), static_cast<float>(m_Size.y)));
        Back.setFillColor(m_BorderColor);
        target.draw(Back, states);

        // Reset the transformation
        states.transform = sf::Transform();

        // Clear our render texture
        m_RenderTexture->clear(m_BackgroundColor);

        // Adjust the text position
        if (m_Scroll != NULL)
            states.transform.translate(2, - static_cast<float>(m_Scroll->m_Value % m_LineHeight));
        else
            states.transform.translate(2, 0);

/// TODO: Support selection
        // Draw the text
        m_RenderTexture->draw(m_TextBeforeSelection, states);

        // Only draw the selection point if it has a width
        if (selectionPointWidth > 0)
        {
            // Only draw it when needed
            if ((m_Focused) && (m_SelectionPointVisible))
            {
                // Create the selection point rectangle
                sf::RectangleShape selectionPoint(sf::Vector2f(selectionPointWidth, m_LineHeight));
                selectionPoint.setFillColor(selectionPointColor);

                // Set the position of the rectangle
                if (m_Scroll == NULL)
                    selectionPoint.setPosition(m_SelectionPointPosition.x - (selectionPointWidth * 0.5f), static_cast<float>(m_SelectionPointPosition.y));
                else
                    selectionPoint.setPosition(m_SelectionPointPosition.x - (selectionPointWidth * 0.5f), static_cast<float>(m_SelectionPointPosition.y) - m_Scroll->m_Value);

                // Draw the selection point
                m_RenderTexture->draw(selectionPoint, states);
            }
        }


        // Set the correct position of the render texture
        states.transform = oldTransform;
        states.transform.translate(static_cast<float>(m_LeftBorder), static_cast<float>(m_TopBorder));

        // Display the render texture
        m_RenderTexture->display();
        target.draw(sf::Sprite(m_RenderTexture->getTexture()), states);

        // Check if there is a scrollbar
        if (m_Scroll != NULL)
        {
            // Reset the transformation
            states.transform = sf::Transform();
            states.transform.translate(getPosition().x + ((m_Size.x - m_RightBorder) * getScale().x) - m_Scroll->getSize().x, getPosition().y + (m_TopBorder * getScale().y));
            m_Scroll->setScale(1, (getScale().y * (m_Size.y - m_TopBorder - m_BottomBorder)) / m_Scroll->getSize().y);

            // Draw the scrollbar
            target.draw(*m_Scroll, states);

            // Reset the scale of the scrollbar
            m_Scroll->setScale(1, 1);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
