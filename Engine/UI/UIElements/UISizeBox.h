#pragma once
#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include "UIElement.h"

class SizeBox : public UIElement {
public:
    SizeBox(const Vector2D& position, const Vector2D& size)
        : UIElement(position, size, sf::Color::White),
          columns(1), rows(1), horizontalSpacing(0), verticalSpacing(0), autoFill(false), padding(0)
    {
        UpdateBackgroundShape();
    }

    void SetGridSize(int cols, int rows) {
        columns = cols;
        this->rows = rows;
    }

    void SetSpacing(float horizontal, float vertical) {
        autoFill = false;
        horizontalSpacing = horizontal;
        verticalSpacing = vertical;
    }

    void SetAutoFill(bool enable) {
        autoFill = enable;
    }

    void SetPadding(float pad) {
        padding = pad;
    }

    void AddChild(std::shared_ptr<UIElement> child) {
        children.push_back(child);
    }

    void SetColor(const sf::Color& color) {
        UIElement::SetColor(color);
        UpdateBackgroundShape();
    }

    void SetScreenPosition(const Vector2D& position) {
        UIElement::SetScreenPosition(position);
        UpdateBackgroundShape();
    }

    void SetScale(const Vector2D& scale) {
        UIElement::SetScale(scale);
        UpdateBackgroundShape();
    }

    void Draw(sf::RenderWindow& window) override {
        // Draw the background first
        window.draw(backgroundShape);

        // Calculate spacing if autoFill is enabled
        if (autoFill) {
            CalculateAutoSpacing();
        }

        // Then draw the children, starting with padding
        float currentX = GetScreenPosition().X + padding;
        float currentY = GetScreenPosition().Y + padding;

        int currentColumn = 0;
        int currentRow = 0;

        for (auto& child : children) {
            Vector2D childSize = child->GetScale(); // Use GetSize()
            child->SetScreenPosition(Vector2D(currentX, currentY));
            child->Draw(window);

            currentX += childSize.X + horizontalSpacing;

            if (++currentColumn >= columns) {
                currentColumn = 0;
                currentX = GetScreenPosition().X + padding;
                currentY += childSize.Y + verticalSpacing;
            }
        }
    }

private:
    std::vector<std::shared_ptr<UIElement>> children;
    int columns;
    int rows;
    float horizontalSpacing;
    float verticalSpacing;
    bool autoFill;
    float padding;
    sf::RectangleShape backgroundShape;

    void UpdateBackgroundShape() {
        backgroundShape.setFillColor(GetColor());
        backgroundShape.setPosition(sf::Vector2f(GetScreenPosition().X, GetScreenPosition().Y));
        backgroundShape.setSize(sf::Vector2f(GetScale().X, GetScale().Y));
    }

    void CalculateAutoSpacing() {
        if (children.empty()) return;

        if (columns <= 0 || rows <= 0) return;

        float availableWidth = GetScale().X - 2 * padding;
        if (columns > 1) {
            float totalChildrenWidth = 0;
            for (const auto& child : children) {
                totalChildrenWidth += child->GetScale().X; // Use GetSize()
            }
            horizontalSpacing = (availableWidth - totalChildrenWidth) / (columns - 1);
            if (horizontalSpacing < 0) horizontalSpacing = 0; // Prevent negative spacing
        } else {
            horizontalSpacing = 0;
        }

        float availableHeight = GetScale().Y - 2 * padding;
        if (rows > 1) {
            float totalChildrenHeight = 0;
            for (const auto& child : children) {
                totalChildrenHeight += child->GetScale().Y; // Use GetSize()
            }
            verticalSpacing = (availableHeight - totalChildrenHeight) / (rows - 1);
            if (verticalSpacing < 0) verticalSpacing = 0; // Prevent negative spacing
        } else {
            verticalSpacing = 0;
        }
    }
};