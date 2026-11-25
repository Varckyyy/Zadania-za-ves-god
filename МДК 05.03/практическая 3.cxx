#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cassert>

using namespace std;

double mem = 0.0; // Память калькулятора

// --- 1. Операции калькулятора (все 11 функций по заданию) ---
double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double divd(double a, double b) {
    if (b == 0.0) throw invalid_argument("Деление на ноль!");
    return a / b;
}
double power(double a, double b) { return pow(a, b); }
double sqRoot(double a) {
    if (a < 0.0) throw invalid_argument("Корень из отрицательного числа!");
    return sqrt(a);
}
unsigned long long fact(int n) {
    if (n < 0) throw invalid_argument("Факториал отрицательного числа!");
    unsigned long long r = 1;
    for (int i = 2; i <= n; ++i) r *= i;
    return r;
}

void memSave(double v) { mem = v; }
double memRead() { return mem; }
void memAdd(double v) { mem += v; }
void memClear() { mem = 0.0; }

// --- 2. Модульные тесты ---
void runTests() {
    const double E = 1e-6;
    assert(abs(add(2.5, 3.5) - 6.0) < E);
    assert(abs(sub(10, 4) - 6.0) < E);
    assert(abs(mul(3, 4) - 12.0) < E);
    assert(abs(divd(15, 3) - 5.0) < E);
    assert(abs(power(2, 3) - 8.0) < E);
    assert(abs(sqRoot(25) - 5.0) < E);
    assert(fact(0) == 1 && fact(5) == 120);

    // Проверка исключений
    int errors = 0;
    try { divd(5, 0); } catch (const invalid_argument&) { errors++; }
    try { sqRoot(-4); } catch (const invalid_argument&) { errors++; }
    try { fact(-3); } catch (const invalid_argument&) { errors++; }
    assert(errors == 3);

    // Проверка памяти
    memClear(); assert(memRead() == 0.0);
    memSave(42.5); assert(abs(memRead() - 42.5) < E);
    memAdd(7.5); assert(abs(memRead() - 50.0) < E);
    memClear(); assert(memRead() == 0.0);

    cout << "[OK] Все модульные тесты успешно пройдены!\n\n";
}

// --- 3. Консольное меню ---
int main() {
    setlocale(LC_ALL, "Russian");
    runTests();

    int cmd;
    double a, b;

    while (true) {
        cout << "=== КАЛЬКУЛЯТОР (В памяти: " << memRead() << ") ===\n"
             << "1. Сложение (+)\n"
             << "2. Вычитание (-)\n"
             << "3. Умножение (*)\n"
             << "4. Деление (/)\n"
             << "5. Возведение в степень (^)\n"
             << "6. Квадратный корень (sqrt)\n"
             << "7. Факториал (!)\n"
             << "8. Сохранить число в память (MS)\n"
             << "9. Прочитать из памяти (MR)\n"
             << "10. Прибавить к памяти (M+)\n"
             << "11. Очистить память (MC)\n"
             << "0. Выход\n"
             << "Выберите действие: ";

        if (!(cin >> cmd) || cmd == 0) break;

        try {
            if (cmd >= 1 && cmd <= 5) {
                cout << "Введите два числа: "; cin >> a >> b;
                if (cmd == 1) cout << "Результат: " << add(a, b) << "\n\n";
                if (cmd == 2) cout << "Результат: " << sub(a, b) << "\n\n";
                if (cmd == 3) cout << "Результат: " << mul(a, b) << "\n\n";
                if (cmd == 4) cout << "Результат: " << divd(a, b) << "\n\n";
                if (cmd == 5) cout << "Результат: " << power(a, b) << "\n\n";
            } else if (cmd == 6) {
                cout << "Введите число: "; cin >> a;
                cout << "Результат: " << sqRoot(a) << "\n\n";
            } else if (cmd == 7) {
                cout << "Введите целое число: "; cin >> a;
                cout << "Результат: " << fact((int)a) << "\n\n";
            } else if (cmd == 8 || cmd == 10) {
                cout << "Введите число: "; cin >> a;
                cmd == 8 ? memSave(a) : memAdd(a);
                cout << "Готово.\n\n";
            } else if (cmd == 9) {
                cout << "Число в памяти: " << memRead() << "\n\n";
            } else if (cmd == 11) {
                memClear();
                cout << "Память очищена.\n\n";
            } else {
                cout << "Неверный пункт меню!\n\n";
            }
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << "\n\n";
        }
    }
    return 0;
}
