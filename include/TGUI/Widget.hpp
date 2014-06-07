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


#ifndef TGUI_WIDGETS_HPP
#define TGUI_WIDGETS_HPP


#include <TGUI/Global.hpp>
#include <TGUI/ConfigFile.hpp>
#include <TGUI/Callback.hpp>
#include <TGUI/Transformable.hpp>
#include <TGUI/SharedWidgetPtr.hpp>
#include <TGUI/Texture.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class Container;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The parent class for every widget.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Widget : public sf::Drawable, public Transformable, public CallbackManager
    {
      public:

        typedef SharedWidgetPtr<Widget> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget(const Widget& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Widget() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget& operator= (const Widget& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget by just calling the copy constructor.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget* clone() = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the absolute position of the widget on the screen
        ///
        /// \return Position of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getAbsolutePosition() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Shows the widget.
        ///
        /// The widget won't receive events nor will it be drawn when hidden. The widget is visible by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void show();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Hides the widget.
        ///
        /// The widget won't receive events nor will it be drawn when hidden. The widget is visible by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void hide();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns true when the widget is visible.
        ///
        /// \return Is the widget visible?
        ///
        /// If this function returns false then the widget is hidden, which means that it won't receive events and it won't be drawn.
        /// All widgets are visible by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isVisible() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Enables the widget.
        ///
        /// The widget will receive events and send callbacks again.
        /// All widgets are enabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void enable();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Disables the widget.
        ///
        /// The widget will no longer receive events and it will thus no longer send callbacks.
        /// All widgets are enabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void disable();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns true when the widget is enabled.
        ///
        /// \return Is the widget enabled?
        ///
        /// If this function returns false then the widget is disabled and will longer receive events and it will thus no longer send callbacks.
        /// All widgets are enabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isEnabled() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns true when the widget is disabled.
        ///
        /// \return Is the widget disabled?
        ///
        /// This means that the widget will longer receive events and it will thus no longer send callbacks.
        /// All widgets are enabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isDisabled() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Focus the widget.
        ///
        /// The previously focused widget will be unfocused.
        ///
        /// \see unfocus
        /// \see focusNextWidget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void focus();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unfocus the widget.
        ///
        /// \see focus
        /// \see focusNextWidget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void unfocus();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns true when the widget is focused and false otherwise.
        ///
        /// \return Is the widget focused?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isFocused() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the type of the widget.
        ///
        /// \return Type of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        WidgetTypes getWidgetType() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a pointer to the parent widget.
        ///
        /// \return Pointer to the parent.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container* getParent() const;


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
        /// \brief Returns the transparency of the widget.
        ///
        /// \return The transparency of the widget.
        ///         0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned char getTransparency() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places the widget before all other widgets.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void moveToFront();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places the widget behind all other widgets.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void moveToBack();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the callback id of the widget.
        ///
        /// \param callbackId  The new callback id
        ///
        /// When receiving callback in a function which takes a Callback as parameter (or when polling the callbacks),
        /// you can find a callbackId in this Callback struct which can identify the widget.
        /// This function changes the id that this widget sends on a callback.
        ///
        /// By default, the callback id will be 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCallbackId(unsigned int callbackId);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the callback id of the widget.
        ///
        /// \return Callback id
        ///
        /// \see setCallbackId
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getCallbackId();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called right after the elapsed time is changed.
        // The elapsed time is only changed when the widget has set m_animatedWidget to true.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // The widgets use this function to send their callbacks to their parent and/or to a callback function.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addCallback();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the mouse enters the widget. If requested, a callback will be send.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseEnteredWidget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the mouse leaves the widget. If requested, a callback will be send.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseLeftWidget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void keyPressed(const sf::Event::KeyEvent& event);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void textEntered(sf::Uint32 key);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetFocused();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetUnfocused();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNotOnWidget();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown();


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
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to Widget.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum WidgetCallbacks
        {
            None = 0,                 ///< No trigger
            Focused = 1,              ///< Widget gained focus.
            Unfocused = 2,            ///< Widget lost focus.
            MouseEntered = 4,         ///< Mouse cursor entered in the Widget area.
            MouseLeft = 8,            ///< Mouse cursor left the Widget area.
            WidgetCallbacksCount = 16
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        // When a widget is disabled, it will no longer receive events
        bool m_enabled;

        // Is the widget visible? When it is invisible it will not receive events and it won't be drawn.
        bool m_visible;

        // This will store the different phases that the widget can have
        // e.g. if there isn't a mouse down image then a button should not try to change its image on mouse down
        unsigned char m_widgetPhase;

        // This will point to our parent widget. If there is no parent then this will be nullptr.
        Container* m_parent;

        // How transparent is the widget
        unsigned char m_opacity;

        // Is the mouse on top of the widget? Did the mouse go down on the widget?
        bool m_mouseHover;
        bool m_mouseDown;

        // Are you focused on the widget?
        bool m_focused;

        // Can the widget be focused?
        bool m_allowFocus;

        // Keep track of the elapsed time.
        bool m_animatedWidget;
        sf::Time m_animationTimeElapsed;

        // This is set to true for widgets that have something to be dragged around (e.g. sliders and scrollbars)
        bool m_draggableWidget;

        // This is set to true for widgets that store other widgets inside them
        bool m_containerWidget;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        friend class Container;
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_WIDGETS_HPP
