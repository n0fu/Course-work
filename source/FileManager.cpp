#include "FileManager.h"
#include <windows.h>
#include <commdlg.h>
#include <fstream>
#include <sstream>

std::string FileManager::OpenFileDialog() {
    OPENFILENAMEA ofn;
    char szFile[260] = {0};
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "MindMap Files\0*.mmp\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
    if (GetOpenFileNameA(&ofn)) {
        return std::string(szFile);
    }
    return "";
}

std::string FileManager::SaveFileDialog() {
    OPENFILENAMEA ofn;
    char szFile[260] = {0};
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "MindMap Files\0*.mmp\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrDefExt = "mmp";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
    
    if (GetSaveFileNameA(&ofn)) {
        return std::string(szFile);
    }
    return "";
}

bool FileManager::SaveMindMap(const std::string& filename,
                             const std::vector<std::unique_ptr<Figure>>& figures,
                             const std::vector<std::unique_ptr<Connections>>& connections) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    // Сохраняем фигуры с полными данными
    file << "FIGURES:" << figures.size() << "\n";
    for (const auto& figure : figures) {
        sf::Vector2f pos = figure->GetFigurePosition();
        sf::Color color = figure->GetFigureColor();
        unsigned int textSize = figure->GetFigureTextSize();
        std::string text = figure->GetFigureText();
        
        // Заменяем переносы строк на специальный символ
        for (char& c : text) {
            if (c == '\n') c = '|';
        }
        
        file << pos.x << " " << pos.y << " "
             << static_cast<int>(color.r) << " " << static_cast<int>(color.g) << " " 
             << static_cast<int>(color.b) << " " << textSize << " " << text << "\n";
    }
    
    // Сохраняем соединения по индексам
    file << "CONNECTIONS:" << connections.size() << "\n";
    for (const auto& conn : connections) {
        int idx1 = -1, idx2 = -1;
        for (size_t i = 0; i < figures.size(); ++i) {
            if (figures[i].get() == conn->GetFigure1()) idx1 = i;
            if (figures[i].get() == conn->GetFigure2()) idx2 = i;
        }
        if (idx1 != -1 && idx2 != -1) {
            file << idx1 << " " << idx2 << "\n";
        }
    }
    
    file.close();
    return true;
}

bool FileManager::LoadMindMap(const std::string& filename,
                             std::vector<std::unique_ptr<Figure>>& figures,
                             std::vector<std::unique_ptr<Connections>>& connections,
                             sf::RenderWindow& window) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    // Очищаем текущие данные
    figures.clear();
    connections.clear();
    
    std::string line;
    
    // Загружаем фигуры с полными данными
    if (std::getline(file, line) && line.find("FIGURES:") == 0) {
        int figureCount = std::stoi(line.substr(8));
        
        for (int i = 0; i < figureCount; ++i) {
            if (std::getline(file, line)) {
                std::istringstream iss(line);
                float x, y;
                int r, g, b;
                unsigned int textSize;
                std::string text;
                
                if (iss >> x >> y >> r >> g >> b >> textSize) {
                    std::getline(iss, text);
                    if (!text.empty() && text[0] == ' ') text = text.substr(1);
                    
                    // Возвращаем переносы строк
                    for (char& c : text) {
                        if (c == '|') c = '\n';
                    }
                    
                    auto figure = std::make_unique<Figure>(window);
                    figure->SetFigurePosition(sf::Vector2f(x, y));
                    figure->SetFigureText(text);
                    figure->SetFigureColor(sf::Color(r, g, b));
                    figure->SetFigureTextSize(textSize);
                    figures.push_back(std::move(figure));
                }
            }
        }
    }
    
    // Загружаем соединения
    if (std::getline(file, line) && line.find("CONNECTIONS:") == 0) {
        int connCount = std::stoi(line.substr(12));
        
        for (int i = 0; i < connCount; ++i) {
            if (std::getline(file, line)) {
                std::istringstream iss(line);
                int idx1, idx2;
                
                if (iss >> idx1 >> idx2) {
                    if (idx1 >= 0 && idx2 >= 0 && 
                        static_cast<size_t>(idx1) < figures.size() && 
                        static_cast<size_t>(idx2) < figures.size()) {
                        connections.push_back(std::make_unique<Connections>(
                            figures[idx1].get(), figures[idx2].get()));
                    }
                }
            }
        }
    }
    
    file.close();
    return true;
}