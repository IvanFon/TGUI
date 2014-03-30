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


#ifndef TGUI_BORDERS_HPP
#define TGUI_BORDERS_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Borders
    {
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param leftBorderWidth    Width of the left border
        /// \param topBorderHeight    Height of the top border
        /// \param rightBorderWidth   Width of the right border
        /// \param bottomBorderHeight Height of the bottom border
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Borders(float leftBorderWidth = 0,
                float topBorderHeight = 0,
                float rightBorderWidth = 0,
                float bottomBorderHeight = 0) :
            left  (leftBorderWidth),
            top   (topBorderHeight),
            right (rightBorderWidth),
            bottom(bottomBorderHeight)
        {
        }

        /// Width of the left border
        float left;

        /// Height of the top border
        float top;

        /// Width of the right border
        float right;

        /// Height of the bottom border
        float bottom;
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Parent class for every widget that has borders.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API WidgetBorders
    {
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the borders.
        ///
        /// \param leftBorder    Size of the left border
        /// \param topBorder     Size of the top border
        /// \param rightBorder   Size of the right border
        /// \param bottomBorder  Size of the bottom border
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBorders(float leftBorder = 0,  float topBorder = 0,
                                float rightBorder = 0, float bottomBorder = 0) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the borders as a tgui::Borders.
        ///
        /// \return border sizes
        ///
        /// The first element will be the size of the left border, the seconds is the size of the top border,
        /// the third is the size of the right border and the the last constains the size of the bottom border.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Borders getBorders() const
        {
            return m_borders;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        Borders m_borders;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_BORDERS_HPP
