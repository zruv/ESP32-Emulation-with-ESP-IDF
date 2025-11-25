
# ESP32 Emulation with QEMU & ESP-IDF

This document outlines the process of setting up an ESP32 emulation environment using QEMU and demonstrating two applications, as per the OSHW Screening Task.

![circuit-setup-1.png](assets/circuit-setup-1.png)
![circuit-setup-2.png](assets/circuit-setup-2.png)
![terminal-output.png](assets/terminal-output.png)

## 1. Overview

*   **Operating System**: Linux

## 2. Setup Steps

This section details the commands used to set up the environment, build, and run the applications.

### 2.1. Environment Setup

It is assumed that you have already cloned the project repository.

1.  **Install ESP-IDF**: Follow the official ESP-IDF Get Started Guide to install the toolchain and dependencies.
    *   [https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)

2.  **Set up ESP-IDF environment**: Before running any `idf.py` commands, you must source the `export.sh` script to set up the necessary environment variables.
    ```bash
    . /path/to/your/esp-idf/export.sh
    ```

### 2.2. Build and Run the Temperature Sensor Simulation

1.  **Navigate to the project directory**:
    ```bash
    cd /path/to/your/project
    ```

2.  **Set the target**:
    ```bash
    idf.py set-target esp32
    ```

3.  **Build the application**:
    ```bash
    idf.py build
    ```

4.  **Run the application in QEMU**:
    ```bash
    qemu-system-xtensa -nographic -machine esp32 -drive file=build/blink.elf,if=mtd,format=raw
    ```

### 2.3. Build and Run the Blink and DHT Sensor Application

1.  **Modify `main/CMakeLists.txt`**: To run the blink and DHT sensor application, you need to modify `main/CMakeLists.txt` to include `app_main.c` and exclude `temperature_sensor.c`.
    ```cmake
    idf_component_register(SRCS "app_main.c" "dht_driver.c"
                           INCLUDE_DIRS "."
                           REQUIRES esp_driver_gpio freertos)
    ```

2.  **Build the application**:
    ```bash
    idf.py build
    ```

3.  **Run the application in QEMU**:
    ```bash
    qemu-system-xtensa -nographic -machine esp32 -drive file=build/blink.elf,if=mtd,format=raw
    ```

## 3. QEMU Setup Guide

This section provides a detailed guide on setting up and using QEMU for ESP32 emulation.

### 3.1. Introduction to QEMU

QEMU (Quick Emulator) is a generic and open-source machine emulator and virtualizer. It can run operating systems and programs made for one machine (e.g., an ARM board) on a different machine (e.g., your own x86 PC). In this project, we use QEMU to emulate an ESP32 microcontroller, which allows us to develop and test ESP32 applications without needing physical hardware.

### 3.2. Building QEMU for ESP32

The official QEMU does not support ESP32 emulation out of the box. We need to use a fork from Espressif that adds support for the Xtensa architecture used in the ESP32.

1.  **Clone the Espressif QEMU repository**:
    ```bash
    git clone https://github.com/espressif/qemu.git
    cd qemu
    ```

2.  **Configure the build for the Xtensa architecture**:
    ```bash
    ./configure --target-list=xtensa-softmmu
    ```

3.  **Compile and install QEMU**:
    ```bash
    make -j$(nproc)
    sudo make install
    ```

### 3.3. Running an ESP32 Application in QEMU

Once you have built your ESP32 application using `idf.py build`, you will get a `.elf` file in the `build` directory. You can run this file in QEMU using the following command:

```bash
qemu-system-xtensa -nographic -machine esp32 -drive file=build/blink.elf,if=mtd,format=raw
```

*   `qemu-system-xtensa`: This is the QEMU emulator for the Xtensa architecture.
*   `-nographic`: This option disables the graphical output and redirects the serial output to the console.
*   `-machine esp32`: This option specifies that we want to emulate an ESP32 machine.
*   `-drive file=build/blink.elf,if=mtd,format=raw`: This option loads the application binary (`blink.elf`) into the emulated flash memory.

## 4. Challenges & Fixes

*   **`idf.py` command not found**:
    *   **Challenge**: The `idf.py` command was not found in the shell's path.
    *   **Fix**: This was resolved by sourcing the `export.sh` script from the ESP-IDF installation directory, which correctly sets up the environment variables.

*   **Duplicate `app_main` function**:
    *   **Challenge**: The build failed due to a duplicate `app_main` function definition. Both `temperature_sensor.c` and `app_main.c` (originally `blink_example_main.c`) had this function.
    *   **Fix**: The `main/CMakeLists.txt` file was modified to only include one of the main files at a time, allowing the user to switch between the two applications.

## 5. Reflection

This setup provides a powerful environment for developing and testing ESP32 applications without the need for physical hardware. By using QEMU, we can automate the testing of student code submissions on a platform like Yaksh.

The process would involve:
1.  Receiving the student's code submission.
2.  Compiling the code using `idf.py`.
3.  Running the compiled `.elf` file in QEMU.
4.  Capturing the console output from QEMU.
5.  Comparing the output against a set of expected results to determine the correctness of the submission.

This automated evaluation platform would significantly streamline the process of grading and providing feedback for embedded systems courses.