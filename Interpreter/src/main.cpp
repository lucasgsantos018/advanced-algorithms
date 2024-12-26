#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int RAM_SIZE = 1000;
const int REG_SIZE = 10;

vector<int> ram(RAM_SIZE, 0);
vector<int> reg(REG_SIZE, 0);

int execute(vector<int> &ram) {
    int pc = 0; // Program Counter
    int instructions_count = 0;

    while (true) {
        instructions_count++;
        int instruction = ram[pc];
        int opcode = instruction / 100;
        int d = (instruction / 10) % 10;
        int s_n = instruction % 10;

        switch (opcode) {
            case 1: // halt
                return instructions_count;
            case 2: // set register d to n
                reg[d] = s_n;
                break;
            case 3: // add n to register d
                reg[d] = (reg[d] + s_n) % 1000;
                break;
            case 4: // multiply register d by n
                reg[d] = (reg[d] * s_n) % 1000;
                break;
            case 5: // set register d to the value of register s
                reg[d] = reg[s_n];
                break;
            case 6: // add the value of register s to register d
                reg[d] = (reg[d] + reg[s_n]) % 1000;
                break;
            case 7: // multiply register d by the value of register s
                reg[d] = (reg[d] * reg[s_n]) % 1000;
                break;
            case 8: // set register d to the value in RAM whose address is in register a
                reg[d] = ram[reg[s_n]];
                break;
            case 9: // set the value in RAM whose address is in register a to the value of register s
                ram[reg[s_n]] = reg[d];
                break;
            case 0: // goto the location in register d unless register s contains 0
                if (reg[s_n] != 0) {
                    pc = reg[d] - 1; // -1 because pc will be incremented
                }
                break;
        }
        pc++;
    }
}

int main() {
    int cases;
    cin >> cases;
    cin.ignore(); // Ignore the newline after the number of cases
    string line;

    while (cases--) {
        fill(ram.begin(), ram.end(), 0);
        fill(reg.begin(), reg.end(), 0);

        int i = 0;
        while (getline(cin, line) && !line.empty()) {
            ram[i++] = stoi(line);
        }

        cout << execute(ram) << endl;
        if (cases) cout << endl;
    }

    return 0;
}
