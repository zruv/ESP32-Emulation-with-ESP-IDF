<div align="center">
  <img src="assets/circuit-setup-1.png" alt="Circuit Setup 1" width="400"/>
  <p><em>Initial circuit setup for the project.</em></p>
  <img src="assets/circuit-setup-2.png" alt="Circuit Setup 2" width="400"/>
  <p><em>Alternative circuit setup.</em></p>
  <img src="assets/terminal-output.png" alt="Terminal Output" width="600"/>
  <p><em>Example terminal output from the emulated ESP32.</em></p>

  <h1 align="center">ESP32 Emulation with QEMU & ESP-IDF</h1>
  <p align="center">
    A project demonstrating a complete ESP32 emulation environment from scratch using QEMU and the ESP-IDF.
    <br />
    <a href="https://github.com/zruv/Arduino-Winter-Internship-2025-Submission-Task-2/blob/master/README.md"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/zruv/Arduino-Winter-Internship-2025-Submission-Task-2/issues">Report Bug</a>
    ·
    <a href="https://github.com/zruv/Arduino-Winter-Internship-2025-Submission-Task-2/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

This project demonstrates how to set up a complete ESP32 emulation environment from scratch using QEMU and the ESP-IDF. It includes two example applications: a simulated temperature sensor and an application that blinks an LED and reads from a (not emulated) DHT sensor.

The primary goal of this project is to create a virtual testing environment for ESP32 applications, which can be used for automated testing and development without the need for physical hardware.

For a detailed, step-by-step guide to this project, including explanations of each step, the libraries installed, and the importance of the project, please see the `instructions.md` file.

<p align="right">(<a href="#top">back to top</a>)</p>

### Built With

*   [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
*   [QEMU](https://www.qemu.org/)
*   [C](https://en.wikipedia.org/wiki/C_(programming_language))
*   [CMake](https://cmake.org/)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple example steps.

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
    Alternatively, you can build QEMU from source by following the instructions in `instructions.md`.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
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
    . /path/to/your/esp-idf/export.sh && idf.py qemu monitor
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
    . /path/to/your/esp-idf/export.sh && idf.py qemu monitor
    ```
    *Note: The DHT sensor will fail to read, as it is not an emulated peripheral. This is expected behavior.*

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

- [x] Set up ESP-IDF and QEMU environment
- [x] Run Temperature Sensor Simulation in QEMU
- [x] Run Blink and DHT Sensor Application in QEMU
- [ ] Add more complex examples
- [ ] Implement automated testing using the QEMU environment

See the [open issues](https://github.com/zruv/Arduino-Winter-Internship-2025-Submission-Task-2/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1.  Fork the Project
2.  Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3.  Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4.  Push to the Branch (`git push origin feature/AmazingFeature`)
5.  Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Your Name - [@your_twitter](https://twitter.com/your_twitter) - email@example.com

Project Link: [https://github.com/zruv/Arduino-Winter-Internship-2025-Submission-Task-2](https://github.com/zruv/Arduino-Winter-Internship-2025-Submission-Task-2)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

*   [Espressif](https://www.espressif.com/)
*   [QEMU](https://www.qemu.org/)
*   [OSHW Community](https://www.oshwa.org/)

<p align="right">(<a href="#top">back to top</a>)</p>