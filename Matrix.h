#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

template <class T>
class Matrix
{
    private:
        int rows, cols;
        T **values;

    public:
        // constructs
        Matrix(int _rows, int _cols)
        {
            rows = _rows;
            cols = _cols;

            values = new T*[rows];
            for(int i = 0; i < rows; i++){
                values[i] = new T[cols]; 
            }
        }

        Matrix(int size)
        {
            cols = size;
            rows = size;

            values = new T*(rows);
            for(int i = 0; i < rows; i++){
                values[i] = new T[cols]; 
            }
        }

        Matrix(const Matrix& matrix)
        {
            rows = matrix.rows;
            cols = matrix.cols;
            values = new T*[rows]; 

            for(int i = 0; i < rows; i++) {
                values[i] = new T;
                for(int j = 0; j < cols; j++) {
                    values[i][j] = matrix.values[i][j];         
                }
            }
        }

        // destructs
        ~Matrix(){
            delete[] values;
        }

        // compare
        bool operator== (const Matrix matrix)
        {
            if(rows != matrix.rows || cols != matrix.cols)
            {
                return false;
            }

            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    if(values[i][j] != matrix.values[i][j])
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool operator!= (const Matrix matrix)
        {
            if(rows != matrix.rows || cols != matrix.cols)
            {
                return true;
            }

            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    if(values[i][j] != matrix.values[i][j])
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        // operator
        T* operator[](int i){
            return this -> values[i]; 
        } 

        Matrix transpose() 
        {
            Matrix result(cols, rows);

            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    result.values[j][i] = values[i][j];
                }
            }

            return result;
        }

        Matrix operator* (const Matrix& matrix)
        {
            if(cols != matrix.rows) {
                throw std::invalid_argument("matrices have not equal number of rows and columns");
            }

            Matrix result(rows, matrix.cols);
            for(int i = 0; i < result.rows; i++) {
                for(int j = 0; j < result.cols; j++) {
                    result.values[i][j] = 0;

                    for(int k = 0; k < cols; k++) {
                        result.values[i][j] += values[i, k] * matrix.values[k, j];
                    }
                }
            }
            return result;
        }

        Matrix& operator*= (const Matrix& matrix)
        {
            if(cols != matrix.rows) {
                throw std::invalid_argument("matrices have not equal number of rows and columns");
            }

            Matrix result(rows, matrix.cols);
            for(int i = 0; i < result.rows; i++) {
                for(int j = 0; j < result.cols; j++) {
                    result.values[i][j] = 0;

                    for(int k = 0; k < cols; k++) {
                        result.values[i][j] += values[i][k] * matrix.values[k][j];
                    }
                }
            }

            this->~Matrix();
            this->rows = result.rows;
            this->cols = result.cols;

            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    this->values[i][j] = result.values[i][j];
                }
            }

            return *this;
        }

        Matrix& operator= (const Matrix& matrix)
        {
            this->~Matrix();
            this->rows = matrix.rows;
            this->cols = matrix.cols;
            this->values = new T*[rows];

            for(int i = 0; i < rows; i++) {
                this->values[i] = new T[cols]; 
                for(int j = 0; j < cols; j++) {
                    this->values[i][j] = matrix.values[i][j];
                }
            }
            return *this;
        }

        Matrix operator- (const Matrix& matrix){
            if(rows != matrix.rows || cols != matrix.cols)
            {
                throw std::invalid_argument("matrices have not equal number of rows and columns");
            }

            Matrix result(rows, cols);
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    result.values[i][j] = values[i][j] - matrix.values[i][j]; 
                }
            }
            return result;
        }

        Matrix& operator-= (const Matrix& matrix){
            if(rows != matrix.rows || cols != matrix.cols)
            {
                throw std::invalid_argument("matrices have not equal number of rows and columns");
            }

            for(int i = 0; i < rows; i++) {
                for(int i = 0; i < cols; i++) {
                    values[i] -= matrix.values[i]; 
                }
            }
            return *this;
        }

        Matrix operator+ (const Matrix& matrix){
            if(rows != matrix.rows || cols != matrix.cols)
            {
                throw std::invalid_argument("matrices have not equal number of rows and columns");
            }

            Matrix result(rows, cols);
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    result.values[i][j] = values[i][j] + matrix.values[i][j]; 
                }
            }
            return result;
        }

        Matrix& operator+= (const Matrix& matrix){
            if(rows != matrix.rows || cols != matrix.cols)
            {
                throw std::invalid_argument("matrices have not equal number of rows and columns");
            }

            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    values[i][j] += matrix.values[i][j]; 
                }
            }
            return *this;
        }

        Matrix operator/(T n)
        {
            Matrix result(rows, cols);
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    result.values[i][j] = values[i][j] / n; 
                }
            }
            return result;
        }

        Matrix& operator/=(T n)
        {
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    values[i][j] /= n; 
                }
            }
            return *this;
        }

        Matrix operator*(T n)
        {
            Matrix result(rows, cols);
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    result.values[i][j] = values[i][j] * n; 
                }
            }
            return result;
        }

        Matrix& operator*=(T n)
        {
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    values[i][j] *= n; 
                }
            }
            return *this;
        }

        // input & output 
        friend void operator>>(istream& s, Matrix& matrix)
        {
            for(int i = 0; i < matrix.rows; i++){
                for(int j = 0; j < matrix.cols; j++){
                    s>>matrix.values[i][j];
                }
            }
        }

        friend void operator<<(ostream& s, Matrix& matrix)
        {
            for(int i = 0; i < matrix.rows; i++){
                for(int j = 0; j < matrix.cols; j++){
                    s<<matrix.values[i][j]<<" ";
                }
                s<<endl;
            }
        }

        friend void operator>>(ifstream& fs, Matrix& matrix)
        {
            for(int i = 0; i < matrix.rows; i++){
                for(int j = 0; j < matrix.cols; j++){
                    fs>>matrix.values[i][j];
                }
            }
        }

        friend void operator<<(ofstream& fs, Matrix& matrix)
        {
            for(int i = 0; i < matrix.rows; i++){
                for(int j = 0; j < matrix.cols; j++){
                    fs<<matrix.values[i][j]<<" ";
                }
                fs<<endl;
            }
       }
};

