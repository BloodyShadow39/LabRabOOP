#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <stdexcept>

using namespace std;

// Класс User
class User {
public:
    int id;
    string name;
    string login;
    string password;

    User(int id, const string& name, const string& login, const string& password)
        : id(id), name(name), login(login), password(password) {}

    string toString() const {
        return to_string(id) + "," + name + "," + login + "," + password;
    }

    static User fromString(const string& str) {
        stringstream ss(str);
        string id_str, name, login, password;

        getline(ss, id_str, ',');
        getline(ss, name, ',');
        getline(ss, login, ',');
        getline(ss, password);

        return User(stoi(id_str), name, login, password);
    }
};

// Интерфейс IDataRepository
template <typename T>
class IDataRepository {
public:
    virtual void add(const T& item) = 0;
    virtual void remove(int id) = 0;
    virtual T getById(int id) = 0;
    virtual vector<T> getAll() = 0;
    virtual void update(int id, const T& item) = 0;
    virtual ~IDataRepository() = default;
};

// Интерфейс IUserRepository
class IUserRepository : public IDataRepository<User> {
public:
    virtual User getByLogin(const string& login) = 0;
    virtual User getByName(const string& name) = 0;
};

// Класс FileUserRepository
class FileUserRepository : public IUserRepository {
private:
    string filename;

public:
    FileUserRepository(const string& filename) : filename(filename) {}

    void add(const User& user) override {
        ofstream file(filename, ios::app);
        file << user.toString() << endl;
    }

    void remove(int id) override {
        vector<User> users = getAll();
        ofstream file(filename);
        for (const auto& user : users) {
            if (user.id != id) {
                file << user.toString() << endl;
            }
        }
    }

    User getById(int id) override {
        vector<User> users = getAll();
        for (const auto& user : users) {
            if (user.id == id) {
                return user;
            }
        }
        throw runtime_error("User not found");
    }

    vector<User> getAll() override {
        ifstream file(filename);
        vector<User> users;
        string line;
        while (getline(file, line)) {
            users.push_back(User::fromString(line));
        }
        return users;
    }

    void update(int id, const User& user) override {
        vector<User> users = getAll();
        ofstream file(filename);
        for (auto& u : users) {
            if (u.id == id) {
                u = user;
            }
            file << u.toString() << endl;
        }
    }

    User getByLogin(const string& login) override {
        vector<User> users = getAll();
        for (const auto& user : users) {
            if (user.login == login) {
                return user;
            }
        }
        throw runtime_error("User not found");
    }

    User getByName(const string& name) override {
        vector<User> users = getAll();
        for (const auto& user : users) {
            if (user.name == name) {
                return user;
            }
        }
        throw runtime_error("User not found");
    }
};

// Интерфейс IUserManager
class IUserManager {
public:
    virtual bool login(const string& login, const string& password) = 0;
    virtual void logout() = 0;
    virtual bool isAuthenticated() const = 0;
    virtual User getCurrentUser() const = 0;
    virtual ~IUserManager() = default;
};

// Класс FileUserManager
class FileUserManager : public IUserManager {
private:
    IUserRepository& userRepository;
    User* currentUser;

public:
    FileUserManager(IUserRepository& userRepo) : userRepository(userRepo), currentUser(nullptr) {}

    bool login(const string& login, const string& password) override {
        try {
            User user = userRepository.getByLogin(login);
            if (user.password == password) {
                currentUser = new User(user.id, user.name, user.login, user.password);
                return true;
            }
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }
        return false;
    }

    void logout() override {
        if (currentUser != nullptr) {
            delete currentUser;
            currentUser = nullptr;
        }
    }

    bool isAuthenticated() const override {
        return currentUser != nullptr;
    }

    User getCurrentUser() const override {
        if (currentUser != nullptr) {
            return *currentUser;
        }
        throw runtime_error("No user is logged in");
    }
};

// Основная программа
int main() {
    setlocale(LC_ALL, "Russian");
    FileUserRepository userRepository("users.txt");
    FileUserManager userManager(userRepository);

    // Проверка, если пользователь уже авторизован, делаем автоматический вход
    if (userManager.isAuthenticated()) {
        cout << "Пользователь уже авторизован: " << userManager.getCurrentUser().name << endl;
    }
    else {
        // Регистрация нового пользователя
        cout << "Регистрация нового пользователя:" << endl;
        string name, login, password;
        cout << "Имя: ";
        cin >> name;
        cout << "Логин: ";
        cin >> login;
        cout << "Пароль: ";
        cin >> password;

        int newId = userRepository.getAll().size() + 1;
        userRepository.add(User(newId, name, login, password));
        cout << "Пользователь зарегистрирован!" << endl;

        // Попытка входа в систему
        cout << "Попытка входа в систему:" << endl;
        cout << "Введите логин: ";
        cin >> login;
        cout << "Введите пароль: ";
        cin >> password;

        if (userManager.login(login, password)) {
            cout << "Добро пожаловать, " << userManager.getCurrentUser().name << "!" << endl;
        }
        else {
            cout << "Неверный логин или пароль!" << endl;
        }
    }

    // Возможность смены пользователя
    char changeUser;
    cout << "Хотите сменить пользователя? (y/n): ";
    cin >> changeUser;

    if (changeUser == 'y' || changeUser == 'Y') {
        userManager.logout();
        cout << "Выход из текущего пользователя." << endl;
    }

    // Выход из системы
    if (userManager.isAuthenticated()) {
        cout << "Выход из системы:" << endl;
        userManager.logout();
        cout << "Вы вышли из системы." << endl;
    }

    return 0;
}
