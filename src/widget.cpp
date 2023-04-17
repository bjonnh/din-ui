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

#include <functional>
#include "../include/ui/widget.hpp"
#include "U8g2lib.h"


namespace UI {
    template class Widget<U8G2>; // TODO Move that somewhere u8g2 specific if possible?

    template<typename D>
    Widget<D>::Widget(Widget<D> &p) {
        parent = &p;
        display = p.display;

        p.add_child(this);
    }

    template<typename D>
    Widget<D>::Widget(D &d) {
        display = &d;
    }

    template<typename D>
    Widget<D>::Widget() { }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

    template<typename D>
    bool Widget<D>::click() {
        if (visible)
            if (focus)
                if (clickAction())
                    return true;
        for (auto &child: childs) {
            if (child->click())
                return true;
        }
        return false;
    }

#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

    template<typename D>
    bool Widget<D>::move_left() {
        if (visible && focus && leftAction())
            return true;
        for (auto &child: childs) {
            if (child->move_left())
                return true;
        }
        return false;
    }

#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

    template<typename D>
    bool Widget<D>::move_right() {
        if (visible && focus && rightAction())
            return true;
        for (auto &child: childs) {
            if (child->move_right())
                return true;
        }
        return false;
    }

#pragma clang diagnostic pop

    template<typename D>
    void Widget<D>::onFocusCall(const std::function<void(bool)> fun) {
        focus_callbacks.push_back(fun);
    }

    template<typename D>
    void Widget<D>::onVisibleCall(const std::function<void(bool)> fun) {
        visible_callbacks.push_back(fun);
    }

    template<typename D>
    void Widget<D>::onExitCall(const std::function<void()> fun) {
        exit_callbacks.push_back(fun);
    }

    template<typename D>
    void Widget<D>::onUpdateCall(const std::function<void()> fun) {
        update_callbacks.push_back(fun);
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

    template<typename D>
    void Widget<D>::draw() {
        if (visible)
            for (auto &child: childs)
                child->draw();
    }

    /**
     * Actions that should be run in the event loop.
     * Keep them short and don't make them draw, they run before drawing.
     * @tparam D
     */
    template<typename D>
    void Widget<D>::action() {
        if (visible)
            for (auto &child: childs)
                child->action();
    }


#pragma clang diagnostic pop

    template<typename D>
    void Widget<D>::add_child(Widget<D> *pWidget) {
        // We still allow to add them but that's on you
        // Same thing if you make a loop
        childs.emplace(pWidget);
    }

    template<typename D>
    void Widget<D>::setFocus(bool f) {
        focus = f;
        if (f)
            parent->focus = false;  // We do not call the function for that as it would enter an endless loop for pages
        for (const auto &item: focus_callbacks)
            item(f);
    }

    template<typename D>
    void Widget<D>::start() {

    }

    template<typename D>
    void Widget<D>::exit() {
        for (const auto &item: exit_callbacks)
            item();
    }

    template<typename D>
    void Widget<D>::update() {
        for (const auto &item: update_callbacks)
            item();
    }

    template<typename D>
    bool Widget<D>::clickAction() {
        return false;
    }

    template<typename D>
    bool Widget<D>::leftAction() {
        return false;
    }

    template<typename D>
    bool Widget<D>::rightAction() {
        return false;
    }

    template<typename D>
    bool Widget<D>::isFocused() {
        return focus;
    }

    template<typename D>
    bool Widget<D>::isVisible() {
        return visible;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

    template<typename D>
    void Widget<D>::setVisible(bool v) {
        visible = v;
        for (const auto &item: visible_callbacks)
            item(v);
        for (auto &child: childs)
            child->setVisible(v);
    }

#pragma clang diagnostic pop
} // Manager
