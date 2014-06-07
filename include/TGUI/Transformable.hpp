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

#ifndef TGUI_TRANSFORMABLE_HPP
#define TGUI_TRANSFORMABLE_HPP


#include <TGUI/Global.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class TGUI_API Transformable
    {
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Transformable();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Transformable() {}


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


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// \param position New position
        ///
        /// \see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPosition(const sf::Vector2f& position);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief get the position of the widget
        ///
        /// \return Current position
        ///
        /// \see setPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Vector2f& getPosition() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Move the widget by a given offset
        ///
        /// This function adds to the current position of the widget, unlike setPosition which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// sf::Vector2f pos = widget.getPosition();
        /// widget.setPosition(pos.x + offsetX, pos.y + offsetY);
        /// \endcode
        ///
        /// \param offsetX X offset
        /// \param offsetY Y offset
        ///
        /// \see setPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void move(float offsetX, float offsetY);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Move the widget by a given offset
        ///
        /// This function adds to the current position of the widget, unlike setPosition which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// widget.setPosition(widget.getPosition() + offset);
        /// \endcode
        ///
        /// \param offset Offset
        ///
        /// \see setPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void move(const sf::Vector2f& offset);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the widget.
        ///
        /// \param width   Width of the widget
        /// \param height  Height of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(float width, float height) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the widget.
        ///
        /// \return Size of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the entire size that the widget is using.
        ///
        /// This function will return a value equal or greater than what getSize returns.
        /// If the widget would e.g. have borders around it then this function will return the size, including these borders.
        ///
        /// \return Full size of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Scale the widget
        ///
        /// \param factorX  Horizontal scale factor
        /// \param factorY  Vertical scale factor
        ///
        /// This function multiplies the current size of the widget with the given scale factors.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// widget.setSize(getSize().x * factorX, getSize().y * factorY);
        /// \endcode
        ///
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void scale(float factorX, float factorY);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Scale the widget
        ///
        /// \param factors  Scale factors
        ///
        /// This function multiplies the current size of the widget with the given scale factors.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// widget.setSize(getSize().x * factors.x, getSize().y * factors.y);
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void scale(const sf::Vector2f& factors);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the transform.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const sf::Transform& getTransform() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      private:

        sf::Vector2f m_position;

        mutable bool          m_transformNeedUpdate;
        mutable sf::Transform m_transform;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TRANSFORMABLE_HPP
