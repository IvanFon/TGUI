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


#include <cmath>

#include <TGUI/Transformable.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Transformable::Transformable() :
    m_position(0, 0),
    m_transformNeedUpdate(true),
    m_transform()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Transformable::setPosition(float x, float y)
    {
        m_position.x = std::floor(x + 0.5f);
        m_position.y = std::floor(y + 0.5f);

        m_transformNeedUpdate = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Transformable::setPosition(const sf::Vector2f& position)
    {
        setPosition(position.x, position.y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Vector2f& Transformable::getPosition() const
    {
        return m_position;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Transformable::move(float offsetX, float offsetY)
    {
        setPosition(m_position.x + offsetX, m_position.y + offsetY);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Transformable::move(const sf::Vector2f& offset)
    {
        setPosition(m_position.x + offset.x, m_position.y + offset.y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f Transformable::getFullSize() const
    {
        return getSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Transformable::scale(float factorX, float factorY)
    {
        setSize(getSize().x * factorX, getSize().y * factorY);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Transformable::scale(const sf::Vector2f& factors)
    {
        setSize(getSize().x * factors.x, getSize().y * factors.y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Transform& Transformable::getTransform() const
    {
        if (m_transformNeedUpdate)
        {
            m_transform = sf::Transform( 1, 0, m_position.x,
                                         0, 1, m_position.y,
                                         0.f, 0.f, 1.f);

            m_transformNeedUpdate = false;
        }

        return m_transform;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
