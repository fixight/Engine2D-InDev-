#include <iostream>
#include <SFML/Graphics.hpp>
#include "Objects/Object.h"
#include "SmartPointer.h"
int main()
{

    
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML Sprite Example");

    // Создаем текстуру
    sf::Texture texture;

    // Загружаем изображение в текстуру
    if (!texture.loadFromFile("Sprites/Test.png")) {
        std::cerr << "Ошибка при загрузке текстуры!" << std::endl;
        return -1;
    }

    // Проверка размера текстуры
    std::cout << "Размер текстуры: " << texture.getSize().x << "x" << texture.getSize().y << std::endl;

    // Создаем спрайт
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Устанавливаем начальное положение спрайта
    sprite.setPosition(100, 100);
    
    sf::Vector2u textureSize = texture.getSize();

    
    float desiredWidth = 100.f;
    float desiredHeight = 100.f;

    SmartPointer<int> sp1(new int(42));
    std::cout << "Создан sp1, количество ссылок: 1\n";

    
    SmartPointer<int> sp2 = sp1;
    std::cout << "Создан sp2 как копия sp1, количество ссылок: 2\n";

    // Вычисляем масштаб
    float scaleX = desiredWidth / textureSize.x;
    float scaleY = desiredHeight / textureSize.y;

    // Устанавливаем масштаб
    sprite.setScale(scaleX, scaleY);

    // Игровой цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Очистка окна
        window.clear(sf::Color::Black);

        // Рисуем спрайт
        window.draw(sprite);

        // Отображаем изменения
        window.display();
    }

    return 0;
    
}

