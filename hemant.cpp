#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

// Struct to represent a product
struct Product
{
    int code;
    string name;
    float price;
    int quantity;
};

class Administrator
{
private:
    vector<string> inventory;
    vector<int> quantities;
    vector<float> price;
    string password;
    bool isShutdown;
    vector<Product> beverages;
    vector<Product> snacks;
    vector<Product> candies;
    vector<Product> biscuits;
    vector<Product> deletedprd;
    // the quantity of the current prd stores the quantities sold rather than the available
    vector<Product> currentprd = {{1, "Coca-Cola", 1.50, 0}, {2, "Pepsi", 1.50, 0}, {3, "Sprite", 1.30, 0}, {4, "Fanta", 1.45, 0}, {5, "Doritos", 2.00, 0}, {6, "Ruffles", 2.00, 0}, {7, "Lays", 1.80, 0}, {8, "Cheetos", 1.75, 0}, {9, "KitKat", 1.00, 0}, {10, "Snickers", 1.25, 0}, {11, "Twix", 1.10, 0}, {12, "M&M's", 1.20, 0}, {13, "Good Day", 0.75, 0}, {14, "Hide & Seek", 0.60, 0}, {15, "Parle G", 0.80, 0}, {16, "Bourbon", 1.00, 0}};

public:
    Administrator()
    {
        inventory = {"Coca-Cola", "Pepsi", "Sprite", "Fanta", "Doritos", "Ruffles", "Lays", "Cheetos", "KitKat", "Snickers", "Twix", "M&M's", "Good Day", "Hide & Seek", "Parle G", "Bourbon"};
        quantities = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
        price = {1.50, 1.50, 1.30, 1.45, 2.00, 2.00, 1.80, 1.75, 1.00, 1.25, 1.10, 1.20, 0.75, 0.60, 0.80, 1.00};
        password = "admin123";
        isShutdown = false;

        // Initialize product categories
        beverages = {{1, "Coca-Cola", 1.50, quantities[0]}, {2, "Pepsi", 1.50, quantities[1]}, {3, "Sprite", 1.30, quantities[2]}, {4, "Fanta", 1.45, quantities[3]}};
        snacks = {{5, "Doritos", 2.00, quantities[4]}, {6, "Ruffles", 2.00, quantities[5]}, {7, "Lays", 1.80, quantities[6]}, {8, "Cheetos", 1.75, quantities[7]}};
        candies = {{9, "KitKat", 1.00, quantities[8]}, {10, "Snickers", 1.25, quantities[9]}, {11, "Twix", 1.10, quantities[10]}, {12, "M&M's", 1.20, quantities[11]}};
        biscuits = {{13, "Good Day", 0.75, quantities[12]}, {14, "Hide & Seek", 0.60, quantities[13]}, {15, "Parle G", 0.80, quantities[14]}, {16, "Bourbon", 1.00, quantities[15]}};
    }

    void displayCategory(const string &categoryName1, const vector<Product> &products1, const string &categoryName2, const vector<Product> &products2)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int productColumnWidth = (width / 2) - 50;

        cout << setw((width / 2) - (categoryName1.length() / 2)) << left << categoryName1 << "\t" << setw((width / 2) - (categoryName2.length() / 2)) << left << categoryName2 << endl;
        cout << setw(width) << setfill('-') << "" << endl;
        cout << setfill(' ') << "Code | Product Name | Price | Qty\t\tCode | Product Name | Price | Qty" << endl;
        cout << setw(width) << setfill('-') << "" << endl;

        for (size_t i = 0; i < max(products1.size(), products2.size()); i++)
        {
            if (i < products1.size())
            {
                cout << setw(5) << products1[i].code << " | " << setw(productColumnWidth) << left << products1[i].name << " | $" << products1[i].price << " | " << setw(3) << products1[i].quantity << "\t\t";
            }
            else
            {
                cout << setw(5) << " "
                     << " | " << setw(productColumnWidth) << " "
                     << " | " << setw(6) << " "
                     << " | " << setw(3) << " "
                     << "\t\t";
            }
            if (i < products2.size())
            {
                cout << setw(5) << products2[i].code << " | " << setw(productColumnWidth) << left << products2[i].name << " | $" << products2[i].price << " | " << setw(3) << products2[i].quantity << endl;
            }
            else
            {
                cout << setw(5) << " "
                     << " | " << setw(productColumnWidth) << " "
                     << " | " << setw(6) << " "
                     << " | " << setw(3) << " " << endl;
            }
        }

        cout << setw(width) << setfill('-') << "" << endl;
        cout << setfill(' ');
    }

    void displayInventory()
    {
        displayCategory("Beverages", beverages, "Snacks", snacks);
        displayCategory("Candies", candies, "Biscuits", biscuits);
    }

    void editInventory()
    {
        cout << "Current Inventory:" << endl;
        displayInventory();

        int choice;
        cout << "1. Restock a product\n2. Replace a product\n0. Cancel\n ";
        cin >> choice;

        if (choice == 1)
        { // Restock a product
            cout << "Enter the item number to restock (0 to exit): ";
            int itemNum;
            cin >> itemNum;

            if (itemNum >= 1 && itemNum <= inventory.size())
            {
                int newQuantity;
                cout << "Enter the new quantity: ";
                cin >> newQuantity;
                quantities[itemNum - 1] = newQuantity;
                if (itemNum / 4 == 0)
                {
                    beverages[(itemNum - 1) % 4].quantity = quantities[itemNum - 1];
                }
                else if (itemNum / 4 == 1)
                {
                    snacks[(itemNum - 1) % 4].quantity = quantities[itemNum - 1];
                }
                else if (itemNum / 4 == 2)
                {
                    candies[(itemNum - 1) % 4].quantity = quantities[itemNum - 1];
                }
                else if (itemNum / 4 == 3)
                {
                    biscuits[(itemNum - 1) % 4].quantity = quantities[itemNum - 1];
                }
                cout << "Inventory updated successfully." << endl;
            }
            else if (itemNum == 0)
            {
                return;
            }
            else
            {
                cout << "Invalid item number." << endl;
            }
        }
        else if (choice == 2)
        { // Replace a product
            cout << "Enter the item number to replace (0 to exit): ";
            int itemNum;
            cin >> itemNum;
            deletedprd.push_back(currentprd[itemNum - 1]);
            if (itemNum >= 1 && itemNum <= inventory.size())
            {
                string newItem;
                cout << "Enter the new item name: ";
                cin >> newItem;
                inventory[itemNum - 1] = newItem;
                cout << "Enter the price: ";
                cin >> price[itemNum - 1];
                cout << "Enter quantity: ";
                cin >> quantities[itemNum - 1];
                if (itemNum / 4 == 0)
                {
                    beverages[(itemNum - 1) % 4].name = newItem;
                    beverages[(itemNum - 1) % 4].price = price[itemNum - 1];
                    beverages[(itemNum - 1) % 4].quantity = quantities[itemNum - 1];
                }
                else if (itemNum / 4 == 1)
                {
                    snacks[(itemNum - 1) % 4].name = newItem;
                    snacks[(itemNum - 1) % 4].price = price[itemNum - 1];
                    snacks[(itemNum - 1) % 4].quantity = quantities[itemNum - 1];
                }
                else if (itemNum / 4 == 2)
                {
                    candies[(itemNum - 1) % 4].name = newItem;
                    candies[(itemNum - 1) % 4].price = price[itemNum - 1];
                    candies[(itemNum - 1) % 4].quantity = quantities[itemNum - 1];
                }
                else if (itemNum / 4 == 3)
                {
                    biscuits[(itemNum - 1) % 4].name = newItem;
                    biscuits[(itemNum - 1) % 4].price = price[itemNum - 1];
                    biscuits[(itemNum - 1) % 4].quantity = quantities[itemNum - 1];
                }
                currentprd[itemNum - 1].name = newItem;
                currentprd[itemNum - 1].price = price[itemNum - 1];
                currentprd[itemNum - 1].quantity = 0;

                cout << "Inventory updated successfully." << endl;
            }
            else if (itemNum == 0)
            {
                return;
            }
            else
            {
                cout << "Invalid item number." << endl;
            }
        }
        else if (choice == 0)
        { // Cancel
            return;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }

    void checkInventory()
    {
        cout << "Current Inventory:" << endl;
        displayInventory();
    }

    void salesReport()
    {
        vector<Product> allProducts = currentprd;
        allProducts.insert(allProducts.end(), deletedprd.begin(), deletedprd.end());

        cout << "Sales Report" << endl;
        cout << "Code\tName\t\tPrice\tQuantity Sold" << endl;
        cout << "-----------------------------------------" << endl;

        float totalAmountEarned = 0.0f;
        int totalQuantitySold = 0;
        int i = 0;
        for (const auto &product : allProducts)
        {
            int quantitySold = product.quantity;
            totalQuantitySold += quantitySold;
            totalAmountEarned += (quantitySold * product.price);
            cout << ++i << "\t" << setw(15) << left << product.name << "\t$" << fixed << setprecision(2) << product.price
                 << "\t" << quantitySold << endl;
        }

        cout << "-----------------------------------------" << endl;
        cout << "Total Quantity Sold: " << totalQuantitySold << endl;
        cout << "Total Amount Earned: $" << fixed << setprecision(2) << totalAmountEarned << endl;
    }

    void changePassword()
    {
        string newPassword;
        cout << "Enter the new password: ";
        cin >> newPassword;
        password = newPassword;
        cout << "Password changed successfully." << endl;
    }

    void shutdownVendingMachine()
    {
        isShutdown = true;
        cout << "Vending machine is shutting down." << endl;
    }

    bool isPasswordCorrect(string enteredPassword)
    {
        return enteredPassword == password;
    }

    bool isVendingMachineShutdown()
    {
        return isShutdown;
    }
    void updateSales(vector<int, int> qty)
    {
        for (int i = 0; i < qty.size(); i++)
            currentprd[qty[i].first - 1].quantity += qty[i].second;
    }
};

int main()
{
    Administrator vm;
    string enteredPassword;

    while (true)
    {
        cout << "Welcome to the Vending Machine Administrator!" << endl;
        cout << "1. Edit Inventory" << endl;
        cout << "2. Check Inventory" << endl;
        cout << "3. Sales Report" << endl;
        cout << "4. Change Password" << endl;
        cout << "5. Shut Down Vending Machine" << endl;
        cout << "6. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            vm.editInventory();
            break;
        case 2:
            vm.checkInventory();
            break;
        case 3:
            vm.salesReport();
            break;
        case 4:
            cout << "Enter the current password: ";
            cin >> enteredPassword;
            if (vm.isPasswordCorrect(enteredPassword))
            {
                vm.changePassword();
            }
            else
            {
                cout << "Incorrect password." << endl;
            }
            break;
        case 5:
            cout << "Enter the password to shut down the vending machine: ";
            cin >> enteredPassword;
            if (vm.isPasswordCorrect(enteredPassword))
            {
                vm.shutdownVendingMachine();
                break;
            }
            else
            {
                cout << "Incorrect password." << endl;
            }
            break;
        case 6:
            cout << "Exiting the Vending Machine Administrator." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        if (vm.isVendingMachineShutdown())
        {
            break;
        }
    }

    return 0;
}