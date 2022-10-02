#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
/* Reads ascii file of 1s and 0s and the writes a binary file. */

struct PBM
{
    unsigned int width;
    unsigned int height;
    string comment;
    vector<vector<char>> data;

    bool ReadAscii(ifstream& f)
    {
        string id;
        if(!getline(f, id) || id != "P1")
        {
            return false;
        }
        if(f.peek() == '#' && !getline(f, comment))
        {
            return false;
        }
        if(!(f >> width >> height))
        {
            return false;
        }
        data.resize(height);
        int temp;
        for(size_t y = 0; y < data.size(); ++y)
        {
            data[y].resize(width);
            for(size_t x = 0; x < width; ++x)
            {
                if(!(f >> temp))
                {
                    return false;
                }
                data[y][x] = static_cast<char>(temp);
            }
        }
        return true;
    }

    bool WriteBinary(ofstream& f)
    {
        if(!(f << "P4\n"))
        {
            return false;
        }
        if(!comment.empty() && !(f << comment << "\n"))
        {
            return false;
        }
        if(!(f << width << " " << height << "\n"))
        {
            return false;
        }
        // vector<char> linebits((width + (CHAR_BIT - 1)) / CHAR_BIT);
        for(size_t y = 0; y < data.size(); ++y)
        {
            // fill(linebits.begin(), linebits.end(), 0);
            // for(size_t x = 0; x < width; ++x)
            // {
            //     const int byte_pos = x / CHAR_BIT;
            //     const int bit_pos = (CHAR_BIT - 1) - (x % CHAR_BIT);
            //     linebits[byte_pos] |= (data[y][x] << bit_pos);
            // }
            // if(!f.write(&linebits[0], linebits.size()))
            // {
            //     return false;
            // }
        }
        return true;
    }
    // bool WriteBinary(ofstream& f)
    // {
    //     if(!(f << "P4\n"))
    //     {
    //         return false;
    //     }
    //     if(!comment.empty() && !(f << comment << "\n"))
    //     {
    //         return false;
    //     }
    //     if(!(f << width << " " << height << "\n"))
    //     {
    //         return false;
    //     }
    //     vector<char> linebits((width + (CHAR_BIT - 1)) / CHAR_BIT);
    //     for(size_t y = 0; y < data.size(); ++y)
    //     {
    //         fill(linebits.begin(), linebits.end(), 0);
    //         for(size_t x = 0; x < width; ++x)
    //         {
    //             const int byte_pos = x / CHAR_BIT;
    //             const int bit_pos = (CHAR_BIT - 1) - (x % CHAR_BIT);
    //             linebits[byte_pos] |= (data[y][x] << bit_pos);
    //         }
    //         if(!f.write(&linebits[0], linebits.size()))
    //         {
    //             return false;
    //         }
    //     }
    //     return true;
    // }
};

int main(int argc, char * argv[])
{
    if(argc != 3)
    {
        cerr << "Usage: convertpbm <ascii filename> <binary filename>\n";
        return 0;
    }

    PBM pbm;

    ifstream inFile(argv[1]);
    if(!inFile)
    {
        cerr << "Could not open '" << argv[1] << "' for input!\n";
        return 0;
    }
    if(!pbm.ReadAscii(inFile))
    {
        cerr << "Error reading input file!\n";
    }

    ofstream outFile(argv[2], ios::binary);
    if(!outFile)
    {
        cerr << "Could not open '" << argv[1] << "' for output!\n";
        return 0;
    }
    if(!pbm.WriteBinary(outFile))
    {
        cerr << "Error writing output file!\n";
    }

    return 0;
}
