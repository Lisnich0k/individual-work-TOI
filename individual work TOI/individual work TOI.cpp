#include <iostream>
#include <string>
#include <vector>
#include "windows.h"

static const int arraySize = 5;
// Структура данных "Продажа"
struct SaleData {
    std::string productName; // Наименование товара
    int quantitySold = 0; // Количество проданных единиц товара
    double pricePerUnit = 0; // Цена за единицу товара
    double totalAmount = 0; // Общая сумма продажи
};

// Индексация по количеству проданных единиц товара
void bubbleSortQuantitySold(SaleData* list[], int listLength) {
    while (listLength--)
    {
        bool swapped = false;

        for (int i = 0; i < listLength; i++)
        {
            if (list[i]->quantitySold > list[i + 1]->quantitySold)
            {
                std::swap(list[i], list[i + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
};

// Индексация по общей сумме продаж
void bubbleSortTotalAmount(SaleData* list[], int listLength) {
    while (listLength--)
    {
        bool swapped = false;

        for (int i = 0; i < listLength; i++)
        {
            if (list[i]->totalAmount < list[i + 1]->totalAmount)
            {
                std::swap(list[i], list[i + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
};

int binarySearchQuantitySold(SaleData* list[], int x) {
    int l = 0;
    int r = arraySize - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (list[mid]->quantitySold == x)
            return mid;

        if (list[mid]->quantitySold < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1; // элемент не найден
}

int binarySearchTotalAmount(SaleData* list[], double x) {
    int l = 0;
    int r = arraySize - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (list[mid]->totalAmount == x)
            return mid;

        if (list[mid]->totalAmount < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1; // элемент не найден
}

void changeArray(SaleData list[])
{
    int index = 1;
    int choice = 1;
    std::cout << "Enter index of object that you want to change: " << std::endl;
    std::cin >> index;
    std::cout << "1).Product name: " << list[index].productName << std::endl;
    std::cout << "2).Quantity sold: " << list[index].quantitySold << std::endl;
    std::cout << "3).Price per unit: " << list[index].pricePerUnit << std::endl;
    std::cout << "Enter number(in the beggining of each feature) that you want to change: " << std::endl;

    std::cin >> choice;
    switch (choice)
    {
    case 1:
        std::cout << "Enter new Product name: " << std::endl;
        std::cin >> list[index].productName;
        break;
    case 2:
        std::cout << "Enter new Quantity sold: " << std::endl;
        std::cin >> list[index].quantitySold;
        list[index].totalAmount = list[index].quantitySold * list[index].pricePerUnit;
        break;
    case 3:
        std::cout << "Enter new Price per unit: " << std::endl;
        std::cin >> list[index].pricePerUnit;
        list[index].totalAmount = list[index].quantitySold * list[index].pricePerUnit;
        break;
    }
};

void deleteKeyArrayQuantitySold(SaleData list[], int arraySize,int key)
{
    key = -1;
    for (int i = 0; i < arraySize; i++) {
        if (list[i].quantitySold == key) {
            key = i;
            break;
        }
    }

    // Если элемент найден, сдвигаем оставшиеся элементы влево
    if (key != -1) {
        for (int i = key; i < arraySize - 1; i++) {
            list[i] = list[i + 1];
        }
        arraySize--; // уменьшаем размер массива
    }
    else {
        std::cout << "Element with key value " << key << " not found" << std::endl;
    }
};

void printIndexers(SaleData* list[], int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        std::cout << "Product name: " << list[i]->productName << std::endl;
        std::cout << "Quantity sold: " << list[i]->quantitySold << std::endl;
        std::cout << "Price per unit: " << list[i]->pricePerUnit << std::endl;
        std::cout << "Total amount: " << list[i]->totalAmount << std::endl;
        std::cout << std::endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
  
    static int forNewArrayDelete = arraySize;
    SaleData sales[arraySize]; //Создаем массив структур SaleData
    SaleData* indexersQuantitySold[arraySize]; //Создаем массив указателей для количества проданных товаров
    SaleData* indexersTotalAmount[arraySize]; //Создаем массив указателей для общей суммы продаж
    int numberToSearchBinaryQuantity; // Переменная для бинарного поиска int
    double numberToSearchBinaryTotal; // Переменная для бинарного поиска double
    int index; // Переменная для вывода значений бинарного поиска
    int key; // Переменная для удаления записи в массиве

    // Ввод данных в массив
    for (int i = 0; i < arraySize; i++) {
        std::cout << "Product ID: " << i + 1 << std::endl;
        std::cout << "Enter product name: ";
        std::cin.ignore(); // Очищаем буфер ввода перед использованием getline
        std::getline(std::cin, sales[i].productName);

        std::cout << "Enter quantity sold: ";
        std::cin >> sales[i].quantitySold;

        std::cout << "Enter price per unit: ";
        std::cin >> sales[i].pricePerUnit;

        // Вычисляем общую сумму продажи
        sales[i].totalAmount = sales[i].quantitySold * sales[i].pricePerUnit;
        std::cout << "--------------------------" << std::endl;
    }

    // Заполняем массив указателей
    for (int i = 0; i < arraySize; i++) {
        indexersTotalAmount[i] = &sales[i];
        indexersQuantitySold[i] = &sales[i];
    }

    // Сортируем массив указателей по количеству проданных товаров(по возрастанию)
    bubbleSortQuantitySold(indexersQuantitySold, arraySize);

    // Сортируем массив указателей по общей сумме продаж(по убыванию)
    bubbleSortTotalAmount(indexersTotalAmount, arraySize);


    // Печать данных из массивов
    std::cout << "Sorting Quanity Sold: " << std::endl;
    std::cout << std::endl;
    printIndexers(indexersQuantitySold, arraySize);
    std::cout << "Sorting Total Amount: " << std::endl;
    std::cout << std::endl;
    printIndexers(indexersTotalAmount, arraySize);

    // Бинарный поиск
    std::cout << "Binary Quanity Sold: " << std::endl;
    std::cout << std::endl;
    std::cout << "Enter number to search: " << std::endl;
    std::cin >> numberToSearchBinaryQuantity;
    index = binarySearchQuantitySold(indexersQuantitySold, numberToSearchBinaryQuantity);

    if (index != -1) {
        std::cout << "Product name: " << indexersQuantitySold[index]->productName << std::endl;
        std::cout << "Quantity sold: " << indexersQuantitySold[index]->quantitySold << std::endl;
        std::cout << "Price per unit: " << indexersQuantitySold[index]->pricePerUnit << std::endl;
        std::cout << "Total amount: " << indexersQuantitySold[index]->totalAmount << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cout << "Element not found in array\n";
    }



    std::cout << "Binary Total Amount: " << std::endl;
    std::cout << std::endl;
    std::cout << "Enter number to search: " << std::endl;
    std::cin >> numberToSearchBinaryTotal;
    index = binarySearchTotalAmount(indexersTotalAmount, numberToSearchBinaryTotal);
    if (index != -1) {
        std::cout << "Product name: " << indexersTotalAmount[index]->productName << std::endl;
        std::cout << "Quantity sold: " << indexersTotalAmount[index]->quantitySold << std::endl;
        std::cout << "Price per unit: " << indexersTotalAmount[index]->pricePerUnit << std::endl;
        std::cout << "Total amount: " << indexersTotalAmount[index]->totalAmount << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cout << "Element not found in array\n";
    }

    // Измененние данных основного массива
    changeArray(sales);
    bubbleSortQuantitySold(indexersQuantitySold, arraySize); // Сортировка для изменение индекса
    bubbleSortTotalAmount(indexersTotalAmount, arraySize); // Сортировка для изменение индекса

    std::cout << "Enter value of Quantity sold to delete index: " << std::endl;
    std::cin >> key;
    deleteKeyArrayQuantitySold(sales, forNewArrayDelete, key);
    bubbleSortQuantitySold(indexersQuantitySold, arraySize); // Сортировка для изменение индекса
    bubbleSortTotalAmount(indexersTotalAmount, arraySize); // Сортировка для изменение индекса

    return 0;
}
