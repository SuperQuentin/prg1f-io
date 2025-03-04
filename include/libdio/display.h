// Original authors:
// - Florian Duruz
// - Aellen Quentin

#ifndef LIBDIO_DISPLAY_H
#define LIBDIO_DISPLAY_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>
/**
 * Display library to be used in the class PRG1-F.
 * This is a work in progress - PRs are very welcome.
 */
namespace Display {

    /**
     * Common colors to be used.
     */
    enum class Color {
        WHITE = 15,
        YELLOW = 226,
        ORANGE = 214,
        RED = 196,
        AQUA = 122,
        PINK = 207,
        GREEN = 40,
        BLUE = 21,
        BLACK = 16
    };

    // DString represents a colored string. Upon creation, it is initialised with
    // a white text color.
    // It inherits the string class, so all the methods for string are also available
    // to `DString`.
    // In addition, you can use the `<<` operator to add new strings or a new color
    // to a `DString`.
    // Once you're done, you can either call `print()` or output the `DString` to `cout`.
    // This allows for a much faster output, specifically if you create a string out
    // of many elements.
    class DString : public std::string {
    public:
        explicit DString(const std::string &s);
        /**
         * Instantiate a new DString.
         * @param c the color of the string.
         */
        explicit DString(Color c = Color::WHITE);
        /**
         * Sets the color for all following text.
         * @param color for all upcoming text.
         * @return a reference to DString for chaining
         */
        DString &setColor(Color color);

        /**
         * Use DString as a stream
         * @return a reference to DString
         */
        DString &operator<<(const DString &obj);
        /**
         * Use DString as a stream
         * @return a reference to DString
         */
        DString &operator<<(const std::string &obj);
        /**
         * Use DString as a stream
         * @return a reference to DString
         */
        DString &operator<<(const char obj[]);
        /**
         * Use DString as a stream
         * @return a reference to DString
         */
        DString &operator<<(const Color &col);
        /**
         * Use DString as a stream
         * @return a reference to DString
         */
        template<typename T>
        DString &operator<<(T obj);

        /**
         * Prints the string and clears DString.
         * @return a reference to the DString for chaining.
         */
        DString &print();

        /**
         * Resets the string and initialises it with
         * a new color.
         * @return a reference to the DString for chaining.
         */
        DString &reset(Color color = Color::WHITE);

        /**
         * Saves the current cursor position.
         * @return a reference to the DString for chaining.
         */
        DString &saveCursorPosition();
        /**
         * Restores the previously saved cursor position.
         * @return a reference to the DString for chaining.
         */
        DString &goBackToCursorPosition();
        /**
         * Adds a clear string command.
         * @return a reference to the DString for chaining.
         */
        DString &clearScreen();

        /**
         * Returns the maximum line-length of this string.
         * @return the longest line of this string without the ANSI codes
         */
        size_t max_width();
        /**
         * Returns the number of lines in this string
         * @return number of lines
         */
        size_t count_lines();
    };

    /**
     * Initialises the screen - mostly needed for Windows.
     * But for cross-compatibility it should be called anyway.
     */
    void init();
    /**
     * Saves the current cursor position.
     */
    void saveCursorPosition();
    /**
     * Restores a previously saved cursor position.
     */
    void restoreCursorPosition();
    /**
     * Clears the screen using ANSI codes.
     */
    void clearScreen();
    /**
     * Clears the screen using the `system` command.
     */
    void systemClearScreen();

    /**
     * Displays a grid of a 2D vector. Any type that can be sent to `to_string`, plus
     * `string` and `DString` can be passed.
     * @tparam T compatible types to `to_string`, `string`, and `DString`
     * @param grid the 2D grid
     * @param show_grid whether to show the lines between the cells
     * @return the DString for the grid. It must be `print`ed to be shown.
     */
    template<typename T>
    DString displayGrid(const std::vector<std::vector<T>> &grid, bool show_grid = true);
    template<>
    DString displayGrid<std::string>(const std::vector<std::vector<std::string>> &grid, bool show_grid);
    template<>
    DString displayGrid<DString>(const std::vector<std::vector<DString>> &grid, bool show_grid);
    /**
     * Like `displayGrid` but also takes a closure to convert the type to a DString.
     * @tparam T compatible types to `to_string`, `string`, and `DString`
     * @param grid the 2D grid
     * @param convert a closure that takes T and returns a `DString`
     * @param show_grid whether to show the lines between the cells
     * @return the DString for the grid. It must be `print`ed to be shown.
     */
    template<typename T>
    DString displayGridConvert(const std::vector<std::vector<T>> &grid, std::function<DString(T)> convert, bool show_grid = true);
}// namespace Display

#include "display.tpp"

#endif// LIBDIO_DISPLAY_H
