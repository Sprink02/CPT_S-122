#pragma once
#include <iostream>
#include <fstream>
#include <print>
#include <string>
#include <sstream>
#include "../BST/BST.hpp"

using std::string;
using std::print;
using std::println;

class DataAnalysis
{
private:
    BST _treeSold;
    BST _treePurchased;
    std::ifstream _csvStream;

    string _currentType;
    int _currentUnits;
    string _currentTransaction;

    bool _f_open();
    void _f_read(string line);
    void _f_complete();
    void _f_compare_insert();
    void _trend_print();

public:
    DataAnalysis();
    ~DataAnalysis();

    void run_analysis();
};

DataAnalysis::DataAnalysis() : _currentUnits(0) {}
DataAnalysis::~DataAnalysis() { _csvStream.close(); }

bool DataAnalysis::_f_open()
{
    _csvStream.open("./static/data.csv");
    println("File open: {}", _csvStream.is_open());
    if (!_csvStream.is_open())
    {
        return false;
    }
    return true;
}
void DataAnalysis::_f_read(string line)
{
    std::stringstream ss(line);
    string unitsStr;

    std::getline(ss, unitsStr, ',');
    std::getline(ss, _currentType, ',');
    std::getline(ss, _currentTransaction, ',');

    _currentUnits = std::stoi(unitsStr);
}
void DataAnalysis::_f_complete()
{
    string line;
    std::getline(_csvStream, line);

    while (std::getline(_csvStream, line))
    {
        _f_read(line);
        _f_compare_insert();

        std::println("--- Sold Tree ---");
        _treeSold.in_order_traversal();
        println("--- Purchased Tree ---");
        _treePurchased.in_order_traversal();
    }
}
void DataAnalysis::_f_compare_insert()
{
    if (_currentTransaction == "Sold")
    {
        _treeSold.insert(_currentType, _currentUnits);
    }
    else if (_currentTransaction == "Purchased")
    {
        _treePurchased.insert(_currentType, _currentUnits);
    }
}
void DataAnalysis::_trend_print()
{
    TransactionNode& mostSold = _treeSold.find_largest();
    TransactionNode& leastSold = _treeSold.find_smallest();
    TransactionNode& mostPurchased = _treePurchased.find_largest();
    TransactionNode& leastPurchased = _treePurchased.find_smallest();

    println("Most sold: {} {}", mostSold.get_data(), mostSold.get_units());
    println("Least sold: {} {}", leastSold.get_data(), leastSold.get_units());
    println("Most purchased: {} {}", mostPurchased.get_data(), mostPurchased.get_units());
    println("Least purchased: {} {}", leastPurchased.get_data(), leastPurchased.get_units());
}



void DataAnalysis::run_analysis()
{
    bool b;
    b = _f_open();
    if (b == false)
    {
        return;
    }
    _f_complete();
    _trend_print();
}