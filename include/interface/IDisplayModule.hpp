/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** IDisplayModule
*/

/// @file IDisplayModule.hpp
/// @brief Interface for graphics libraries in the Arcade project

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "IModule.hpp"

namespace arcade {

    /// @enum Key
    /// @brief Enumeration of all possible key inputs
    enum class Key {
        UNKNOWN = 0,
        // Arrows
        UP,
        DOWN,
        LEFT,
        RIGHT,
        // Actions
        SPACE,
        ENTER,
        ESCAPE,
        BACKSPACE,
        // Numbers
        NUM_0,
        NUM_1,
        NUM_2,
        NUM_3,
        NUM_4,
        NUM_5,
        NUM_6,
        NUM_7,
        NUM_8,
        NUM_9,
        // Letters A-Z
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        // Meta keys for Arcade control
        NEXT_GRAPHICS,  ///< Switch to next graphics library
        PREV_GRAPHICS,  ///< Switch to previous graphics library
        NEXT_GAME,      ///< Switch to next game
        PREV_GAME,      ///< Switch to previous game
        RESTART,        ///< Restart current game
        MENU,           ///< Return to menu
        EXIT            ///< Exit the program
    };

    /// @struct Color
    /// @brief RGBA color representation
    struct Color {
        uint8_t r;  ///< Red component (0-255)
        uint8_t g;  ///< Green component (0-255)
        uint8_t b;  ///< Blue component (0-255)
        uint8_t a;  ///< Alpha channel (0-255, 255 = opaque)

        /// @brief Construct a color
        /// @param red Red component (default: 255)
        /// @param green Green component (default: 255)
        /// @param blue Blue component (default: 255)
        /// @param alpha Alpha component (default: 255)
        Color(uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255, uint8_t alpha = 255)
            : r(red), g(green), b(blue), a(alpha)
        {
        }
    };

    /// @namespace Colors
    /// @brief Predefined common colors
    namespace Colors {
        const Color BLACK(0, 0, 0);
        const Color WHITE(255, 255, 255);
        const Color RED(255, 0, 0);
        const Color GREEN(0, 255, 0);
        const Color BLUE(0, 0, 255);
        const Color YELLOW(255, 255, 0);
        const Color CYAN(0, 255, 255);
        const Color MAGENTA(255, 0, 255);
    }  // namespace Colors

    /// @struct Position
    /// @brief 2D position in screen space
    struct Position {
        float x;  ///< X coordinate
        float y;  ///< Y coordinate

        /// @brief Construct a position
        /// @param posX X coordinate (default: 0.0)
        /// @param posY Y coordinate (default: 0.0)
        Position(float posX = 0.0f, float posY = 0.0f) : x(posX), y(posY) {}
    };

    /// @struct Rect
    /// @brief Rectangle definition for sprites and shapes
    struct Rect {
        int x;       ///< X coordinate of top-left corner
        int y;       ///< Y coordinate of top-left corner
        int width;   ///< Width of rectangle
        int height;  ///< Height of rectangle

        /// @brief Construct a rectangle
        /// @param posX X coordinate (default: 0)
        /// @param posY Y coordinate (default: 0)
        /// @param w Width (default: 0)
        /// @param h Height (default: 0)
        Rect(int posX = 0, int posY = 0, int w = 0, int h = 0)
            : x(posX), y(posY), width(w), height(h)
        {
        }
    };

    /// @enum CoordinateSpace
    /// @brief Coordinate space used by a game for rendering
    enum class CoordinateSpace {
        GRID,  ///< Logical grid coordinates (tile/cell based)
        PIXEL  ///< Logical pixel coordinates
    };

    /// @struct RenderContext
    /// @brief Logical render space description provided by a game
    struct RenderContext {
        int width;              ///< Logical width of the game world
        int height;             ///< Logical height of the game world
        CoordinateSpace space;  ///< Coordinate system used by game entities/text

        RenderContext(int w = 0, int h = 0, CoordinateSpace s = CoordinateSpace::GRID)
            : width(w), height(h), space(s)
        {
        }
    };

    /// @struct Entity
    /// @brief Displayable game entity (character, sprite, or tile)
    ///
    /// This structure supports both terminal-based (ASCII) and graphical rendering.
    /// Terminal libraries will use the character field, while graphical libraries
    /// will use the spritePath and spriteRect fields.
    struct Entity {
        Position pos;            ///< Position on screen
        Position size;           ///< Logical entity size (width/height), <= 0 means auto
        char character;          ///< ASCII character (for terminal-based display)
        Color color;             ///< Entity foreground color
        Color backgroundColor;   ///< Entity background color
        std::string spritePath;  ///< Path to sprite/texture (for graphical libs)
        Rect spriteRect;         ///< Rectangle within sprite sheet (for sprite atlases)

        /// @brief Default constructor
        Entity()
            : size(0.0f, 0.0f), character(' '), color(Colors::WHITE), backgroundColor(Colors::BLACK)
        {
        }
    };

    /// @struct Text
    /// @brief Text to be displayed on screen
    struct Text {
        std::string content;  ///< Text content to display
        Position pos;         ///< Position on screen
        Color color;          ///< Text color
        int fontSize;         ///< Font size (in points or equivalent)

        /// @brief Construct a text object
        /// @param text Text content (default: empty string)
        /// @param x X coordinate (default: 0)
        /// @param y Y coordinate (default: 0)
        /// @param textColor Text color (default: white)
        /// @param size Font size (default: 12)
        Text(const std::string& text = "", float x = 0, float y = 0,
             const Color& textColor = Colors::WHITE, int size = 12)
            : content(text), pos(x, y), color(textColor), fontSize(size)
        {
        }
    };

    /// @class IDisplayModule
    /// @brief Interface for graphics libraries
    ///
    /// This interface must be implemented by all graphics libraries (nCurses, SDL2, SFML, etc.)
    /// The core program will use this interface to render the game state without knowing
    /// which specific graphics library is being used.
    ///
    /// Graphics libraries must NOT contain any game logic. They are purely responsible for
    /// rendering entities and handling input events.
    class IDisplayModule : public IModule {
        public:
        /// @brief Virtual destructor
        virtual ~IDisplayModule() = default;

        /// @brief Initialize the display module
        ///
        /// Opens window/terminal and prepares the graphics system for rendering.
        /// This method should be called once before any rendering operations.
        virtual void init() = 0;

        /// @brief Stop and cleanup the display module
        ///
        /// Closes window/terminal and releases all graphics resources.
        /// This method should be called once when shutting down.
        virtual void stop() = 0;

        /// @brief Get the name of this display module
        /// @return Name of the graphics library (e.g., "SFML", "SDL2", "nCurses")
        virtual const std::string& getName() const = 0;

        /// @brief Clear the screen/window
        ///
        /// Should be called at the beginning of each frame before drawing.
        virtual void clear() = 0;

        /// @brief Display/present the current frame
        ///
        /// Should be called at the end of each frame to show all rendered content.
        /// This typically performs a buffer swap or screen refresh.
        virtual void display() = 0;

        /// @brief Draw an entity at a specific position
        /// @param entity The entity to draw (contains position, color, character/sprite info)
        virtual void drawEntity(const Entity& entity) = 0;

        /// @brief Draw text on screen
        /// @param text The text structure containing content, position, color, and size
        virtual void drawText(const Text& text) = 0;

        /// @brief Draw a filled rectangle
        /// @param rect Rectangle dimensions and position
        /// @param color Fill color
        virtual void drawRectangle(const Rect& rect, const Color& color) = 0;

        /// @brief Get the last key pressed
        ///
        /// Non-blocking call that returns the last key event.
        /// Should return Key::UNKNOWN if no key was pressed since last check.
        ///
        /// @return Key code or Key::UNKNOWN if no key was pressed
        virtual Key getKey() = 0;

        /// @brief Check if the display is still open/running
        /// @return true if window is open, false if user closed it
        virtual bool isOpen() const = 0;

        /// @brief Set the window/screen title
        /// @param title The title string
        virtual void setTitle(const std::string& title) = 0;

        /// @brief Provide the game's logical render context to the display module
        /// @param context Logical render context (size + coordinate space)
        virtual void setRenderContext(const RenderContext& context) = 0;

        /// @brief Get the display width
        /// @return Display width in cells (for terminal) or pixels (for graphical)
        virtual int getWidth() const = 0;

        /// @brief Get the display height
        /// @return Display height in cells (for terminal) or pixels (for graphical)
        virtual int getHeight() const = 0;
    };
}  // namespace arcade
