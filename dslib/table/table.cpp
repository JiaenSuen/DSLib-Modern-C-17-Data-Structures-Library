template <typename T>
class dynamic_table {
    private :
        T** table;
    public :
        unsigned int rows;
        unsigned int cols;
        dynamic_table(unsigned int row_size, unsigned int col_size) {
            rows = row_size;
            cols = col_size;
            table = new T*[rows]();
            for (unsigned int i = 0; i < rows; ++i) table[i] = new T[cols]();
        }
        ~dynamic_table() {
            for (unsigned int i = 0; i < rows; ++i) delete[] table[i];
            delete[] table;
        }
        T* operator[](unsigned int index) {
            return table[index];
        }
 

        friend ostream& operator<<(ostream& os,  dynamic_table<T>& dt) {
            for (unsigned int i = 0; i < dt.rows; ++i) {
                for (unsigned int j = 0; j < dt.cols; ++j) os << dt[i][j] << " ";
                os << "\n";
            } return os;
        }
};