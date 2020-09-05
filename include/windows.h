#ifndef __WINDOWS_H
#define __WINDOWS_H

class Window {
    public:
    int m_x1, m_x2, m_y1, m_y2;
    Window(int x1, int x2, int y1, int y2)
        : m_x1(x1), m_x2(x2), m_y1(y1), m_y2(y2) {}
};

#endif