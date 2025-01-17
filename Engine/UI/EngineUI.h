#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "UIElements/Border.h"
#include "UIElements/UIElement.h"
#include "UIElements/UISizeBox.h"
#include "UIElements/UIText.h"

class EngineUI
{
public:
    
    
    void AddElement(std::shared_ptr<UIElement> element) {
        m_elements.push_back(element);
    }
    
    void RemoveElement(std::shared_ptr<UIElement> element) {
        m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), element), m_elements.end());
    }
    
    void Draw(sf::RenderWindow& window) {
        for (auto& element : m_elements) {
            element->Draw(window);
        }
    }

private:
    std::vector<std::shared_ptr<UIElement>> m_elements;
};
