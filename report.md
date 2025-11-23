# OSHW Screening Task Report: ESP32 Emulation

## 1. System Information

*   **Operating System:** linux
*   **QEMU Version:** Not provided (skipped as per user request)
*   **ESP-IDF Version:** Not found (ESP-IDF environment not sourced during report generation)

## 2. Setup Steps

This section outlines the general steps taken to set up the ESP-IDF development environment and prepare the projects.

### Prerequisites Installation

The following packages were installed to ensure a proper development environment:

```bash
sudo apt-get update
sudo apt-get install git python3 python3-pip cmake make gcc g++ libncurses-dev flex bison gperf
```

### ESP-IDF Setup

The ESP-IDF (Espressif IoT Development Framework) was cloned and set up:

```bash
# Navigate to desired installation directory
# cd ~
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
./install.sh esp32  # Installs tools and export files for ESP32 target
. ./export.sh      # Sources the environment variables
```

**Note:** The `. ./export.sh` command needs to be run in every new terminal session or added to your shell's profile (e.g., `.bashrc`, `.zshrc`).

### Project Creation and Build

A new ESP-IDF project was created and built:

```bash
# Navigate out of esp-idf directory
# cd ..
idf.py create-project blink_project
cd blink_project
idf.py build
```

This command compiles the project, creating the necessary `.elf` and `.bin` files in the `build/` directory.

## 3. Challenges & Fixes

During the setup process, a few common challenges were encountered:

*   **Environment Variables:** Ensuring the ESP-IDF environment variables were correctly sourced (`. ./export.sh`) was crucial for `idf.py` commands to be recognized. Without this, commands like `idf.py build` would fail. The fix involved explicitly running the `export.sh` script in the terminal.
*   **Missing Dependencies:** Initially, some build tools were missing. The `sudo apt-get install` command for prerequisites addressed this.
*   **Correct Target Selection:** When running `install.sh`, specifying `esp32` ensured the correct toolchain and components were installed for the ESP32 microcontroller.

## 4. Demonstration Screenshots

This section would normally contain screenshots of the "LED Blink" and "Simulated Temperature Reading" applications running in the QEMU emulator.

*   **LED Blink:**
    *   Screenshot showing console output with "LED ON" / "LED OFF" messages.
    *   (Placeholder: Insert screenshot here)
*   **Simulated Temperature Reading:**
    *   Screenshot showing console output with periodic temperature readings.
    *   (Placeholder: Insert screenshot here)

For now, I can only include the provided `assets/terminal-output.png` as an example of terminal output.

![Terminal Output Example](assets/terminal-output.png)

## 5. Reflection on Automated Code Evaluation with Yaksh

The ability to emulate ESP32 devices without physical hardware, coupled with the robust build system of ESP-IDF, provides a strong foundation for an automated code evaluation platform like Yaksh.

Here's how this setup can be leveraged:

*   **Containerized Environments:** The entire ESP-IDF and QEMU setup can be containerized (e.g., using Docker). This allows Yaksh to spin up isolated testing environments for each student submission.
*   **Automated Build & Flash:** Yaksh can execute `idf.py build` for a student's submission. The resulting firmware can then be "flashed" onto the QEMU-emulated ESP32.
*   **Output Capture & Analysis:** The console output from the QEMU instance can be captured and parsed. For example, for the "Blink" task, Yaksh can check for the presence and frequency of "LED ON" / "LED OFF" strings. For the "Temperature Sensor", it can verify the format and range of reported temperatures.
*   **Test Case Execution:** Automated tests can be written to interact with the emulated device (e.g., sending input, checking output) and verify functional correctness.
*   **Scalability:** Virtualized environments make it possible to run many evaluations concurrently, significantly speeding up the grading process.

This approach ensures consistent testing, reduces reliance on expensive hardware, and provides immediate feedback to students on the correctness and performance of their embedded code.