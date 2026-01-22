#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str);
void parseLine(string line, string& command, string& parametre1, string& parametre2, string& mainPart);
bool isRegister(string str);
int registerToIndex(string str);
bool isNumber(const string& s) ;

int main(int argc, char *argv[])
{
    string fileName;
    int option;
    vector<string> lines;
    ifstream file;
    string tempLine;
    int registers[6] = {0, 0, 0, 0, 0, 0};
    int counter = 0;
    bool halted = false;
    string command, parametre1, parametre2, mainPart;
    int index;
    int tempIndex;
    int lineIndex;
    char character;

    if (argc != 3)
    {
        cerr << "You should enter 3 parameters. Command format: ./yourProg filename option";

        return 1;
    }

    fileName = argv[1];
    option = stoi(argv[2]);

    if (option != 0 && option != 1)
    {
        cerr << "You can not enter except 0 and 1.\n";

        return 1;
    }

    file.open(fileName);
    if (!file.is_open())
    {
        cerr << "The file does not open.\n";

        return 1;
    }

    while (getline(file, tempLine))
    {
        lines.push_back(tempLine);
    }
    file.close();

    while (!halted && counter < lines.size())
    {
        parseLine(lines[counter], command, parametre1, parametre2, mainPart);

        if (option == 1)
        {
            cout << mainPart << endl;
        }

        if (command == "HLT")
        {
            halted = true;
        }

        else if (command == "MOV")
        {
            if (!isRegister(parametre2))
            {
                if (!isNumber(parametre2)) 
                {
                    cerr << "Error: We expected number but input -> " << parametre2 << endl;

                    halted = true;
                    break;
                }

                else
                {
                    index = registerToIndex(parametre1);
                    if (index == -1) 
                    {
                        cerr << "Error: Invalid register name -> " << parametre1 << endl;

                        halted = true;
                        break;
                    }
                    registers[index] = stoi(parametre2);
                }
            }

            else
            {
                index = registerToIndex(parametre1);
                if (index == -1) 
                {
                    cerr << "Error: Invalid register name -> " << parametre1 << endl;

                    halted = true;
                    break;
                }

                tempIndex = registerToIndex(parametre2);
                if (tempIndex == -1) 
                {
                    cerr << "Error: Invalid register name -> " << parametre2 << endl;

                    halted = true;
                    break;
                }
                registers[index] = registers[tempIndex];
            }

            counter++;
        }
        
        else if (command == "ADD")
        {
            if (!isRegister(parametre2))
            {
                if (!isNumber(parametre2)) 
                {
                    cerr << "Error: We expected number but input -> " << parametre2 << endl;
                    
                    halted = true;
                    break;
                }

                else
                {
                    index = registerToIndex(parametre1);
                    if (index == -1) 
                    {
                        cerr << "Error: Invalid register name -> " << parametre1 << endl;

                        halted = true;
                        break;
                    }
                    registers[index] += stoi(parametre2);
                }
            }

            else
            {
                index = registerToIndex(parametre1);
                if (index == -1) 
                {
                    cerr << "Error: Invalid register name -> " << parametre1 << endl;

                    halted = true;
                    break;
                }

                tempIndex = registerToIndex(parametre2);
                if (tempIndex == -1) 
                {
                    cerr << "Error: Invalid register name -> " << parametre2 << endl;

                    halted = true;
                    break;
                }
                registers[index] += registers[tempIndex];
            }

            counter++;
        }

        else if (command == "SUB")
        {
            if (!isRegister(parametre2))
            {
                if (!isNumber(parametre2)) 
                {
                    cerr << "Error: We expected number but input -> " << parametre2 << endl;
                    
                    halted = true;
                    break;
                }

                else
                {
                    index = registerToIndex(parametre1);
                    if (index == -1) 
                    {
                        cerr << "Error: Invalid register name -> " << parametre1 << endl;

                        halted = true;
                        break;
                    }
                    
                    registers[index] -= stoi(parametre2);
                }
            }

            else
            {
                index = registerToIndex(parametre1);
                if (index == -1) 
                {
                    cerr << "Error: Invalid register name -> " << parametre1 << endl;

                    halted = true;
                    break;
                }

                tempIndex = registerToIndex(parametre2);
                if (tempIndex == -1) 
                {
                    cerr << "Error: Invalid register name -> " << parametre2 << endl;

                    halted = true;
                    break;
                }
                registers[index] -= registers[tempIndex];
            }

            counter++;
        }
        
        else if (command == "JMP")
        {
            if (parametre2 == "")
            {
                if (!isNumber(parametre1)) 
                {
                    cerr << "Error: We expected number but input -> " << parametre1 << endl;
                    
                    halted = true;
                    break;
                }

                else
                {   
                    lineIndex = stoi(parametre1) - 1;
                    if (lineIndex >= lines.size())
                    {
                        cerr << "You can enter until " << lines.size() << " line" << endl;

                        halted = true;
                        break;
                    }
                    counter = lineIndex;
                }
            }

            else
            {
                index = registerToIndex(parametre1);
                if (index == -1) 
                {
                    cerr << "Error: Invalid register name -> " << parametre1 << endl;

                    halted = true;
                    break;
                }

                if (registers[index] == 0)
                {
                    if (!isNumber(parametre2)) 
                    {
                        cerr << "Error: We expected number but input -> " << parametre2 << endl;
                        
                        halted = true;
                        break;
                    }

                    else
                    {
                        lineIndex = stoi(parametre2) - 1;

                        if (lineIndex >= lines.size())
                        {
                            cerr << "You can enter until " << lines.size() << endl;

                            halted = true;
                            break;
                        }
                        counter = lineIndex;
                    }
                }

                else
                    counter++;
            }
        }
        
        else if (command == "PRN")
        {
            if (!isRegister(parametre1))
            {
                if (!isNumber(parametre1))
                {
                    cerr << "Error: Invalid PRN name -> " << parametre1 << endl;
                    
                    halted = true;
                    break;
                }

                else
                    cout << stoi(parametre1) << endl;
            }
            
            else
            {
                index = registerToIndex(parametre1);
                if (index == -1) 
                {
                    cerr << "Error: Invalid register name -> " << parametre1 << endl;

                    halted = true;
                    break;
                }

                cout << registers[index] << endl;
            }
                
            counter++;
        }
        
        else if (command == "INP")
        {
            cin >> character;

            index = registerToIndex(parametre1);
            if (index == -1) 
            {
                cerr << "Error: Invalid register name -> " << parametre1 << endl;

                halted = true;
                break;
            }
            registers[index] = character;

            counter++;
        }

        else
        {
            cerr << command <<" does not found. Please enter valid command.\n";

            halted = true;
        }

        if (option == 1)
        {
            cout << "R1=" << registers[0] << ", R2=" << registers[1] << ", R3=" << registers[2] 
                 << ", R4=" << registers[3] << ", R5=" << registers[4] << ", R6=" << registers[5] << endl << endl;
        }
    }
}

string trim(const string& str) 
{
    const string WHITESPACE = " \t\n\r";
    int start = str.find_first_not_of(WHITESPACE);
    int end;

    if (start == string::npos) 
        return "";

    end = str.find_last_not_of(WHITESPACE);

    return str.substr(start, (end - start + 1));
}

void parseLine(string line, string& command, string& parametre1, string& parametre2, string &mainPart)
{
    string parameters;
    int positionOfMain;
    int positionOfCommand;
    int positionOfParametre1;

    positionOfMain = line.find(";");  //MOV R1, 10 ; line 1, load value 10 to the register 1 //JMP 2 ; line 5, go to line 2 //HLT ; finish the program
    mainPart = trim(line.substr(0, positionOfMain));  //MOV R1, 10  //JMP 2  //HLT 

    positionOfCommand = mainPart.find(" ");  
    if (positionOfCommand == string::npos)
    {
        command = trim(mainPart.substr(0));  //for HLT
        parametre1 = "";
        parametre2 = "";

        return;
    }
    command = trim(mainPart.substr(0, positionOfCommand));
    parameters = trim(mainPart.substr(positionOfCommand));

    positionOfParametre1 = parameters.find(",");
    if (positionOfParametre1 == string::npos)
    {
        parametre1 = parameters;  //for JMP 2
        parametre2 = "";

        return;
    }
    parametre1 = trim(parameters.substr(0, positionOfParametre1));

    parametre2 = trim(parameters.substr(positionOfParametre1 + 1));
}

bool isRegister(string str)
{
    if (str[0] == 'R')
        return true;
    
    else
        return false;
}

int registerToIndex(string str)
{
    if (str == "R1")
        return 0;
    
    else if (str == "R2")
        return 1;

    else if (str == "R3")
        return 2;

    else if (str == "R4")
        return 3;

    else if (str == "R5")
        return 4;

    else if (str == "R6")
        return 5;

    else
        return -1;
}

bool isNumber(const string& s) 
{
    if (s.empty()) 
        return false;

    for (char c : s) 
    {
        if (!isdigit(c) && c != '-') 
            return false;
    }

    return true;
}