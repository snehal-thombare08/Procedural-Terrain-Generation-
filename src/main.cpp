#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <array>

const int WIDTH = 1024, HEIGHT = 768;
const int TILE = 4;
const int COLS = WIDTH / TILE;
const int ROWS = HEIGHT / TILE;

// Perlin Noise
float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }
float lerp(float a, float b, float t) { return a + t * (b - a); }
float grad(int hash, float x, float y) {
    int h = hash & 3;
    float u = h < 2 ? x : y;
    float v = h < 2 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

std::array<int,512> perm;
void initPerlin(int seed = 42) {
    std::array<int,256> p;
    for(int i=0;i<256;i++) p[i]=i;
    for(int i=255;i>0;i--) {
        int j = (seed * 1664525 + 1013904223 * i) & 255;
        std::swap(p[i], p[j]);
    }
    for(int i=0;i<512;i++) perm[i]=p[i&255];
}

float perlin(float x, float y) {
    int xi = (int)std::floor(x) & 255;
    int yi = (int)std::floor(y) & 255;
    float xf = x - std::floor(x);
    float yf = y - std::floor(y);
    float u = fade(xf), v = fade(yf);
    int aa=perm[perm[xi]+yi], ab=perm[perm[xi]+yi+1];
    int ba=perm[perm[xi+1]+yi], bb=perm[perm[xi+1]+yi+1];
    return lerp(lerp(grad(aa,xf,yf), grad(ba,xf-1,yf),u),
                lerp(grad(ab,xf,yf-1), grad(bb,xf-1,yf-1),u), v);
}

float octavePerlin(float x, float y, int octaves, float persistence) {
    float total=0, frequency=1, amplitude=1, maxVal=0;
    for(int i=0;i<octaves;i++){
        total += perlin(x*frequency, y*frequency) * amplitude;
        maxVal += amplitude;
        amplitude *= persistence;
        frequency *= 2;
    }
    return total / maxVal;
}

sf::Color heightColor(float h) {
    if(h < 0.3f) return sf::Color(30, 100, 200);        // Deep water
    if(h < 0.38f) return sf::Color(60, 140, 220);       // Shallow water
    if(h < 0.42f) return sf::Color(240, 220, 160);      // Sand/beach
    if(h < 0.6f)  return sf::Color(80, 160, 60);        // Grass
    if(h < 0.72f) return sf::Color(60, 120, 40);        // Forest
    if(h < 0.82f) return sf::Color(120, 100, 80);       // Mountain rock
    if(h < 0.92f) return sf::Color(160, 140, 120);      // High rock
    return sf::Color(240, 240, 255);                     // Snow
}

int main() {
    sf::RenderWindow window(sf::VideoMode({(unsigned)WIDTH,(unsigned)HEIGHT}), "Procedural Terrain Gen - WASD to move, +/- zoom");
    window.setFramerateLimit(60);

    initPerlin(42);

    float offsetX = 0, offsetY = 0;
    float scale = 0.004f;
    bool needRegen = true;

    sf::Image img({(unsigned)WIDTH,(unsigned)HEIGHT});
    sf::Texture tex;
    tex.resize({(unsigned)WIDTH,(unsigned)HEIGHT});
    sf::Sprite sprite(tex);

    sf::Font font;
    bool hasFont = font.openFromFile("C:/Windows/Fonts/arial.ttf");
    sf::Text info(font);
    info.setCharacterSize(16);
    info.setFillColor(sf::Color::White);
    info.setOutlineColor(sf::Color::Black);
    info.setOutlineThickness(1);
    info.setPosition({10,10});

    while(window.isOpen()) {
        while(auto ev = window.pollEvent()) {
            if(ev->is<sf::Event::Closed>()) window.close();
            if(auto* k = ev->getIf<sf::Event::KeyPressed>()) {
                if(k->code == sf::Keyboard::Key::Escape) window.close();
                if(k->code == sf::Keyboard::Key::Equal) { scale *= 0.8f; needRegen=true; }
                if(k->code == sf::Keyboard::Key::Hyphen) { scale *= 1.25f; needRegen=true; }
                if(k->code == sf::Keyboard::Key::R) { initPerlin(rand()); needRegen=true; }
            }
        }

        float speed = 80.f * scale;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { offsetY -= speed; needRegen=true; }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { offsetY += speed; needRegen=true; }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { offsetX -= speed; needRegen=true; }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { offsetX += speed; needRegen=true; }

        if(needRegen) {
            for(int row=0; row<ROWS; row++) {
                for(int col=0; col<COLS; col++) {
                    float nx = (col * TILE + offsetX) * scale;
                    float ny = (row * TILE + offsetY) * scale;
                    float h = octavePerlin(nx, ny, 6, 0.5f);
                    h = (h + 1.f) * 0.5f;
                    sf::Color c = heightColor(h);
                    for(int dy=0;dy<TILE;dy++)
                        for(int dx=0;dx<TILE;dx++)
                            img.setPixel({(unsigned)(col*TILE+dx),(unsigned)(row*TILE+dy)}, c);
                }
            }
            tex.update(img);
            needRegen = false;
        }

        if(hasFont) {
            info.setString("WASD: Move  |  +/-: Zoom  |  R: New Seed  |  Esc: Quit");
        }

        window.clear();
        window.draw(sprite);
        if(hasFont) window.draw(info);
        window.display();
    }
    return 0;
}
