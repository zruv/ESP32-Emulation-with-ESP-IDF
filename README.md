<div align="center">
  <img src="assets/circuit-setup-1.png" alt="Circuit Setup 1" width="400"/>
  <p><em>Circuit setup - 1 for the project.</em></p>
  <img src="assets/circuit-setup-2.png" alt="Circuit Setup 2" width="400"/>
  <p><em>Circuit setup - 2 for the project.</em></p>
  <img src="assets/terminal-output.png" alt="Terminal Output" width="600"/>
  <p><em>Example terminal output from the emulated ESP32 from ESP-IDF.</em></p>

  <h1 align="center">ESP32 Emulation with QEMU & ESP-IDF</h1>
  <p align="center">
    A project demonstrating a complete ESP32 emulation environment from scratch using QEMU and the ESP-IDF.
</div>

## About The Project

This project demonstrates how to set up a complete ESP32 emulation environment from scratch using QEMU and the ESP-IDF. It includes two example applications: a simulated temperature sensor and an application using virtual environment of QEMU.
The primary goal of this project is to create a virtual testing environment for ESP32 applications, which can be used for automated testing and development without the need for physical hardware.

### Built With

*   [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
*   [QEMU](https://www.qemu.org/)
*   [CMake](https://cmake.org/)
*   [Espressif-Qemu](https://github.com/espressif/qemu)

### Prerequisites

*   **ESP-IDF**: The ESP-IDF (Espressif IoT Development Framework) is required to build the applications. Please follow the official [ESP-IDF Get Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) to install the toolchain and dependencies.

### Installation

1.  **Clone the repo**
    ```sh
    git clone https://github.com/zruv/Arduino-Winter-Internship-2025-Submission-Task-2.git
    ```
2.  **Install QEMU**
    This project requires a custom version of QEMU that supports ESP32 emulation. The recommended way to install this is using the ESP-IDF's built-in tools:
    ```sh
    python $IDF_PATH/tools/idf_tools.py install qemu-xtensa
    ```

## Usage

To run the applications, you first need to modify `main/CMakeLists.txt` to select the desired application, and then use the `idf.py qemu monitor` command.

Before running any `idf.py` commands, you must source the `export.sh` script from your ESP-IDF installation directory:
```bash
. /path/to/your/esp-idf/export.sh
```

### Running the "Temperature Sensor Simulation"

1.  **Configure `main/CMakeLists.txt`** to include only `temperature_sensor.c`:
    ```cmake
    idf_component_register(SRCS "temperature_sensor.c"
                           INCLUDE_DIRS "."
                           REQUIRES esp_driver_gpio freertos)
    ```

2.  **Build and run in QEMU:**
    ```bash
    . ~/esp/esp-idf/export.sh && idf.py qemu monitor
    ```

### Running the "Blink and DHT Sensor Application"

1.  **Configure `main/CMakeLists.txt`** to include `app_main.c` and `dht_driver.c`:
    ```cmake
    idf_component_register(SRCS "app_main.c" "dht_driver.c"
                           INCLUDE_DIRS "."
                           REQUIRES esp_driver_gpio freertos)
    ```

2.  **Build and run in QEMU:**
    ```bash
    . ~/esp/esp-idf/export.sh && idf.py qemu monitor
    ```
    *Note: The DHT sensor will fail to read, as it is not an emulated peripheral. This is expected behavior.*
