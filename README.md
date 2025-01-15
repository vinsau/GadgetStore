# Gadget Store Management System

## Overview
A C++ console application for managing a gadget store inventory. This system allows store owners to track and manage various electronic gadgets, their specifications, and inventory levels.

## Features
- Add new gadgets with detailed specifications
- View all gadgets in the inventory
- Search gadgets by various criteria
- Update gadget information
- Remove gadgets from inventory
- Automatic serial number generation
- Input validation for all fields
- Color selection from predefined list
- Price and quantity management

## Technical Details
- Language: C++
- Dependencies: Standard C++ libraries only
- Input Validation: Comprehensive validation for all user inputs
- Data Structure: Uses STL containers (map, vector) for efficient data management

## Building and Running

### Using VS Code
1. Download both files (`GadgetStoreSingle.cpp` and `README.md`)
2. Open the terminal (Ctrl + ~)
3. Navigate to the program's directory:
   ```bash
   cd /path/to/directory
   ```
4. Compile the program:
   ```bash
   g++ -o GadgetStoreSingle GadgetStoreSingle.cpp
   ```
5. Run the program:
   ```bash
   ./GadgetStoreSingle
   ```

### Using Embarcadero Dev C++
1. Download the `GadgetStoreSingle.cpp` file
2. Open it in the IDE
3. Compile and run the program directly from the interface

## Project Structure
- `GadgetStoreSingle.cpp`: Main source file containing all classes and functionality
  - `Gadget`: Class for individual gadget items
  - `InputValidator`: Class for input validation
  - `ErrorMessages`: Class for centralized error message management
  - `GadgetStore`: Main class managing store operations

## Input Validation
- Model names: Must be alphanumeric and not purely numeric
- Categories: Letters and spaces only
- Brand names: Alphanumeric with special characters allowed
- Colors: Selection from predefined list
- Prices: Range validation with decimal support
- Quantities: Integer range validation

## Authors
BSCPE 2-G
- Augusto
- Tagaan
- Ribo


## Support
If you encounter any issues while running the program, you can:
1. Check the error messages for specific validation requirements
2. Ensure all input meets the specified criteria
3. Verify your C++ compiler is properly configured
