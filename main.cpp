#include <iostream>
#include <limits> // para std::numeric_limits e etc

void pausar();

void depositar (double& saldo, std::string unidade);

void retirar (double& saldo, std::string unidade);

bool validarSelec (int& selec);

bool validarQuant (double saldo, std::string unidade, double& valor);

void menu (double saldo, std::string unidade);

void err ();

void limparTela ();

int main() {
    
    double saldo = 391.59;
    std::string unidade = "R$ ";
    int selec;
    char repetir = 's';
    
    while (repetir == 's' || repetir == 'S')
    {
        menu(saldo, unidade);
    
        if (!validarSelec(selec))
        {
            selec = 3;
        }
    
    
        switch (selec)
        {
            case 1:
            depositar(saldo, unidade);
            break;
        
            case 2:
            retirar(saldo, unidade);
            break;
        
            default:
            err();
            break;
        }
    
        std::cout << "\n\tDeseja retornar ao menu? (S ou n): ";
        std::cin >> repetir;
        if (repetir != 's' && repetir != 'S' && repetir != 'n' && repetir != 'N')
        {
            err();
            repetir = 'n';
        }
    }
    
    return 0;
}

void menu(double saldo, std::string unidade)
{
    std::cout << "\t|    Simulador de banco    |";
    std::cout << "\n\t|  1 = Depositar.          |";
    std::cout << "\n\t|  2 = Retirar.            |";
    std::cout << "\n\n\tSaldo: " << unidade << saldo;
}

void err()
{
    std::cout << "\nSeleção invalida";
    pausar();
    limparTela();
}

bool validarSelec (int& selec)
{
    std::cout << "\n\n\tSelecionar: ";
    std::cin >> selec;
    if (std::cin.fail()) { // se a leitura falhar
        std::cin.clear(); // limpa o estado de erro
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descarta o valor invalido
        return false;
    }
    
    // verifica se há caracteres como 12.3 ou 12abc
    char next = std::cin.peek();
    if (next != '\n' && next != EOF) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    
    return true;
}

void limparTela()
{
    // ANSI sequence for Windows and Unix-like systems
    std::cout << "\033[2J\033[1;1H";
}

void pausar()
{
    std::cout << "\nPressione ENTER para seguir...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

void depositar (double& saldo, std::string unidade)
{
    double valor;
    if(!validarQuant(saldo, unidade, valor))
    {
        err();
    }
    else
    {
        saldo += valor;
    }
}

bool validarQuant (double saldo, std::string unidade, double& valor)
{
    std::cout << "Valor a depositar/retirar: " << unidade;
    std::cin >> valor;
    if (std::cin.fail()) { // se a leitura falhar
        std::cin.clear(); // limpa o estado de erro
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descarta o valor invalido
        return false;
    }
    
    // verifica se há caracteres como 12.3 ou 12abc
    char next = std::cin.peek();
    if (next != '\n' && next != EOF) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    
    return true;
}

void retirar (double& saldo, std::string unidade)
{
    double valor;
    if(!validarQuant(saldo, unidade, valor))
    {
        err();
    }
    else
    {
        saldo -= valor;
        std::cout << saldo;
    }
}