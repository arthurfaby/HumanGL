#ifndef MATRIX4_HPP
#define MATRIX4_HPP

class Matrix4
{
public:
    // Constructors
    Matrix4() = default;
    explicit Matrix4(const float[16]);
    Matrix4(const Matrix4& other) = default;
    
    // Destructor
    ~Matrix4() = default;
    
    // Getters
    [[nodiscard]] int getM() const;
    [[nodiscard]] int getN() const ;
    [[nodiscard]] float getValueAt(int, int) const;
    [[nodiscard]] float getMatrix(int) const;

    // Setters
    void setRow(int, float[4]);
    void setCol(int, float[4]);
    void setValueAt(int, int, float);
    void setMatrix(float[16]);

    // Operator overloads
    Matrix4& operator=(const Matrix4& other) = default;

    // Methods
    
private:
    /**
     * The data of the matrix such as :<br>
     *  [0, 1, 2, 3]<br>
     *  [4, 5, 6, 7]<br>
     *  [8, 9, 10, 11]<br>
     *  [12, 13, 14, 15]<br>
     */
    float _data[16]{};

    /**
    * The number of rows of the matrix.
    */
    int _m = 4;

    /**
    * The number of columns of the matrix.
    */
    int _n = 4;

    // Methods
    
};

#endif //MATRIX4_HPP
