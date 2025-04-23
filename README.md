To run and use the Storage Management System:

1) Compile and launch
    - Compile with a C++ compiler and then start it by running the warehouse executable.

2) Main menu
    - As soon as the program begins, you’ll see five numbered options:

    1) Add item

    2) Find item by ID

    3) Remove item by ID

    4) List items by description

    5) Quit

3) Adding an item

    - Choose option 1.

    - You’ll be prompted to enter the item’s unique ID (e.g. ITEM007), its description (e.g. USB Cable), and its storage location (e.g. Aisle 4, Shelf 2).

    - If that ID already exists in the system, you will see a “DuplicateItemException” error. Otherwise, the program confirms “Item added.”

4) Finding an item by ID

    - Choose option 2.

    - Enter the ID you want to look up.

    - If the item exists, its ID, description, and location will be printed. If not, you will see an “ItemNotFoundException” message.

5) Removing an item by ID

    - Choose option 3.

    - Enter the ID of the item to delete.

    - On success, the program prints “Item removed.” If the ID isn’t found, you get an   “ItemNotFoundException” error.

6) Listing all items

    - Choose option 4.

    - The system will print every stored item in alphabetical order of their descriptions (so “Battery Pack” appears before “LED Light,” etc.).

    - If there are no items in storage yet, you’ll see “No items in storage.”

7) Exiting

    - Choose option 5 to quit the menu loop and terminate the program cleanly.

8) Error handling and validation
    - Non-numeric or out-of-range menu choices prompt you to enter a valid number (1–5).
    - Duplicate IDs and “not found” lookups/removals throw custom exceptions that are caught and displayed, so the program never crashes—you’re simply returned to the main menu with an explanatory message.