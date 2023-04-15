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

#include "ui/page.hpp"
#include "U8g2lib.h"

namespace UI::Widgets {
    template class Page<U8G2>;

    template<typename D>
    void Page<D>::add_child(Widget<D> *pWidget)  {
        if (first_widget == nullptr)
            first_widget = pWidget;
        Widget<D>::add_child(pWidget);
    }

    template<typename D>
    void Page<D>::setFocus(bool f) {
        for (auto &child: this->childs) {
            child->setFocus(false);
        }
        if (f) {
            // we set focus on one of the childs (we may really need to use a vector here)
            if (first_widget) {
                first_widget->setFocus(true);
            }
        }
    }

    template<typename D>
    void Page<D>::setVisible(bool f) {
        // This doesn't seem to do much besides not calling the callbacks compared to the version in Widget
        this->visible = f;
        for (auto &child: this->childs)
            child->setVisible(f);
    }
}
