#pragma once
#include <string>
#include <vector>
#include "Figure.h"
#include "Connections.h"
#include <memory>

class FileManager {
public:
    static std::string OpenFileDialog();
    static std::string SaveFileDialog();
    
    static bool SaveMindMap(const std::string& filename, 
                           const std::vector<std::unique_ptr<Figure>>& figures,
                           const std::vector<std::unique_ptr<Connections>>& connections);
    
    static bool LoadMindMap(const std::string& filename,
                           std::vector<std::unique_ptr<Figure>>& figures,
                           std::vector<std::unique_ptr<Connections>>& connections,
                           sf::RenderWindow& window);
};