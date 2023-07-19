#include <iostream>
#include <fstream>
#include <vector>

struct Product {
    std::string name;
    int quantity;
};


void stockManagement() {
    std::vector<Product> products;
    std::string fileName = "stock.txt";


    products = readProductsFromFile(fileName);

    char choice;
    do {
        std::cout << "---Stock Management---" << std::endl;
        std::cout << "1. Add product" << std::endl;
        std::cout << "2. Remove product" << std::endl;
        std::cout << "3. Display stock" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case '1': {
            std::string name;
            int quantity;
            std::cout << "Enter product name: ";
            std::cin >> name;
            std::cout << "Enter product quantity: ";
            std::cin >> quantity;


            Product product;
            product.name = name;
            product.quantity = quantity;
            products.push_back(product);
            std::cout << "Product added to stock." << std::endl;
            break;
        }
        case '2': {
            std::string name;
            int quantityToRemove;
            std::cout << "Enter product name to remove: ";
            std::cin >> name;
            std::cout << "Enter quantity to remove: ";
            std::cin >> quantityToRemove;


            bool found = false;
            for (auto it = products.begin(); it != products.end(); ++it) {
                if (it->name == name) {
                    if (it->quantity <= quantityToRemove) {
                        products.erase(it);
                    }
                    else {
                        it->quantity -= quantityToRemove;
                    }
                    found = true;
                    break;
                }
            }

            if (found) {
                std::cout << "Product removed from stock." << std::endl;
            }
            else {
                std::cout << "Product not found in stock." << std::endl;
            }
            break;
        }
        case '3': {

            std::cout << "Stock:" << std::endl;
            for (const auto& product : products) {
                std::cout << "Product: " << product.name << ", Quantity: " << product.quantity << std::endl;
            }
            break;
        }
        case '4':

            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;
    } while (choice != '4');


    writeProductsToFile(products, fileName);
}


std::vector<Product> readProductsFromFile(const std::string& fileName) {
    std::vector<Product> products;
    std::ifstream inputFile(fileName);

    if (!inputFile) {
        std::cout << "Error opening file." << std::endl;
        return products;
    }

    std::string name;
    int quantity;
    while (inputFile >> name >> quantity) {
        Product product;
        product.name = name;
        product.quantity = quantity;
        products.push_back(product);
    }

    inputFile.close();
    return products;
}


void writeProductsToFile(const std::vector<Product>& products, const std::string& fileName) {
    std::ofstream outputFile(fileName);

    if (!outputFile) {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    for (const auto& product : products) {
        outputFile << product.name << " " << product.quantity << std::endl;
    }

    outputFile.close();
}



int main() {
    stockManagement();

    return 0;
}
