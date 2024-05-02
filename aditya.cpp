#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

int inputChecker(string &s);

float inputCheckerFloat(string &s);

// Struct to represent a product
class Product
{
public:
    // Public member functions to access private members
    int getCode() const { return code; }
    string getName() const { return name; }
    float getPrice() const { return price; }

    // Constructor
    Product(int code, const string &name, float price) : code(code), name(name), price(price), stock(30)
    {
    }

    int code;
    string name;
    float price;
    int quantity = 0, stock; // Quantity attribute to keep track of the quantity in the cart
    int qtySold = 0;
};

class Administration
{
private:
    int pin;

public:
    vector<Product> deletedprd;
    Administration()
    {
        pin = 1234;
    }
    void displayProductQuantities(const string &categoryName, const vector<Product> &products)
    {

        for (const auto &product : products)
        {
            cout << setw(5) << product.code << " | "
                 << setw(20) << left << product.name << " | "
                 << setw(10) << product.stock << endl;
        }
    }
    void editInventory(vector<Product> &beverages, vector<Product> &snacks, vector<Product> &candies, vector<Product> &biscuits)
    {
        cout << endl;
        cout << setw(20) << "Inventory Report" << endl;
        cout << "---------------------------------------------\n";

        cout << "Code       Name       Stock Quantity\n";
        cout << "---------------------------------------------\n";

        displayProductQuantities("Beverages", beverages);
        displayProductQuantities("Snacks", snacks);
        displayProductQuantities("candies", candies);
        displayProductQuantities("Biscuits", biscuits);

        string choice_str;
        cout << "1.Restock a product\n2.Replace a product\n0.Cancel\n ";
        cout << "Enter your choice :";
        int choice = inputChecker(choice_str);

        if (choice == 1)
        { // Restock a product
            cout << "Enter the item number to restock (0 to exit): ";

            string itemNum_str;
            int itemNum = inputChecker(itemNum_str);

            if (itemNum >= 1 && itemNum <= 16)
            {
                string newQuantity_str;
                int newQuantity = 0;
                while (newQuantity <= 0 || newQuantity > 30)
                {
                    cout << "Enter the new quantity: ";
                    newQuantity = inputChecker(newQuantity_str);
                    if (newQuantity <= 0 || newQuantity > 30)
                        cout << "Invalid Quantity" << endl;
                }
                if (itemNum >= 1 && itemNum <= 4)
                {
                    beverages[itemNum - 1].stock = newQuantity;
                }
                else if (itemNum >= 5 && itemNum <= 8)
                {
                    snacks[itemNum - 5].stock = newQuantity;
                }
                else if (itemNum >= 9 && itemNum <= 12)
                {
                    candies[itemNum - 9].stock = newQuantity;
                }
                else if (itemNum >= 13 && itemNum <= 16)
                {
                    biscuits[itemNum - 13].stock = newQuantity;
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
            string itemNum_str;
            int itemNum = inputChecker(itemNum_str);

            if (itemNum >= 1 && itemNum <= 16)
            {
                string newItem;
                cout << "Enter the new item name: ";
                cin >> newItem;

                string qty_str;
                int qty = 0;
                while (qty <= 0 || qty > 30)
                {
                    cout << "Enter the stock: ";
                    qty = inputChecker(qty_str);
                    if (qty <= 0 || qty > 30)
                        cout << "Invalid Quantity" << endl;
                }

                cout << "Enter the price: ";
                string price_str;
                float price = inputCheckerFloat(price_str);

                if (itemNum >= 1 && itemNum <= 4)
                {
                    deletedprd.push_back(beverages[itemNum - 1]);
                    beverages[itemNum - 1].name = newItem;
                    beverages[itemNum - 1].stock = qty;
                    beverages[itemNum - 1].price = price;
                    beverages[itemNum - 1].qtySold = 0;
                }
                else if (itemNum >= 5 && itemNum <= 8)
                {
                    deletedprd.push_back(snacks[itemNum - 5]);
                    snacks[itemNum - 5].name = newItem;
                    snacks[itemNum - 5].stock = qty;
                    snacks[itemNum - 5].price = price;
                    snacks[itemNum - 5].qtySold = 0;
                }
                else if (itemNum >= 9 && itemNum <= 12)
                {
                    deletedprd.push_back(candies[itemNum - 9]);
                    candies[itemNum - 9].name = newItem;
                    candies[itemNum - 9].stock = qty;
                    candies[itemNum - 9].price = price;
                    candies[itemNum - 9].qtySold = 0;
                }
                else if (itemNum >= 13 && itemNum <= 16)
                {
                    deletedprd.push_back(biscuits[itemNum - 13]);
                    biscuits[itemNum - 13].name = newItem;
                    biscuits[itemNum - 13].stock = qty;
                    biscuits[itemNum - 13].price = price;
                    biscuits[itemNum - 13].qtySold = 0;
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
        else if (choice == 0)
        { // Cancel
            return;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }

    void salesReport(const vector<Product> &beverages, const vector<Product> &snacks, const vector<Product> &candies, const vector<Product> &biscuits)
    {
        cout << setw(10) << "Code" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;

        float totalAmount = 0;
        int totalProductsSold = 0;
        int cnt = 0;

        // Display beverages
        for (const auto &product : beverages)
        {
            cout << setw(10) << ++cnt << setw(20) << product.getName() << setw(10) << product.qtySold << setw(10) << product.getPrice() << endl;
            totalProductsSold += product.qtySold;
            totalAmount += product.qtySold * product.getPrice();
        }

        // Display snacks
        for (const auto &product : snacks)
        {
            cout << setw(10) << ++cnt << setw(20) << product.getName() << setw(10) << product.qtySold << setw(10) << product.getPrice() << endl;
            totalProductsSold += product.qtySold;
            totalAmount += product.qtySold * product.getPrice();
        }

        // Display candies
        for (const auto &product : candies)
        {
            totalAmount += product.qtySold * product.getPrice();
            cout << setw(10) << ++cnt << setw(20) << product.getName() << setw(10) << product.qtySold << setw(10) << product.getPrice() << endl;
            totalProductsSold += product.qtySold;
        }

        // Display biscuits
        for (const auto &product : biscuits)
        {
            cout << setw(10) << ++cnt << setw(20) << product.getName() << setw(10) << product.qtySold << setw(10) << product.getPrice() << endl;
            totalAmount += product.qtySold * product.getPrice();
            totalProductsSold += product.qtySold;
        }
        // Display deleted products
        for (const auto &product : deletedprd)
        {
            cout << setw(10) << ++cnt << setw(20) << product.getName() << setw(10) << product.qtySold << setw(10) << product.getPrice() << endl;
            totalAmount += product.qtySold * product.getPrice();
            totalProductsSold += product.qtySold;
        }
        cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;

        cout << "Total Products Sold: " << totalProductsSold << endl;
        cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
    }
    void displayAdmin(vector<Product> &beverages, vector<Product> &snacks, vector<Product> &candies, vector<Product> &biscuits)

    {
        while (true)
        {
            cout << "Enter pin" << endl;
            string tmp_str;
            int tmp = inputChecker(tmp_str);

            if (pin == tmp)
                break;
            else
            {
                cout << "Invalid pin" << endl;
                return;
            }
        }

        while (true)
        {
            cout << "\nWelcome to the Vending Machine Administrator" << endl;
            cout << "1. Edit Inventory" << endl;
            cout << "2. Check Inventory" << endl;
            cout << "3. Sales Report" << endl;
            cout << "4. Change Password" << endl;
            cout << "5. Shut Down Vending Machine" << endl;
            cout << "6. Exit" << endl;

            string choice_str;
            cout << "Enter your choice: ";
            int choice = inputChecker(choice_str);

            switch (choice)
            {
            case 1:
                editInventory(beverages, snacks, candies, biscuits);
                break;
            case 2:
                cout << endl;
                cout << setw(20) << "Inventory Report" << endl;
                cout << "---------------------------------------------\n";

                cout << "Code       Name       Stock Quantity\n";
                cout << "---------------------------------------------\n";

                displayProductQuantities("Beverages", beverages);
                displayProductQuantities("Snacks", snacks);
                displayProductQuantities("candies", candies);
                displayProductQuantities("Biscuits", biscuits);

                break;
            case 3:
                salesReport(beverages, snacks, candies, biscuits);

                break;
            case 4:
                while (true)
                {
                    cout << "Enter pin" << endl;
                    string tmp_str;
                    int tmp = inputChecker(tmp_str);
                    if (pin == tmp)
                    {

                        cout << "Enter new pin" << endl;
                        string pin_str;
                        pin = inputChecker(pin_str);
                        cout << "Pin changed" << endl;
                        break;
                    }
                    else
                    {
                        cout << "Invalid pin" << endl;
                        break;
                    }
                }
                break;
            case 5:
                while (true)
                {
                    cout << "Enter pin" << endl;
                    string tmp_str;
                    int tmp = inputChecker(tmp_str);
                    if (pin == tmp)
                    {
                        cout << "Shutting down";
                        exit(0);
                    }
                    else
                    {
                        cout << "Invalid pin" << endl;
                        break;
                    }
                }
            case 6:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
        return;
    }
};

class VendingMachine
{
public:
    VendingMachine()
    {
    }
    void displayTwoCategories(const string &categoryName1, const vector<Product> &products1,
                              const string &categoryName2, const vector<Product> &products2)
    {
        cout << "---------------------------------------------\t---------------------------------------------\n";
        cout << "Category: " << setw(31) << left << categoryName1 << "\tCategory: " << setw(31) << left << categoryName2 << endl;
        cout << "---------------------------------------------\t---------------------------------------------\n";
        cout << "Code  |  Product Name        |  Price\t\tCode  |  Product Name        |  Price\n";
        cout << "---------------------------------------------\t---------------------------------------------\n";

        size_t maxSize = max(products1.size(), products2.size());

        for (size_t i = 0; i < maxSize; ++i)
        {
            if (i < products1.size())
            {
                cout << setw(5) << products1[i].getCode() << " | " << setw(20) << left << products1[i].getName() << " | $" << products1[i].getPrice() << "\t\t";
            }
            else
            {
                cout << setw(5) << " "
                     << " | " << setw(20) << " "
                     << " | " << setw(6) << " "
                     << "\t\t";
            }

            if (i < products2.size())
            {
                cout << setw(5) << products2[i].getCode() << " | " << setw(20) << left << products2[i].getName() << " | $" << products2[i].getPrice() << endl;
            }
            else
            {
                cout << setw(5) << " "
                     << " | " << setw(20) << " "
                     << " | " << setw(6) << " " << endl;
            }
        }
        cout << "---------------------------------------------\t---------------------------------------------\n";
    }

    void addItem(vector<Product> &cart, vector<Product> &beverages, vector<Product> &snacks, vector<Product> &candies, vector<Product> &biscuits)
    {
        while (true) // Loop until the user chooses to go back to the main menu
        {
            string code_str, quantity_str;
            int code, quantity;
            bool found = false;
            Product *productToUpdate = nullptr; // Pointer to keep track of the product to update stock

            do
            {
                cout << "\nEnter the product code to add to cart (0 to go back to Menu): ";
                code = inputChecker(code_str);

                // If the user enters 0, return without adding any item
                if (code == 0)
                    return;

                found = false;

                // Check if the code exists in any category
                for (Product &product : beverages)
                {
                    if (product.getCode() == code)
                    {
                        found = true;
                        productToUpdate = &product;
                        break;
                    }
                }

                if (!found)
                {
                    for (Product &product : snacks)
                    {
                        if (product.getCode() == code)
                        {
                            found = true;
                            productToUpdate = &product;
                            break;
                        }
                    }
                }

                if (!found)
                {
                    for (Product &product : candies)
                    {
                        if (product.getCode() == code)
                        {
                            found = true;
                            productToUpdate = &product;
                            break;
                        }
                    }
                }

                if (!found)
                {
                    for (Product &product : biscuits)
                    {
                        if (product.getCode() == code)
                        {
                            found = true;
                            productToUpdate = &product;
                            break;
                        }
                    }
                }

                if (!found)
                {
                    cout << "Product not found. Please enter a valid product code." << endl;
                }
            } while (!found);

            // Ask for the quantity after a valid product code is entered
            cout << "Enter the quantity: ";
            quantity = inputChecker(quantity_str);

            // If quantity is 0, don't add the item to the cart
            if (quantity == 0)
            {
                cout << "Quantity is 0. Product not added to the cart." << endl;
                continue; // Prompt for product code again
            }

            // Check if the requested quantity is available in stock
            if (productToUpdate != nullptr && productToUpdate->stock >= quantity)
            {
                // Update the stock of the product
                productToUpdate->stock -= quantity;

                // Add the product to the cart
                found = false;
                for (Product &product : cart)
                {
                    if (product.getCode() == code)
                    {
                        product.quantity += quantity;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    Product newProduct = *productToUpdate; // Create a copy of the product to add to the cart
                    newProduct.quantity = quantity;
                    cart.push_back(newProduct);
                }

                cout << "Product added to the cart successfully." << endl;
            }
            else
            {
                // If the requested quantity is not available, display the available stock
                if (productToUpdate != nullptr)
                {
                    cout << "Not enough stock. Only " << productToUpdate->stock << " items available." << endl;
                }
            }
        }
    }

    // Function to display items in the cart
    void displayCart(const vector<Product> &cart)
    {
        cout << "\n-------------------------------------------------------------------------------" << endl;
        // Calculate the spacing needed to center the "Cart" header
        int headerSpacing = (80 - 4 - 5) / 2; // Total width - length of "Cart" - 5 spaces around "Cart"
        cout << setw(headerSpacing) << ""
             << "Cart" << endl; // Print "Cart" centered
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Sr. No. |  Code  |  Product Name        |  Quantity  |  Price  |  Total Price" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;

        int srNo = 1;
        float totalPrice = 0;
        for (const auto &item : cart)
        {
            float totalItemPrice = item.getPrice() * item.quantity;
            totalPrice += totalItemPrice;
            cout << setw(7) << srNo++ << " | ";
            cout << setw(6) << item.getCode() << " | ";
            cout << setw(20) << left << item.getName() << " | ";
            cout << setw(10) << item.quantity << " | ";
            cout << setw(8) << item.getPrice() << " | ";
            cout << setw(12) << totalItemPrice << endl;
        }

        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Total Price: $" << totalPrice << endl;
    }

    // Function to edit the quantity of an item in the cart
    void editCart(vector<Product> &cart, vector<Product> &beverages, vector<Product> &snacks, vector<Product> &candies, vector<Product> &biscuits)
    {
        string srNo_str, newQuantity_str;
        int srNo, newQuantity;

        cout << "\nEnter the Sr. No. of the item you want to edit: ";
        srNo = inputChecker(srNo_str);

        if (srNo < 1 || srNo > static_cast<int>(cart.size()))
        {
            cout << "Invalid Sr No. Please enter a valid Sr No." << endl;
            return;
        }
re1:
        cout << "Enter the new quantity: ";
        newQuantity = inputChecker(newQuantity_str);

        if (newQuantity < 0 || newQuantity > (30 - (cart[srNo - 1].quantity)))
        {
            cout << "Invalid quantity. Please enter a valid quantity." << endl;
             cout<<"Available quantity is : "<<(30 - cart[srNo - 1].quantity)<<endl;
            goto re1;
        }

        // Update the quantity of the item
        cart[srNo - 1].quantity = newQuantity;

        // If the new quantity is zero, remove the item from the cart
        if (newQuantity == 0)
        {
            cart.erase(cart.begin() + (srNo - 1));
            cout << "Item removed from the cart." << endl;

            // No need to display the cart again if item is removed
            return;
        }
        else
        {
            cout << "Quantity updated successfully." << endl;
        }

        // Display the cart again with updated quantity or removal
        displayCart(cart);

        // Rest of the function remains the same
        cout << "\nOptions:" << endl;
        cout << "1. Edit Cart" << endl;
        cout << "2. Empty Cart" << endl;
        cout << "3. Check Out" << endl;
        cout << "4. Back" << endl;
        cout << "Enter your choice: ";
        string cartOption_str;
        int cartOption = inputChecker(cartOption_str);
        switch (cartOption)
        {
        case 1:
            editCart(cart, beverages, snacks, candies, biscuits);
            break;
        case 2:
            emptyCart(cart);
            break;
        case 3:
            checkout(cart, beverages, snacks, candies, biscuits);
            break;
        case 4:
            // Back to main menu
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    // Function to empty the cart
    void emptyCart(vector<Product> &cart)
    {
        cart.clear();
        cout << "Cart emptied successfully." << endl;
    }
    // Function to handle the checkout process
    // Function to handle the checkout process
    void checkout(vector<Product> &cart, vector<Product> &beverages, vector<Product> &snacks, vector<Product> &candies, vector<Product> &biscuits)
    {
        float totalPrice = 0;
        for (const auto &item : cart)
        {
            totalPrice += item.getPrice() * item.quantity;
        }

        displayCart(cart);

        string amountPaid_str;

        cout << "Enter the amount paid: ";
        float amountPaid = inputCheckerFloat(amountPaid_str);

        // Loop to ensure the user pays the correct amount
        while (amountPaid < totalPrice)
        {
            cout << "Amount paid is less than the total price. Please pay the correct amount." << endl;
            cout << "Enter the amount paid: ";
            cin >> amountPaid;
        }

        float change = amountPaid - totalPrice;
        if (change == 0)
        {

            cout << "Change: 0$" << endl;
        }
        else
        {

            cout << "Change: $" << change << endl;
        }

        // Update the stock of each product in the cart
        for (Product &product : cart)
        {
            // Since the products in the cart are references to the original products,
            // updating the quantity here will update the stock in the original product lists.
            product.stock -= product.quantity;
        }

        // Clear the cart
        cart.clear();

        // Display a thank you message
        cout << "Thank you for your purchase. Have a nice day!" << endl;

        // Wait for 10 seconds
        this_thread::sleep_for(chrono::seconds(5));

        // Clear the screen
        system("cls"); // For Windows4

        // Display all the categories with their items again
        displayTwoCategories("Beverages", beverages, "Snacks", snacks);
        displayTwoCategories("Candies", candies, "Biscuits", biscuits);
    }
};

int main()
{
    VendingMachine vm;

    Administration admin;
    // Define categories and products
    vector<Product> beverages = {
        Product(1, "Coca-Cola", 1.50),
        Product(2, "Pepsi", 1.50),
        Product(3, "Sprite", 1.30),
        Product(4, "Fanta", 1.45)};

    vector<Product> snacks = {
        Product(5, "Doritos", 2.00),
        Product(6, "Ruffles", 2.00),
        Product(7, "Lays", 1.80),
        Product(8, "Cheetos", 1.75)};

    vector<Product> candies = {
        Product(9, "KitKat", 1.00),
        Product(10, "Snickers", 1.25),
        Product(11, "Twix", 1.10),
        Product(12, "M&M's", 1.20)};

    vector<Product> biscuits = {
        Product(13, "Good Day", 0.75),
        Product(14, "Hide & Seek", 0.60),
        Product(15, "Parle G", 0.80),
        Product(16, "Bourbon", 1.00)};

    // Display two categories side by side
    vm.displayTwoCategories("Beverages", beverages, "Snacks", snacks);
    vm.displayTwoCategories("Candies", candies, "Biscuits", biscuits);

    // Cart to store selected items
    vector<Product> cart;

    // Display menu
    int choice;
    do
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << setw(10) << "Menu:";
        cout << setw(20) << "1. Add Item";
        cout << setw(20) << "2. Cart";
        cout << setw(20) << "3. Settings" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;

        string choice_str;
        int choice;
        string cartOption_str;
        int cartOption;

        do
        {
            cout << "\nEnter your choice: ";
            choice = inputChecker(choice_str);
            if (choice > 3 || choice < 0)
            {
                cout << "Invalid input , Please enter valid input ." << endl;
            }
        } while (choice > 3 || choice < 0);

        switch (choice)
        {
        case 1:
            vm.addItem(cart, beverages, snacks, candies, biscuits);
            break;
        case 2:
            vm.displayCart(cart);
            cout << "Options:" << endl;
            cout << "1. Edit Cart" << endl;
            cout << "2. Empty Cart" << endl;
            cout << "3. Check Out" << endl;
            cout << "4. Back" << endl;
            cout << "Enter your choice: ";
            cartOption = inputChecker(cartOption_str);
            switch (cartOption)
            {
            case 1:
                vm.editCart(cart, beverages, snacks, candies, biscuits);
                break;
            case 2:
                vm.emptyCart(cart);
                break;
            case 3:

                vm.checkout(cart, beverages, snacks, candies, biscuits);
                break;

            case 4:
                // Back to main menu
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
            }
            break;
        case 3:
            admin.displayAdmin(beverages, snacks, candies, biscuits);
            break;

        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }

    } while (choice != 0);

    return 0;
}

int inputChecker(string &s)
{

    bool check;
    do
    {
        check = true;
        getline(cin, s);
        if (s == "")
        {
            cout << "Enter valid input " << endl;
            check = false;
            continue;
        }

        for (int i = 0; i < s.length(); i++)
        {
            if (!(s[i] >= '0' && s[i] <= '9'))
            {
                cout << "Enter valid input " << endl;
                check = false;
                break;
            }
        }
    } while (!check);

    return stoi(s);
}

float inputCheckerFloat(string &s)
{

    bool check;
    int count = 0;
    do
    {
        check = true;
        getline(cin, s);
        if (s == "")
        {
            cout << "Enter valid input " << endl;
            check = false;
            continue;
        }

        for (int i = 0; i < s.length(); i++)
        {
            if (!(s[i] >= '0' && s[i] <= '9') && s[i] != '.')
            {
                cout << "Enter valid input " << endl;
                check = false;
                break;
            }
            if (s[i] == '.')
            {
                count++;
                if (count > 1)
                {
                    cout << "Enter valid input " << endl;
                    check = false;
                    break;
                }
            }
        }
    } while (!check);

    return stof(s);
}
