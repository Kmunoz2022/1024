/*
Author: Kevin Munoz
Course: CSCI-135
Instructor: Tong Yi
Assignment: Project 3

This program is the game 1024
*/
#include <string>
#include <cctype>
#include <vector>
#include <iomanip>
#include "Board.hpp"
#include <iostream>
#include <cstdlib> 
#include <ctime>


Board::Board()
{
    numRows = 3;
    numCols = 3;
    max = 0;
    target = 1024;
    panel = new int*[numRows];
    for(int r = 0; r < numRows; r++){
        panel[r] = new int[numCols];
        for(int c = 0; c < numCols; c++){
            panel[r][c] = 0;
        }
    }
    srand(1);
}

Board::Board(int m)
{
    if(m >= 1)
    {
        numRows = m;
        numCols = m;
    }
    else
    {
        numRows = 3;
        numCols = 3;
    }
    max = 0;
    target = 1024;
    panel = new int*[numRows];
    for(int r = 0; r < numRows; r++)
    {
        panel[r] = new int[numCols];
        for(int c = 0; c < numCols; c++)
        {
            panel[r][c] = 0;
        }
    }
    srand(1);
}

Board::Board(int m, int n)
{
    if(m >= 1 && n >= 1)
    {
        numRows = m;
        numCols = n;
    }
    else
    {
        numRows = 3;
        numCols = 3;
    }
    max = 0;
    target = 1024;
    panel = new int*[numRows];
    for(int r = 0; r < numRows; r++)
    {
        panel[r] = new int[numCols];
        for(int c = 0; c < numCols; c++)
        {
            panel[r][c] = 0;
        }
    }
    srand(1);
}

Board::~Board() 
{    
    for(int x = 0; x < numRows; x++)
    {
        delete[] panel[x];
    }    
    delete[] panel;
}

void Board::print() const
{
    for(int r = 0; r < numRows; r++)
    {
        std::cout << "+";
        for(int c = 0; c < numCols; c++)
        {
            std::cout << "----+";
        }
        std::cout << "\n";
        std::cout << "|";
        for(int c = 0; c < numCols; c++)
        {
            if(panel[r][c] != 0)
            {
                std::cout << std::setw(4) << panel[r][c] << "|";
            }
            else
            {
                std::cout << "    |";
            }
        }
        std::cout << "\n";
    }
    std::cout << "+";
    for(int c = 0; c < numCols; c++)
    {
        std::cout << "----+";
    }
    std::cout << "\n";
}

struct Location
{
    int row;
    int col; 
};

void Board::selectRandomCell(int& row, int& col)
{
    std::vector<Location> zeros;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if(panel[i][j] == 0)
            {
                Location cell;
                cell.row = i;
                cell.col = j;
                zeros.push_back(cell);
            }
        }
    }
    if(zeros.size() > 0)
    {
        int index = rand() % zeros.size(); 
        row = zeros[index].row;
        col = zeros[index].col;
        panel[row][col] = 1;
        print();
    }
    if(zeros.size() == 0 || zeros.size() == 1)
    {
        if(noAdjacentSameValue())
        {
            if(max < target)
            {
                std::cout << "Game over. Try again." << "\n";
            }
            else
            {
                std::cout << "Congratulations!" << "\n";
            }
            exit(0);
        }
        else
        {
            return;
        }
    }
}

bool Board::noAdjacentSameValue() const
{
    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols - 1; j++){
            if(panel[i][j] == panel[i][j + 1]){
                return false;
            }
        }
    }
    for (int j = 0; j < numCols; j++){
        for (int i = 0; i < numRows - 1; i++){
            if(panel[i][j] == panel[i + 1][j]){
                return false;
            }
        }
    }
    return true;
}



int Board::getNumRows() const
{
    return numRows;
}

int Board::getNumCols() const
{
    return numCols;
}

int Board::getTarget() const
{
    return target;
}

int Board::getMax() const
{
    return max;
}

void merge(std::vector<int>& result, int& max)
{
    int i = 0;
    int size = result.size();
    while(i < size)
    {
        if(i + 1 < size && result[i + 1] == result[i])
        {
            result[i] *= 2;
            if(result[i] > max)
            {
                max = result[i];
            }
            result[i+1] = 0;
            i += 2;
        }
        else
        {
            i++;
        }
    }
}

void Board::pressUp()
{
    for(int col = 0; col < numCols; col++)
    {
        std::vector<int> nonZeros;
        for (int row = 0; row < numRows; row++)
        {
            if (panel[row][col] != 0)
            {
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros, max);
        int row = 0;
        for(int i = 0; i < nonZeros.size(); i++)
        {
            if (nonZeros[i] != 0)
            {
                panel[row][col] = nonZeros[i];
                row++;
            }
        }
        while (row < numRows)
        { 
            panel[row][col] = 0; 
            row++;
        }            
    }
    int row = 0;
    int col = 0; 
    selectRandomCell(row,col);
}

void Board::pressDown(){
    for(int col = 0; col < numCols; col++)
    {
        std::vector<int> nonZeros;
        for (int row = numRows - 1; row >= 0; row--)
        {
            if (panel[row][col] != 0)
            {
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros, max);
        int row = numRows - 1;
        for(int i = 0; i < nonZeros.size(); i++)
        {
            if (nonZeros[i] != 0)
            {
                panel[row][col] = nonZeros[i];
                row--;
            }
        }
        while (row >= 0)
        { 
            panel[row][col] = 0; 
            row--;
        }            
    }
    int row = 0;
    int col = 0; 
    selectRandomCell(row,col);
}

void Board::pressLeft(){
    for(int row = 0; row < numRows; row++)
    {
        std::vector<int> nonZeros;
        for (int col = 0; col < numCols; col++)
        {
            if (panel[row][col] != 0)
            {
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros,max);
        int col = 0;
        for(int i = 0; i < nonZeros.size(); i++)
        {
            if (nonZeros[i] != 0)
            {
                panel[row][col] = nonZeros[i];
                col++;
            }
        }
        while (col < numCols)
        { 
            panel[row][col] = 0; 
            col++;
        }            
    }
    int row = 0;
    int col = 0; 
    selectRandomCell(row,col);
}

void Board::pressRight()
{
    for(int row = 0; row < numRows; row++)
    {
        std::vector<int> nonZeros;
        for (int col = numCols-1; col >= 0; col--)
        {
            if (panel[row][col] != 0)
            {
                nonZeros.push_back(panel[row][col]);
            }
        }
        merge(nonZeros, max);
        int col = numCols - 1;
        for(int i = 0; i < nonZeros.size(); i++)
        {
            if (nonZeros[i] != 0)
            {
                panel[row][col] = nonZeros[i];
                col--;
            }
        }
        while (col >= 0)
        { 
            panel[row][col] = 0; 
            col--;
        }            
    }
    int row = 0;
    int col = 0; 
    selectRandomCell(row,col);
}




void Board::start(){
    int round = 1;
    int row;
    int col;
    char ch;
    max = 1;
    selectRandomCell(row, col);
    selectRandomCell(row,col);
    while(true)
    {
        if(max >= target)
        {
            std::cout << "Congratulation!" << "\n";
            break;
        }
        ch = getchar();
        if(ch == 'S')
        {
            break;
        }
        if(ch == '\033')
        {
            getchar();
            switch(getchar())
            {
            case 'A':
                std::cout << "Round " << std::setw(4) << round << ": ";
                std::cout << "Press UP. "
                     << "Goal: " << target << "\n";
                pressUp();
                round++; 
                break;
            case 'B':
                std::cout << "Round " << std::setw(4) << round << ": ";
                std::cout << "Press DOWN. "
                     << "Goal: " << target << "\n";
                pressDown();
                round++; 
                break;
            case 'D':
                std::cout << "Round " << std::setw(4) << round << ": ";
                std::cout << "Press LEFT. "
                     << "Goal: " << target << "\n";
                pressLeft();
                round++; 
                break;
            case 'C':
                std::cout << "Round " << std::setw(4) << round << ": ";
                std::cout << "Press RIGHT. "
                     << "Goal: " << target << "\n";
                pressRight();
                round++; 
                break;
            }
        }
    }
}