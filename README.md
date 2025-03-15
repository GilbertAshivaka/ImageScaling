# ImageScaling

A multithreaded image downloader to demonstrate how to use QFuture and QtConcurrent for parallel image processing.

## Overview

ImageScaling is a Qt/C++ application that showcases parallel processing techniques for image downloading and scaling operations. By leveraging Qt's concurrency frameworks (QFuture and QtConcurrent), the application demonstrates how to efficiently handle multiple image processing tasks simultaneously.

## Features

- Multithreaded image downloading
- Parallel image scaling and processing
- Non-blocking UI during intensive operations
- Progress monitoring for concurrent tasks
- Example implementation of QFuture and QtConcurrent

## Technology Stack

- Qt Framework
- C++
- QML for UI
- QtConcurrent for parallelism

## Project Structure

- `assets/` - Application resources and image assets
- `Main.qml` - Main QML interface
- `imagescaling.cpp/h` - Core implementation of the parallel image processor
- `main.cpp` - Application entry point

## Prerequisites

- Qt 6.0 or higher (recommended)
- CMake 3.15 or higher
- C++ compiler with C++17 support

## Building the Application

1. Clone the repository:
   ```
   git clone https://github.com/GilbertAshivaka/ImageScaling.git
   ```

2. Navigate to the project directory:
   ```
   cd ImageScaling
   ```

3. Create a build directory:
   ```
   mkdir build && cd build
   ```

4. Configure with CMake:
   ```
   cmake ..
   ```

5. Build the project:
   ```
   cmake --build .
   ```

## Usage

1. Launch the application
2. Add image URLs for downloading
3. Set scaling parameters (optional)
4. Start the download and processing operation
5. Monitor progress through the UI
6. View and save the processed images

## Implementation Details

The application demonstrates several key concepts:

- Using QFuture to represent asynchronous computations
- Implementing QtConcurrent::run for CPU-bound tasks
- Managing thread pools for optimal performance
- Connecting signal/slot mechanisms for progress updates
- Handling cancellation of ongoing operations

## Learning Outcomes

This project serves as an educational resource for developers looking to implement:

- Parallel processing in Qt applications
- Efficient image handling techniques
- Non-blocking UI design
- Progress reporting for long-running operations

## Contributing

Contributions to ImageScaling are welcome! Please feel free to submit a Pull Request or open an Issue to discuss potential improvements.


## Contact

Gilbert Ashivaka - [GitHub Profile](https://github.com/GilbertAshivaka)

Project Link: [https://github.com/GilbertAshivaka/ImageScaling](https://github.com/GilbertAshivaka/ImageScaling)
