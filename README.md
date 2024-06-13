# Flight Management System

## Overview
This project is a comprehensive system designed to manage flights, including departure and arrival airports and reservations. It enables users to add and list airports and flights, manage flight reservations, and keep track of the current system date. The program is written in C and utilizes various data structures, including arrays and hash tables, to efficiently handle and retrieve information.

## Features
- **Airport Management**: Add new airports and list existing ones.
- **Flight Management**: Add new flights, list all flights, and filter flights by departure or arrival airport.
- **Reservation Management**: Add reservations to flights, list reservations, and delete reservations or flights.
- **Date Management**: Update and display the current system date.

## Usage
The system operates through a command-line interface where users can input specific commands to perform various actions. Below are the available commands and their functions:

### Commands
- **Add Airport (`a`)**: Adds a new airport to the system.
    - **Usage**: `a <id> <country> <city>`
- **List Airports (`l`)**: Lists all airports or specified airports.
    - **Usage**: `l [<id1> <id2> ...]`
- **Add Flight (`v`)**: Adds a new flight to the system or lists all flights.
    - **Usage**: `v` or `v <flycode> <dep_airport> <arriv_airport> <date> <time> <duration> <capacity>`
- **List Flights by Departure (`p`)**: Lists flights departing from a specified airport.
    - **Usage**: `p <dep_airport_id>`
- **List Flights by Arrival (`c`)**: Lists flights arriving at a specified airport.
    - **Usage**: `c <arriv_airport_id>`
- **Update System Date (`t`)**: Updates the current date of the system.
    - **Usage**: `t <day>-<month>-<year>`
- **Manage Reservations (`r`)**: Adds a reservation or lists reservations for a flight.
    - **Usage**: `r <flycode> <date> <reservation_code> <num_passengers>`
- **Delete Flight or Reservation (`e`)**: Deletes a specified flight or reservation.
    - **Usage**: `e <flycode_or_reservation_code>`
- **Quit (`q`)**: Exits the program and performs necessary cleanup.

### Example Commands
1. **Add an Airport**:
    ```
    a JFK USA NewYork
    ```
    Output: `airport JFK`

2. **List All Airports**:
    ```
    l
    ```
    Output: List of all airports in the system.

3. **List Flights by Departure**:
    ```
    p JFK
    ```
    Output: List of flights departing from JFK.

4. **Add a Flight**:
    ```
    v AA123 JFK LAX 2024-06-13 14:30 06:00 150
    ```

5. **Add a Reservation**:
    ```
    r AA123 2024-06-13 RES456 3
    ```
    
6. **Delete a Flight**:
    ```
    e AA123
    ```

By following the usage instructions and commands listed above, users can effectively manage airports, flights, and reservations within the system.

### Build and Clean Commands

- To build the project, simply run:
    ```sh
    make
    ```
    This will compile the source files and generate the `run` executable.

- To clean the build files, run:
    ```sh
    make clean
    ```
    This will remove the compiled object files and the executable.

- To clean result files generated during testing, run:
    ```sh
    make clean-results
    ```
    This will delete all result files in the `tests` directory.

By following these instructions, users can compile, manage, and clean the project effectively.<hr>

For details on running tests, please refer to the `tests` directory.
