#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

using namespace std;

class AssetManager
{
private:
    std::map<std::string, sf::Texture*> mTexturePaths;

    static AssetManager* Instance;

private:

    AssetManager();
    ~AssetManager();

    sf::Texture* LoadTexture(std::string path);

public:
    static AssetManager* Get() {
        if (Instance == nullptr) {
            Instance = new AssetManager;
        }

        return Instance;
    }

    sf::Texture* GetTexture(std::string path);
};
