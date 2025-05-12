#include <iostream>
#include <vector>
#include "../include/utilities.h"

int execute_program(std::vector<int>& ram, std::vector<int>& registers) {
    int pc = 0;
    int instructions_executed = 0;
    
    while (true) {
        int instruction = ram[pc];
        int op = instruction / 100;
        int d = (instruction / 10) % 10;
        int n = instruction % 10;
        int s = n; // para as instruções que usam s ao invés de n
        
        instructions_executed++;
        pc++;
        
        switch (op) {
            case 1: // parar
                return instructions_executed;
            case 2: // registrador d para n
                registers[d] = n;
                break;
            case 3: // adicionando n ao registro d
                registers[d] = (registers[d] + n) % 1000;
                break;
            case 4: // multiplicando o registro d por n
                registers[d] = (registers[d] * n) % 1000;
                break;
            case 5: // definir o registro d com valor do s
                registers[d] = registers[s];
                break;
            case 6: // adicionar valor do s ao d
                registers[d] = (registers[d] + registers[s]) % 1000;
                break;
            case 7: // multiplicar o d pelo valor do s
                registers[d] = (registers[d] * registers[s]) % 1000;
                break;
            case 8: // definir registro d como RAM[registrador a]
                registers[d] = ram[registers[n]];
                break;
            case 9: // definir RAM[register a] com o valor do registro s
                ram[registers[n]] = registers[s];
                break;
            case 0: // ir p endereço do registrador d a menos que o s tenha 0
                if (registers[s] != 0) {
                    pc = registers[d];
                }
                break;
        }
    }
}

int main() {
    std::vector<int> ram = read_ram_input();
    std::vector<int> registers;
    initialize_system(ram, registers);
    
    int result = execute_program(ram, registers);
    std::cout << result << std::endl;
    
    return 0;
}