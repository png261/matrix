using namespace std;

template <class T>
class Matrix {
    private:
        int rows, cols;
        T *values;

    public:
        Matrix(int _rows, int _cols) {
            cols = _cols;
            rows = _rows;
            values = new T[rows * cols]; 
        }

        Matrix(int size) {
            cols = size;
            rows = size;
            values = new T[rows * cols];
        }

        Matrix(const Matrix& matrix) {
            rows = matrix.rows;
            cols = matrix.cols;
            values = new T[rows * cols]; 

            for(int i = 0; i < rows; i++) {
                values[i] = matrix.values[i];         
            }
        }

        ~Matrix(){
            delete[] values;
        }
};
