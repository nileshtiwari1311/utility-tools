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
    ifstream ifile;
    ofstream ofile, mfile;

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
          mfile.open(optarg, ios::out);
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
    map<char, char> charMapForw;
    map<char, char> charMapBack;
    set<int> charSet;

    for (int i=0; i<26; i++) {
        int idx = rand() % 26;
        while (idx == i || charSet.count(idx)) 
            idx = rand() % 26;
        charSet.insert(idx);

        charMapForw[char('a' + i)] = char('a' + idx);
        // cout << "charMapForw " << char('a' + i) << " -> " << charMapForw[char('a' + i)] << endl;
        charMapForw[char('A' + i)] = char('A' + idx);
        // cout << "charMapForw " << char('A' + i) << " -> " << charMapForw[char('A' + i)] << endl;
        charMapBack[char('a' + idx)] = char('a' + i);
        // cout << "charMapBack " << char('a' + idx) << " -> " << charMapBack[char('a' + idx)] << endl;
        charMapBack[char('A' + idx)] = char('A' + i);
        // cout << "charMapBack " << char('A' + idx) << " -> " << charMapBack[char('A' + idx)] << endl;
        // cout << endl;
    }

    // cout << "Forward Map" << endl;
    // for (auto ptr : charMapForw) {
    //     cout << ptr.first << " -> " << ptr.second << endl;
    // }

    // cout << endl << "Backward Map" << endl;
    // for (auto ptr : charMapBack) {
    //     cout << ptr.first << " -> " << ptr.second << endl;
    // }

    for (auto ptr : charMapBack) {
        mfile << int(ptr.first) << " " << int(ptr.second) << endl;
        cout << ptr.first << " -> " << ptr.second << endl;
    }

    // Read characters one by one until end of file
    while (ifile.get(ch)) {
        // Process the character (you can do whatever you want here)
        if (charMapForw.count(ch))
            chNew = charMapForw[ch];
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
