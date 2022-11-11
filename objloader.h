#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include <QMatrix4x4>
#include "crapvectors.h"
#include "crapvectors.h"

#include "vertex.h"

class OBJLoader {
protected:
    static std::vector<Vertex> loadOBJ(const char* fileName, const CrapVector3& color) {
        std::vector"crapvectors.h" vertexPos;
        std::vector"crapvectors.h" vertexTextCoord;
        std::vector"crapvectors.h" vertexNormal;

        std::vector<int> vertexPositionIndicies;
        std::vector<int> vertexNormalIndicies;
        std::vector<int> vertexTextCoordIndicies;

        std::vector<Vertex> vertices;

        std::stringstream ss;
        std::ifstream inFile(fileName);
        std::string line = "";
        std::string prefix = "";

        CrapVector3 tempVec3;
        CrapVector2 tempVec2;
        int tempInt;

        if (!inFile.is_open()) {
            throw "Could not load obj file.";
        }

        while (std::getline(inFile, line)) {
            ss.clear();
            ss.str(line);
            ss >> prefix;

            if (prefix == "v") {
                float x, y, z;
                ss >> x >> y >> z;
                tempVec3 = {x, y, z};
                vertexPos.push_back(tempVec3);
            }
            else if (prefix == "vt") {
                float x, y;
                ss >> x >> y;
                tempVec2 = {x, y};
                vertexTextCoord.push_back(tempVec2);
            }
            else if (prefix == "vn") {
                float x, y, z;
                ss >> x >> y >> z;
                tempVec3 = {x, y, z};
                vertexNormal.push_back(tempVec3);
            }
            else if (prefix == "f") {
                int counter = 0;
                while (ss >> tempInt)
                {
                    if (counter == 0)
                        vertexPositionIndicies.push_back(tempInt);
                    else if (counter == 1)
                        vertexTextCoordIndicies.push_back(tempInt);
                    else if (counter == 2)
                        vertexNormalIndicies.push_back(tempInt);


                    if (ss.peek() == '/') {
                        counter++;
                        ss.ignore(1, '/');
                    }
                    else if (ss.peek() == ' ') {
                        counter++;
                        ss.ignore(1, ' ');
                    }


                    if (counter > 2) {
                        counter = 0;
                    }
                }
            }
        }

        vertices.reserve(vertexPositionIndicies.size());

        for (int i = 0; i < vertexPositionIndicies.size(); i++) {
            CrapVector3 position = vertexPos[vertexPositionIndicies[i]-1];
            CrapVector2 texcoord = vertexTextCoord[vertexTextCoordIndicies[i]-1];
            CrapVector3 normal = vertexNormal[vertexNormalIndicies[i]-1];
            if (color.x() == 0 && color.y() == 0 && color.z() == 0) {
                Vertex vert(position, normal, texcoord.x(), texcoord.y());
                vertices.push_back(vert);
            }
            else {
                Vertex vert(position, color.x(), color.y(), color.z());
                vertices.push_back(vert);
            }
        }


        inFile.close();


        return vertices;
    }
};
#endif // OBJLOADER_H
