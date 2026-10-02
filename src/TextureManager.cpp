#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

class TextureManager 
{
 public:
    static sf::Texture& get(const std::string &filename) 
	{
        auto& map = getTextures();
        auto it = map.find(filename);
        if(it != map.end())
            return it->second;

        sf::Texture& texture = map[filename];
        if(!texture.loadFromFile(filename)) 
		{
            fprintf(stderr, "Error! Failed to load a texture\n");
			exit(-1);
        }
        return texture;
    }

private:
    static std::unordered_map<std::string, sf::Texture> &getTextures() 
	{
        static std::unordered_map<std::string, sf::Texture> textures;
        return textures;
    }
};