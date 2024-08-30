#include <bits/stdc++.h>
using namespace std;

inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
}

inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

inline void trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
}

string toBinary(int num, int num_digits) {
        if(num < 0){
            num = (1 << num_digits) + num;
        }
        string binary;
        while (num > 0) {
            if(num%2 == 1)binary += '1';
            else  binary += '0';   
            num /= 2;
        }
        reverse(binary.begin(), binary.end());
        while (binary.length() < num_digits) {
            binary = '0' + binary;
        }
    return binary;
}


string getFirstWord(string &line)
{
    istringstream iss(line);
    string firstWord;
    int ind = -1;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ' ' || line[i] == ',' || line[i] == ':' || (line[i] == '\n'))
        {
            ind = i;
            break;
        }
    }
    if (ind == -1)
        ind = line.length();
    firstWord = line.substr(0, ind);
    return firstWord;
}

string to_hex(string bin_ins){

    map < string , string > map4bits;

    for(int i = 0; i <= 15; i++){
        if(i <= 9){
            map4bits[toBinary(i, 4)] = '0' + i;
        }else{
            map4bits[toBinary(i, 4)] = 'a' + (i - 10);
        }
    }
    string hexstring;
    for(int i = 0; i < 32; i+= 4){
        string binary4 = bin_ins.substr(i,4);
        hexstring += map4bits[binary4];
    }

    return hexstring;
}
void R_format(map<string, string> &m_opcode,
              map<string, char> &m_format,
              map<string, int> &m_funct3, map<string, string> &alias, string &line, string &command, int lineno)
{
    string temp = line;
    int i = 0;
    string cmd, rs1, rs2, rd, funct3, funct7, opcode;
    while (true)
    {
        string firstWord = getFirstWord(temp);
        // cout << alias[firstWord] << "\n";
        if (i == 0)
        {
            cmd = firstWord;
        }
        else if (i == 1)
        {
            rd = firstWord;
        }
        else if (i == 2)
        {
            rs1 = firstWord;
        }
        else if (i == 3)
        {
            rs2 = firstWord;
        }
        i++;
        if (i == 1)
        {
            int ind_sp = temp.find(' ');
            temp = temp.substr(ind_sp + 1);
            trim(temp);
        }
        else
        {
            int ind_cm = temp.find(',');
            temp = temp.substr(ind_cm + 1);
            trim(temp);
        }
        if (i == 4)
            break;
    }
    rd=alias[rd];
    rs1=alias[rs1];
    rs2=alias[rs2];
    if (alias.find(rs1) == alias.end() || alias.find(rs2) == alias.end() || alias.find(rd) == alias.end()||(int)stoi(rs1.substr(1))>31||(int)stoi(rs2.substr(1))>31||(int)stoi(rd.substr(1))>31)
    {
        cerr << "incorrect register value\n in line " << lineno << "\n";
        exit(0);
    }
    opcode = m_opcode[cmd];
    // cout<<alias[rs1]<<" "<<alias[rd]<<"\n";
    rs1=toBinary(stoi((alias[rs1]).substr(1)),5);
    rs2=toBinary(stoi((alias[rs2]).substr(1)),5);
    rd=toBinary(stoi((alias[rd]).substr(1)),5);
    funct3 = toBinary(m_funct3[cmd],3);

    funct7 = "0000000";
    if (cmd.compare("sub")==0 || cmd.compare("sra")==0)
        funct7 = "0100000";
    string binenc = funct7 + rs2 + rs1 + funct3 + rd + opcode;
    string hexenc=to_hex(binenc);
    cout << hexenc << "\n";
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

    map<string, string> alias;
    alias["zero"] = "x0";
    alias["ra"] = "x1";
    alias["sp"] = "x2";
    alias["gp"] = "x3";
    alias["tp"] = "x4";
    alias["s0"] = "x8";
    alias["fp"] = "x8";  
    alias["s1"] = "x9";

    for (int i = 0; i < 32; i++) {
        alias["x" + to_string(i)] = "x" + to_string(i);
    }
    
    for (int i = 0; i <= 2; ++i) {
        alias["t" + to_string(i)] = "x" + to_string(5 + i);
    }

        for (int i = 0; i <= 7; ++i) {
        alias["a" + to_string(i)] = "x" + to_string(10 + i);
    }

    for (int i = 2; i <= 11; ++i) {
        alias["s" + to_string(i)] = "x" + to_string(18 + (i - 2));
    }

    for (int i = 3; i <= 6; ++i) {
        alias["t" + to_string(i)] = "x" + to_string(28 + (i - 3));
    }
    string filename = "input.s";

    ifstream infile(filename);

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
        if (m_opcode.find(firstWord) == m_opcode.end())
        {
            cerr << "Command not found: " << firstWord << " in line " << lineno << endl;
            return 0;
        }
        else
        {
            char format = m_format[m_opcode[firstWord]];
            if (format == 'R')
            {
                R_format(m_opcode, m_format, m_funct3, alias, line, firstWord, lineno);
            }
        }
        // cout << line << std::endl;
    }
    infile.close();
    return 0;
}