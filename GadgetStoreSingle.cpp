// Project Made by: Augusto, Tagaan, Ribo
// BSCPE 2-G
// Gadget Store Management System

// Required Libraries

// iostream: Provides input/output stream functionality (cin, cout) for user interaction
#include <iostream>

// iomanip: Provides tools for formatting output (setw, setprecision) for table display
#include <iomanip>

// string: Provides string class and related functions for text manipulation
#include <string>

// map: Provides map container to store gadgets organized by categories
#include <map>

// vector: Provides dynamic array functionality for storing lists of gadgets
#include <vector>

// random: Provides random number generation for creating unique serial numbers
#include <random>

// algorithm: Provides algorithms like transform() for string manipulation
#include <algorithm>

// cctype: Provides character handling functions (toupper) for case conversion
#include <cctype>

/*
 * Gadget Class: Represents a single gadget item in the store
 * Contains all properties of a gadget and methods to access/modify them
 */
class Gadget {
private:
    std::string model;          // Name/model of the gadget
    std::string category;       // Category (phone, laptop, etc.)
    std::string serialNumber;   // Unique identifier
    std::string brand;          // Manufacturer/brand name
    double price;              // Price in currency
    std::string color;         // Color of the gadget
    int stockQuantity;         // Available quantity in stock

public:
    // Default constructor
    Gadget() = default;

    // Constructor with all gadget properties
    Gadget(const std::string& model, const std::string& category, 
           const std::string& serialNumber, const std::string& brand,
           double price, const std::string& color, int stockQuantity)
        : model(model), category(category), serialNumber(serialNumber),
          brand(brand), price(price), color(color), stockQuantity(stockQuantity) {}

    // Getter methods: Return the respective property values
    std::string getModel() const { return model; }
    std::string getCategory() const { return category; }
    std::string getSerialNumber() const { return serialNumber; }
    std::string getBrand() const { return brand; }
    double getPrice() const { return price; }
    std::string getColor() const { return color; }
    int getStockQuantity() const { return stockQuantity; }

    // Setter methods: Update the respective property values
    void setModel(const std::string& model) { this->model = model; }
    void setCategory(const std::string& category) { this->category = category; }
    void setSerialNumber(const std::string& serialNumber) { this->serialNumber = serialNumber; }
    void setBrand(const std::string& brand) { this->brand = brand; }
    void setPrice(double price) { this->price = price; }
    void setColor(const std::string& color) { this->color = color; }
    void setStockQuantity(int quantity) { this->stockQuantity = quantity; }
};

/*
 * GadgetStore Class: Manages the entire gadget store operations
 * Handles all CRUD operations and user interface
 */
class GadgetStore {
private:
    // Store gadgets organized by category
    std::map<std::string, std::vector<Gadget>> gadgetsByCategory;
    
    // Random number generator for serial numbers
    std::random_device rd;
    std::mt19937 gen;

    // Converts string to uppercase for case-insensitive comparisons
    std::string toUpper(const std::string& str) const {
        std::string upper = str;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return upper;
    }

    // Clears the console screen for better UI
    void clearScreen() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    // Displays centered header for each menu section
    void displayHeader(const std::string& title) const {
        clearScreen();
        std::cout << std::string(50, '=') << '\n';
        std::cout << std::setw((50 + title.length()) / 2) << std::right << title << '\n';
        std::cout << std::string(50, '=') << '\n';
    }

    // Gets user input with a prompt
    std::string getInput(const std::string& prompt) const {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        return input;
    }

    // Generates unique serial number for new gadgets
    std::string generateSerialNumber() {
        const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::uniform_int_distribution<> dis(0, chars.length() - 1);
        
        std::string serialNumber;
        do {
            serialNumber.clear();
            for (int i = 0; i < 6; ++i) {
                serialNumber += chars[dis(gen)];
            }
        } while (!isSerialNumberUnique(serialNumber));
        
        return serialNumber;
    }

    // Checks if a serial number is already in use
    bool isSerialNumberUnique(const std::string& serialNumber) const {
        for (const auto& category : gadgetsByCategory) {
            for (const auto& gadget : category.second) {
                if (gadget.getSerialNumber() == serialNumber) {
                    return false;
                }
            }
        }
        return true;
    }

    // Displays gadgets in a formatted table
    void displayGadgetTable(const std::vector<Gadget>& gadgets) const {
        std::cout << std::string(100, '-') << '\n';
        std::cout << std::left 
                  << std::setw(8) << "SERIAL#" << " | "
                  << std::setw(15) << "BRAND" << " | "
                  << std::setw(15) << "MODEL" << " | "
                  << std::setw(10) << "CATEGORY" << " | "
                  << std::setw(8) << "PRICE" << " | "
                  << std::setw(10) << "COLOR" << " | "
                  << std::setw(5) << "STOCK" << '\n';
        std::cout << std::string(100, '-') << '\n';

        for (const auto& gadget : gadgets) {
            std::cout << std::left
                      << std::setw(8) << toUpper(gadget.getSerialNumber()) << " | "
                      << std::setw(15) << toUpper(gadget.getBrand()) << " | "
                      << std::setw(15) << toUpper(gadget.getModel()) << " | "
                      << std::setw(10) << toUpper(gadget.getCategory()) << " | "
                      << std::setw(8) << std::fixed << std::setprecision(2) << gadget.getPrice() << " | "
                      << std::setw(10) << toUpper(gadget.getColor()) << " | "
                      << std::setw(5) << gadget.getStockQuantity() << '\n';
        }
        std::cout << std::string(100, '-') << '\n';
    }

public:
    // Initialize random number generator
    GadgetStore() : gen(rd()) {}

    // Add new gadget to the store with user input
    void addGadget() {
        displayHeader("ADD NEW GADGET");
        
        std::string model = getInput("Enter gadget model: ");
        std::string category = getInput("Enter gadget category (phone/laptop/etc.): ");
        std::string brand = getInput("Enter brand name: ");
        
        double price;
        while (true) {
            try {
                std::string priceStr = getInput("Enter price: ");
                price = std::stod(priceStr);
                if (price >= 0) break;
                std::cout << "Price must be non-negative!\n";
            } catch (...) {
                std::cout << "Invalid price! Please enter a valid number.\n";
            }
        }
        
        std::string color = getInput("Enter color: ");
        
        int quantity;
        while (true) {
            try {
                std::string quantityStr = getInput("Enter stock quantity: ");
                quantity = std::stoi(quantityStr);
                if (quantity >= 0) break;
                std::cout << "Quantity must be non-negative!\n";
            } catch (...) {
                std::cout << "Invalid quantity! Please enter a valid number.\n";
            }
        }

        std::string serialNumber = generateSerialNumber();
        Gadget gadget(model, category, serialNumber, brand, price, color, quantity);
        gadgetsByCategory[category].push_back(gadget);
        
        std::cout << "\nGadget added successfully!\n";
        std::cout << "Generated Serial Number: " << serialNumber << "\n";
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // Search for gadgets by category, brand, or model
    void searchGadget() const {
        displayHeader("SEARCH GADGET");
        
        std::string searchTerm = toUpper(getInput("Enter search term (brand/model/category): "));
        std::vector<Gadget> results;
        
        // Search in categories first
        for (const auto& category : gadgetsByCategory) {
            if (toUpper(category.first).find(searchTerm) != std::string::npos) {
                std::cout << "\nFound gadgets in category '" << toUpper(category.first) << "':\n\n";
                displayGadgetTable(category.second);
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                return;
            }
        }

        // Then search in brands
        bool foundBrand = false;
        for (const auto& category : gadgetsByCategory) {
            for (const auto& gadget : category.second) {
                if (toUpper(gadget.getBrand()).find(searchTerm) != std::string::npos) {
                    if (!foundBrand) {
                        std::cout << "\nFound gadgets of brand '" << toUpper(searchTerm) << "':\n\n";
                        foundBrand = true;
                    }
                    results.push_back(gadget);
                }
            }
        }

        if (foundBrand) {
            displayGadgetTable(results);
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            return;
        }

        // Finally search in models
        results.clear();
        for (const auto& category : gadgetsByCategory) {
            for (const auto& gadget : category.second) {
                if (toUpper(gadget.getModel()).find(searchTerm) != std::string::npos) {
                    results.push_back(gadget);
                }
            }
        }
        
        if (results.empty()) {
            std::cout << "\nNo gadgets found matching your search.\n";
        } else {
            std::cout << "\nFound " << results.size() << " matching gadget(s) by model:\n\n";
            displayGadgetTable(results);
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // Delete a gadget using its serial number
    bool deleteGadget() {
        displayHeader("DELETE GADGET");
        
        if (gadgetsByCategory.empty()) {
            std::cout << "\nNo gadgets in store!\n";
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            return false;
        }

        std::cout << "\nCurrent Gadgets in Store:\n\n";
        for (const auto& category : gadgetsByCategory) {
            displayGadgetTable(category.second);
            std::cout << '\n';
        }
        
        std::string serialNumber = toUpper(getInput("\nEnter gadget serial number to delete: "));
        
        for (auto& category : gadgetsByCategory) {
            auto& gadgets = category.second;
            for (auto it = gadgets.begin(); it != gadgets.end(); ++it) {
                if (toUpper(it->getSerialNumber()) == serialNumber) {
                    gadgets.erase(it);
                    std::cout << "\nGadget deleted successfully!\n";
                    std::cout << "\nPress Enter to continue...";
                    std::cin.get();
                    return true;
                }
            }
        }
        
        std::cout << "\nGadget not found!\n";
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return false;
    }

    // Modify existing gadget properties
    bool modifyGadget() {
        displayHeader("MODIFY GADGET");
        
        if (gadgetsByCategory.empty()) {
            std::cout << "\nNo gadgets in store!\n";
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            return false;
        }

        std::cout << "\nCurrent Gadgets in Store:\n\n";
        for (const auto& category : gadgetsByCategory) {
            displayGadgetTable(category.second);
            std::cout << '\n';
        }
        
        std::string serialNumber = toUpper(getInput("\nEnter gadget serial number to modify: "));
        
        for (auto& category : gadgetsByCategory) {
            auto& gadgets = category.second;
            for (auto& gadget : gadgets) {
                if (toUpper(gadget.getSerialNumber()) == serialNumber) {
                    std::cout << "\nSelected gadget details:\n";
                    std::vector<Gadget> currentGadget = {gadget};
                    displayGadgetTable(currentGadget);
                    
                    std::cout << "\nEnter new details (press Enter to keep current value):\n";
                    
                    std::string input;
                    
                    input = getInput("Model [" + gadget.getModel() + "]: ");
                    if (!input.empty()) gadget.setModel(input);
                    
                    input = getInput("Brand [" + gadget.getBrand() + "]: ");
                    if (!input.empty()) gadget.setBrand(input);
                    
                    input = getInput("Color [" + gadget.getColor() + "]: ");
                    if (!input.empty()) gadget.setColor(input);
                    
                    input = getInput("Price [" + std::to_string(gadget.getPrice()) + "]: ");
                    if (!input.empty()) {
                        try {
                            double price = std::stod(input);
                            if (price >= 0) gadget.setPrice(price);
                            else std::cout << "Invalid price! Keeping current value.\n";
                        } catch (...) {
                            std::cout << "Invalid price! Keeping current value.\n";
                        }
                    }
                    
                    input = getInput("Stock Quantity [" + std::to_string(gadget.getStockQuantity()) + "]: ");
                    if (!input.empty()) {
                        try {
                            int quantity = std::stoi(input);
                            if (quantity >= 0) gadget.setStockQuantity(quantity);
                            else std::cout << "Invalid quantity! Keeping current value.\n";
                        } catch (...) {
                            std::cout << "Invalid quantity! Keeping current value.\n";
                        }
                    }
                    
                    std::cout << "\nGadget modified successfully!\n";
                    std::cout << "\nPress Enter to continue...";
                    std::cin.get();
                    return true;
                }
            }
        }
        
        std::cout << "\nGadget not found!\n";
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return false;
    }

    // Display all gadgets in the store
    void listGadgets() const {
        displayHeader("LIST ALL GADGETS");
        
        if (gadgetsByCategory.empty()) {
            std::cout << "\nNo gadgets in store!\n";
        } else {
            for (const auto& category : gadgetsByCategory) {
                std::cout << "\nCategory: " << toUpper(category.first) << "\n\n";
                displayGadgetTable(category.second);
                std::cout << '\n';
            }
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // Display main menu options
    void displayMenu() const {
        displayHeader("GADGET STORE MANAGEMENT SYSTEM");
        std::cout << "\n1. Add Gadget";
        std::cout << "\n2. Search Gadget";
        std::cout << "\n3. Delete Gadget";
        std::cout << "\n4. Modify Gadget";
        std::cout << "\n5. List All Gadgets";
        std::cout << "\n6. Exit";
        std::cout << "\n\nEnter your choice (1-6): ";
    }

    // Main program loop
    void run() {
        while (true) {
            displayMenu();
            std::string choice = getInput("");
            
            switch (choice[0]) {
                case '1':
                    addGadget();
                    break;
                case '2':
                    searchGadget();
                    break;
                case '3':
                    deleteGadget();
                    break;
                case '4':
                    modifyGadget();
                    break;
                case '5':
                    listGadgets();
                    break;
                case '6':
                    std::cout << "\nThank you for using Gadget Store Management System!\n";
                    return;
                default:
                    std::cout << "\nInvalid choice! Press Enter to continue...";
                    std::cin.get();
            }
        }
    }
};

// Program entry point
int main() {
    GadgetStore store;
    store.run();
    return 0;
}
