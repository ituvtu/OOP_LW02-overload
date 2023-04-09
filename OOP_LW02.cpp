#include <iostream>


using namespace std;

class Matrix {
private:
    int columns;        // кількість стовпців матриці
    int rows;           // кількість рядків матриці
    int** elements;     // вказівник на масив даних матриці
public:

    //Конструктор за замовчуванням
    Matrix() {
        columns = 3;
        rows = 3;
        elements = new int* [rows];
        for (int i = 0; i < rows; i++) {
            elements[i] = new int[columns];
        }

        // Ініціалізація масиву даних матриці нулями
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                elements[i][j] = 0;
            }
        }
    }

    //Конструктор матриці з параметрами(розмір)
    Matrix(int r, int c, int num_for_matrix) {
        rows = r;
        columns = c;
        elements = new int* [rows];
        for (int i = 0; i < rows; i++) {
            elements[i] = new int[columns];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                elements[i][j] = num_for_matrix;
            }
        }
    }

    //Конструктор з параметрами(елементи вводяться з консолі)
    Matrix(int r, int c) {
        rows = r;
        columns = c;
        elements = new int* [rows];
        for (int i = 0; i < rows; i++) {
            elements[i] = new int[columns];
            for (int j = 0; j < columns; j++) {
                cout << "Enter element [" << i << "][" << j << "]:";
                cin >> elements[i][j];
            }
        }
    }

    // Деструктор
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] elements[i];
        }
        delete[] elements;
    }

    //Конструктор параметром якого є масив
    Matrix(int* arr, int r, int c) {
        rows = r;
        columns = c;
        // Виділення пам'яті для елементів матриці
        elements = new int* [r];
        for (int i = 0; i < r; i++) {
            elements[i] = new int[c];
        }

        // Заповнення матриці елементами з масиву
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                elements[i][j] = arr[i * c + j];
            }
        }
    }

    // Копіюючий конструктор
    Matrix(const Matrix& other) {
        rows = other.rows;
        columns = other.columns;

        // Виділення пам'яті для масиву даних матриці
        elements = new int* [rows];
        for (int i = 0; i < rows; i++) {
            elements[i] = new int[columns];
        }

        // Копіювання даних з іншої матриці
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                elements[i][j] = other.elements[i][j];
            }
        }

    }

    // Геттер для кількості стовпців
    int getColumns() const {
        return columns;
    }

    // Сеттер для кількості стовпців
    void setColumns(int cols) {
        columns = cols;
    }

    // Геттер для кількості рядків
    int getRows() const {
        return rows;
    }

    // Сеттер для кількості рядків
    void setRows(int rows) {
        this->rows = rows;
    }

    // Геттер для елемента матриці з заданими індексами
    int getElement(int row, int col) const {
        if (row >= rows || col >= columns) {
            cout << "Invalid index of element";
            return -1;
   
        }
        return elements[row][col];
    }

    // Сеттер для елемента матриці з заданими індексами
    void setElement(int row, int col, int value) {
        if (row >= rows || col >= columns) {
            cout << "Invalid index of element";
            return;
        }
        elements[row][col] = value;
    }

    // Оператор присвоєння
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            // Видаляємо старі дані
            for (int i = 0; i < rows; ++i) {
                delete[] elements[i];
            }
            delete[] elements;

            // Копіюємо нові дані
            rows = other.rows;
            columns = other.columns;
            elements = new int* [rows];
            for (int i = 0; i < rows; ++i) {
                elements[i] = new int[columns];
                for (int j = 0; j < columns; ++j) {
                    elements[i][j] = other.elements[i][j];
                }
            }
        }
        return *this;
    }

    //Перевантаження операторів [] 
    const int* operator[](int r) const {
        return elements[r];
    }

    // Перевантаження оператора << для виводу на консоль
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << endl;
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.columns; j++) {
                os << "|" << matrix.elements[i][j] << "|";
            }
            os << endl;
        }
        return os;
    }


    // Перевантаження оператора >> для вводу з консолі
    friend std::istream& operator>>(std::istream& is, Matrix& matrix) {
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.columns; j++) {
                cout << "Enter element [" << i << ", " << j << "]:";
                is >> matrix.elements[i][j];
            }
        }
        return is;
    }

    // перевантаження оператора +
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || columns != other.columns) {
            // матриці мають різну розмірність, неможливо додати
            cout << "Matrices have different dimensions";
            return Matrix(); // Повертаємо пусту матрицю
        }

        Matrix result(rows, columns,0);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result.elements[i][j] = elements[i][j] + other.elements[i][j];
            }
        }
        return result;
    }

    //перевантаження оператора ! для транспонування матриці
    Matrix operator!() const {
        Matrix result(columns, rows,0);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < columns; j++) {
                result.elements[j][i] = elements[i][j];
            }
        }
        return result;
    }

    //Перевантаження оператора * для добутку матриць
    Matrix operator *(const Matrix& other) const {
        Matrix result(rows, other.columns,0);
        // перевірка на відповідність розмірів матриць
        if (columns != other.rows) {
            cout << "Matrix dimensions do not match for multiplication!" << endl;
            // повертаємо пусту матрицю
            return Matrix();
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.columns; j++) {
                // обчислення добутку елементів відповідних рядків та стовпців
                int sum = 0;
                for (int k = 0; k < columns; k++) {
                    sum += elements[i][k] * other.elements[k][j];
                }
                result.elements[i][j]= sum;  // присвоєння значення елементу нової матриці
            }
        }

        return result;  // повертаємо нову матрицю
    }

    //Перевантаження оператора* для добутку з числом
    Matrix operator*(int num) {
    Matrix result(rows, columns,0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result.elements[i][j] = elements[i][j] * num;
        }
    }
    return result;
    }

    // перевантаження операції порівняння ==
    bool operator==(const Matrix& other) const {
        if (rows != other.rows || columns != other.columns) {
            return false;
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (elements[i][j] != other.elements[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    // перевантаження операції порівняння !=
    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    // перевантаження операції >
    bool operator>(const Matrix& other) const {
        if (rows != other.rows || columns != other.columns) {
            cout << "Cannot compare matrices of different sizes."<<endl;
            return false;
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (elements[i][j] <= other.elements[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    // перевантаження операції <
    bool operator<(const Matrix& other) const {
        if (rows != other.rows || columns != other.columns) {
            cout << "Cannot compare matrices of different sizes."<<endl;
            return false;
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (elements[i][j] >= other.elements[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    // перевантаження операції >=
    bool operator>=(const Matrix& other) const {
        return (*this > other) || (*this == other);
    }

    // перевантаження операції <=
    bool operator<=(const Matrix& other) const {
        return (*this < other) || (*this == other);
    }
};
int main() {
    // Створення матриці з нулів розміром 3х3
    Matrix m1;
    // Створення матриці за допомогою конструктора з параметрами(ввод з консолі)
    Matrix m2(2, 2);
    // Створення матриці за допомогою конструктора з масивом
    int arr[] = { 1, 2, 3, 4 };
    Matrix m3(arr, 1, 4);
    // Створення копії матриці
    Matrix m4 = m3;
    // Вивід елементів матриці
    cout << "Matrix m1:" << endl;
    for (int i = 0; i < m1.getRows(); i++) {
        for (int j = 0; j < m1.getColumns(); j++) {
            cout << m1.getElement(i, j) << " ";
        }
        cout << endl;
    }
    cout << "Matrix m2:" <<m2<< endl;
    
    cout << "Matrix m3:" <<m3<< endl;
    
    cout << "Matrix m4:" <<m4<< endl;

    // Зміна значення елементу матриці
    m2.setElement(0, 0, 100);
    cout << "Matrix m2 after change:" <<m2<< endl;
    
    
    cout << "create new matrix A"<<endl;

    Matrix A(2,2);
    // Множення матриці на число
    Matrix G = A * 2;
    // Виведення результату множення на число на консоль
    cout << "A * 2 =" << G << endl;


    cout << "create new matrix B" << endl;
    Matrix B(2,2);
    // Введення матриць з консолі
    Matrix Check;
    cout << "Enter matrix for checking console input:\n";
    cin >> Check;
    cout <<"\nthat your matrix from console";
    cout << Check << endl;
    // Додавання матриць
    Matrix C = A + B;

    // Виведення результату додавання на консоль
    cout << "A + B =" << C << endl;

    // Транспонування матриць
    Matrix D = !A;
    
    Matrix E = !B;
    
    // Виведення результату транспонування на консоль
    cout << "Transpose of A:" << D << endl;
    cout << "Transpose of B:" << E << endl;

    // Добуток матриць
    Matrix F = A * B;
    

    // Виведення результату добутку на консоль
    cout << "A * B =" << F << endl;

    // Перевірка рівності матриць
    if (A == B) {
        cout << "A = B" << endl;
    }
    else {
        cout << "A != B" << endl;
    }

    // Перевірка порівняння матриць
    if (A > B) {
        cout << "A > B" << endl;
    }
    else {
        cout << "B > A" << endl;
    }

    // Використання оператора [] для отримання доступу до елементів матриці
    cout << "Element at row 1, column 1 of matrix A: " << A[1][1] << endl;

    return 0;
}