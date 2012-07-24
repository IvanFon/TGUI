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


#ifndef _TGUI_CHILD_WINDOW_INCLUDED_
#define _TGUI_CHILD_WINDOW_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Movable Panel with title bar.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct TGUI_API ChildWindow : public Panel, OBJECT_BORDERS
    {

        // Layouts
        enum Layout
        {
            LayoutLeft,
            LayoutRight
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChildWindow();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChildWindow(const ChildWindow& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~ChildWindow();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChildWindow& operator= (const ChildWindow& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Makes a copy of the object.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ChildWindow* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Creates the child window.
        ///
        /// \param width            Sets the width of the child window.
        /// \param height           Sets the height of the child window.
        /// \param backgroundColor  Sets the background color of the child window.
        /// \param pathname         The path to the folder that contains the images for the titlebar and an optional background image.
        ///                         The folder must also contain an info.txt file, which will give more information about the child window.
        ///
        /// \return
        ///        - true on success
        ///        - false when the pathname was empty
        ///        - false when the info.txt file was not found
        ///        - false when the images couldn't be loaded
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool load(unsigned int width, unsigned int height, const sf::Color& backgroundColor, const std::string pathname);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the pathname that was used to load the child window.
        ///
        /// When the child window has not been loaded yet then this function will return an empty string.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getLoadedPathname();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Change the height of the title bar.
        ///
        /// The default height is the height of the title bar image that is loaded with the load function.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTitlebarHeight(unsigned int height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the height of the title bar.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTitleBarHeight() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the transparency of the window.
        ///
        /// By default all objects in the window are drawn fully opaque, but with this function you can make them semi-transparent.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTransparency(unsigned char transparency);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the transparency of the window.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned char getTransparency() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the borders.
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
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Send the event to all underlying objects.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void handleEvent(sf::Event& event, const float mouseX = 0, const float mouseY = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // With this function, the child window will tell the EventManager if the mouse is on top of it or not.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnObject(float x, float y);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Because this struct is derived from sf::Drawable, you can just call the draw function from your sf::RenderTarget.
        // This function will be called and it will draw the child window on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /// Should the close button be on the right side or on the left side of the title bar?
        Layout layout;

        /// The distance between the side of the title bar and the close button.
        unsigned int distanceToSide;

        /// The color that is used to draw the borders of the window
        sf::Color borderColor;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        unsigned int  m_TitleBarHeight;
        std::string   m_LoadedPathname;
        bool          m_SplitImage;
        Vector2f      m_DraggingPosition;
        unsigned char m_Opacity;

        sf::Texture*  m_TextureTitleBar_L;
        sf::Texture*  m_TextureTitleBar_M;
        sf::Texture*  m_TextureTitleBar_R;

        sf::Sprite    m_SpriteTitleBar_L;
        sf::Sprite    m_SpriteTitleBar_M;
        sf::Sprite    m_SpriteTitleBar_R;

        tgui::Button* m_CloseButton;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_CHILD_WINDOW_INCLUDED_
