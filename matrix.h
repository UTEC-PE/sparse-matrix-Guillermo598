#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;

    public:
        Matrix(){
            hRows = hColumns = nullptr;
            columns = rows = 0;
        };
        Matrix(int sizeX, int sizeY){
            columns = sizeX;
            rows = sizeY;
            hRows = new Node<T>(0);
            Node<T>* temp = hRows;
            for (int i = 1; i < rows; i++){
                Node<T>* current = new Node<T>(i);
                temp -> down = current;
                temp = current;
            }
            hColumns = new Node<T>(0);
            temp = hColumns;
            for (int i = 1; i < columns; i++){
                Node<T>* current = new Node<T>(i);
                temp -> next = current;
                temp = current;
            }
        };

        void set(int x, int y, T data){
            if (x+1 <= columns && x >= 0 && y >= 0 && y+1 <= rows){
                Node<T>* currentX = hColumns;
                for (int i = 0; i < x; i++)
                    currentX = currentX -> next;
                Node<T>* currentY = hRows;
                for (int i = 0; i < x; i++)
                    currentY = currentY -> down;
                bool exists = 0;
                while (currentX -> down){
                    if (currentX -> down -> y < y)
                        currentX = currentX -> down;
                    else if (currentX -> down -> y == y){
                        exists = 1;
                        break;
                    }
                    else
                        break;
                }
                if (!exists){
                    if (data != 0) {
                        while (currentY -> next) {
                            if (currentY -> next -> x < x)
                                currentY = currentY -> next;
                            else
                                break;
                        }
                        Node<T> *temp = new Node<T>(x, y, data);
                        temp -> next = currentY -> next;
                        currentY -> next = temp;
                        temp -> down = currentX -> down;
                        currentX -> down = temp;
                    }
                }
                else{
                    if (data != 0)
                        currentX -> down -> data = data;
                    else {
                        while (currentY -> next -> x < x)
                            currentY = currentY -> next;
                        Node<T>* temp = currentX -> down;
                        currentX -> down = temp -> down;
                        currentY -> next = temp -> next;
                        delete temp;
                    }
                }
            }
            else
                cout << "Coordenadas invalidas\n";
        };
        T operator()(int x, int y){
            if (x+1 <= columns && x >= 0 && y >= 0 && y+1 <= rows) {
                Node<T> *current = hColumns;
                for (int i = 0; i < x; i++)
                    current = current->next;
                while (current->down) {
                    if (current->down->y < y)
                        current = current->down;
                    else if (current->down->y == y)
                        return current->down->data;
                    else
                        return 0;
                }
            }
            else
                cout << "Coordenadas invalidas\n";
        };
        Matrix<T> operator*(Matrix<T> other){
            if (columns == other.rows){
                Matrix<T>* c = new Matrix(other.columns,rows);
                for (int i = 0; i < c->columns; i++){
                    for (int j = 0; j < c->rows; j++){
                        T value = 0;
                        for (int r = 0; r < columns; r++)
                            value += this->operator()(r, i) * other(j, r);
                        c->set(i, j, value);
                    }

                }
                return *c;
            }
            else
                cout << "Tamanios incompatibles" << endl;
        };
        Matrix<T> operator*(T scalar){
            Node<T>* currentX = hColumns;
            while (currentX){
                Node<T>* currentY = currentX -> down;
                while (currentY){
                    currentY -> data *= scalar;
                    currentY = currentY -> down;
                }
                currentX = currentX -> next;
            }
            return *this;
        };
        Matrix<T> operator+(Matrix<T> other){
            if (columns == other.columns && rows == other.rows){
                for (int i = 0; i < columns; i++){
                    for (int j = 0; j < rows; j++)
                        this -> set(i, j, (other(i, j) + this->operator()(i,j)));
                }
                return *this;
            }
            else
                cout << "Tamanios incompatibles" << endl;
        };
        Matrix<T> operator-(Matrix<T> other){
            if (columns == other.columns && rows == other.rows){
                for (int i = 0; i < columns; i++){
                    for (int j = 0; j < rows; j++)
                        this -> set(i, j, (this->operator()(i,j) - other(i, j)));
                }
                return *this;
            }
            else
                cout << "Tamanios incompatibles" << endl;
        };
        Matrix<T> transposed(){
            Matrix<T>* c = new Matrix(rows, columns);
            for (int i = 0; i < columns; i++){
                for (int j = 0; j < rows; j++){
                    c->set(j, i, this->operator()(i, j));
                }
            }
            return *c;
        };
        Matrix<T> operator=(Matrix<T> other){
            if (columns == other.columns && rows == other.rows){
                for (int i = 0; i < columns; i++){
                    for (int j = 0; j < rows; j++)
                        this -> set(i, j, other(i, j));
                }
                return *this;
            }
            else
                cout << "Tamanios incompatibles" << endl;
        };
        ~Matrix(){
            Node<T>* current = hColumns;
            Node<T>* next = hColumns -> next;
            while (next){
                current -> killSelf();
                current = next;
                next = next -> next;
            }
            current -> killSelf();
            hRows -> killSelf();
        };
};

#endif
