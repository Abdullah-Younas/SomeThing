#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <math.h>

float smoothstep(float edge0, float edge1, float x) {
    // Scale, and clamp x to 0..1 range
    x = std::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    // Evaluate polynomial
    return x * x * (3 - 2 * x);
}
sf::Vector2f fract(const sf::Vector2f& uv) {
    return sf::Vector2f(std::fmod(uv.x, 1.0f), std::fmod(uv.y, 1.0f));
}

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(500, 500), "Animated Circles"); // creating window
    sf::Font font;
    if (!font.loadFromFile("G:\\abdullah\\Abdullah(Dont Delete Any thing)\\FONTS\\Rubik_Mono_One\\RMOR.ttf")) {
        std::cout << "Can't load/find the file" << '\n';
    }
    sf::Clock clock;
    sf::Clock fpsClock;
    int fpsCounter = 0;
    std::vector<sf::RectangleShape> pixels;
    int Pixels = 500;
    int r = 255;
    int g = 255;
    int b = 255;
    float elapsedTime = 0.0;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds() * 2; // Get the elapsed time since the last frame
        elapsedTime += deltaTime;
        fpsCounter++;
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0) {
            std::cout << "FPS: " << fpsCounter << std::endl;
            fpsCounter = 0;
            fpsClock.restart();
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Clicking\n";
            }
        }

        // Clearing the vector of pixels
        pixels.clear();

        // Creating new pixels
        float pixelSize = 2.5f; // Adjust the pixel size as needed
        float xPos = 0;
        float yPos = 0;

        for (int row = 0; row < window.getSize().y / pixelSize; ++row) {
            for (int col = 0; col < window.getSize().x / pixelSize; ++col) {
                float rowF = row;
                float colF = col;

                sf::Vector2f uv(colF / (window.getSize().x / pixelSize), rowF / (window.getSize().y / pixelSize));
                uv.x = uv.x - 0.5f;
                uv.y = uv.y - 0.5f;
                uv.x = uv.x * 2.0f;
                uv.y = uv.y * 2.0f;

                sf::Color colllor = sf::Color(75,175,255);

                // Use the distance from the center to calculate a grayscale value
                float distance = sqrtf(uv.x * uv.x + uv.y * uv.y);
                distance = distance * 10.0;
                distance = sin(distance + elapsedTime) / distance; // Use elapsedTime
                distance = abs(distance);
                float gradient = 0.08 / distance;
                colllor.r *= gradient;
                colllor.g *= gradient;
                colllor.b *= gradient;
                sf::RectangleShape newPixel(sf::Vector2f(pixelSize, pixelSize));

                // Adjust the color values to create a gradient
                sf::Color pixelColor = sf::Color(255 * colllor.r, 255 * colllor.g, colllor.b, 255);
                newPixel.setFillColor(pixelColor);
                newPixel.setPosition(xPos, yPos);
                pixels.push_back(newPixel);

                // Update positions for the next iteration
                xPos += pixelSize;
            }

            // Move to the next row
            xPos = 0;
            yPos += pixelSize;
        }

        window.clear(); // clearing window before using

        // Draw all the pixels in the vector
        for (const auto& pixel : pixels) {
            window.draw(pixel);
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        window.display(); // displaying everything
    }

    return 0;
}
