#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Product {
    string name;
    string store;
    double price;
    string quantity;
};

const int MAX_PRODUCTS = 100;

// Function to add a new product to the list
void addProduct(Product productList[], int& numProducts) {
    if (numProducts == MAX_PRODUCTS) {
        cout << "Maximum number of products reached." << endl;
        return;
    }

    Product newProduct;
    cout << "Enter the product name: ";
    cin >> newProduct.name;
    cout << "Enter the store name: ";
    cin >> newProduct.store;
    cout << "Enter the product price: ";
    cin >> newProduct.price;
    cout << "Enter the quantity: ";
    cin.ignore();
    getline(cin, newProduct.quantity);

    productList[numProducts] = newProduct;
    numProducts++;

    cout << "Product added to the list." << endl;
}

// Function to remove a product from the list by name
void removeProduct(Product productList[], int& numProducts, const string& productName) {
    for (int i = 0; i < numProducts; i++) {
        if (productList[i].name == productName) {
            for (int j = i; j < numProducts - 1; j++) {
                productList[j] = productList[j + 1];
            }
            numProducts--;
            cout << "Product \"" << productName << "\" removed from the list." << endl;
            return;
        }
    }

    cout << "Product with name \"" << productName << "\" not found." << endl;
}

// Function to display information about the products
void displayProducts(const Product productList[], int numProducts) {
    for (int i = 0; i < numProducts; i++) {
        cout << "Product Name: " << productList[i].name << endl;
        cout << "Store Name: " << productList[i].store << endl;
        cout << "Product Price: " << productList[i].price << " USD" << endl;
        cout << "Quantity: " << productList[i].quantity << endl;
        cout << "--------------------------" << endl;
    }
}

// Function to save the list of products to a file
void save(const Product productList[], int numProducts, const string& filename) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    for (int i = 0; i < numProducts; i++) {
        outputFile << productList[i].name << endl;
        outputFile << productList[i].store << endl;
        outputFile << productList[i].price << endl;
        outputFile << productList[i].quantity << endl;
    }
    outputFile.close();
    cout << "Product list successfully saved to file: " << filename << endl;
}

// Function to read the list of products
void read(Product productList[], int& numProducts, const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }
    numProducts = 0;
    string line;
    while (getline(inputFile, line)) {
        productList[numProducts].name = line;
        getline(inputFile, productList[numProducts].store);
        inputFile >> productList[numProducts].price;
        inputFile.ignore();
        getline(inputFile, productList[numProducts].quantity);
        numProducts++;
    }
    inputFile.close();
    cout << "Product list successfully read from file: " << filename << endl;
}
int main() {
    Product productList[MAX_PRODUCTS];
    int numProducts = 0;
    string filename = "products.txt";
    read(productList, numProducts, filename);
    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add a product" << endl;
        cout << "2. Remove a product" << endl;
        cout << "3. Display the product list" << endl;
        cout << "4. Save the product list to a file" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose an action: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct(productList, numProducts);
                break;
            case 2: {
                cout << "Enter the name of the product to remove: ";
                string productName;
                cin >> productName;
                removeProduct(productList, numProducts, productName);
                break;
            }
            case 3:
                displayProducts(productList, numProducts);
                break;
            case 4:
                save(productList, numProducts, filename);
                break;
            case 0:
                save(productList, numProducts, filename);
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
