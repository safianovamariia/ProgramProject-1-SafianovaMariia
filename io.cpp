#include "io.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace io
{
    namespace
    {
        // Lambda function parses a string to double
        auto parse_double = [](const std::string &token, int line_number)
        {
            try
            {
                std::size_t pos = 0;
                double value = std::stod(token, &pos);
                if (pos != token.size())
                {
                    throw std::invalid_argument("unparsed characters left");
                }
                return value;
            }
            catch (const std::exception&)
            {
                throw std::runtime_error("Line " + std::to_string(line_number) + ": failed to read a number from '" + token + "'");
            }
        };
    }

    InputData read_input(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file)
        {
            throw std::runtime_error("Failed to open file '" + filename + "'");
        }
        InputData data;
        int line_number = 0;
        std::string line;

        // first line
        if (!std::getline(file, line))
        {
            throw std::runtime_error("Cannot read the first line");
        }
        ++line_number;
        {
            std::size_t pos = 0;
            bool ok = true;
            try
            {
                data.n = std::stol(line, &pos);
            }
            catch (const std::exception&)
            {
                ok = false;
            }
            if (!ok || pos != line.size() || data.n <= 0)
            {
                throw std::runtime_error("Expected positive number of points");
            }
        }

        // second line
        if (!std::getline(file, line))
        {
            throw std::runtime_error("Start point line not found");
        }
        ++line_number;
        {
            std::istringstream iss(line);
            std::string tx, ty, extra;
            if (!(iss >> tx >> ty) || (iss >> extra))
                throw std::runtime_error("Expected coordinates (x,y)");
            data.start.x = parse_double(tx, line_number);
            data.start.y = parse_double(ty, line_number);
        }

        // transformation lines
        while (std::getline(file, line))
        {
            ++line_number;

            if (line.find_first_not_of(" \t\r\n") != std::string::npos)
            {
                std::istringstream iss(line);
                std::vector<std::string> tokens;
                std::string tok;

                while (iss >> tok)
                {
                    tokens.push_back(tok);
                }

                if (tokens.size() != 6)
                {
                    throw std::runtime_error("Transformation requires exactly 6 numbers, found in file " + std::to_string(tokens.size()));
                }
                AffineTransform t;
                t.a11 = parse_double(tokens[0], line_number);
                t.a12 = parse_double(tokens[1], line_number);
                t.a21 = parse_double(tokens[2], line_number);
                t.a22 = parse_double(tokens[3], line_number);
                t.b1  = parse_double(tokens[4], line_number);
                t.b2  = parse_double(tokens[5], line_number);
                data.transforms.push_back(t);
            }
        }

        if (data.transforms.empty())
        {
            throw std::runtime_error("Affine transformations was not found in the file");
        }
        return data;
    }
}