#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int width, length;
vector<vector<int>> matrix;

int getTerrainWidth()
{
    return width;
}

int getTerrainLength()
{
    return length;
}

vector<vector<int>> getTerrainMatrix()
{
    return matrix;
}

void readPPMFile(string fileName)
{
    ifstream ppmFile(fileName);

    if (ppmFile.is_open())
    {
        int lineNumber = 0;
        while (ppmFile)
        {
            string line;
            getline(ppmFile, line);

            stringstream stringSeparator(line);

            if (lineNumber == 0 || lineNumber == 2)
            {
                lineNumber++;
                continue;
            }

            if (lineNumber == 1)
            {
                int i = 0;
                while(getline(stringSeparator, line, ' '))
                {
                    if (i == 0)
                    {
                        width = stoi(line);
                    }
                    else if (i == 1)
                    {
                        length = stoi(line);
                    }

                    i++;
                }

                matrix.resize(length, vector<int>(width, 0));
            }
            else
            {
                int i = 0;
                int j = lineNumber - 3;

                while(getline(stringSeparator, line, ' '))
                {
                    matrix[j][i] = stoi(line);
                    i++;
                }
            }

            lineNumber++;
        }
    }

    ppmFile.close();
}