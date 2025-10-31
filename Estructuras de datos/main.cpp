#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846

struct Soldier {
    sf::CircleShape shape;
    bool isAlive;
    int id;
    float x, y;
    
    Soldier(float posX, float posY, int soldierID) : isAlive(true), id(soldierID), x(posX), y(posY) {
        shape.setRadius(25.0f);
        shape.setPosition(sf::Vector2f(posX - 25.0f, posY - 25.0f));
        shape.setFillColor(sf::Color::Blue);
        shape.setOutlineThickness(3.0f);
        shape.setOutlineColor(sf::Color::White);
    }
    
    void eliminate() {
        isAlive = false;
        shape.setFillColor(sf::Color::Red);
        shape.setOutlineColor(sf::Color::Black);
    }
};

class JosephusVisualization {
private:
    std::vector<Soldier> soldiers;
    int numSoldiers;
    int currentPosition;
    int aliveCount;
    int survivor;
    int attackerPosition;
    int targetPosition;
    bool showAttackLine;
    
public:
    JosephusVisualization(int n) : numSoldiers(n), currentPosition(0), aliveCount(n), 
                                   attackerPosition(-1), targetPosition(-1), showAttackLine(false) {
        createCircle();
        survivor = calculateSurvivor(n);
        std::cout << "Numero de soldados: " << n << std::endl;
        std::cout << "El soldado sobreviviente sera: " << survivor << std::endl;
        std::cout << "Presiona 'K' para eliminar soldados uno por uno" << std::endl;
    }
    
    void createCircle() {
        float centerX = 400.0f;
        float centerY = 300.0f;
        float radius = 200.0f;
        
        for (int i = 0; i < numSoldiers; i++) {
            float angle = (2.0f * M_PI * i) / numSoldiers;
            float x = centerX + radius * cos(angle);
            float y = centerY + radius * sin(angle);
            soldiers.emplace_back(x, y, i + 1);
        }
    }
    
    int calculateSurvivor(int n) {
        if (n == 1) return 1;
        return ((calculateSurvivor(n - 1) + 1) % n) + 1;
    }
    
    void eliminateNext() {
        if (aliveCount <= 1) return;
        
        // Guardar la posición del atacante (soldado actual)
        attackerPosition = currentPosition;
        
        // Encontrar el siguiente soldado vivo (saltando uno)
        int steps = 0;
        while (steps < 2) {
            if (soldiers[currentPosition].isAlive) {
                steps++;
            }
            if (steps < 2) {
                currentPosition = (currentPosition + 1) % numSoldiers;
            }
        }
        
        // Guardar la posición del objetivo
        targetPosition = currentPosition;
        showAttackLine = true;
        
        // Eliminar el soldado actual
        soldiers[currentPosition].eliminate();
        aliveCount--;
        
        std::cout << "Soldado " << soldiers[attackerPosition].id << " ataca al soldado " 
                  << soldiers[targetPosition].id << ". Soldados restantes: " << aliveCount << std::endl;
        
        // Mover al siguiente soldado vivo
        do {
            currentPosition = (currentPosition + 1) % numSoldiers;
        } while (!soldiers[currentPosition].isAlive && aliveCount > 0);
    }
    
    void draw(sf::RenderWindow& window) {
        // Dibujar soldados
        for (auto& soldier : soldiers) {
            window.draw(soldier.shape);
        }
        
        // Dibujar línea de ataque si está activa
        if (showAttackLine && attackerPosition >= 0 && targetPosition >= 0 && 
            attackerPosition < soldiers.size() && targetPosition < soldiers.size()) {
            
            // Crear línea usando RectangleShape
            float dx = soldiers[targetPosition].x - soldiers[attackerPosition].x;
            float dy = soldiers[targetPosition].y - soldiers[attackerPosition].y;
            float length = sqrt(dx * dx + dy * dy);
            
            if (length > 0) {
                sf::RectangleShape line(sf::Vector2f(length, 3.0f));
                line.setPosition(sf::Vector2f(soldiers[attackerPosition].x, soldiers[attackerPosition].y));
                line.setFillColor(sf::Color::Yellow);
                
                // Calcular ángulo de rotación
                float angle = atan2(dy, dx) * 180.0f / M_PI;
                line.setRotation(sf::degrees(angle));
                
                window.draw(line);
                
                // Resaltar al soldado atacante con un borde amarillo
                soldiers[attackerPosition].shape.setOutlineColor(sf::Color::Yellow);
                soldiers[attackerPosition].shape.setOutlineThickness(5.0f);
                
                // Resaltar al soldado objetivo con un borde rojo más grueso
                if (soldiers[targetPosition].isAlive) {
                    soldiers[targetPosition].shape.setOutlineColor(sf::Color::Red);
                    soldiers[targetPosition].shape.setOutlineThickness(5.0f);
                }
            }
        }
    }
    
    bool isFinished() {
        return aliveCount <= 1;
    }
    
    int getAliveCount() {
        return aliveCount;
    }
    
    void resetHighlights() {
        for (auto& soldier : soldiers) {
            if (soldier.isAlive) {
                soldier.shape.setOutlineColor(sf::Color::White);
                soldier.shape.setOutlineThickness(3.0f);
            } else {
                soldier.shape.setOutlineColor(sf::Color::Black);
                soldier.shape.setOutlineThickness(3.0f);
            }
        }
        showAttackLine = false;
    }
};

int main() {
    int numSoldiers;
    std::cout << "=== PROBLEMA DE JOSEPHUS ===" << std::endl;
    std::cout << "Ingrese el numero de soldados: ";
    std::cin >> numSoldiers;
    
    if (numSoldiers < 1 || numSoldiers > 50) {
        std::cout << "Numero invalido de soldados! (debe ser entre 1 y 50)" << std::endl;
        return -1;
    }
    
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Problema de Josephus");
    JosephusVisualization josephus(numSoldiers);
    
    sf::Clock clock;
    bool justAttacked = false;
    
    while (window.isOpen()) {
        std::optional<sf::Event> event;
        while ((event = window.pollEvent())) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            if (auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::K && !josephus.isFinished()) {
                    josephus.eliminateNext();
                    justAttacked = true;
                    clock.restart();
                }
            }
        }
        
        // Resetear highlights después de 2 segundos
        if (justAttacked && clock.getElapsedTime().asSeconds() > 2.0f) {
            josephus.resetHighlights();
            justAttacked = false;
        }
        
        window.clear(sf::Color::Black);
        josephus.draw(window);
        window.display();
    }
    
    return 0;
}