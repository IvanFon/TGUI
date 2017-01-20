---
layout: page
title: "Example: Scalable login screen"
breadcrumb: "scalable login screen"
---
``` c++
#include <TGUI/TGUI.hpp>
#include <iostream>

void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{
    std::cout << "Username: " << username->getText().toAnsiString() << std::endl;
    std::cout << "Password: " << password->getText().toAnsiString() << std::endl;
}

void loadWidgets( tgui::Gui& gui )
{
    // Create the background image
    // The picture is of type tgui::Picture::Ptr which is actually just a typedef for std::shared_widget<Picture>
    // Instead of setting a fixed size, we are passing a layout represented as a string
    // The layout will take care of resizing the picture when the parent (here the gui) gets resized
    // Giving the picture a minimum size of 800x600 is just for show what the layout system can do
    auto picture = tgui::Picture::create("../xubuntu_bg_aluminium.jpg");
    picture->setSize({"max(800, parent.width)", "max(600, parent.height)"});
    gui.add(picture);

    // Create the username edit box
    // Similar to the picture, we set a layout to automatically update the position and size when the size of the gui changes
    // In case it isn't obvious, the default text is the text that is displayed when the edit box is empty
    auto editBoxUsername = tgui::EditBox::create();
    editBoxUsername->setSize({"parent.width * 2/3", "parent.height / 8"});
    editBoxUsername->setPosition({"parent.width / 6", "parent.height / 6"});
    editBoxUsername->setDefaultText("Username");
    gui.add(editBoxUsername);

    // Create the password edit box
    // We copy the previous edit box here and keep the same size
    auto editBoxPassword = tgui::EditBox::copy(editBoxUsername);
    editBoxPassword->setPosition({"parent.width / 6", "parent.height * 5/12"});
    editBoxPassword->setPasswordCharacter('*');
    editBoxPassword->setDefaultText("Password");
    gui.add(editBoxPassword);

    // Create the login button
    // Instead of "parent.width" and "parent.width", we use the shorter "&.w" and "&.h" here as an example
    auto button = tgui::Button::create("Login");
    button->setSize({"&.w / 2", "&.h / 6"});
    button->setPosition({"&.w / 4", "&.h * 7/10"});
    gui.add(button);

    // Call the login function when the button is pressed and pass the edit boxes that we created as parameters
    button->connect("pressed", login, editBoxUsername, editBoxPassword);
}

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(400, 300), "TGUI window");
    tgui::Gui gui(window);

    try
    {
        loadWidgets(gui);
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return 1;
    }

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // When the window is closed, the application ends
            if (event.type == sf::Event::Closed)
                window.close();

            // When the window is resized, the view is changed
            else if (event.type == sf::Event::Resized)
            {
                window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
                gui.setView(window.getView());
            }

            // Pass the event to all the widgets
            gui.handleEvent(event);
        }

        window.clear();

        // Draw all created widgets
        gui.draw();

        window.display();
    }

    return EXIT_SUCCESS;
}
```