#include <bits/stdc++.h>
using namespace std;

void R_format(map<string, string> &m_opcode,
              map<string, char> &m_format,
              map<string, int> &m_funct3)
{
    

}
string getFirstWord(string &line)
{
    istringstream iss(line);
    string firstWord;
    if (iss >> firstWord)
    {
        return firstWord;
    }

    return "";
}
int main()
{
    map<string, string> m_opcode;
    map<string, char> m_format;
    map<string, int> m_funct3;
    m_opcode["add"] = "0110011";
    m_opcode["sub"] = "0110011";
    m_opcode["and"] = "0110011";
    m_opcode["or"] = "0110011";
    m_opcode["xor"] = "0110011";
    m_opcode["sll"] = "0110011";
    m_opcode["srl"] = "0110011";
    m_opcode["sra"] = "0110011";

    m_format["0110011"] = 'R';

    m_funct3["add"] = 0;
    m_funct3["sub"] = 0;
    m_funct3["xor"] = 4;
    m_funct3["or"] = 6;
    m_funct3["and"] = 7;
    m_funct3["sll"] = 1;
    m_funct3["srl"] = 5;
    m_funct3["sra"] = 5;

    string filename = "example.txt";

    // Create an input file stream object
    ifstream infile(filename);

    // Check if the file was opened successfully
    if (!infile)
    {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string line;
    int lineno = 0;
    while (getline(infile, line))
    {
        lineno++;
        string firstWord = getFirstWord(line);
        if (m_format.find(firstWord) == m_format.end())
        {
            cerr << "Command not found: " << firstWord << "in line " << lineno << endl;
            return 0;
        }
        else
        {
            char format = m_format[m_opcode[firstWord]];
            if (format == 'R')
            {
                R_format(m_opcode, m_format, m_funct3);
            }
        }
        cout << line << std::endl;
    }

    infile.close();

    return 0;
}