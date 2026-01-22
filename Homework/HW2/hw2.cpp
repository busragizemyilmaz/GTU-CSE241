#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Memory {
public:
    Memory()
    {
        for (int i = 0; i < 100; i++)
            memory[i] = 0;
    }

    int getValue(int address)
    {
        if (address >= 0 && address < 100)
            return memory[address];
        
        else
            return -1;
    }

    void setValue(int address, int value)
    {
        memory[address] = value;
    }

    void printMemory()
    {
        for (int i = 0; i < 100; i++)
            cout << memory[i] << " ";
    }
private:
    int memory[100];
};

class CPU {
public:
    CPU()
    {
        for (int i = 0; i < 6; i++)
            registers[i] = 0;
        
        PC = 0;
        isHalted = false;
    }

    void loadInstructions(string filename);
    void run(int option);
    void execute(string instructionLine);
    void printRegisters()
    {
        for (int i = 0; i < 6; i++)
            cout << "R"<< i + 1 << "=" << registers[i] << "  ";
    }
private:
    int registers[6];
    int PC;
    Memory myMemory;
    bool isHalted;
    vector<string> instructions;
    bool isRegister(string s);
    bool isAddress(string s);
    int getRegisterIndex(string r);
    int getAddressValue(string a);
    int getOperandValue(string op);
};

int stringToInteger(string str);
string trim(const string& str);
vector<string> parseInstruction(string line);

void CPU::loadInstructions(string filename)
{
    ifstream file;
    string line;
    int counter = 0;

    file.open(filename);

    while(getline(file, line))
    {
        instructions.push_back(line);

        counter++;

        if (counter > 500)
        {
            cerr << "The program allow at most 500 lines or instructions. You can not this limit!\n";

            break;
        }
    }

    file.close();
}

void CPU::run(int option)
{
    string currentLine;

    while (!isHalted && PC < instructions.size())
    {
        currentLine = instructions[PC];

        if (option == 0)
        {
            execute(currentLine); 
        }

        else if (option == 1)
        {
            if (currentLine.substr(0, 3) != "HLT")
            {
                cout << currentLine << endl;
                execute(currentLine); 
                printRegisters();
                cout << endl << endl;
            }

            else
            {
                cout << currentLine << endl;
                execute(currentLine);
            }
        }

        else if (option == 2)
        {
            if (currentLine.substr(0, 3) != "HLT")
            {
                cout << currentLine << endl;
                execute(currentLine);
                printRegisters();
                cout << endl;
                myMemory.printMemory();
                cout << endl << endl;
            }

            else
            {
                cout << currentLine << endl;
                execute(currentLine);
            }
        }

        else if (option != 0)
        {
            cerr << "This option is invalid!\n";
            isHalted = true;
        }

        if (!isHalted)
            PC++;
    }
}

void CPU::execute(string instructionLine)
{
    string mainPart;
    vector<string> parts = parseInstruction(instructionLine);
    string command = parts[0];
    string parametre1;
    string parametre2;
    int value1;
    int value2;
    int result;

    if (command == "HLT")
    {
        isHalted = true;
        printRegisters(); 
        cout << endl;
        myMemory.printMemory(); 
        cout << endl;
    }
    
    else if (command == "MOV")
    {
        parametre1 = parts[1];
        parametre2 = parts[2];

        value2 = getOperandValue(parametre2);

        if (isRegister(parametre1))
            registers[getRegisterIndex(parametre1)] = value2;

        else if (isAddress(parametre1))
            myMemory.setValue(getAddressValue(parametre1), value2);

        else
        {
            cerr << "Parametre1 can not be constant!\n";
            isHalted = true;
            return;
        }
    }

    else if (command == "ADD")
    {
        parametre1 = parts[1];
        parametre2 = parts[2];

        if (!isRegister(parametre1))
        {
            cerr << "Parametre1 must be register!\n";
            isHalted = true;
            return;
        }

        value1 = getOperandValue(parametre1);
        value2 = getOperandValue(parametre2);

        result = value1 + value2;
        registers[getRegisterIndex(parametre1)] = result;
    }

    else if (command == "SUB")
    {
        parametre1 = parts[1];
        parametre2 = parts[2];

        if (!isRegister(parametre1))
        {
            cerr << "Parametre1 must be register!\n";
            isHalted = true;
            return;
        }

        value1 = getOperandValue(parametre1);
        value2 = getOperandValue(parametre2);

        result = value1 - value2;
        registers[getRegisterIndex(parametre1)] = result;  
    }

    else if (command == "JPN")
    {
        parametre1 = parts[1];
        parametre2 = parts[2];

        value1 = getOperandValue(parametre1);
        value2 = stringToInteger(parametre2);

        if (value1 <= 0)
        {
            PC = value2 - 2;
        }
    }

    else if (command == "JMP")
    {
        parametre1 = parts[1];

        value1 = stringToInteger(parametre1);

        PC = value1 - 2;
    }

    else if (command == "PRN")
    {
        parametre1 = parts[1];

        cout << getOperandValue(parametre1) << endl;
    }

    else if (command == "INP")
    {
        parametre1 = parts[1];

        if (!isRegister(parametre1))
        {
            cerr << "Parametre1 must be register!" << endl;
            isHalted = true;

            return;
        }

        char inputChar;
        cout << "Input: ";
        cin >> inputChar;
        registers[getRegisterIndex(parametre1)] = (int)inputChar;
    }

    else
    {
        cerr << "This command is not found!\n";

        return;
    }
}

int main(int argc, char* argv[])
{
    string fileName;
    int option;
    CPU myCPU;

    if (argc != 3)
    {
        cerr << "You should enter 3 parameters. Command format: ./yourProg filename option";

        return 1;
    }

    fileName = argv[1];
    option = stringToInteger(argv[2]);
    myCPU.loadInstructions(fileName);
    myCPU.run(option);
}

int stringToInteger(string str)
{
    bool isNegative = false;
    int startIndex = 0;
    int result = 0;

    if (str[0] == '-')
    {
        isNegative = true;
        startIndex = 1;
    }

    for (int i = startIndex; i < str.size(); i++)
    {
        if (isdigit(str[i]))
            result = (result * 10) + (str[i] - '0');

        else
            continue;
    }

    if (isNegative)
        return -result;

    else
        return result;
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

vector<string> parseInstruction(string line)
{
    vector<string> parts;
    string command;
    string parameters;
    string parametre1;
    string parametre2;
    int positionOfMain;
    int positionOfCommand;
    int positionOfParametre1;

    positionOfMain = line.find(";");  //MOV R1, 10 ; line 1, load value 10 to the register 1 //JMP 2 ; line 5, go to line 2 //HLT ; finish the program
    line = trim(line.substr(0, positionOfMain));  //MOV R1, 10  //JMP 2  //HLT 

    positionOfCommand = line.find(" ");  
    if (positionOfCommand == string::npos)
    {
        command = trim(line.substr(0));  //for HLT
        parametre1 = "";
        parametre2 = "";

        parts.push_back(command);

        return parts;
    }
    command = trim(line.substr(0, positionOfCommand));
    parts.push_back(command);
    parameters = trim(line.substr(positionOfCommand));

    positionOfParametre1 = parameters.find(",");
    if (positionOfParametre1 == string::npos)
    {
        parametre1 = parameters;  //for JMP 2
        parametre2 = "";

        parts.push_back(parametre1);
        return parts;
    }
    parametre1 = trim(parameters.substr(0, positionOfParametre1));
    parts.push_back(parametre1);

    parametre2 = trim(parameters.substr(positionOfParametre1 + 1));
    parts.push_back(parametre2);

    return parts;
}

bool CPU::isRegister(string s)
{
    if (s[0] == 'R')
        return true;

    else
        return false;
}

bool CPU::isAddress(string s)
{
    if (s[0] == '#')
        return true;

    else
        return false;
}

int CPU::getRegisterIndex(string r)
{
    return stringToInteger(r.substr(1)) - 1;
}

int CPU::getAddressValue(string a)
{
    return stringToInteger(a.substr(1));
}

int CPU::getOperandValue(string op)
{
    if (isRegister(op))
    {

        return registers[getRegisterIndex(op)];
    }

    else if (isAddress(op))
    {
        return myMemory.getValue(getAddressValue(op));
    }

    else
    {
        return stringToInteger(op);
    }
}