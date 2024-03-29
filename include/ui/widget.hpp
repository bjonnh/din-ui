/*
 * Copyright (c) 2023. Jonathan Bisson
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef DIN_UI_2040_WIDGET_HPP
#define DIN_UI_2040_WIDGET_HPP

#include <functional>
#include <cstdint>
#include <set>
#include <memory>

#define UI_WIDGET_CALLBACKS 3
using Uint8FunctionPointer = void(*)(uint8_t);

namespace UI {
    template<typename D>
    class Widget {
    public:
        Widget(Widget<D> &parent);
        /**
         * For the root widget only, all the child widgets will inherit the display (fancy right?)
         * @param display
         */
        explicit Widget(D &display);

        explicit Widget();

        virtual void start();

        virtual void setFocus(bool f);

        virtual void onFocusCall(std::function<void(bool)>);

        virtual void onVisibleCall(std::function<void(bool)>);

        virtual void onExitCall(std::function<void()>);

        virtual void onUpdateCall(std::function<void()>);

        virtual void exit();

        virtual bool click();

        virtual bool move_left();

        virtual bool move_right();

        virtual void update();

        virtual bool clickAction();

        virtual bool leftAction();

        virtual bool rightAction();

        [[nodiscard]] bool isFocused();
        [[nodiscard]] bool isVisible();

        virtual void draw();

        virtual void action();

        virtual void setVisible(bool v);

        std::set<std::unique_ptr<Widget>> childs = {};
    private:
        Widget *parent = nullptr;

        std::vector<std::function<void(bool)>> focus_callbacks = {};
        std::vector<std::function<void(bool)>> visible_callbacks = {};
        std::vector<std::function<void()>> exit_callbacks = {};
        std::vector<std::function<void()>> update_callbacks = {};
    protected:
        D *display;
        bool focus = false;
        bool visible = false;

        virtual void add_child(Widget *pWidget);
    };

} // Manager

#endif //DIN_UI_2040_WIDGET_HPP
