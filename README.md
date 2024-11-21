# fingerprintAuth

This repository contains a demo application showcasing the use of the **HiScan** fingerprint scanner SDK by Biometrika. The application demonstrates key functionalities such as fingerprint registration and identification using the HiScan device, all implemented within a user-friendly graphical interface.

## Features

- **Fingerprint Registration**: Register up to 3 fingerprints for each of the 10 fingers of a user.  
- **Identification Test (1:N)**: Identify a user by matching an input fingerprint against all registered fingerprints in the database.  
- **Graphical User Interface**: A clear and intuitive interface built with Windows Forms to simplify user interaction with the system.

## Prerequisites

- A working **HiScan** fingerprint scanner by Biometrika.
- The **HiScan SDK** (not included in this repository; see disclaimer below).
- Visual Studio with support for Windows Forms development.

## Installation

1. Clone this repository:

 ```bash
   git clone https://github.com/your-username/hiscan-demo-app.git
```

2. Open the project in **Visual Studio**.

3. Add the HiScan SDK dependencies:
   - Download the SDK by contacting Biometrika (see disclaimer below).

4. Build and run the application

## How to Use

1. Connect the HiScan fingerprint scanner to your system.
2. Launch the application.
3. Use the following functionalities:
   - **Register Fingerprints**: Add up to 3 fingerprints for each finger of a user.
   - **Identify User**: Perform a 1:N identification by matching an input fingerprint against the registered database.

## Disclaimer

The HiScan SDK is **not publicly available**. To obtain access, you must contact **Biometrika** or the repository owner. Redistribution of the SDK is strictly prohibited, and this repository does not include the SDK files.

## License

This software includes references to the HiScan SDK, which is proprietary software owned by Biometrika. Access to the SDK must be requested directly from Biometrika, and this repository does not include the SDK. The use of this application is restricted to those who have obtained proper licensing for the SDK.


## Contact

For questions or inquiries, please contact:

- **Biometrika**: https://www.biometrika.it/
- **Repository Owner**
