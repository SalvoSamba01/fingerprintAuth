# fingerprintAuth

This repository contains a demo application showcasing the use of the **HiScan** fingerprint scanner SDK v.2.7 by UMPI. The application demonstrates key functionalities such as fingerprint registration and identification using the HiScan device, all implemented within a user-friendly graphical interface.

## Features

- **Fingerprint Registration**: Register up to 3 fingerprints for each of the 10 fingers of a user.  
- **Identification Test (1:N)**: Identify a user by matching an input fingerprint against all registered fingerprints in the database.  
- **Graphical User Interface**: A clear and intuitive interface built with Windows Forms to simplify user interaction with the system.

## Prerequisites

- A working **HiScan** fingerprint scanner by UMPI.
- The **HiScan SDK v.2.7** (not included in this repository; see disclaimer below).
- Visual Studio with support for Windows Forms development.

## Installation

1. Clone this repository:

 ```bash
   git clone https://github.com/your-username/hiscan-demo-app.git
```

2. Open the project in **Visual Studio**.

3. Add the HiScan SDK dependencies:
   - Download the SDK by contacting UMPI (see disclaimer below).

4. Build and run the application

## How to Use

1. Connect the HiScan fingerprint scanner to your system.
2. Launch the application.
3. Use the following functionalities:
   - **Register Fingerprints**: Add up to 3 fingerprints for each finger of a user.
   - **Identify User**: Perform a 1:N identification by matching an input fingerprint against the registered database.

## Disclaimer

The HiScan SDK is **not publicly available**. To obtain access, you must contact **UMPI** or the repository owner. Redistribution of the SDK is strictly prohibited, and this repository does not include the SDK files.

**The FxISO SDK libraries are owned by UMPI, which allows Users to use, copy, share and create anything derived from them;
The libraries work exclusively with UMPI scanners and the fingerprint images captured by them.
It is forbidden to: reverse engineer, decompile, translate, disassemble or otherwise attempt to extract part or all of the source code of the libraries.**

## License

This software includes references to the HiScan SDK, which is proprietary software owned by UMPI. Access to the SDK must be requested directly from UMPI. The use of this application is restricted to those who have obtained proper licensing for the SDK.


## Contact

For questions or inquiries, please contact:

- **UMPI**: [website](https://www.umpi.it/biometrika/)
- **Repository Owner**
