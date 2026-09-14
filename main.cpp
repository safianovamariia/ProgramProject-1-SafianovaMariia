// compiler MSVC
// Author: Safianova Mariia K25
// Variant: 2

#include <iostream>
#include <fstream>
#include <functional>
#include <exception>
#include "point.h"
#include "affine_transform.h"
#include "random_transformer.h"
#include "io.h"
using namespace std;

// Generates n points and writes them to "out"
void generate_sequence(Point start, long n, const function<Point(const Point &)> &next, ostream &out)
{
    Point current = start;
    for (long i = 0; i < n; ++i)
    {
        current = next(current);
        out << current.x << ' ' << current.y << '\n';
    }
}

int main(int argc, char *argv[]) {

    string input_file = "input.txt";
    string output_file = "output.txt";
    if (argc > 1) 
    {
        input_file = argv[1];
    }
    if (argc > 2) 
    {
        output_file = argv[2];
    }

    try
    {
        io::InputData data = io::read_input(input_file);
        RandomAffineTransformer transformer(data.transforms);
        function<Point(const Point &)> next = transformer;
        ofstream out(output_file);
        if (!out)
        {
            throw runtime_error("Failed to create output file " + output_file);
        }
        generate_sequence(data.start, data.n, next, out);

        cout << "Generation has done " << data.n << " points to " << output_file << endl;
    }
    catch (const exception &ex)
    {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}
