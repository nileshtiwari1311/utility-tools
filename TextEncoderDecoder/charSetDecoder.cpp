#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>
#include <map>
#include <set>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream ifile, mfile;
    ofstream ofile;

    static struct option long_options[] =
    {
        /* These options don’t set a flag.
           We distinguish them by their indices. */
        {"in",  required_argument, 0, 'i'},
        {"out",  required_argument, 0, 'o'},
        {"map",  required_argument, 0, 'm'},
        {0, 0, 0, 0}
    };

    while (1)
    {
        /* getopt_long stores the option index here. */
        int option_index = 0;
        int id;

        id = getopt_long (argc, argv, "i:o:m:", long_options, &option_index);

        /* Detect the end of the options. */
        if (id == -1)
          break;

        switch (id)
        {
        case 'i':
          ifile.open(optarg, ios::in);
          break;

        case 'o':
          ofile.open(optarg, ios::out);
          break;

        case 'm':
          mfile.open(optarg, ios::in);
          break;

        case '?':
          /* getopt_long already printed an error message. */
          abort();
          break;

        default:
          abort ();
        }
    }

    srand(42);

    char ch, chNew;
    map<char, char> charMap;
    int x, y;

    while (mfile >> x >> y) {
        charMap[char(x)] = char(y);
    }

    for (auto ptr : charMap) {
        cout << ptr.first << " -> " << ptr.second << endl;
    }

    // Read characters one by one until end of file
    while (ifile.get(ch)) {
        // Process the character (you can do whatever you want here)
        if (charMap.count(ch))
            chNew = charMap[ch];
        else
            chNew = ch;
        ofile << chNew;
    }

    // Close the file
    ifile.close();
    ofile.close();
    mfile.close();

    return 0;
}
