//
// Created by oleg on 18.12.2021.
//
#include <SFML/Graphics.hpp>
#include <unistd.h>

#include <cmath>
#include <iostream>


void drawLineRed(int x1, int y1, int x2, int y2, sf::RenderWindow &window) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    sf::Vertex point(sf::Vector2f(x2, y2), sf::Color::Red);
    window.draw(&point, 1, sf::Points);
    while (x1 != x2 || y1 != y2) {
        sf::Vertex point1(sf::Vector2f(x1, y1), sf::Color::Red);
        window.draw(&point1, 1, sf::Points);
        int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}
double distance(std::pair<int, int> P0, std::pair<int, int> P1, std::pair<int, int> P2) {
    double ch = std::abs((P2.second - P0.second) * P1.first + (P0.first - P2.first) * P1.second - P0.first * P2.second + P2.first * P0.second);
    double zn = std::sqrt((P0.first - P2.first) * (P0.first - P2.first) + (P2.second - P0.second) * (P2.second - P0.second));
    if (zn == 0) return 0;
    else
        return ch / zn;
}
std::vector<std::pair<int, int>> bezie(std::pair<int, int> P0, std::pair<int, int> P1, std::pair<int, int> P2, sf::RenderWindow &window) {
    std::vector<std::pair<int, int>> v;
    std::vector<std::pair<int, int>> v_tmp;
    if (distance(P0, P1, P2) > 4) {
        std::pair<int, int> P0_(0.5 * (P0.first + P1.first), 0.5 * (P0.second + P1.second));
        std::pair<int, int> P1_(0.5 * (P1.first + P2.first), 0.5 * (P1.second + P2.second));
        std::pair<int, int> P0__(0.5 * (P0_.first + P1_.first), 0.5 * (P0_.second + P1_.second));
        v_tmp = bezie(P0, P0_, P0__, window);
        for (int i = 0; i < v_tmp.size(); ++i) {
            v.push_back(v_tmp[i]);
        }
        v_tmp = bezie(P0__, P1_, P2, window);
        for (int i = 0; i < v_tmp.size(); ++i) {
            v.push_back(v_tmp[i]);
        }
        return v;
    } else
        drawLineRed(P0.first, P0.second, P2.first, P2.second, window);
    v.push_back(P0);
    v.push_back(P2);
    return v;
}

void bezieX(std::vector<std::pair<int, int>> v, sf::RenderWindow &window){
    for (std::size_t a = 0; a < 360; a += 10) {
        float alpha = a * M_PI / 180;

        std::vector<std::pair<int, int>> vx;
        for (int i = 0; i < v.size() ; ++i) {
            vx.push_back(std::make_pair(v[i].first, v[i].second*std::cos(alpha)));
        }

        auto it0 = vx.begin();
        auto it1 = vx.begin();
        ++it1;
        for (; it1 != vx.end(); ++it0, ++it1) {
          drawLineRed(it0->first, it0->second, it1->first, it1->second, window);
        }

    }
}
void bezieY(std::vector<std::pair<int, int>> v, sf::RenderWindow &window){
    for (std::size_t a = 0; a < 360; a += 10) {
        float alpha = a * M_PI / 180;

        std::vector<std::pair<int, int>> vx;
        for (int i = 0; i < v.size() ; ++i) {

            vx.push_back(std::make_pair(v[i].first * std::cos(alpha), v[i].second));
        }

        auto it0 = vx.begin();
        auto it1 = vx.begin();
        ++it1;
        for (; it1 != vx.end(); ++it0, ++it1) {
            drawLineRed(it0->first, it0->second, it1->first, it1->second, window);
        }

    }
}
void bezieZ(std::vector<std::pair<int, int>> v, sf::RenderWindow &window){
    for (std::size_t a = 0; a < 360; a += 10) {
        float alpha = a * M_PI / 180;

        std::vector<std::pair<int, int>> vx;
        for (int i = 0; i < v.size() ; ++i) {
            vx.push_back(std::make_pair(v[i].first * std::cos(alpha) - v[i].second * std::sin(alpha) ,
                                        v[i].first * std::sin(alpha) + v[i].second * std::cos(alpha)));
        }

        auto it0 = vx.begin();
        auto it1 = vx.begin();
        ++it1;
        for (; it1 != vx.end(); ++it0, ++it1) {
            drawLineRed(it0->first, it0->second, it1->first, it1->second, window);
        }

    }
}
int main() {
    sf::RenderWindow window(sf::VideoMode(740, 680), "HW6");
    window.setFramerateLimit(50);
    std::vector<std::pair<int, int>> vec_points;
    bool dr = false;
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                    return 0;
                }
                case sf::Event::MouseButtonPressed: {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (vec_points.size() < 3) {
                            vec_points.insert(vec_points.begin(), 1, std::make_pair(event.mouseButton.x, event.mouseButton.y));
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        if (vec_points.size() >= 3) {
            auto it0 = vec_points.begin();
            auto it1 = vec_points.begin();
            ++it1;
            //for (; it1 != vec_points.end(); ++it0, ++it1) {
             //   drawLineRed(it0->first, it0->second, it1->first, it1->second, window);
            //}
            auto v = bezie(vec_points[0], vec_points[1], vec_points[2], window);
            //bezieX(v, window);
            //bezieY(v, window);
           bezieZ(v, window);
        }
        window.display();
    }
    return 0;
}

