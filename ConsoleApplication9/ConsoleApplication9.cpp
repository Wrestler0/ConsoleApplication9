#include <iostream>
#include <string>

// Класс Client для представления клиента банка
class Client {
public:
    std::string name;
    int clientId;

    Client(const std::string& name, int clientId) : name(name), clientId(clientId) {}
};

// Класс BankAccount для представления банковского счета
class BankAccount {
public:
    int accountNumber;
    double balance;

    BankAccount(int accountNumber, double balance) : accountNumber(accountNumber), balance(balance) {}

    void Deposit(double amount) {
        balance += amount;
        std::cout << "На счет " << accountNumber << " зачислено: " << amount << " руб.\n";
    }

    void Withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            std::cout << "Со счета " << accountNumber << " снято: " << amount << " руб.\n";
        }
        else {
            std::cout << "Недостаточно средств на счете.\n";
        }
    }

    double CheckBalance() const {
        return balance;
    }
};

// Интерфейс BankService для банковских услуг
class BankService {
public:
    virtual void Deposit(double amount) = 0;
    virtual void Withdraw(double amount) = 0;
    virtual double CheckBalance() const = 0;
    virtual ~BankService() = default;
};

// Класс BankAdapter адаптирует BankAccount к интерфейсу BankService
class BankAdapter : public BankService {
private:
    BankAccount* bankAccount;

public:
    BankAdapter(BankAccount* account) : bankAccount(account) {}

    void Deposit(double amount) override {
        bankAccount->Deposit(amount);
    }

    void Withdraw(double amount) override {
        bankAccount->Withdraw(amount);
    }

    double CheckBalance() const override {
        return bankAccount->CheckBalance();
    }
};

// Основная функция main
int main() {
    // Установка русской локализации
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale());

    Client client("Иван Иванов", 1);
    BankAccount account(12345, 1000.0);
    BankService* service = new BankAdapter(&account);

    std::cout << L"Клиент: " << client.name << L"\n";
    std::wcout << L"Текущий баланс: " << service->CheckBalance() << L" руб.\n";

    service->Deposit(500.0);
    std::wcout << L"Баланс после пополнения: " << service->CheckBalance() << L" руб.\n";

    service->Withdraw(200.0);
    std::wcout << L"Баланс после снятия: " << service->CheckBalance() << L" руб.\n";

    delete service;

    return 0;
}