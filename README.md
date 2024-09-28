# Boids Simulation

This project is a Boids simulation implemented in C++ using the SFML library. Boids is an artificial life program that simulates the flocking behavior of birds. This was my first project using C++ and SFML, and it was a great learning experience. I used [vanhunteradams(https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html) as a reference for the implementation. I also used the [SFML documentation](https://www.sfml-dev.org/tutorials/2.5/) to learn how to use the library.

## Features

- Simulates flocking behavior using three simple rules: separation, alignment, and cohesion.
- Visual representation of boids using SFML.
- Adjustable parameters for flocking behavior.

## Requirements

- C++17 or later
- SFML 2.5 or later

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/boids.git
    ```
2. Navigate to the project directory:
    ```sh
    cd boids
    ```
3. Install SFML:
    Follow the instructions on the [SFML website](https://www.sfml-dev.org/download.php) to install SFML for your operating system.

4. Build the project:
    Use the build_sfml.sh script to build the project with SFML. (this will also run the project)
    ```sh
    build_sfml main.cpp
    ```
    This will create an executable called sfml-app.

## Usage

Once you have built the project, you can run the executable to see the boids simulation. The boids will flock together and avoid colliding with each other.
```sh
./sfml-app
```

## Configuration

You can adjust the parameters for the boids' behavior in the top of the Boid class.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

- Craig Reynolds for the original Boids algorithm.
- The SFML community for their excellent library.
